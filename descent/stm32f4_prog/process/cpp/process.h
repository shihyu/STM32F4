#ifndef PROCESS_H
#define PROCESS_H

const int MAX_PROC_NUM=10;
extern int cur_proc_num;
typedef void (*FuncPtr)(void);

class Process
{
  public:
    FuncPtr exec;
    char *stack_pointer;  
    int pid_;
    void init_proc(char *stack_ptr, FuncPtr fptr);
    void init_proc(char *stack_ptr);
};

extern Process *ready_process;

#endif
