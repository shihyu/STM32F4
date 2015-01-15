// mpu test
#include "stm32.h"
#include "type.h"

#define MPU_TYPE_REG_ADDR 0xe000ed90
#define MPU_TYPE_REG (*((u32 volatile *)MPU_TYPE_REG_ADDR))

#define MPU_CTRL_REG_ADDR 0xe000ed94
#define MPU_CTRL_REG (*((u32 volatile *)MPU_CTRL_REG_ADDR))

#define MPU_NUM_REG_ADDR 0xe000ed98
#define MPU_NUM_REG (*((u32 volatile *)MPU_NUM_REG_ADDR))

#define MPU_BASE_REG_ADDR 0xe000ed9c
#define MPU_BASE_REG (*((u32 volatile *)MPU_BASE_REG_ADDR))

#define MPU_ATTR_SIZE_REG_ADDR 0xe000eda0
#define MPU_ATTR_SIZE_REG (*((u32 volatile *)MPU_ATTR_SIZE_REG_ADDR))

extern u32 mpu_reg1_begin_;
extern u32 mpu_reg1_end_;

extern u32 mpu_reg2_begin_, mpu_reg2_end_;

__attribute__ ((section (".mpu_r1")))
int reg1[256];

__attribute__ ((section (".mpu_r2")))
void test_mpu()
{
  int i=1;
  ++i;
}

bool init_mpu();

// ref: http://blog.feabhas.com/2013/02/setting-up-the-cortex-m34-armv7-m-memory-protection-unit-mpu/
// mymain is extern "C" declare
void mymain()
{
  SYSTEM_HANDLER_CTRL_STATE_REG |= (1 << 16); // enable mem-fault exception
  init_mpu();
  reg1[0] = 10;
  //int a = reg1[0];
  //test_mpu();
  int i=5;
  while(1)
  {
    i++;
  }
}


// ref: arm cortex-m3: 嵌入式系統設計入門 p13-9
bool init_mpu()
{
  // ref: Cortex™-M3 Technical Reference Manual 9.2 (file name: DDI0337E_cortex_m3_r1p1_trm.pdf)
  // in stm32f4discovery the value is 0x800
  // so there are 8 regions
  // qemu-system-arm -M lm3s6965evb -kernel list.bin -S -gdb tcp::1234
  // the mpu_type is 0x0
#if 0
  u32 volatile *mpu_type_reg_addr = (u32*)0xe000ed90; 
  if (*mpu_type_reg_addr == 0) // there is no mpu
    return false;
#endif

  if (MPU_TYPE_REG == 0) // there is no mpu
    return false;

  // base 0x0, 4g size
  MPU_NUM_REG = 0;
  MPU_BASE_REG = 0;
  MPU_ATTR_SIZE_REG = 0x307003f;
  //(*((u32 volatile *)MPU_BASE_REG_ADDR)) = 0x307002f;
  MPU_NUM_REG = 1;
  MPU_BASE_REG = (u32)&mpu_reg1_begin_;
  MPU_ATTR_SIZE_REG = 0x707000F; // read only
  //MPU_ATTR_SIZE_REG = 0x307000F; // r/w
  // ap: 111 read only
  // size: 256 byte
  // S: 1, C: 1, B: 1
  // TEX: 000

#if 0
  MPU_NUM_REG = 2;
  MPU_BASE_REG = (u32)&mpu_reg2_begin_;
  MPU_ATTR_SIZE_REG = 0x1007000F;
  // disable execute
#endif

  MPU_CTRL_REG = 1; // enable MPU

  __asm__ ("isb");
  __asm__ ("dsb");

  return true;
}

