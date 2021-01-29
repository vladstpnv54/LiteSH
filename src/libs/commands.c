#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include "commands.h"

int create_process(const char *command) {
    int status;
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        execl(SHELL, SHELL, "-c", command, NULL);
        _exit(EXIT_FAILURE);
    } else if (pid < 0) {
        status = -1;
    } else {
        if (waitpid(pid, &status, 0) != pid) {
            status = -1;
        }
    }

    return status;
}

int create_background_process(const char *command) {
    int status = 0;
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        setsid();
        fclose(stdin);
        fclose(stdout);
        fclose(stderr);
        execl(SHELL, SHELL, "-c", command, NULL);
        _exit(EXIT_FAILURE);
    } else if (pid < 0) {
        status = -1;
    }

    return status;
}

int send_signal(pid_t pid, int signum) {
    if (kill(pid, signum) == -1) {
        return 1;
    }

    return 0;
}

void signal_handler(int signumber) {
    printf("\nSignal - %d received successfully (Press Enter...)\n", signumber);
}

int receive_signal(int signumber) {
    if (signal(signumber, signal_handler) == SIG_ERR) {
        return 1;
    }

    return 0;
}
