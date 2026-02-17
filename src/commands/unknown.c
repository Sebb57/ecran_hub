#include "my_ftp.h"
#include <stdio.h>

int unknown(my_ftp_t* server)
{
    if (!server)
        return FAILURE;
    dprintf(server->fds[server->loop_index].fd, "Unknown command\n");
    return SUCCESS;
}
