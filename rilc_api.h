#ifndef __RILC
#define __RILC

int RILC_init(const char *device);
int RILC_uninit();
int RILC_requestIMEI();
int RILC_requestIMSI();

void RILC_TEST_REQ();
#endif //__RILC
