#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define CMD_GIT_CHECK_VERSION "git -v"
#define CMD_APPEND_NO_OUTPUT " > nul 2>&1"
#define STREAM_READ_BUFFER 100

#define _(str) gettext(str)
#define gettext(Msgid) ((const char *)(Msgid))

#define N_(str) gettext_noop(str)
#define gettext_noop(String) String

#define program_name "bootstrap"
#define PACKAGE_BUGREPORT "example@taicaile.com"

void print_stream(FILE *stream)
{
    char buffer[STREAM_READ_BUFFER] = {0};
    while (fgets(buffer, STREAM_READ_BUFFER - 1, stream) != NULL)
    {
        printf("%s", buffer);
    }
}

void read_stream(FILE *stream)
{
    char buffer[STREAM_READ_BUFFER] = {0};
    while (fgets(buffer, STREAM_READ_BUFFER - 1, stream) != NULL)
    {
        ;
    }
}

static void print_help(void)
{
    /* TRANSLATORS: --help output 1 (synopsis)
       no-wrap */
    printf(_("\
Usage: %s [OPTION]...\n"),
           program_name);

    /* TRANSLATORS: --help output 2 (brief description)
       no-wrap */
    fputs(_("\
Print a friendly, customizable greeting.\n"),
          stdout);

    puts("");
    /* TRANSLATORS: --help output 3: options 1/2
       no-wrap */
    fputs(_("\
  -h, --help          display this help and exit\n\
  -v, --version       display version information and exit\n"),
          stdout);

    puts("");
    /* TRANSLATORS: --help output 4: options 2/2
       no-wrap */
    fputs(_("\
  -t, --traditional       use traditional greeting format\n\
  -n, --next-generation   use next-generation greeting format\n\
  -g, --greeting=TEXT     use TEXT as the greeting message\n"),
          stdout);

    printf("\n");
    /* TRANSLATORS: --help output 5 (end)
       TRANSLATORS: the placeholder indicates the bug-reporting address
       for this application.  Please add _another line_ with the
       address for translation bugs.
       no-wrap */
    printf(_("\
Report bugs to <%s>.\n"),
           PACKAGE_BUGREPORT);
}

int main(void)
{
    FILE *output;

    output = popen(CMD_GIT_CHECK_VERSION CMD_APPEND_NO_OUTPUT, "r");
    if (output == NULL)
    {
        fprintf(stderr, "[error] command run failed, please contact %s.\n", PACKAGE_BUGREPORT);
        return EXIT_FAILURE;
    }

    // check return code
    if (pclose(output) != 0)
    {
        read_stream(output);
        fprintf(stderr, "[error] git not found\n");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "[info] git found:\n");
    output = popen(CMD_GIT_CHECK_VERSION, "r");
    print_stream(output);
    pclose(output);
    // print_help();
    return EXIT_SUCCESS;
}
