#include "../inc/header.h"

void str_trim_lf (char* arr, int length) {
  int i;
  for (i = 0; i < length; i++) { 
    if (arr[i] == '\n') {
      arr[i] = '\0';
      break;
    }
  }
}

void print_client_addr(struct sockaddr_in addr){
    printf("%d.%d.%d.%d",
        addr.sin_addr.s_addr & 0xff,
        (addr.sin_addr.s_addr & 0xff00) >> 8,
        (addr.sin_addr.s_addr & 0xff0000) >> 16,
        (addr.sin_addr.s_addr & 0xff000000) >> 24);
}

char* itoa(int num, char* buffer, int base) {
    int curr = 0;
 
    if (num == 0) {
        buffer[curr++] = '0';
        buffer[curr] = '\0';
        return buffer;
    }
 
    int num_digits = 0;
 
    if (num < 0) {
        if (base == 10) {
            num_digits ++;
            buffer[curr] = '-';
            curr ++;
            num *= -1;
        }
        else
            return NULL;
    }
 
    num_digits += (int)floor(log(num) / log(base)) + 1;

    while (curr < num_digits) {
        int base_val = (int) pow(base, num_digits-1-curr);

        int num_val = num / base_val;
 
        char value = num_val + '0';
        buffer[curr] = value;
 
        curr ++;
        num -= base_val * num_val;
    }
    buffer[curr] = '\0';
    return buffer;
}

char *mx_strnew(const int size) {
    int i = 0;

    if (size < 0)
        return 0;
    char *str = (char *)malloc(size + 1);
    while (i < size) {
        str[i] = '\0';
        i++;
    }
    str[i] = '\0';
    return str;
}
