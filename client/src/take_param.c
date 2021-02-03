#include "../inc/header.h"

char *take_param(char *params, int number) {
    char *result = NULL;
    char *start = strchr(params, '<');
    char *end = strchr(params, '>');
    int length = strlen(start) - strlen(end) - 1;
    result = strndup(&start[1], length);
	number--;
	while (number != 0)
	{
		number--;
        start = strchr(end, '<');
        end = strchr(&end[1], '>');
        length = strlen(start) - strlen(end) - 1;
        result = strndup(&start[1], length);
	}
    return result;
}
