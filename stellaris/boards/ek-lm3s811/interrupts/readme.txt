Interrupts

This example application demonstrates the interrupt preemption and
tail-chaining capabilities of Cortex-M3 microprocessor and NVIC.  Nested
interrupts are synthesized when the interrupts have the same priority,
increasing priorities, and decreasing priorities.  With increasing
priorities, preemption will occur; in the other two cases tail-chaining
will occur.  The currently pending interrupts and the currently executing
interrupt will be displayed on the LCD; GPIO pins D0 through D2 will be
asserted upon interrupt handler entry and de-asserted before interrupt
handler exit so that the off-to-on time can be observed with a scope or
logic analyzer to see the speed of tail-chaining (for the two cases where
tail-chaining is occurring).

-------------------------------------------------------------------------------

Copyright (c) 2005-2009 Luminary Micro, Inc.  All rights reserved.
Software License Agreement

Luminary Micro, Inc. (LMI) is supplying this software for use solely and
exclusively on LMI's microcontroller products.

The software is owned by LMI and/or its suppliers, and is protected under
applicable copyright laws.  All rights are reserved.  You may not combine
this software with "viral" open-source software in order to form a larger
program.  Any use in violation of the foregoing restrictions may subject
the user to criminal sanctions under applicable laws, as well as to civil
liability for the breach of the terms and conditions of this license.

THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
LMI SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

This is part of revision 5125 of the EK-LM3S811 Firmware Package.
