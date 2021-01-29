#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // to read and sleep
#include <netinet/in.h>
#include "libs/erproc.h"
#include "libs/commands.h"

int main() {
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34545); // port to listen
    Bind(server, (struct sockaddr *) &adr, sizeof adr);    // connect socket to adress

    Listen(server, 5); // just listen client
    socklen_t adrlen = sizeof adr;
    int fd = Accept(server, (struct sockaddr *) &adr, &adrlen); // bind save old value of adr, now we can change adr value

    char *choice = malloc(sizeof(char) * 256);
    char *rmessage = malloc(sizeof(char) * 256);
    char *rrmessage = malloc(sizeof(char) * 256);

    ssize_t nread;
    int quit = 0;
    while (!quit) {
        //Recv choice
        nread = recv(fd, choice, 1, 0);
        if (nread == -1) {
            perror("Recv failed");
            exit(EXIT_FAILURE);
        }
        if (nread == 0) {
            printf("END OF FILE occured\n");
        }

        if (!strcmp(choice, "1")) {
            //Send "Enter rmessage of process:"
            send(fd, "Enter name of process: ", 24, 0);
            //Recv rmessage of process
            nread = recv(fd, rmessage, 256, 0);
            if (nread == -1) {
                perror("Recv failed");
                exit(EXIT_FAILURE);
            }
            if (nread == 0) {
                printf("END OF FILE occured\n");
            }
            rmessage[nread] = '\0';
            printf("1. Name of process = %s\n", rmessage);

            //Create process
            create_process(rmessage);
            //Send "Process closed"
            send(fd, "Procces closed\n", 16, 0);
            printf("-1. Name of process = %s\n", rmessage);

        } else if (!strcmp(choice, "2")) {
            //Send "Enter name of silent process:"
            send(fd, "Enter name of silent process: ", 31, 0);
            //Recv rmessage of silent process
            nread = recv(fd, rmessage, 256, 0);
            if (nread == -1) {
                perror("Recv failed");
                exit(EXIT_FAILURE);
            }
            if (nread == 0) {
                printf("END OF FILE occured\n");
            }
            printf("2. Name of silent process = %s\n", rmessage);

            //Create background process
            create_background_process(rmessage);
            //Send "Procces created"
            send(fd, "Procces created\n", 17, 0);
            printf("~2. Name of process = %s\n", rmessage);

        } else if (!strcmp(choice, "3")) {
            //Send "Enter PID:"
            send(fd, "Enter PID: ", 12, 0);
            //Recv PID of process
            nread = read(fd, rmessage, 256);
            if (nread == -1) {
                perror("Recv failed");
                exit(EXIT_FAILURE);
            }
            if (nread == 0) {
                printf("END OF FILE occured\n");
            }
            rmessage[nread] = '\0';
            printf("3. PID = %s\n", rmessage);

            //Send "Enter signal:"
            send(fd, "Enter signal: ", 15, 0);
            //Recv signal
            nread = read(fd, rrmessage, 256);
            if (nread == -1) {
                perror("Recv failed");
                exit(EXIT_FAILURE);
            }
            if (nread == 0) {
                printf("END OF FILE occured\n");
            }
            rrmessage[nread] = '\0';
            printf("3. Signal = %s\n", rrmessage);

            //Send signal
            send_signal(atoi(rmessage), atoi(rrmessage));
            //Send "Signal sent"
            send(fd, "Signal sent\n", 13, 0);
            printf("~3. PID = %s, Signal = %s\n", rmessage, rrmessage);

        } else if (!strcmp(choice, "4")) {
            //Send "Enter signal:"
            send(fd, "Enter signal: ", 15, 0);
            //Recv signal
            nread = recv(fd, rmessage, 256, 0);
            if (nread == -1) {
                perror("Recv failed");
                exit(EXIT_FAILURE);
            }
            if (nread == 0) {
                printf("END OF FILE occured\n");
            }
            rmessage[nread] = '\0';
            printf("4. Signal = %s\n", rmessage);

            //Receive signal
            if (receive_signal(atoi(rmessage)) == 1) {
                printf("Failed to receive signal\n");
            }
            //Send "Process recieve signal"
            send(fd, "Process recieve signal\n", 24, 0);
            printf("~4. Signal = %s\n", rmessage);

        } else {
            quit++;
        }
    }

    free(choice);
    free(rmessage);
    free(rrmessage);

    sleep(5);

    close(fd);
    close(server);

    return 0;
}
