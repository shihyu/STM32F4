//*****************************************************************************
//
// ringbuf.h - Defines and Macros for the ring buffer utilities.
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

#ifndef __RINGBUF_H__
#define __RINGBUF_H__

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
// The structure used for encapsulating all the items associated with a
// ring buffer.
//
//*****************************************************************************
typedef struct
{
    //
    // The ring buffer size.
    //
    unsigned long ulSize;

    //
    // The ring buffer write index.
    //
    volatile unsigned long ulWriteIndex;

    //
    // The ring buffer read index.
    //
    volatile unsigned long ulReadIndex;

    //
    // The ring buffer.
    //
    unsigned char *pucBuf;

}
tRingBufObject;

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
extern tBoolean RingBufFull(tRingBufObject *ptRingBuf);
extern tBoolean RingBufEmpty(tRingBufObject *ptRingBuf);
extern void RingBufFlush(tRingBufObject *ptRingBuf);
extern unsigned long RingBufUsed(tRingBufObject *ptRingBuf);
extern unsigned long RingBufFree(tRingBufObject *ptRingBuf);
extern unsigned long RingBufContigUsed(tRingBufObject *ptRingBuf);
extern unsigned long RingBufContigFree(tRingBufObject *ptRingBuf);
extern unsigned long RingBufSize(tRingBufObject *ptRingBuf);
extern unsigned char RingBufReadOne(tRingBufObject *ptRingBuf);
extern void RingBufRead(tRingBufObject *ptRingBuf, unsigned char *pucData,
                        unsigned long ulLength);
extern void RingBufWriteOne(tRingBufObject *ptRingBuf, unsigned char ucData);
extern void RingBufWrite(tRingBufObject *ptRingBuf, unsigned char *pucData,
                         unsigned long ulLength);
extern void RingBufAdvanceWrite(tRingBufObject *ptRingBuf,
                                unsigned long ulNumBytes);
extern void RingBufAdvanceRead(tRingBufObject *ptRingBuf,
                                unsigned long ulNumBytes);
extern void RingBufInit(tRingBufObject *ptRingBuf, unsigned char *pucBuf,
                        unsigned long ulSize);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  __RINGBUF_H__
