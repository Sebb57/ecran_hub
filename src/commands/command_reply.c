#include <stdio.h>
#include "my_ftp.h"

void command_reply(my_ftp_t* server, size_t code, char reply[])
{
    if (!server || !reply)
        return;
    dprintf(server->fds[server->loop_index].fd, "%li" FTP_SP "%s" FTP_CRLF, code, reply);
}
