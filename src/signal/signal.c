#include "my_ftp.h"
#include <string.h>
#include <sys/wait.h>

void stop_server(int __attribute__((unused))sig)
{
    running = 0;
}

void kill_child(int __attribute__((unused))sig)
{
    (void)sig;
    while (waitpid(-1, NULL, WNOHANG) > 0);
}
