#include "../inc/header.h"

char *param_1(char *params) {
    char *start_frst = strchr(params, '<');
    char *end_frst = strchr(params, '>');
    int length_frst = strlen(start_frst) - strlen(end_frst) - 1;
    char *result = strndup(&start_frst[1], length_frst);
    return result;
}

char *param_2(char *params) {
    char *end_frst = strchr(params, '>');
    char *start_scnd = strchr(end_frst, '<');
    char *end_scnd = strchr(&end_frst[1], '>');
    int length_scnd = strlen(start_scnd) - strlen(end_scnd) - 1;
    char *result = strndup(&start_scnd[1], length_scnd);
    return result;
}

char *param_3(char *params) {
    char *end_frst = strchr(params, '>');
    char *end_scnd = strchr(&end_frst[1], '>');
    char *start_thrd = strchr(end_scnd, '<');
    char *end_thrd = strchr(&end_scnd[1], '>');
    int length_thrd = strlen(start_thrd) - strlen(end_thrd) - 1;
    char *result = strndup(&start_thrd[1], length_thrd);
    return result;
}

char *param_4(char *params) {
    char *end_frst = strchr(params, '>');
    char *end_scnd = strchr(&end_frst[1], '>');
    char *end_thrd = strchr(&end_scnd[1], '>');
    char *start_frth = strchr(end_thrd, '<');
    char *end_frth = strchr(&end_thrd[1], '>');
    int length_frth = strlen(start_frth) - strlen(end_frth) - 1;
    char *result = strndup(&start_frth[1], length_frth);
    return result;
}

char *param_5(char *params) {
    char *end_frst = strchr(params, '>');
    char *end_scnd = strchr(&end_frst[1], '>');
    char *end_thrd = strchr(&end_scnd[1], '>');
    char *end_frth = strchr(&end_thrd[1], '>');
    char *start_ffth = strchr(end_frth, '<');
    char *end_ffth = strchr(&end_frth[1], '>');
    int length_ffth = strlen(start_ffth) - strlen(end_ffth) - 1;
    char *result = strndup(&start_ffth[1], length_ffth);
    return result;
}
