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

int validate_ip(char *ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result;
}


int validate_port(char *port) {
	int port_len = strlen(port);
	if (port_len > 6 || port_len < 3) {
		return 0;
	}
	if (!validate_number(port)) {
		return 0;
	}
	return 1;
}
