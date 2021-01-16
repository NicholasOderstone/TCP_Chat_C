#include "../inc/module_one.h"

void *get_cmd() {

	return NULL;
}

void *make_msg() {
	//sleep (10);
	while(1) {

	}

	return NULL;
}



int main() {
	pthread_t th_read_msg;
	pthread_t th_make_cmd;

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("Mutex initialization failed.\n");
        return 1;
    }
	if (pthread_mutex_init(&print_lock, NULL) != 0)
    {
        printf("Mutex initialization failed.\n");
        return 1;
    }

    return 0;
}
