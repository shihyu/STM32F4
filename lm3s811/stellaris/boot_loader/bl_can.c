//*****************************************************************************
//
// bl_can.c - Functions to transfer data via the CAN port.
//
// Copyright (c) 2008-2009 Luminary Micro, Inc.  All rights reserved.
// Software License Agreement
// 
// Luminary Micro, Inc. (LMI) is supplying this software for use solely and
// exclusively on LMI's microcontroller products.
// 
// The software is owned by LMI and/or its suppliers, and is protected under
// applicable copyright laws.  All rights are reserved.  You may not combine
// this software with "viral" open-source software in order to form a larger
// program.  Any use in violation of the foregoing restrictions may subject
// the user to criminal sanctions under applicable laws, as well as to civil
// liability for the breach of the terms and conditions of this license.
// 
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// LMI SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
// CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 5125 of the Stellaris Firmware Development Package.
//
//*****************************************************************************

#include "inc/hw_can.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_flash.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "bl_config.h"
#include "boot_loader/bl_can.h"
#include "boot_loader/bl_can_timing.h"
#include "boot_loader/bl_flash.h"
#include "boot_loader/bl_hooks.h"

//*****************************************************************************
//
//! \addtogroup bl_can_api
//! @{
//
//*****************************************************************************
#if defined(CAN_ENABLE_UPDATE) || defined(DOXYGEN)

//*****************************************************************************
//
//
//*****************************************************************************
#define CAN_CMD_SUCCESS         0x00
#define CAN_CMD_FAIL            0x01

//*****************************************************************************
//
// Macros used to generate correct pin definitions.
//
//*****************************************************************************
#define CAN_RX_PIN_M            (1 << CAN_RX_PIN)
#define CAN_TX_PIN_M            (1 << CAN_TX_PIN)

//*****************************************************************************
//
// These functions are used on parts that require the work around for the CAN
// controller errata, while parts that do not will use the direct access to
// the registers.
//
//*****************************************************************************
#ifdef CAN_ERRATA_FIX
#define CAN_RW_DELAY            (5)

static unsigned long CANRegRead(unsigned long ulRegAddress);
static void CANRegWrite(unsigned long ulRegAddress, unsigned long ulRegValue);

#define CANRegWrite             CANRegWrite
#define CANRegRead              CANRegRead
#else
#define CANRegWrite(ulAddress, ulValue)                                     \
                                HWREG(ulAddress) = ulValue

#define CANRegRead(ulAddress)                                               \
                                HWREG(ulAddress)
#endif

//*****************************************************************************
//
// The message object number and index to the local message object memory to
// use when accessing the messages.
//
//*****************************************************************************
#define MSG_OBJ_BCAST_RX_ID     1
#define MSG_OBJ_BCAST_TX_ID     2

//*****************************************************************************
//
// A prototype for the function (in the startup code) for a predictable length
// delay.
//
//*****************************************************************************
extern void Delay(unsigned long ulCount);

unsigned long CANSendBroadcastMsg(unsigned long ulId,
                                  const unsigned char *pucData,
                                  unsigned long ulSize);
unsigned long CANReceive(unsigned char *pucData, unsigned long *pulSize);

//*****************************************************************************
//
// Holds the current address to write to when data is received via the Send
// Data Command.
//
//*****************************************************************************
unsigned long g_ulTransferAddress;

//*****************************************************************************
//
// Holds the remaining bytes expected to be received.
//
//*****************************************************************************
unsigned long g_ulTransferSize;

//*****************************************************************************
//
// The buffer used to receive data from the update.
//
//*****************************************************************************
static unsigned char pucCommandBuffer[8];

//*****************************************************************************
//
// These globals are used to store the first two words to prevent a partial
// image from being booted.
//
//*****************************************************************************
unsigned long g_ulStartValues[2];
unsigned long g_ulStartSize;
unsigned long g_ulStartAddress;

//*****************************************************************************
//
//! Sends data over the CAN interface.
//!
//! \param pucData is the buffer containing the data to write out to the CAN
//! interface.
//! \param ulSize is the number of bytes provided in \e pucData buffer that
//! will be written out to the CAN interface.
//!
//! This function sends \e ulSize bytes of data from the buffer pointed to by
//! \e pucData via the CAN interface.
//!
//! \return None.
//
//*****************************************************************************
void
CANSend(const unsigned char *pucData, unsigned long ulSize)
{
    unsigned long ulBytes;

    //
    // Transmit the number of bytes requested on the CAN interface.
    //
    while(ulSize != 0)
    {
        //
        // Rail the number of bytes to the maximum for a CAN packet.
        //
        if(ulSize > 8)
        {
            ulBytes = 8;
        }
        else
        {
            ulBytes = ulSize;
        }

        //
        // Send out a packet of data.
        //
        if(CANSendBroadcastMsg(LM_API_UPD, pucData, ulBytes) == 0)
        {
            //
            // Move the pointer forward and reduce the number of bytes to send.
            //
            pucData += ulBytes;
            ulSize -= ulBytes;
        }
    }
}

//*****************************************************************************
//
//! Initializes the CAN controller after reset.
//!
//! After reset, the CAN controller is left in the disabled state.  However,
//! the memory used for message objects contains undefined values and must be
//! cleared prior to enabling the CAN controller the first time.  This prevents
//! unwanted transmission or reception of data before the message objects are
//! configured.  This function must be called before enabling the controller
//! the first time.
//!
//! \return None.
//
//*****************************************************************************
void
CANInit(void)
{
    int iMsg;

    //
    // Place CAN controller in init state, regardless of previous state.  This
    // will put controller in idle, and allow the message object RAM to be
    // programmed.
    //
    CANRegWrite(CAN0_BASE + CAN_O_CTL, CAN_CTL_INIT);

    //
    // Wait for busy bit to clear
    //
    while(CANRegRead(CAN0_BASE + CAN_O_IF1CRQ) & CAN_IF1CRQ_BUSY)
    {
    }

    //
    // Clear the message value bit in the arbitration register.  This indicates
    // the message is not valid and is a "safe" condition to leave the message
    // object.  The same arb reg is used to program all the message objects.
    //
    CANRegWrite(CAN0_BASE + CAN_O_IF1CMSK,
                CAN_IF1CMSK_WRNRD | CAN_IF1CMSK_ARB | CAN_IF1CMSK_CONTROL);
    CANRegWrite(CAN0_BASE + CAN_O_IF1ARB2, 0);
    CANRegWrite(CAN0_BASE + CAN_O_IF1MCTL, 0);

    //
    // Loop through to program all 32 message objects
    //
    for(iMsg = 1; iMsg <= 32; iMsg++)
    {
        //
        // Wait for busy bit to clear
        //
        while(CANRegRead(CAN0_BASE + CAN_O_IF1CRQ) & CAN_IF1CRQ_BUSY)
        {
        }

        //
        // Initiate programming the message object
        //
        CANRegWrite(CAN0_BASE + CAN_O_IF1CRQ, iMsg);
    }

    //
    // Make sure that the interrupt and new data flags are updated for the
    // message objects.
    //
    CANRegWrite(CAN0_BASE + CAN_O_IF1CMSK, CAN_IF1CMSK_NEWDAT |
                CAN_IF1CMSK_CLRINTPND);

    //
    // Loop through to program all 32 message objects
    //
    for(iMsg = 1; iMsg <= 32; iMsg++)
    {
        //
        // Wait for busy bit to clear.
        //
        while(CANRegRead(CAN0_BASE + CAN_O_IF1CRQ) & CAN_IF1CRQ_BUSY)
        {
        }

        //
        // Initiate programming the message object
        //
        CANRegWrite(CAN0_BASE + CAN_O_IF1CRQ, iMsg);
    }

    //
    // Acknowledge any pending status interrupts.
    //
    CANRegRead(CAN0_BASE + CAN_O_STS);
}

//*****************************************************************************
//
//! This function configures the message object used to receive commands.
//!
//! This function configures the message object used to receive all firmware
//! update messages.  This will not actually read the data from the message it
//! is used to prepare the message object to receive the data when it is sent.
//!
//! \return None.
//
//*****************************************************************************
void
CANMessageSetRx(void)
{
    unsigned short usCmdMaskReg;
    unsigned short usMaskReg[2];
    unsigned short usArbReg[2];
    unsigned short usMsgCtrl;

    //
    // Wait for busy bit to clear
    //
    while(CANRegRead(CAN0_BASE + CAN_O_IF1CRQ) & CAN_IF1CRQ_BUSY)
    {
    }

    //
    // This is always a write to the Message object as this call is setting a
    // message object.  This call will also always set all size bits so it sets
    // both data bits.  The call will use the CONTROL register to set control
    // bits so this bit needs to be set as well.
    //
    // Set the MASK bit so that this gets trasferred to the Message Object.
    // Set the Arb bit so that this gets transferred to the Message object.
    //
    usCmdMaskReg = (CAN_IF1CMSK_WRNRD | CAN_IF1CMSK_DATAA | CAN_IF1CMSK_DATAB |
                    CAN_IF1CMSK_CONTROL | CAN_IF1CMSK_MASK | CAN_IF1CMSK_ARB);

    //
    // Set the UMASK bit to enable using the mask register.
    // Set the data length since this is set for all transfers.  This is also a
    // single transfer and not a FIFO transfer so set EOB bit.
    //
    usMsgCtrl = CAN_IF1MCTL_UMASK | CAN_IF1MCTL_EOB;

    //
    // Configure the Mask Registers.
    //
    //
    // Set the 29 bits of Identifier mask that were requested.
    //
    usMaskReg[0] = (unsigned short)LM_API_UPD;

    //
    // If the caller wants to filter on the extended ID bit then set it.
    //
    usMaskReg[1] =
        (unsigned short)(CAN_IF1MSK2_MXTD | (LM_API_UPD >> 16));

    //
    // Set the 29 bit version of the Identifier for this message object.
    // Mark the message as valid and set the extended ID bit.
    //
    usArbReg[0] = LM_API_UPD & CAN_IF1ARB1_ID_M;
    usArbReg[1] = ((LM_API_UPD >> 16) & CAN_IF1ARB2_ID_M) |
                   (CAN_IF1ARB2_MSGVAL | CAN_IF1ARB2_XTD);

    //
    // Write out the registers to program the message object.
    //
    CANRegWrite(CAN0_BASE + CAN_O_IF1CMSK, usCmdMaskReg);
    CANRegWrite(CAN0_BASE + CAN_O_IF1MSK1, usMaskReg[0]);
    CANRegWrite(CAN0_BASE + CAN_O_IF1MSK2, usMaskReg[1]);
    CANRegWrite(CAN0_BASE + CAN_O_IF1ARB1, usArbReg[0]);
    CANRegWrite(CAN0_BASE + CAN_O_IF1ARB2, usArbReg[1]);
    CANRegWrite(CAN0_BASE + CAN_O_IF1MCTL, usMsgCtrl);

    //
    // Transfer the message object to the message object specifiec by
    // MSG_OBJ_BCAST_RX_ID.
    //
    CANRegWrite(CAN0_BASE + CAN_O_IF1CRQ,
                MSG_OBJ_BCAST_RX_ID & CAN_IF1CRQ_MNUM_M);
}

//*****************************************************************************
//
//! This function reads data from the receive message object.
//!
//! \param pucData is a pointer to the buffer to store the data read from the
//! CAN controller.
//! \param pulMsgID is a pointer to the ID that was received with the data.
//!
//! This function will reads and acknowledges the data read from the message
//! object used to receive all CAN firmware update messages.  It will also
//! return the message identifier as this holds the API number that was
//! attached to the data.  This message identifier should be one of the
//! LM_API_UPD_* definitions.
//!
//! \return The number of valid bytes returned in the \e pucData buffer or
//! 0xffffffff if data was overwritten in the buffer.
//
//*****************************************************************************
unsigned long
CANMessageGetRx(unsigned char *pucData, unsigned long *pulMsgID)
{
    unsigned short usCmdMaskReg;
    unsigned short usArbReg0, usArbReg1;
    unsigned short usMsgCtrl;
    unsigned long ulBytes;
    int iIdx;
    unsigned long *pulRegister;
    unsigned long ulValue;

    //
    // This is always a read to the Message object as this call is setting a
    // message object.
    // Clear a pending interrupt and new data in a message object.
    //
    usCmdMaskReg = (CAN_IF2CMSK_DATAA | CAN_IF2CMSK_DATAB |
                    CAN_IF1CMSK_CONTROL | CAN_IF2CMSK_CLRINTPND |
                    CAN_IF2CMSK_ARB);

    //
    // Set up the request for data from the message object.
    //
    CANRegWrite(CAN0_BASE + CAN_O_IF2CMSK, usCmdMaskReg);

    //
    // Transfer the message object to the message object specifiec by
    // MSG_OBJ_BCAST_RX_ID.
    //
    CANRegWrite(CAN0_BASE + CAN_O_IF2CRQ,
                MSG_OBJ_BCAST_RX_ID & CAN_IF1CRQ_MNUM_M);

    //
    // Wait for busy bit to clear
    //
    while(CANRegRead(CAN0_BASE + CAN_O_IF2CRQ) & CAN_IF1CRQ_BUSY)
    {
    }

    //
    // Read out the IF Registers.
    //
    usArbReg0 = CANRegRead(CAN0_BASE + CAN_O_IF2ARB1);
    usArbReg1 = CANRegRead(CAN0_BASE + CAN_O_IF2ARB2);
    usMsgCtrl = CANRegRead(CAN0_BASE + CAN_O_IF2MCTL);

    //
    // Set the 29 bit version of the Identifier for this message object.
    //
    *pulMsgID = ((usArbReg1 & CAN_IF1ARB2_ID_M) << 16) | usArbReg0;

    //
    // See if there is new data available.
    //
    if((usMsgCtrl & (CAN_IF1MCTL_NEWDAT | CAN_IF1MCTL_MSGLST)) ==
        CAN_IF1MCTL_NEWDAT)
    {
        //
        // Get the amount of data needed to be read.
        //
        ulBytes = usMsgCtrl & CAN_IF1MCTL_DLC_M;

        //
        // Read out the data from the CAN registers.
        //
        pulRegister = (unsigned long *)(CAN0_BASE + CAN_O_IF2DA1);

        //
        // Loop always copies 1 or 2 bytes per iteration.
        //
        for(iIdx = 0; iIdx < ulBytes; )
        {
            //
            // Read out the data 16 bits at a time since this is how the
            // registers are aligned in memory.
            //
            ulValue = CANRegRead((unsigned long)(pulRegister++));

            //
            // Store the first byte.
            //
            pucData[iIdx++] = (unsigned char)ulValue;

            //
            // Only read the second byte if needed.
            //
            if(iIdx < ulBytes)
            {
                pucData[iIdx++] = (unsigned char)(ulValue >> 8);
            }
        }

        //
        // Now clear out the new data flag.
        //
        CANRegWrite(CAN0_BASE + CAN_O_IF2CMSK, CAN_IF1CMSK_NEWDAT);

        //
        // Transfer the message object to the message object specifiec by
        // MSG_OBJ_BCAST_RX_ID.
        //
        CANRegWrite(CAN0_BASE + CAN_O_IF2CRQ, MSG_OBJ_BCAST_RX_ID);

        //
        // Wait for busy bit to clear
        //
        while(CANRegRead(CAN0_BASE + CAN_O_IF2CRQ) & CAN_IF2CRQ_BUSY)
        {
        }
    }
    else
    {
        //
        // Data was lost so inform the caller.
        //
        ulBytes = 0xffffffff;
    }
    return(ulBytes);
}

//*****************************************************************************
//
//! This function sends data using the transmit message object.
//!
//! \param ulId is the ID to use with this message.
//! \param pucData is a pointer to the buffer with the data to be sent.
//! \param ulSize is the number of bytes to send and should not be more than
//! 8 bytes.
//!
//! This function will reads and acknowledges the data read from the message
//! object used to receive all CAN firmware update messages.  It will also
//! return the message identifier as this holds the API number that was
//! attached to the data.  This message identifier should be one of the
//! LM_API_UPD_* definitions.
//!
//! \return None.
//
//*****************************************************************************
void
CANMessageSetTx(unsigned long ulId, const unsigned char *pucData,
                unsigned long ulSize)
{
    unsigned short usCmdMaskReg;
    unsigned short usArbReg0, usArbReg1;
    unsigned short usMsgCtrl;
    int iIdx;
    unsigned long *pulRegister;
    unsigned long ulValue;

    //
    // Wait for busy bit to clear
    //
    while(CANRegRead(CAN0_BASE + CAN_O_IF1CRQ) & CAN_IF1CRQ_BUSY)
    {
    }

    //
    // This is always a write to the Message object as this call is setting a
    // message object.  This call will also always set all size bits so it sets
    // both data bits.  The call will use the CONTROL register to set control
    // bits so this bit needs to be set as well.
    //
    usCmdMaskReg = (CAN_IF1CMSK_WRNRD | CAN_IF1CMSK_DATAA | CAN_IF1CMSK_DATAB |
                    CAN_IF1CMSK_CONTROL | CAN_IF1CMSK_ARB);

    //
    // Set the 29 bit version of the Identifier for this message object.
    //
    usArbReg0 = ulId & CAN_IF1ARB1_ID_M;

    //
    // Mark the message as valid and set the extended ID bit.
    //
    usArbReg1 = (((ulId >> 16) & CAN_IF1ARB2_ID_M) |
                 (CAN_IF1ARB2_DIR | CAN_IF1ARB2_MSGVAL | CAN_IF1ARB2_XTD));

    //
    // Set the TXRQST bit and the reset the rest of the register.
    // Set the data length since this is set for all transfers.  This is also a
    // single transfer and not a FIFO transfer so set EOB bit.
    //
    //
    usMsgCtrl = (CAN_IF1MCTL_TXRQST | CAN_IF1MCTL_EOB |
                 (ulSize & CAN_IF1MCTL_DLC_M));

    //
    // Write the data out to the CAN Data registers if needed.
    //
    pulRegister = (unsigned long *)(CAN0_BASE + CAN_O_IF1DA1);

    //
    // Loop always copies 1 or 2 bytes per iteration.
    //
    for(iIdx = 0; iIdx < ulSize; )
    {

        //
        // Write out the data 16 bits at a time since this is how the registers
        // are aligned in memory.
        //
        ulValue = pucData[iIdx++];

        //
        // Only write the second byte if needed otherwise it will be zero.
        //
        if(iIdx < ulSize)
        {
            ulValue |= (pucData[iIdx++] << 8);
        }
        CANRegWrite((unsigned long)(pulRegister++), ulValue);
    }

    //
    // Write out the registers to program the message object.
    //
    CANRegWrite(CAN0_BASE + CAN_O_IF1CMSK, usCmdMaskReg);
    CANRegWrite(CAN0_BASE + CAN_O_IF1ARB1, usArbReg0);
    CANRegWrite(CAN0_BASE + CAN_O_IF1ARB2, usArbReg1);
    CANRegWrite(CAN0_BASE + CAN_O_IF1MCTL, usMsgCtrl);

    //
    // Transfer the message object to the message object specifiec by
    // MSG_OBJ_BCAST_RX_ID.
    //
    CANRegWrite(CAN0_BASE + CAN_O_IF1CRQ,
                (MSG_OBJ_BCAST_TX_ID) & CAN_IF1CRQ_MNUM_M);
}

//*****************************************************************************
//
//! Configures the CAN interface.
//!
//! \param ulSetTiming determines if the CAN bit timing should be configured.
//!
//! This function configures the CAN controller, preparing it for use by
//! the boot loader.   If the \e ulSetTiming parameter is 0, the bit timing
//! for the CAN bus will be left alone.  This occurs when the boot loader was
//! entered from a running application that already has configured the timing
//! for the system.  When \e ulSetTiming is non-zero the bit timing will be
//! set to the defaults defined in the <tt>bl_config.h</tt> file in the
//! project.
//!
//! \return None.
//
//*****************************************************************************
void
ConfigureCANInterface(unsigned long ulSetTiming)
{
    //
    // Reset the state of all the message object and the state of the CAN
    // module to a known state.
    //
    CANInit();

    //
    // If a device identifier was specified then this was due to an update from
    // a running CAN application so don't change the CAN bit timing.
    //
    if(ulSetTiming != 0)
    {
        //
        // Set the bit fields of the bit timing register according to the
        // parms.
        //
        CANRegWrite(CAN0_BASE + CAN_O_BIT, CAN_BIT_TIMING);

        //
        // Set the divider upper bits in the extension register.
        //
        CANRegWrite(CAN0_BASE + CAN_O_BRPE, 0);
    }

    //
    // Take the CAN0 device out of INIT state.
    //
    //
    CANRegWrite(CAN0_BASE + CAN_O_CTL,
                CANRegRead(CAN0_BASE + CAN_O_CTL) & ~CAN_CTL_INIT);

    //
    // Configure the broadcast receive message object.
    //
    CANMessageSetRx();

    //
    // Enable auto-retry on CAN transmit.
    //
    CANRegWrite(CAN0_BASE + CAN_O_CTL,
                (CANRegRead(CAN0_BASE + CAN_O_CTL) & ~CAN_CTL_DAR));
}

//*****************************************************************************
//
// Sends a broacast firmware update message on the CAN bus to all devices.
//
// \param ulId is the ID to use with this message.
// \param pucData is a pointer to the buffer with the data to be sent.
// \param ulSize is the number of bytes to send and should not be more than
// 8 bytes.
// This command will send a broadcast message to all devices on the CAN bus.
// The /e ulId paramer is the Identifier to use, pucData holds the data, and
// ulSize holds the size.
//
//*****************************************************************************
unsigned long
CANSendBroadcastMsg(unsigned long ulId, const unsigned char *pucData,
                    unsigned long ulSize)
{
    int iIndex;

    //
    // Set the number of times to retry reading the status before a timeout
    // and generating an error.
    //
    iIndex = 1000;

    //
    // Make sure the last transmission was successful.
    //
    while(iIndex)
    {
        //
        // Wait for the transmit status to indicate that the previous message
        // was transmitted.
        //
        if(CANRegRead(CAN0_BASE + CAN_O_TXRQ1) == 0)
        {
            break;
        }
        iIndex--;
    }

    //
    // If there was no timeout then send Object to the CAN controller.
    //
    if(iIndex != 0)
    {
        //
        // Send the response packet.
        //
        CANMessageSetTx(ulId, pucData, ulSize);
    }
    else
    {
        return(0xffffffff);
    }
    return(0);
}

//*****************************************************************************
//
//! This is the main routine for handling updating over CAN.
//!
//! This function accepts boot loader commands over CAN to perform a firmware
//! update over the CAN bus.  This function assumes that the CAN bus timing
//! and message objects have been configured elsewhere.
//!
//! \return None.
//
//*****************************************************************************
void
UpdaterCAN(void)
{
    unsigned long ulBytes;
    unsigned long ulCmd;
    unsigned long ulFlashSize;
    unsigned long ulTemp;
    unsigned char ucStatus;

    while(1)
    {
        ulBytes = 8;
        ulCmd = CANReceive(pucCommandBuffer, &ulBytes);

        ucStatus = CAN_CMD_SUCCESS;

        switch(ulCmd)
        {
            case LM_API_UPD_PING:
            {
                break;
            }
            case LM_API_UPD_RESET:
            {
                //
                // Perform a software reset request.  This will cause the
                // microcontroller to reset; no further code will be executed.
                //
                HWREG(NVIC_APINT) = (NVIC_APINT_VECTKEY |
                                     NVIC_APINT_SYSRESETREQ);

                //
                // The microcontroller should have reset, so this should never
                // be reached.  Just in case, loop forever.
                //
                while(1)
                {
                }
            }
            case LM_API_UPD_SEND_DATA:
            {
                //
                // If this is overwriting the boot loader then the application
                // has already been erased so now erase the boot loader.
                //
                if(g_ulTransferAddress == 0)
                {
                    //
                    // Clear the flash access interrupt.
                    //
                    BL_FLASH_CL_ERR_FN_HOOK();

                    //
                    // Erase the application before the boot loader.
                    //
                    for(ulTemp = 0; ulTemp < APP_START_ADDRESS;
                        ulTemp += FLASH_PAGE_SIZE)
                    {
                        //
                        // Erase this block.
                        //
                        BL_FLASH_ERASE_FN_HOOK(ulTemp);
                    }

                    //
                    // Return an error if an access violation occurred.
                    //
                    if(BL_FLASH_ERROR_FN_HOOK())
                    {
                        //
                        // Setting g_ulTransferSize to zero makes
                        // COMMAND_SEND_DATA fail to accept any more data.
                        //
                        g_ulTransferSize = 0;

                        //
                        // Indicate that the flash erase failed.
                        //
                        ucStatus = CAN_CMD_FAIL;
                    }
                }

                //
                // Check if there are any more bytes to receive.
                //
                if(g_ulTransferSize >= ulBytes)
                {
                    //
                    // Decrypt the data if required.
                    //
#ifdef BL_DECRYPT_FN_HOOK
                    BL_DECRYPT_FN_HOOK(pucCommandBuffer, ulBytes);
#endif

                    //
                    // Skip the first transfer.
                    //
                    if(g_ulStartSize == g_ulTransferSize)
                    {
                        g_ulStartValues[0] =
                            *((unsigned long *)&pucCommandBuffer[0]);
                        g_ulStartValues[1] =
                            *((unsigned long *)&pucCommandBuffer[4]);
                    }
                    else
                    {
                        //
                        // Clear the flash access interrupt.
                        //
                        BL_FLASH_CL_ERR_FN_HOOK();

                        //
                        // Loop over the words to program.
                        //
                        BL_FLASH_PROGRAM_FN_HOOK(g_ulTransferAddress,
                                                 pucCommandBuffer,
                                                 ulBytes);
                    }

                    //
                    // Return an error if an access violation occurred.
                    //
                    if(BL_FLASH_ERROR_FN_HOOK())
                    {
                        //
                        // Indicate that the flash programming failed.
                        //
                        ucStatus = CAN_CMD_FAIL;
                    }
                    else
                    {
                        //
                        // Now update the address to program.
                        //
                        g_ulTransferSize -= ulBytes;
                        g_ulTransferAddress += ulBytes;

                        //
                        // If a progress hook function has been provided, call
                        // it here.
                        //
#ifdef BL_PROGRESS_FN_HOOK
                        BL_PROGRESS_FN_HOOK(g_ulStartSize - g_ulTransferSize,
                                            g_ulStartSize);
#endif
                    }
                }
                else
                {
                    //
                    // This indicates that too much data is being sent to the
                    // device.
                    //
                    ucStatus = CAN_CMD_FAIL;
                }

                //
                // If the last expected bytes were received then write out the
                // first two words of the image to allow it to boot.
                //
                if(g_ulTransferSize == 0)
                {
                    //
                    // Loop over the words to program.
                    //
                    BL_FLASH_PROGRAM_FN_HOOK(g_ulStartAddress,
                                             (unsigned char *)&g_ulStartValues,
                                             8);

                    //
                    // If an end signal hook function has been provided, call
                    // it here since we have finished a download.
                    //
#ifdef BL_END_FN_HOOK
                    BL_END_FN_HOOK();
#endif
                }
                break;
            }
            case LM_API_UPD_DOWNLOAD:
            {

                g_ulTransferAddress = *((unsigned long *)&pucCommandBuffer[0]);
                g_ulTransferSize = *((unsigned long *)&pucCommandBuffer[4]);
                g_ulStartSize = g_ulTransferSize;
                g_ulStartAddress = g_ulTransferAddress;

                //
                // This determines the size of the flash available on the
                // part in use.
                //
                ulFlashSize = (((HWREG(SYSCTL_DC0) &
                                 SYSCTL_DC0_FLASHSZ_M) + 1) << 11);

                //
                // If we are reserving space at the top of flash then this
                // space is not available for application download but it
                // is availble to be updated directly.
                //
#ifdef FLASH_RSVD_SPACE
                if((ulFlashSize - FLASH_RSVD_SPACE) != g_ulTransferAddress)
                {
                    ulFlashSize -= FLASH_RSVD_SPACE;
                }
#endif

                //
                // Check for a valid starting address and image size.
                //
                if(!BL_FLASH_AD_CHECK_FN_HOOK(g_ulTransferAddress,
                                              g_ulTransferSize))
                {
                    //
                    // Set the code to an error to indicate that the last
                    // command failed.  This informs the updater program
                    // that the download command failed.
                    //
                    ucStatus = CAN_CMD_FAIL;

                    //
                    // This packet has been handled.
                    //
                    break;
                }

                //
                // Only erase the space that we need if we are not
                // protecting the code.
                //
#ifndef FLASH_CODE_PROTECTION
                ulFlashSize = g_ulTransferAddress + g_ulTransferSize;
#endif

                //
                // Clear the flash access interrupt.
                //
                BL_FLASH_CL_ERR_FN_HOOK();

                //
                // Leave the boot loader present until we start getting an
                // image.
                //
                for(ulTemp = g_ulTransferAddress; ulTemp < ulFlashSize;
                    ulTemp += FLASH_PAGE_SIZE)
                {
                    //
                    // Erase this block.
                    //
                    BL_FLASH_ERASE_FN_HOOK(ulTemp);
                }

                //
                // Return an error if an access violation occurred.
                //
                if(BL_FLASH_ERROR_FN_HOOK())
                {
                    ucStatus = CAN_CMD_FAIL;
                }

                //
                // See if the command was successful.
                //
                if(ucStatus != CAN_CMD_SUCCESS)
                {
                    //
                    // Setting g_ulTransferSize to zero makes COMMAND_SEND_DATA
                    // fail to accept any data.
                    //
                    g_ulTransferSize = 0;
                }
#ifdef BL_START_FN_HOOK
                else
                {
                    //
                    // If a start signal hook function has been provided, call
                    // it here since we are about to start a new download.
                    //
                    BL_START_FN_HOOK();
                }
#endif

                break;
            }
            default:
            {
                ucStatus = CAN_CMD_FAIL;
                break;
            }
        }
        CANSendBroadcastMsg(LM_API_UPD_ACK, &ucStatus, 1);
    }
}

//*****************************************************************************
//
//! This is the application entry point to the CAN updater.
//!
//! This function should only be entered from a running application and not
//! when running the boot loader with no application present.
//!
//! \return None.
//
//*****************************************************************************
void
AppUpdaterCAN(void)
{
    //
    // Configure the CAN controller but don't change the bit timing.
    //
    ConfigureCANInterface(0);

    //
    // Call the main update routine.
    //
    UpdaterCAN();
}

#ifdef CAN_ERRATA_FIX
//*****************************************************************************
//
//! \internal
//!
//! Reads a CAN controller register.
//!
//! \param ulRegAddress is the full address of the CAN register to be read.
//!
//! This function performs the necessary synchronization to read from a CAN
//! controller register.
//!
//! This function replaces the original CANReadReg() API and performs the same
//! actions.  A macro is provided in <tt>can.h</tt> to map the original API to
//! this API.
//!
//! \note This function provides the delay required to access CAN registers.
//! This delay is required when accessing CAN registers directly.
//!
//! \return Returns the value read from the register.
//
//*****************************************************************************
static unsigned long
CANRegRead(unsigned long ulRegAddress)
{
    volatile int iDelay;
    unsigned long ulRetVal;

    //
    // Trigger the inital read to the CAN controller.  The value returned at
    // this point is not valid.
    //
    HWREG(ulRegAddress);

    //
    // This delay is necessary for the CAN have the correct data on the bus.
    //
    for(iDelay = 0; iDelay < CAN_RW_DELAY; iDelay++)
    {
    }

    //
    // Do the final read that has the valid value of the register.
    //
    ulRetVal = HWREG(ulRegAddress);

    return(ulRetVal);
}

//*****************************************************************************
//
//! \internal
//!
//! Writes a CAN controller register.
//!
//! \param ulRegAddress is the full address of the CAN register to be written.
//! \param ulRegValue is the value to write into the register specified by
//! \e ulRegAddress.
//!
//! This function takes care of the synchronization necessary to write to a
//! CAN controller register.
//!
//! This function replaces the original CANWriteReg() API and performs the same
//! actions.  A macro is provided in <tt>can.h</tt> to map the original API to
//! this API.
//!
//! \note The delays in this function are required when accessing CAN registers
//! directly.
//!
//! \return None.
//
//*****************************************************************************
static void
CANRegWrite(unsigned long ulRegAddress, unsigned long ulRegValue)
{
    volatile int iDelay;

    //
    // Trigger the inital write to the CAN controller.  The value will not make
    // it out to the CAN controller for CAN_RW_DELAY cycles.
    //
    HWREG(ulRegAddress) = ulRegValue;

    //
    // Delay to allow the CAN controller to receive the new data.
    //
    for(iDelay = 0; iDelay < CAN_RW_DELAY; iDelay++)
    {
    }
}
#endif

//*****************************************************************************
//
//! Receives data over the CAN interface.
//!
//! \param pucData is the buffer to read data into from the CAN interface.
//! \param pulSize is a pointer to the number of bytes provided in the
//! \e pucData buffer that should be written with data from the CAN interface.
//!
//! This function reads back \e ulSize bytes of data from the CAN interface,
//! into the buffer that is pointed to by \e pucData.  This function will not
//! return until \e pulSize number of bytes have been received.
//!
//! \return None.
//
//*****************************************************************************
unsigned long
CANReceive(unsigned char *pucData, unsigned long *pulSize)
{
    unsigned long ulBytesRead;
    unsigned long ulSize;
    unsigned long ulMsgID;

    ulSize = *pulSize;
    *pulSize = 0;
    ulMsgID = 0;

    //
    // Receive the number of bytes requested on the CAN interface.
    //
    while(ulSize != 0)
    {
        //
        // Wait for the receive status to indicate a previous message
        // was received.
        //
        while(CANRegRead(CAN0_BASE + CAN_O_NWDA1) == 0)
        {
        }

        ulBytesRead = CANMessageGetRx(pucData, &ulMsgID);

        if(ulBytesRead != 0xffffffff)
        {
            pucData += ulBytesRead;
            ulSize -= ulBytesRead;

            *pulSize += ulBytesRead;
        }

        //
        // If less bytes were received than requested exit since that was the
        // end of the data.
        //
        if((unsigned long)ulBytesRead != 8)
        {
            break;
        }
    }
    return(ulMsgID);
}

//*****************************************************************************
//
//! Generic configuration is handled in this function.
//!
//! This function is called by the start up code to perform any configuration
//! necessary before calling the update routine.
//!
//! \return None.
//
//*****************************************************************************
void
ConfigureCAN(void)
{
#ifdef CRYSTAL_FREQ
    //
    // Since the crystal frequency was specified, enable the main oscillator
    // and clock the processor from it.
    //
    HWREG(SYSCTL_RCC) &= ~(SYSCTL_RCC_MOSCDIS);
    Delay(524288);
#if CRYSTAL_FREQ == 3579545
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_3_57MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 3686400
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_3_68MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 4000000
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_4MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 4096000
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_4_09MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 4915200
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_4_91MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 5000000
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_5MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 5120000
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_5_12MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 6000000
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_6MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 6144000
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_6_14MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 7372800
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_7_37MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 8000000
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_8MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 8192000
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_8_19MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 10000000
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_10MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 12000000
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_12MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 12288000
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_12_2MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 13560000
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_13_5MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 14318180
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_14_3MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 16000000
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                            SYSCTL_RCC_XTAL_16MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif
#if CRYSTAL_FREQ == 16384000
    HWREG(SYSCTL_RCC) = ((HWREG(SYSCTL_RCC) &
                          ~(SYSCTL_RCC_XTAL_M | SYSCTL_RCC_OSCSRC_M)) |
                         SYSCTL_RCC_XTAL_16_3MHZ | SYSCTL_RCC_OSCSRC_MAIN);
#endif

    //
    // Set the flash programming time based on the specified crystal frequency.
    //
    HWREG(FLASH_USECRL) = ((CRYSTAL_FREQ + 999999) / 1000000) - 1;
#else
    //
    // Set the flash to program at 16 MHz since that is just beyond the fastest
    // that we could run.
    //
    HWREG(FLASH_USECRL) = 15;
#endif

    //
    // Enable the CAN controller.
    //
    HWREG(SYSCTL_RCGC0) |= SYSCTL_RCGC0_CAN0;

#if CAN_RX_PERIPH == CAN_TX_PERIPH
    //
    // Enable the GPIO associated with CAN0
    //
    HWREG(SYSCTL_RCGC2) |= CAN_RX_PERIPH;

    //
    // Set the alternate function selects.
    //
    HWREG(CAN_RX_PORT + GPIO_O_AFSEL) |= CAN_RX_PIN_M | CAN_TX_PIN_M;

    //
    // Set the pin type to it's digital function.
    //
    HWREG(CAN_RX_PORT + GPIO_O_DEN) |= CAN_RX_PIN_M | CAN_TX_PIN_M;

#else
    //
    // Enable the GPIO associated with CAN0
    //
    HWREG(SYSCTL_RCGC2) |= CAN_RX_PERIPH | CAN_TX_PERIPH;

    //
    // Set the alternate function selects.
    //
    HWREG(CAN_RX_PORT + GPIO_O_AFSEL) |= CAN_RX_PIN_M;
    HWREG(CAN_TX_PORT + GPIO_O_AFSEL) |= CAN_TX_PIN_M;

    //
    // Set the pin type to it's digital function.
    //
    HWREG(CAN_RX_PORT + GPIO_O_DEN) |= CAN_RX_PIN_M;
    HWREG(CAN_TX_PORT + GPIO_O_DEN) |= CAN_TX_PIN_M;
#endif

    //
    // Configure the CAN interface.
    //
    ConfigureCANInterface(1);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
#endif
