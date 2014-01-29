//*****************************************************************************
//
// bl_can_timing.h - Timing definitions for the CAN controller.
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

#ifndef __BL_CAN_TIMING_H__
#define __BL_CAN_TIMING_H__

#ifdef CAN_ENABLE_UPDATE

//*****************************************************************************
//
// This macro is used to generate the proper value for CAN_BIT_TIMING.
//
//*****************************************************************************
#define CAN_BIT_REG(seg2, seg1, sjw, brp)                                     \
                                ((((seg2 - 1) << CAN_BIT_TSEG2_S) &           \
                                  CAN_BIT_TSEG2_M) |                          \
                                 (((seg1 - 1) << CAN_BIT_TSEG1_S) &           \
                                  CAN_BIT_TSEG1_M) |                          \
                                 (((sjw - 1) << CAN_BIT_SJW_S) &              \
                                  CAN_BIT_SJW_M) |                            \
                                 (((brp - 1) << CAN_BIT_BRP_S) &              \
                                  CAN_BIT_BRP_M))

//*****************************************************************************
//
// The settings for a 16MHz crystal frequency.
//
//*****************************************************************************
#if CRYSTAL_FREQ == 16000000
#if CAN_BIT_RATE == 1000000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 2, 2, 2)
#elif CAN_BIT_RATE == 500000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 4)
#elif CAN_BIT_RATE == 250000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 8)
#elif CAN_BIT_RATE == 125000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 16)
#elif CAN_BIT_RATE == 50000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 40)
#elif CAN_BIT_RATE == 20000
#define CAN_BIT_TIMING          CAN_BIT_REG(8, 7, 2, 50)
#else
#error Invalid CAN_BIT_RATE value used with a 16MHz crystal.
#endif

//*****************************************************************************
//
// The settings for a 12MHz crystal frequency.
//
//*****************************************************************************
#elif CRYSTAL_FREQ == 12000000
#if CAN_BIT_RATE == 1000000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 2, 1)
#elif CAN_BIT_RATE == 500000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 2, 2)
#elif CAN_BIT_RATE == 250000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 2, 4)
#elif CAN_BIT_RATE == 125000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 2, 8)
#elif CAN_BIT_RATE == 50000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 2, 20)
#elif CAN_BIT_RATE == 20000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 2, 50)
#else
#error Invalid CAN_BIT_RATE value used with a 12MHz crystal.
#endif

//*****************************************************************************
//
// The settings for a 10MHz crystal frequency.
//
//*****************************************************************************
#elif CRYSTAL_FREQ == 10000000
#if CAN_BIT_RATE == 1000000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 2, 1)
#elif CAN_BIT_RATE == 500000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 2, 2)
#elif CAN_BIT_RATE == 250000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 2, 4)
#elif CAN_BIT_RATE == 125000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 2, 8)
#elif CAN_BIT_RATE == 50000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 2, 20)
#elif CAN_BIT_RATE == 20000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 2, 50)
#else
#error Invalid CAN_BIT_RATE value used with a 10MHz crystal.
#endif

//*****************************************************************************
//
// The settings for a 8MHz crystal frequency.
//
//*****************************************************************************
#elif CRYSTAL_FREQ == 8000000
#if CAN_BIT_RATE == 1000000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 1)
#elif CAN_BIT_RATE == 500000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 2)
#elif CAN_BIT_RATE == 250000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 4)
#elif CAN_BIT_RATE == 125000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 8)
#elif CAN_BIT_RATE == 50000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 20)
#elif CAN_BIT_RATE == 20000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 50)
#else
#error Invalid CAN_BIT_RATE value used with a 8MHz crystal.
#endif

//*****************************************************************************
//
// The settings for a 6MHz crystal frequency.
//
//*****************************************************************************
#elif CRYSTAL_FREQ == 6000000
#if CAN_BIT_RATE == 500000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 2, 1)
#elif CAN_BIT_RATE == 250000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 2, 2)
#elif CAN_BIT_RATE == 125000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 2, 4)
#elif CAN_BIT_RATE == 50000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 2, 10)
#elif CAN_BIT_RATE == 20000
#define CAN_BIT_TIMING          CAN_BIT_REG(6, 5, 2, 25)
#else
#error Invalid CAN_BIT_RATE value used with a 6MHz crystal.
#endif

//*****************************************************************************
//
// The settings for a 5MHz crystal frequency.
//
//*****************************************************************************
#elif CRYSTAL_FREQ == 5000000
#if CAN_BIT_RATE == 500000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 2, 1)
#elif CAN_BIT_RATE == 250000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 2, 2)
#elif CAN_BIT_RATE == 125000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 2, 4)
#elif CAN_BIT_RATE == 50000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 2, 10)
#elif CAN_BIT_RATE == 20000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 2, 25)
#else
#error Invalid CAN_BIT_RATE value used with a 5MHz crystal.
#endif

//*****************************************************************************
//
// The settings for a 4MHz crystal frequency.
//
//*****************************************************************************
#elif CRYSTAL_FREQ == 4000000
#if CAN_BIT_RATE == 500000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 1)
#elif CAN_BIT_RATE == 250000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 2)
#elif CAN_BIT_RATE == 125000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 4)
#elif CAN_BIT_RATE == 50000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 10)
#elif CAN_BIT_RATE == 20000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 25)
#else
#error Invalid CAN_BIT_RATE value used with a 4MHz crystal.
#endif

//*****************************************************************************
//
// The settings for a 2MHz crystal frequency.
//
//*****************************************************************************
#elif CRYSTAL_FREQ == 2000000
#if CAN_BIT_RATE == 250000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 1)
#elif CAN_BIT_RATE == 125000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 2)
#elif CAN_BIT_RATE == 50000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 5)
#elif CAN_BIT_RATE == 20000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 2, 10)
#else
#error Invalid CAN_BIT_RATE value used with a 2MHz crystal.
#endif

//*****************************************************************************
//
// The settings for a 1MHz crystal frequency.
//
//*****************************************************************************
#elif CRYSTAL_FREQ == 1000000
#if CAN_BIT_RATE == 125000
#define CAN_BIT_TIMING          CAN_BIT_REG(4, 3, 2, 1)
#elif CAN_BIT_RATE == 50000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 2, 2)
#elif CAN_BIT_RATE == 20000
#define CAN_BIT_TIMING          CAN_BIT_REG(5, 4, 2, 5)
#else
#error Invalid CAN_BIT_RATE value used with a 1MHz crystal.
#endif

//*****************************************************************************
//
// An unsupported crystal frequency was specified.
//
//*****************************************************************************
#else
#error The CRYSTAL_FREQ value is not supported by the CAN controller.
#endif

#endif

#endif // __BL_CAN_TIMING_H__
