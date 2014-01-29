#******************************************************************************
#
# Makefile - Rules for building the qs_ek-lm3s811 example.
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
# The default rule, which causes the qs_ek-lm3s811 example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/qs_ek-lm3s811.axf

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
# Rules for building the qs_ek-lm3s811 example.
#
${COMPILER}/qs_ek-lm3s811.axf: ${COMPILER}/display96x16x1.o
${COMPILER}/qs_ek-lm3s811.axf: ${COMPILER}/game.o
${COMPILER}/qs_ek-lm3s811.axf: ${COMPILER}/qs_ek-lm3s811.o
${COMPILER}/qs_ek-lm3s811.axf: ${COMPILER}/random.o
${COMPILER}/qs_ek-lm3s811.axf: ${COMPILER}/screen_saver.o
${COMPILER}/qs_ek-lm3s811.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/qs_ek-lm3s811.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
ifeq (${COMPILER}, gcc)
${COMPILER}/qs_ek-lm3s811.axf: qs_ek-lm3s811.ld
endif
SCATTERgcc_qs_ek-lm3s811=qs_ek-lm3s811.ld
ifeq (${COMPILER}, sourcerygxx)
${COMPILER}/qs_ek-lm3s811.axf: qs_ek-lm3s811_sourcerygxx.ld
endif
SCATTERsourcerygxx_qs_ek-lm3s811=lm3s811-rom.ld -T qs_ek-lm3s811_sourcerygxx.ld
ENTRY_qs_ek-lm3s811=ResetISR

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
