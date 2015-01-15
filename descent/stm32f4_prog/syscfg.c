#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_rcc.h"

/**
  * @brief  Selects the GPIO pin used as EXTI Line.
  * @param  EXTI_PortSourceGPIOx : selects the GPIO port to be used as source for
  *          EXTI lines where x can be (A..I).
  * @param  EXTI_PinSourcex: specifies the EXTI line to be configured.
  *           This parameter can be EXTI_PinSourcex where x can be (0..15, except
  *           for EXTI_PortSourceGPIOI x can be (0..11).
  * @retval None
  */
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex)
{
  uint32_t tmp = 0x00;

#if 0
  /* Check the parameters */
  assert_param(IS_EXTI_PORT_SOURCE(EXTI_PortSourceGPIOx));
  assert_param(IS_EXTI_PIN_SOURCE(EXTI_PinSourcex));
#endif
  tmp = ((uint32_t)0x0F) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03));
  SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] &= ~tmp;
  SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
}

