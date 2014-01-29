#******************************************************************************
#
# Makefile - Rules for building the board specific examples.
#
# Copyright (c) 2007-2009 Luminary Micro, Inc.  All rights reserved.
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
# This is part of revision 5125 of the Stellaris Firmware Development Package.
#
#******************************************************************************

DIRS=dk-lm3s101       \
     dk-lm3s102       \
     dk-lm3s301       \
     dk-lm3s801       \
     dk-lm3s811       \
     dk-lm3s815       \
     dk-lm3s817       \
     dk-lm3s818       \
     dk-lm3s828       \
     dk-lm3s9b96      \
     ek-lm3s811       \
     ek-lm3s1968      \
     ek-lm3s2965_reva \
     ek-lm3s2965      \
     ek-lm3s3748      \
     ek-lm3s6965_reva \
     ek-lm3s6965      \
     ek-lm3s8962      \
     ek-lm3s9b90      \
     ek-lm3s9b92      \
     rdk-acim         \
     rdk-bdc          \
     rdk-bldc         \
     rdk-idm          \
     rdk-idm-l35      \
     rdk-idm-sbc      \
     rdk-s2e          \
     rdk-stepper
DIRS+= rdk-lp-lm3s2b93

all:
	@for i in ${DIRS};                  \
	 do                                 \
	     if [ -d $${i} ];               \
	     then                           \
	         make -C $${i} || exit $$?; \
	     fi;                            \
	 done

clean:
	@for i in ${DIRS};            \
	 do                           \
	     if [ -d $${i} ];         \
	     then                     \
	         make -C $${i} clean; \
	     fi;                      \
	 done
	@rm -f ${wildcard *~} __dummy__
