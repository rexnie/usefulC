#ifndef __STACK_H

#ifndef MAX_VAL
#define MAX_VAL 64
#endif

extern int init_stack(void);
extern int push(char ch);
extern char pop(void);
extern int get_stack_size(void);
extern int get_element_num_in_stack(void);

#endif //__STACK_H
