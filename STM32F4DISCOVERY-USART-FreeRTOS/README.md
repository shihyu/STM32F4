Example Code For Using USART on STM32F4DISCOVERY (Cortex M4-F) Using FreeRTOS
========================

USART example code (check : src/main.c) for STM32F4DISCOVERY. The code was tested on a STM32F4 Discovery board.

Using USART2 on STM32F4DISCOVERY and minicom (or any other serial terminal) this code will loop back the data sent to STM32F4DISCOVERY.

Toolchain
---------

The project is known to work with following toolchains :

* Sourcery G++ Lite 2011.03-42
* summon-arm-toolchain : <https://github.com/esden/summon-arm-toolchain>

Should work fine with other toolchains for Cortex. 

Compiling
---------

Clone the repo and enter the directory. Use following to get .elf & .bin in obj directory.

    $ make

To clean : 

    $ make clean

Running & Debugging
-------

This code was ported to STM32F4DISCOVERY using st-link : <https://github.com/texane/stlink>
Configure and follow instruction at above link on how to flash and debug it.

Credit
------

Credit to Thomas Kindler on sharing FreeRTOS port demo : <https://github.com/thomask77/STM32F4_demo>

License
-------

MIT licensed

Copyright (C) 2013 Chetan Patil, http://chetanpatil.info
