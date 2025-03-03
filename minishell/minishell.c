#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int sig)
{
    (void)sig;
    printf("\n");  // Move to a new line
    rl_on_new_line(); // Tell readline we're on a new line
    rl_replace_line("", 0); // Clear the current input
    rl_redisplay(); // Re-display the prompt
}

int compare(char *s1, char *s2)
{
    if (!s1 || !s2)
        return 0;
    return strcmp(s1, s2) == 0;
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;

    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        char *input = readline("minishell> ");

        if (!input)
        {
            printf("exit\n");
            break;
        }

        if (compare(input, "exit"))
        {
            free(input);
            exit(0);
        }

        if (*input)
            add_history(input);

        free(input);
    }

    return 0;
}
