/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** my_ftp.h
*/

#ifndef MY_FTP_H_
    #define MY_FTP_H_

#include "my_ftp_struct.h"
#include "my_ftp_commands.h"
#include <signal.h>

#define SUCCESS 0
#define FAILURE 84
#define ERROR -1

#define FTP_CRLF "\r\n"
#define FTP_SP  " "

extern volatile sig_atomic_t running;
extern command_t const commands[];

void stop_server(int __attribute__((unused))sig);
void kill_child(int __attribute__((unused))sig);

int server(int port, char const * path);
void remove_client(struct pollfd *fds, int *fds_index, int i);
int create_socket(void);
my_ftp_t* init_server(int port, char const * path);
void destroy_server(my_ftp_t* server);

int exec_command(my_ftp_t* server);
void command_reply(my_ftp_t* server, size_t code, char reply[]);

#endif /* MY_FTP_H_ */
