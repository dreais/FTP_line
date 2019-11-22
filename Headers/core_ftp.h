#ifndef CORE_FTP_H
#define CORE_FTP_H

/* ------------ *\
 * INCLUDES	*
 \* ----------- */
#include <sys/poll.h>
#include "easylogs.h"
#include "raw_commands.h"
// -----------


/**			**\
 * 	STRUCTs		 *
\**			**/
struct raw_com { 
    char command[5];
    void (*func)(char *);
};

/**			**\
 * 	TYPEDEFs	 *
\**			**/
typedef unsigned char byte; // 1 byte
typedef struct raw_com raw_com_t;

/**			**\
 *	PROTOTYPEs	 *
\**			**/
void handle_req(char command[5], char *args);
// Sockets/
void destroy_socket(int fd);
void receive_connections(struct pollfd *sockets, int *ret_v);
int create_socket(char *ip_addr, short port);

int send_command(struct pollfd sockets[2], int index, char *CMD, char *args);

#endif //CORE_FTP_H
