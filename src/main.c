/*
** EPITECH PROJECT, 2026
** bs
** File description:
** bs.c
*/

#include <stdlib.h>
#include "my_ftp.h"
#include "parser.h"

int main(int ac, char const * const av[])
{
    parser_t *parser = init_parser();
    int ret_val = 0;
    if (!parser)
        return FAILURE;
    signal(SIGCHLD, kill_child);
    signal(SIGINT, stop_server);
    if (!parse(ac, av, parser))
        return FAILURE;
    if (parser->path)
        ret_val = server(parser->port, parser->path);
    destroy_parser(parser);
    return ret_val;
}
