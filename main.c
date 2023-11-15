#include <stdio.h>
#include <stdlib.h>

#define CMD_GIT_CHECK_VERSION "git -v"
#define STREAM_READ_BUFFER 100

void print_stream(FILE *stream)
{
    char buffer[STREAM_READ_BUFFER] = {0};
    while (fgets(buffer, STREAM_READ_BUFFER - 1, stream) != NULL)
    {
        printf("%s", buffer);
    }
}

int main(void)
{
    FILE *output;

    output = popen(CMD_GIT_CHECK_VERSION, "r");
    if (!output)
    {
        fprintf(stderr, "git not found, please install the git and configure the ssh key.\n");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "[git found]: ");
    print_stream(output);

    if (pclose(output) != 0)
    {
        fprintf(stderr, "Could not close the output\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
