// https://blog.kriegsman.org/2013/12/01/optimizing-10-lines-of-arduino-code-youre-wrong-so-am-i/

#include "pch.h"
#include "optabslookup.h"

// rules abs maps to 0 to (n-1) outside equals n
char brightness[] = { 32, 16, 6, 2, 1 }; 
char numberBright = sizeof(brightness) - 1;
char shiftNegMask = sizeof(brightness[0]) * 8 - 1;

unsigned char brightness_shiftless_abs(char led, char pos)
{
   char absDiff = led >= pos ? led - pos : pos - led;
   return brightness[ numberBright > absDiff ? absDiff : numberBright];
}

// rules abs maps to 0 to (n-1) outside equals n
char brightness[] = { 32, 16, 6, 2, 1 }; 
char numberBright = sizeof(brightness) - 1;
char shiftNegMask = sizeof(brightness[0]) * 8 - 1;
// 11 operations 1 parallel ~10 * latency
unsigned char brightness_abs(char led, char pos)
{
   char diff = led - pos;
   char negMask = diff >> shiftNegMask;
   char absDiff = (diff ^ negMask) - negMask;
   char outMask = (~(absDiff - numberBright)) >> shiftNegMask; 
   char inVal = absDiff & ~outMask;
   char outVal = numberBright & outMask;
   return brightness[inVal | outVal];
}

// 18 operations 7 parallel ~11 * latency
unsigned char brightness_bitmask(char led, char pos)
{
   char diff = led - pos;
   char negMask = diff >> shiftNegMask;
   char inNegVal = (-diff) & negMask;
   char inPosVal = (~negMask) & diff;
   char posOutMask = (~(diff - numberBright)) >> shiftNegMask; // n or greater
   char negOutMask = (diff + numberBright) >> shiftNegMask; // -n or lesser
   char outMask = posOutMask | negOutMask;
   char outVal = numberBright & outMask;
   char inVal = (~outMask) & (inNegVal | inPosVal);
   return brightness[inVal | outVal];
}

unsigned char brightness_s( const char led, const char pos)
{
   static char bright[] = {1, 2, 6, 16, 32, 16, 6, 2, 1 };
   char adj = 4 + led - pos;
   return bright[(~(adj >> 7)) & (-(adj - 8) >> 7) & adj];
}



unsigned char brightness_13(const char led, const char pos) { 
   char diff; 
   diff = led - pos;
   if( diff < 0 ) diff = -diff;

   // test for the most common case first
   if( diff > 3 )  return 1;
   // then handle all the more special cases
   if( diff == 3)  return 2;
   if( diff == 2)  return 6;
   if( diff == 1)  return 16;
   /* diff == 0 */ return 32;
}
