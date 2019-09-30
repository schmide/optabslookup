#ifndef _OPTABSLOOKUP
#define _OPTABSLOOKUP_EXTERN 
#endif

_OPTABSLOOKUP_EXTERN unsigned char brightness_bitmask(const char led, const char pos);
_OPTABSLOOKUP_EXTERN unsigned char brightness_abs(char led, char pos);


#ifndef _OPTABSLOOKUP
#define _OPTABSLOOKUP
#undef _OPTABSLOOKUP_EXTERN
#define _OPTABSLOOKUP_EXTERN extern
#endif


