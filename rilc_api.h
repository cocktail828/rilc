#ifndef __RILC
#define __RILC

int RILC_init(const char *device);
int RILC_uninit();
int RILC_requestIMSI();
int RILC_sendEnvelope(const char *);
int RILC_onUnsocial(void *);
#endif //__RILC
