/*
MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 128K
  SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}
*/

/* Specify the memory areas */
/* form: STM32F4-Discovery_FW_V1.1.0/Project/Peripheral_Examples/IO_Toggle/TrueSTUDIO/IO_Toggle/stm32_flash.ld */
MEMORY
{
  FLASH (rx)      : ORIGIN = 0x00000000, LENGTH = 1024K
  SRAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 192K
  MEMORY_B1 (rx)  : ORIGIN = 0x60000000, LENGTH = 0K
}


SECTIONS
{
  .text :
  {
    KEEP(*(.isr_vector .isr_vector.*))
    *(.text .text.*)
    *(.rodata .rodata*)
    _etext = .;
  } > FLASH

  /* .ARM.exidx is sorted, so has to go in its own output section.  
        __exidx_start = .;
        .ARM.exidx :
        {
                *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        } >FLASH
        __exidx_end = .;
     if no -fno-exceptions -fno-rtti, g++ will procude the sections
  */

  .data : AT (_etext)
  {
    _data = .;
    *(.data .data.*)
    _edata = .;
  } > SRAM
  .bss(NOLOAD) :
  {
    _bss = .;
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > SRAM




  .stackarea(NOLOAD) :
  {
    . = ALIGN(8);
    *(.stackarea .stackares.*)
    . = ALIGN(8);
  } > SRAM

  . = ALIGN(4);
  _end = .;
}
