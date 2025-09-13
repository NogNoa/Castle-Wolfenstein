#define DEV_undefined (byte)  -1
#define DEV_keyboard 0
#define DEV_joystick 1


#ifdef __WATCOMC__
void r_ctrls_load(void);
int w_ctrls_load(void);
void select_monitor(void);
void kb_cnfg(void);
#endif /* __WATCOMC__ */
