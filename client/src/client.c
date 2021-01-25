#include "../inc/header.h"


int main(int argc, char **argv) {

// --- Checking IP & Port No ---

    static client_t client;
    client_t *p_client = (client_t *)malloc(sizeof(client_t *));
    p_client = &client;
    GObject *connect_b;
    gtk_init(&argc, &argv);

    /* По максимуму надо уменьшить мейн и разнести все по функциям
    * Функция, которая инициализирует потоки
    * Функция, которая инициализирует интерфейс
    * Главная суть в том, чтобы интерфейс и код клиента были связаны по минимуму,
    * через переключатели, функции и т.п.
    * Это нужно для того, чтобы можно было заниматься отдельно кодом клиента и отдельно интерфейсом,
    * а не ломать одно, чтобы построить другое.
    */
    init_interface(&builder, &window);
    init_connect_page(&connect_b, &builder, (gpointer) p_client);
    gtk_widget_show(window);
    gtk_main();

	exit(0);
	return EXIT_SUCCESS;
}
