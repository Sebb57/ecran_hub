/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** my_ftp_commands.h
*/

#ifndef MY_FTP_COMMANDS_H_
    #define MY_FTP_COMMANDS_H_

#include "my_ftp_struct.h"

typedef enum {
    CMD_UNKNOWN,
    CMD_QUIT,
} command_type_t;

typedef struct {
    command_type_t type;
    int (*func)(my_ftp_t *);
} command_t;

int unknown(my_ftp_t* server);
int quit(my_ftp_t* server);

#endif /* MY_FTP_COMMANDS_H_ */
