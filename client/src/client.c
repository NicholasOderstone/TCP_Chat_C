#include "../inc/header.h"

int main(int argc, char **argv) {
    static client_t client;
    client_t *p_client = (client_t *)malloc(sizeof(client_t *));
    p_client = &client;

    init_interface(&builder, &argc, &argv, (gpointer) p_client);
    init_switches();

    if (pthread_mutex_init(&chat_lock, NULL) != 0) {
      printf("Mutex initialization failed.\n");
      return 1;
    }

    if (pthread_mutex_init(&msg_id_lock, NULL) != 0) {
      printf("Mutex initialization failed.\n");
      return 1;
    }

    if (pthread_mutex_init(&add_chat_lock, NULL) != 0) {
      printf("Mutex initialization failed.\n");
      return 1;
    }

    pthread_t init_threads_thread;
	if(pthread_create(&init_threads_thread, NULL, init_threads, (void*)p_client) != 0){
		perror("ERROR: pthread\n");
		return 1;
	}

    gtk_main();

    client.exit = 1;
	close(client.sockfd);
    pthread_join(init_threads_thread, NULL);
	pthread_mutex_destroy(&client.mutex);

	exit(0);
	return EXIT_SUCCESS;
}
