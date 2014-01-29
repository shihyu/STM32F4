EK-LM3S811 Quickstart Application

A game in which a ship is navigated through an endless tunnel.  The
potentiometer is used to move the ship up and down, and the user push
button is used to fire a missile to destroy obstacles in the tunnel.  Score
accumulates for survival and for destroying obstacles.  The game lasts for
only one ship; the score is displayed on the virtual UART at 115,200, 8-N-1
during game play and will be displayed on the screen at the end of the
game.

Since the OLED display on the evaluation board has burn-in characteristics
similar to a CRT, the application also contains a screen saver.  The screen
saver will only become active if two minutes have passed without the user
push button being pressed while waiting to start the game (that is, it will
never come on during game play).  An implementation of the Game of Life is
run with a field of random data as the seed value.

After two minutes of running the screen saver, the display will be turned
off and the user LED will blink.  Either mode of screen saver (Game of Life
or blank display) will be exited by pressing the user push button.  The
button will then need to be pressed again to start the game.

-------------------------------------------------------------------------------

Copyright (c) 2006-2009 Luminary Micro, Inc.  All rights reserved.
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
