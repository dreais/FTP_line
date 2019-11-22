#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../Headers/core_ftp.h"

int send_command(struct pollfd sockets[2], int index, char *CMD, char *args)
{
    char buffer[512];
    short str_size = strlen(CMD) + strlen(args) + 1;
    char *command = malloc(sizeof(char) * (str_size + 1));
    int sent;

    command[str_size] = '\0';
    strcpy(command, CMD);
    command[strlen(CMD)] = ' ';
    strcat(command, args);
    output_logs_str(PREFIX_DEBUG, "Sending '%s' to file descriptor %d\n", command, sockets[index].fd);
    sent = write(sockets[index].fd, command, strlen(command));
    if (sent != strlen(command)) {
	output_logs_str(PREFIX_WARNING, "'%s' was not properly written. Only %d characters were sent.\n", command, sent);
    } else {
	output_logs_str(PREFIX_DEBUG, "'%s' was proprely sent and %d characters were sent.\n", command, sent);
    }
    recv(sockets[index].fd, buffer, 512, MSG_DONTWAIT);
    printf("%s\n", buffer);
    return 0;
}
