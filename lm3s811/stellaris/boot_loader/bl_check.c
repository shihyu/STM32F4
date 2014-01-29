//*****************************************************************************
//
// bl_check.c - Code to check for a forced update.
//
// Copyright (c) 2006-2009 Luminary Micro, Inc.  All rights reserved.
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

#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "bl_config.h"
#include "boot_loader/bl_check.h"
#include "boot_loader/bl_hooks.h"

//*****************************************************************************
//
//! \addtogroup bl_check_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// A prototype for the function (in the startup code) for a predictable length
// delay.
//
//*****************************************************************************
extern void Delay(unsigned long ulCount);

//*****************************************************************************
//
//! Checks a GPIO for a forced update.
//!
//! This function checks the state of a GPIO to determine if a update is being
//! requested.
//!
//! \return Returns a non-zero value if an update is being requested and zero
//! otherwise.
//
//*****************************************************************************
#ifdef ENABLE_UPDATE_CHECK
unsigned long
CheckGPIOForceUpdate(void)
{
    //
    // Enable the required GPIO module.
    //
    HWREG(SYSCTL_RCGC2) |= FORCED_UPDATE_PERIPH;

    //
    // Wait a while before accessing the peripheral.
    //
    Delay(3);

    //
    // Enable the pin used to see if an update is being requested.
    //
    HWREG(FORCED_UPDATE_PORT + GPIO_O_DEN) |= 1 << FORCED_UPDATE_PIN;

    //
    // Wait a while before reading the pin.
    //
    Delay(1000);

    //
    // Check the pin to see if an update is being requested.
    //
    if(HWREG(FORCED_UPDATE_PORT + (1 << (FORCED_UPDATE_PIN + 2))) ==
       (FORCED_UPDATE_POLARITY << FORCED_UPDATE_PIN))
    {
        return(1);
    }
    else
    {
        return(0);
    }
}
#endif

//*****************************************************************************
//
//! Checks if an update is needed or is being requested.
//!
//! This function detects if an update is being requested or if there is no
//! valid code presently located on the microcontroller.  This is used to tell
//! whether or not to enter update mode.
//!
//! \return Returns a non-zero value if an update is needed or is being
//! requested and zero otherwise.
//
//*****************************************************************************
unsigned long
CheckForceUpdate(void)
{
#ifdef BL_CHECK_UPDATE_FN_HOOK
    //
    // If the update check function is hooked, call the application to determine
    // how to proceed.
    //
    return(BL_CHECK_UPDATE_FN_HOOK());
#else
    unsigned long *pulApp;

    //
    // See if the first location is 0xfffffffff or something that does not
    // look like a stack pointer, or if the second location is 0xffffffff or
    // something that does not look like a reset vector.
    //
    pulApp = (unsigned long *)APP_START_ADDRESS;
    if((pulApp[0] == 0xffffffff) || ((pulApp[0] & 0xfff00000) != 0x20000000) ||
       (pulApp[1] == 0xffffffff) || ((pulApp[1] & 0xfff00001) != 0x00000001))
    {
        return(1);
    }

    //
    // If simple GPIO checking is configured, determine whether or not to force
    // an update.
    //
#ifdef ENABLE_UPDATE_CHECK
    return(CheckGPIOForceUpdate());
#else
    //
    // No update was needed or requested.
    //
    return(0);
#endif
#endif
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
