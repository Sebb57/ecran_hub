#include "my_ftp.h"
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "reply.h"

volatile sig_atomic_t running = 1;

int create_socket()
{
    int domain = AF_INET;
    int type = SOCK_STREAM;
    int protocol = 0;

    return socket(domain, type, protocol);
}

void remove_client(struct pollfd *fds, int *fds_index, int to_delete)
{
    close(fds[to_delete].fd);
    fds[to_delete] = fds[*fds_index - 1];
    (*fds_index)--;
}

static void add_to_poll(my_ftp_t* server)
{
    socklen_t len = sizeof(server->cliaddr);
    server->cfd = accept(server->sfd, (struct sockaddr*)&server->cliaddr, &len);
    if (server->cfd != -1 && server->fds_index < MAX_SIZE) {
        server->fds[server->fds_index].fd = server->cfd;
        server->fds[server->fds_index].events = POLLIN;
        server->fds_index++;
        dprintf(server->cfd, "%d" FTP_SP "%s" FTP_CRLF, CONNECTION_CODE, CONNECTION_REPLY);
        dprintf(server->fds[server->fds_index].fd, "Connection from: %s:%d\n", 
                inet_ntoa(server->cliaddr.sin_addr), ntohs(server->cliaddr.sin_port));
    }
}

int server(int port, char const * path)
{
    my_ftp_t* server = init_server(port, path);

    if (!server)
        return printf("null server\n"), FAILURE;
    if (server->sfd == ERROR)
        return printf("socket create err\n"), FAILURE;
    if (bind(server->sfd, (struct sockaddr*)&server->servaddr, sizeof(server->servaddr)) == ERROR)
        return printf("bind err\n"), FAILURE;
    if (listen(server->sfd, MAX_SIZE) == ERROR)
        return printf("listen err\n"), FAILURE;

    while (running) {
        poll(server->fds, server->fds_index, -1);
        
        for (server->loop_index = 0; server->loop_index < server->fds_index; server->loop_index++) {
            if (!(server->fds[server->loop_index].revents & POLLIN))
                continue;
            if (server->fds[server->loop_index].fd == server->sfd)
                add_to_poll(server);
            else if (exec_command(server) == ERROR)
                dprintf(server->fds[server->loop_index].fd, "Error executing command\n");
        }
        usleep(500);
    }
    close(server->fds[0].fd);
    destroy_server(server);
    return SUCCESS;
}
