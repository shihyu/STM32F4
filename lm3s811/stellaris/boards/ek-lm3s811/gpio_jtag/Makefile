#******************************************************************************
#
# Makefile - Rules for building the gpio_jtag example.
#
# Copyright (c) 2006-2009 Luminary Micro, Inc.  All rights reserved.
# Software License Agreement
# 
# Luminary Micro, Inc. (LMI) is supplying this software for use solely and
# exclusively on LMI's microcontroller products.
# 
# The software is owned by LMI and/or its suppliers, and is protected under
# applicable copyright laws.  All rights are reserved.  You may not combine
# this software with "viral" open-source software in order to form a larger
# program.  Any use in violation of the foregoing restrictions may subject
# the user to criminal sanctions under applicable laws, as well as to civil
# liability for the breach of the terms and conditions of this license.
# 
# THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
# OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
# LMI SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
# CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
# 
# This is part of revision 5125 of the EK-LM3S811 Firmware Package.
#
#******************************************************************************

#
# Defines the part type that this project uses.
#
PART=LM3S811

#
# The base directory for DriverLib.
#
ROOT=../../..

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

#
# Where to find source files that do not live in this directory.
#
VPATH=../drivers

#
# Where to find header files that do not live in the source directory.
#
IPATH=..
IPATH+=../../..

#
# The default rule, which causes the gpio_jtag example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/gpio_jtag.axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir ${COMPILER}

#
# Rules for building the gpio_jtag example.
#
${COMPILER}/gpio_jtag.axf: ${COMPILER}/display96x16x1.o
${COMPILER}/gpio_jtag.axf: ${COMPILER}/gpio_jtag.o
${COMPILER}/gpio_jtag.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/gpio_jtag.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
ifeq (${COMPILER}, gcc)
${COMPILER}/gpio_jtag.axf: gpio_jtag.ld
endif
SCATTERgcc_gpio_jtag=gpio_jtag.ld
ifeq (${COMPILER}, sourcerygxx)
${COMPILER}/gpio_jtag.axf: gpio_jtag_sourcerygxx.ld
endif
SCATTERsourcerygxx_gpio_jtag=lm3s811-rom.ld -T gpio_jtag_sourcerygxx.ld
ENTRY_gpio_jtag=ResetISR

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
