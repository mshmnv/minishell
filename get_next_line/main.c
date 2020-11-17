//gcc -Wall -Wextra -Werror -D BUFFER_SIZE=4 main.c get_next_line.c get_next_line_utils.c get_next_line.h
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int     i;
    int     j;
    int     fd;
    int     fd2;
    char    *line;

    j = 0;
    line = NULL;
    fd = open("file", O_RDONLY);
    fd2 = open("file2", O_RDONLY);
    //fd = 0;
    //fd = 42;
    while (((i = get_next_line(fd, &line)) > 0) /*&& j < 2*/)
	{
    	printf("|  %d  | '%s'\n", i, line);
        free(line);
        j++;
    }
    printf("|  %d  | '%s'\n", i, line);
    free(line);
   
//     while ((i = get_next_line(fd2, &line)))
// 	{
//     	printf("      |  %d  |-'%s'\n", i, line);
//         free(line);
//         line = NULL;
//     }
//     printf("      |  %d  |-'%s'\n", i, line);
//      free(line);
//      line = NULL;

//    while ((i = get_next_line(fd, &line)))
// 	{
//     	printf("|  %d  |-'%s'\n", i, line);
//         free(line);
//         line = NULL;
//     }
//     printf("|  %d  | '%s'\n", i, line);
//     free(line);
//     line = NULL;
 
    close (fd2);
    close(fd);
	//sleep(100);
    return (0);
}