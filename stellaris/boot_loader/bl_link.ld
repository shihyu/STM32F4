/******************************************************************************
 *
 * bl_link.ld - Scatter file for Gnu tools
 *
 * Copyright (c) 2007-2009 Luminary Micro, Inc.  All rights reserved.
 * Software License Agreement
 * 
 * Luminary Micro, Inc. (LMI) is supplying this software for use solely and
 * exclusively on LMI's microcontroller products.
 * 
 * The software is owned by LMI and/or its suppliers, and is protected under
 * applicable copyright laws.  All rights are reserved.  You may not combine
 * this software with "viral" open-source software in order to form a larger
 * program.  Any use in violation of the foregoing restrictions may subject
 * the user to criminal sanctions under applicable laws, as well as to civil
 * liability for the breach of the terms and conditions of this license.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * LMI SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 * 
 * This is part of revision 5125 of the Stellaris Firmware Development Package.
 *
 *****************************************************************************/

SECTIONS
{
    .text 0x20000000 : AT (0x00000000)
    {
        _text = .;
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
        _etext = .;
    }

    .data 0x20000000 + SIZEOF(.text) : AT (SIZEOF(.text))
    {
        _data = .;
        *(.data*)
        _edata = .;
    }

    .bss 0x20000000 + SIZEOF(.text) + SIZEOF(.data) :
        AT (ADDR(.data) + SIZEOF(.data))
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    }
}
