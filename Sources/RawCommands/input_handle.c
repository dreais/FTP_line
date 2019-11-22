#include <stdlib.h>
#include <string.h>

#include "../../Headers/core_ftp.h"

#define SIZE_CMD_ARRAY 1

static const char comm_arr[4][5] = {
    {USER},{PASS},{CWD},{QUIT}
};

static const struct raw_com input_arr[] = {
    {.command = USER, .func = &cmd_user}
};

void handle_req(char command[5], char *arg)
{
    for (int i = 0; i < SIZE_CMD_ARRAY; i++) {
	if (strcmp(comm_arr[i], command) == 0) {
	    (input_arr[i].func)(arg);
	}
    }
}
