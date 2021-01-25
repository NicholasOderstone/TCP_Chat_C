#include "../inc/header.h"

int validate_number(char *str) {
   while (*str) {
      if (!isdigit(*str)) { //if the character is not a number, return false
         return 0;
      }
      str++; //point to next character
   }
   return 1;
}
