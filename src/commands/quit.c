#include "my_ftp.h"
#include "reply.h"

int quit(my_ftp_t* server)
{
    if (!server)
        return FAILURE;
    command_reply(server, QUIT_CODE, QUIT_RELPY);
    remove_client(server->fds, &server->fds_index, server->loop_index);
    return SUCCESS;
}
