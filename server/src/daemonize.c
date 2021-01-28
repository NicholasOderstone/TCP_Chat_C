#include "../inc/header.h"

static pid_t signal_dir(pid_t pid) {
    struct sigaction sa;

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        printf("./uchat_server: immposible to ignore signal SIGHUP");
        exit(EXIT_FAILURE);
    }
    if ((pid = fork()) < 0){
        printf("./uchat_server: error fork");
        exit(EXIT_FAILURE);
    }
    else if (pid != 0) // Close parent process.
        exit(EXIT_SUCCESS);
    chdir(getenv("PWD"));
    return getpid();
}

void daemonize() {
    int fd;
    pid_t pid;
    pid_t sed;

    if ((pid = fork()) < 0) {  // Become the leader to lose the managem. termin.
        printf("./uchat_server: error fork");
        exit(EXIT_FAILURE);
    }
    else if (pid != 0) {  // Close parent process.
        exit(EXIT_SUCCESS);
    }
    umask(0);
    if ((sed = setsid()) < 0) {
        printf("2\n");
        exit(EXIT_FAILURE);
    }
    printf("server id -> %d\n", pid);
    pid = signal_dir(pid);
    printf("server id -> %d\n", pid);
    //auditor_lol_2(dir);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    fd = open("uchat_server.log", O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, S_IRWXU);
    dup2(fd, 1);
    dup2(fd, 2);
    close(fd);
}
