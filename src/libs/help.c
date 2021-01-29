#include <stdio.h>

void print_help() {
    printf("\033[2J");
    printf("\033[0;0f");
    printf("/This programm can send and receive signals to/from processes\n"
            "/and create processes.\n"
            ".To create process enter 1, next type the name of process\n"
            " programm create process with this command.\n"
            " (Enter name of programm on your computer)\n"
            ".To create background process enter 2, type name\n"
            " programm do the same things as create ordionary process,\n"
            " but created process will running on another thread.\n"
            " (Enter name of programm on your computer)\n"
            ".To send signal enter 3, type Process ID, and number of\n"
            " signal.\n"
            "     PID: 777777\n"
            "    Signal: 15)\n"
            ".To receive signal enter 4, type number of signal, when\n"
            " process receive this signal, you will see message -\n"
            " \"Signal - {number of signal} received successfully\"\n"
            ".To get help enter 5.\n"
            ".To exit enter 6.\n"
            "Authors: Stepanov Vlad.\n");
    printf("Press Enter...\n");
    getchar();
}
