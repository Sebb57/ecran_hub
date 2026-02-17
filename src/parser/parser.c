#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

static bool print_help(void)
{
    printf("USAGE: ./myftp port path\n"
           "\tport is the port number on which the server socket listens\n"
           "\tpath is the path to the home directory for the Anonymous use\n"
    );
    return true;
}

parser_t* init_parser(void)
{
    parser_t *parser = malloc(sizeof(parser_t));

    if (!parser)
        return NULL;
    parser->path = NULL;
    parser->port = 0;
    return parser;
}

void destroy_parser(parser_t* parser)
{
    if (!parser)
        return;
    if (parser->path)
        free(parser->path);
    free(parser);
}


static bool parse_inputs(char const * const av[], parser_t* parser) {
    errno = 0;
    char *endptr = NULL;
    long port = strtol(av[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0')
        return fprintf(stderr, "Erorr %s is not a valid number\n", av[1]), false;
    parser->port = port;
    char *path = realpath(av[2], NULL);
    if (!path)
        return fprintf(stderr, "Error getting path"), false;
    parser->path = path;
    return true;
}


bool parse(int const ac, char const * const av[], parser_t* parser)
{
    if (!av || !parser)
        return NULL;
    switch (ac) {
        case 3:
            return parse_inputs(av, parser);
        default:
            return print_help();
    }
}
