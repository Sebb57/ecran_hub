/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** my_ftp_struct.h
*/

#ifndef MY_FTP_STRUCT_H_
    #define MY_FTP_STRUCT_H_

#include <netinet/in.h>
#include <sys/poll.h>
#include <sys/socket.h>

#define MAX_SIZE 50

typedef struct {
    int port;
    char* path;
    int sfd;
    int cfd;
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;
    struct pollfd fds[MAX_SIZE];
    int fds_index;
    int loop_index;
} my_ftp_t;

#endif /* MY_FTP_STRUCT_H_ */
