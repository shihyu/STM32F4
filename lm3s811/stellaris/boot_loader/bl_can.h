//*****************************************************************************
//
// bl_can.h - Definitions for the CAN transport functions.
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

#ifndef __BL_CAN_H__
#define __BL_CAN_H__

//*****************************************************************************
//
// These defines are used to define the range of values that are used for
// the Luminary Micro CAN update protocol.
//
//*****************************************************************************
#define CAN_MSGID_DTYPE_UPDATE  0x1f000000
#define CAN_MSGID_MFR_LM        0x00020000

//*****************************************************************************
//
// The masks of the fields that are used in the message identifier.
//
//*****************************************************************************
#define CAN_MSGID_DEVNO_M       0x0000003f
#define CAN_MSGID_API_M         0x0000ffc0
#define CAN_MSGID_MFR_M         0x00ff0000
#define CAN_MSGID_DTYPE_M       0x1f000000
#define CAN_MSGID_DEVNO_S       0
#define CAN_MSGID_API_S         6
#define CAN_MSGID_MFR_S         16
#define CAN_MSGID_DTYPE_S       24

//*****************************************************************************
//
// The Luminary Micro Motor Class Firmware Update API definitions.
//
//*****************************************************************************
#define LM_API_UPD              (CAN_MSGID_MFR_LM | CAN_MSGID_DTYPE_UPDATE)
#define LM_API_UPD_PING         (LM_API_UPD | (0 << CAN_MSGID_API_S))
#define LM_API_UPD_DOWNLOAD     (LM_API_UPD | (1 << CAN_MSGID_API_S))
#define LM_API_UPD_SEND_DATA    (LM_API_UPD | (2 << CAN_MSGID_API_S))
#define LM_API_UPD_RESET        (LM_API_UPD | (3 << CAN_MSGID_API_S))
#define LM_API_UPD_ACK          (LM_API_UPD | (4 << CAN_MSGID_API_S))

#endif // __BL_CAN_H__
