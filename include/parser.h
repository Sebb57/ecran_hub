/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** parser.h
*/

#ifndef PARSER_H_
    #define PARSER_H_

#include <stdbool.h>

typedef struct {
    char* path;
    int port;
} parser_t;

bool parse(int const ac, char const * const av[], parser_t* parser);
parser_t* init_parser(void);
void destroy_parser(parser_t* parser);

#endif /* PARSER_H_ */
