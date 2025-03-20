#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <time.h>

#define MAX_ARGS 128
#define MAX_COMMAND_LENGTH 1024
#define HISTORY_FILE ".mybash_history"


pid_t background_jobs[64];
int job_count = 0;


void get_time(char *buffer, int size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%H:%M:%S", tm_info);
}


void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("\nUse 'exit' to quit\n");
    } else if (sig == SIGTSTP) {
        printf("\nUse 'bg' or 'fg' to manage jobs\n");
    }
}


void print_help() {
    printf("\033[1;36mAvailable commands:\033[0m\n");
    printf("\033[1;32m  cd, exit, help, jobs, fg, bg, history, whoami, uptime, sysinfo\033[0m\n");
    printf("\033[1;34m  Standard Linux commands (ls, cat, echo, etc.) are also supported\033[0m\n");
}


void add_to_history(char *command) {
    add_history(command);
    FILE *file = fopen(HISTORY_FILE, "a");
    if (file) {
        fprintf(file, "%s\n", command);
        fclose(file);
    }
}


void execute_command(char *command) {
    char *args[MAX_ARGS];
    int i = 0;
    args[i] = strtok(command, " ");
    while (args[i] != NULL) {
        args[++i] = strtok(NULL, " ");
    }
    if (args[0] == NULL) return;

    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    } else if (strcmp(args[0], "cd") == 0) {
        chdir(args[1] ? args[1] : getenv("HOME"));
    } else if (strcmp(args[0], "help") == 0) {
        print_help();
    } else if (strcmp(args[0], "whoami") == 0) {
        system("whoami");
    } else if (strcmp(args[0], "uptime") == 0) {
        system("uptime");
    } else if (strcmp(args[0], "sysinfo") == 0) {
        system("uname -a");
    } else if (strcmp(args[0], "history") == 0) {
        system("cat " HISTORY_FILE);
    } else {
        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("Command execution failed");
            exit(1);
        } else {
            waitpid(pid, NULL, 0);
        }
    }
}


void load_history() {
    FILE *file = fopen(HISTORY_FILE, "r");
    if (file) {
        char line[MAX_COMMAND_LENGTH];
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = 0;
            add_history(line);
        }
        fclose(file);
    }
}


int get_background_job_count() {
    int count = 0;
    int status;
    for (int i = 0; i < job_count; i++) {
        if (waitpid(background_jobs[i], &status, WNOHANG) == 0) {
            count++;
        }
    }
    return count;
}


int main() {
    signal(SIGINT, handle_signal);
    signal(SIGTSTP, handle_signal);
    
    load_history();

    char *command;
    while (1) {
        char cwd[256];  
        getcwd(cwd, sizeof(cwd));

        char time_str[10];
        get_time(time_str, sizeof(time_str));

        int bg_count = get_background_job_count();

        char hostname[256] = "unknown";
        if (gethostname(hostname, sizeof(hostname)) != 0) {
            strcpy(hostname, "unknown");
        }

        const char *user = getenv("USER");
        if (!user) user = "unknown";

        char prompt[512]; 

        
        snprintf(prompt, sizeof(prompt), "\033[1;35m[%s]\033[0m ", time_str);
        snprintf(prompt + strlen(prompt), sizeof(prompt) - strlen(prompt),
                 "\033[1;32m%s@%s\033[0m:", user, hostname);
        snprintf(prompt + strlen(prompt), sizeof(prompt) - strlen(prompt),
                 "\033[1;34m%s\033[0m ", cwd);
        snprintf(prompt + strlen(prompt), sizeof(prompt) - strlen(prompt),
                 "\033[1;33m[%d jobs]\033[0m$ ", bg_count);

        command = readline(prompt);
        if (!command) break;

        if (*command) {
            add_to_history(command);
            execute_command(command);
        }
        free(command);
    }
    return 0;
}