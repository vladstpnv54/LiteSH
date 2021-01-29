#ifndef COMMANDS_H
#define COMMANDS_H

#define SHELL "/bin/sh"

int create_process(const char *command);

int create_background_process(const char *command); 

int send_signal(pid_t pid, int signum); 

void signal_handler(int signumber); 

int receive_signal(int signumber); 

#endif
