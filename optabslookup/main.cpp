#include "pch.h"
#include <iostream>
#include "optabslookup.h"

int main()
{
   char out = brightness_abs(0, 0);
   out = brightness_abs(0, 1);
   out = brightness_abs(0, 2);
   out = brightness_abs(0, 3);
   out = brightness_abs(0, 4);
   out = brightness_abs(0, 5);
   out = brightness_abs(0, 100);
   out = brightness_abs(0, -1);
   out = brightness_abs(0, -2);
   out = brightness_abs(0, -3);
   out = brightness_abs(0, -4);
   out = brightness_abs(0, -5);
   out = brightness_abs(0, -100);
}