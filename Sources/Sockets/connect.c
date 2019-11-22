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

static int retrieve_sockets(struct pollfd *sockets, int size)
{
    for (int i = 0; i < size; i++) {
	if (sockets[i].revents & POLLIN) {
	    return i;
	}
    }
    return 0;
}

void receive_connections(struct pollfd *sockets, int *ret_v)
{
    int tmp_ret_v = 0;
    char buffer[512] = {'\0'};
    int index = -1;

    while (tmp_ret_v <= 0) {
	if (poll(sockets, 2, 5) > 0) {
	    index = retrieve_sockets(sockets, 2);
	}
	if (index >= 0) {
	    tmp_ret_v = recv(sockets[index].fd, buffer, 512, MSG_DONTWAIT);
	    if (tmp_ret_v > 0) {
		char tmp_buf[4] = {'\0'};

		for (int i = 0; i < 3; i++) {
		    tmp_buf[i] = buffer[i];
		}
		ret_v[index] = atoi(tmp_buf);
		output_logs_str(PREFIX_DEBUG, "Got %d from socket %d.\n", ret_v[index], sockets[index].fd);
	    }
	    index--;
	}
    }
    return;
}

int create_socket(char *ip_addr, short port)
{
    int fd; // will be the file descriptor of our socket
    struct sockaddr_in sock_details;
    char buffer[512];

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
