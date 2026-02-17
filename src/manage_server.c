#include "my_ftp.h"
#include <stdlib.h>
#include<string.h>

my_ftp_t* init_server(int port, char const * path)
{
    my_ftp_t* server = malloc(sizeof(my_ftp_t));

    if (!server || !path)
        return NULL;
    server->path = strdup(path);
    if (!server->path)
        return NULL;
    server->port = port;
    server->sfd = create_socket();
    server->cfd = 0;
    memset(&server->servaddr, 0, sizeof(server->servaddr));
    server->servaddr.sin_family = AF_INET;
    server->servaddr.sin_addr.s_addr = INADDR_ANY;
    server->servaddr.sin_port = htons(port);
    memset(&server->cliaddr, 0, sizeof(server->cliaddr));
    memset(&server->fds, 0, sizeof(server->fds));
    server->fds[0].fd = server->sfd;
    server->fds[0].events = POLLIN;
    server->fds_index = 1;
    server->loop_index = 0;
    return server; 
}

void destroy_server(my_ftp_t* server)
{
    if (!server || !server->path)
        return;
    free(server->path);
    free(server);
}
