#include "../inc/header.h"

int main(int argc, char **argv) {
    static client_t client;
    client_t *p_client = (client_t *)malloc(sizeof(client_t *));
    p_client = &client;

    if (connect_to_server(p_client, argc, argv) == 1)
        return EXIT_FAILURE;

    init_interface(&argc, &argv, (gpointer) p_client);
    init_switches();

    if (pthread_mutex_init(&chat_lock, NULL) != 0) {
      printf("Mutex initialization failed.\n");
      return EXIT_FAILURE;
    }

    if (pthread_mutex_init(&msg_id_lock, NULL) != 0) {
      printf("Mutex initialization failed.\n");
      return EXIT_FAILURE;
    }

    if (pthread_mutex_init(&add_chat_lock, NULL) != 0) {
      printf("Mutex initialization failed.\n");
      return EXIT_FAILURE;
    }
	sem_exit = sem_open("uchat_sem_exit", O_CREAT, 0666, 0);
	sem_msg_q = sem_open("uchat_sem_msg_q", O_CREAT, 0666, 0);
	sem_cmd_q = sem_open("uchat_sem_cmd_q", O_CREAT, 0666, 0);
	sem_reconnect = sem_open("uchat_sem_reconnect", O_CREAT, 0666, 0);

    pthread_t init_threads_thread;
    if(pthread_create(&init_threads_thread, NULL, init_threads, (void*)p_client) != 0){
      perror("ERROR: pthread\n");
      return EXIT_FAILURE;
    }
    // sleep(100);
    gtk_main();

    client.exit = 1;
    sem_post(sem_exit);
    sem_post(sem_exit);
	close(client.sockfd);
    pthread_join(init_threads_thread, NULL);
	pthread_mutex_destroy(&client.mutex);

    sem_close(sem_exit);
    sem_unlink("uchat_sem_exit");

    sem_close(sem_msg_q);
    sem_unlink("uchat_sem_msg_q");

    sem_close(sem_cmd_q);
    sem_unlink("uchat_sem_cmd_q");
    
    sem_close(sem_reconnect);
    sem_unlink("uchat_sem_reconnect");
	
    exit(0);
    return EXIT_SUCCESS;
}
