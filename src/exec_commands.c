#include "my_ftp.h"
#include "my_ftp_commands.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

static command_type_t parse_command(const char *buf)
{
    if (strncmp(buf, "QUIT", 4) == 0) return CMD_QUIT;
    return CMD_UNKNOWN;
}


static int play_video(const char *url)
{
    static pid_t last_pid = -1;
    if (last_pid > 0) {
        kill(last_pid, SIGTERM);
        last_pid = -1;
    }
    pid_t pid = fork();
    if (pid == 0) {
        setsid(); 
        execlp("mpv",
               "mpv",
               "--really-quiet",
               "--no-terminal",
               "--loop-file=inf",
               url,
               (char *)NULL);
        exit(1);
    }
    if (pid > 0) {
        last_pid = pid;
    }
    return 0;
}

int exec_command(my_ftp_t* server)
{
    char buf[1024];
    ssize_t n = read(server->fds[server->loop_index].fd, buf, sizeof(buf) - 1);
    if (n <= 0) {
        remove_client(server->fds, &server->fds_index, server->loop_index);
        server->loop_index -= 1;
        return ERROR;
    }
    buf[n] = '\0';
    buf[strcspn(buf, "\r\n")] = 0;
    printf("%s\n", buf);
    if (strncmp(buf, "https://", 8) == 0) {
        quit(server);
        return play_video(buf);
    }
    if (strncmp(buf, "q", 1) == 0)
        return quit(server);
    return 0;
}


