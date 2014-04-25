STM32F4-Discovery-FreeRTOS-GCC
==============================

Porting FreeRTOS on STM32F4-Discovery using GCC on linux


1. git clone https://github.com/vagabondtt1503/STM32F4-Discovery-FreeRTOS-GCC
2. . ../build.env 
3. make  // 產生 obj資料夾 STM32F4_Test.bin
4. st-flash write STM32F4_Test.bin 0x8000000  // 把image燒錄到板子

// 使用gdb
5. st-util   // Run gdbserver by st-link utility
6. arm-none-eabi-gdb
7. (gdb) target remote localhost:4242
8. (gdb) load STM32F4_Test.elf
9. (gdb) continue

