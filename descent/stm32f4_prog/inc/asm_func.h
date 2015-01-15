#ifndef ASM_FUNC_H
#define ASM_FUNC_H

#ifdef __cplusplus
extern "C"
{
#endif
void run(char* sp);
void asm_init_systick();
void pendsv_isr(void);
void svc_isr(void);
#ifdef __cplusplus
}
#endif

#endif
