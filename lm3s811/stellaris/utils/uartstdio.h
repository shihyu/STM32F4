//*****************************************************************************
//
// uartstdio.h - Prototypes for the UART console functions.
//
// Copyright (c) 2007-2009 Luminary Micro, Inc.  All rights reserved.
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

#ifndef __UARTSTDIO_H__
#define __UARTSTDIO_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// If built for buffered operation, the following labels define the sizes of
// the transmit and receive buffers respectively.
//
//*****************************************************************************
#ifdef UART_BUFFERED
#ifndef UART_RX_BUFFER_SIZE
#define UART_RX_BUFFER_SIZE     128
#endif
#ifndef UART_TX_BUFFER_SIZE
#define UART_TX_BUFFER_SIZE     1024
#endif
#endif

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern void UARTStdioInit(unsigned long ulPort);
extern int UARTgets(char *pcBuf, unsigned long ulLen);
extern unsigned char UARTgetc(void);
extern void UARTprintf(const char *pcString, ...);
extern int UARTwrite(const char *pcBuf, unsigned long ulLen);
#ifdef UART_BUFFERED
extern int UARTPeek(unsigned char ucChar);
extern void UARTFlushTx(tBoolean bDiscard);
extern void UARTFlushRx(void);
extern int UARTRxBytesAvail(void);
extern int UARTTxBytesFree(void);
extern void UARTEchoSet(tBoolean bEnable);
#endif

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __UARTSTDIO_H__
