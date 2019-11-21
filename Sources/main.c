#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// opening a file
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../Headers/core_ftp.h"

static int get_stat_file(struct stat *statbuff, char filename_src[80])
{
    int result = stat(filename_src, statbuff);

    if (result != 0) {
	output_logs_str(PREFIX_WARNING, "Could not gather file stats.\n");
	printf("Could not gather file stats.\n");
	return result;
    }
    output_logs_str(PREFIX_INFO, "'%s': file is %d bytes.\n", filename_src, (int)statbuff->st_size);
    return result;
}

void copy_file(char filename_src[80])
{
    FILE *f = fopen(filename_src, "r");
    FILE *dest = fopen("copy", "w");
    struct stat statbuff;
    byte *file;
    long int f_size;
    
    if (f == NULL) {
	output_logs_str(PREFIX_WARNING, "Could not open the file \"%s\".\n", filename_src);
	printf("Could not open the file \"%s\".\n", filename_src);
	return;
    }
    if (get_stat_file(&statbuff, filename_src) != 0) {
	return;
    }
    f_size = (long int) statbuff.st_size;
    file = malloc(sizeof(byte) * f_size);
    fread(file, sizeof(byte), f_size, f);
    fwrite(file, sizeof(byte), f_size, dest);
    fclose(f);
    fclose(dest);
}

int main(int ac, char **av)
{
    char *filename;

    get_log_file();
    output_logs_str(PREFIX_INFO, "Welcome to FTP.\n");
    if (ac <= 1) {
	output_logs_str(PREFIX_WARNING, "Missing args.\n");
	printf("Usage: /ftp [filename]\nNote that the filename IS mandatory.\n");
	return 1;
    }
    printf("%s\n", av[0]+2);
    filename = strdup(av[1]);

    copy_file(filename);
    // ---------
    close_file();
    free(filename);
    return 0;
}
