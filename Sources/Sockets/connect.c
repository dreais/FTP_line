#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

#include "../../Headers/core_ftp.h"

void destroy_socket(int fd)
{
    struct sockaddr_in sock_details;
    socklen_t socklen;

    if (getpeername(fd, (struct sockaddr*) &sock_details, &socklen) == 0) {
	output_logs_str(PREFIX_WARNING, "Closing connection at %s:%d\n", inet_ntoa(sock_details.sin_addr), ntohs(sock_details.sin_port));
	close(fd);
	return;
    }
    output_logs_str(PREFIX_WARNING, "Closing connection on file descriptor %d.\n", fd);
    close(fd);
}

int create_socket(char *ip_addr, short port)
{
    int fd; // will be the file descriptor of our socket
    struct sockaddr_in sock_details;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
	return fd;
    }
    sock_details.sin_family = AF_INET;
    sock_details.sin_addr.s_addr = inet_addr(ip_addr);
    if (port > 0) {
	sock_details.sin_port = htons(port);
    }
    if (connect(fd, (struct sockaddr*) &sock_details, sizeof(struct sockaddr_in)) == 0) {
	output_logs_str(PREFIX_INFO, "Socket connected at %s:%d\n", ip_addr, port);
	printf("Connection successful\n");
    } else {
	output_logs_str(PREFIX_WARNING, "Socket could not be connected at %s:%d\n", ip_addr, port);
    }
    return fd;
}
