#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <locale.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64
#define MAX_PATH_SIZE 4096
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

char* find_command(const char *command) {
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");

    while (dir != NULL) {
        char full_path[MAX_PATH_SIZE];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return strdup(full_path);
        }

        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

void parse_input(char *input, char **args) {
    int i = 0;
    args[i] = strtok(input, " ");
    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " ");
    }
}

void execute_cd(char **args) {
    const char *target_dir = args[1];
    if (target_dir == NULL) {
        target_dir = getenv("HOME");
        if (target_dir == NULL) {
            fprintf(stderr, "cd: Не удалось определить домашнюю директорию.\n");
            return;
        }
    }

    if (chdir(target_dir) != 0) {
        perror("cd");
    }
}

void get_commands_list() {
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");

    printf("Доступные команды:\n");
    while (dir != NULL) {
        DIR *dp = opendir(dir);
        if (dp != NULL) {
            struct dirent *entry;
            while ((entry = readdir(dp)) != NULL) {
                if (entry->d_type == DT_REG) { 
                    char full_path[MAX_PATH_SIZE];
                    snprintf(full_path, sizeof(full_path), "%s/%s", dir, entry->d_name);
                    if (access(full_path, X_OK) == 0) {
                        printf("  %s\n", entry->d_name);
                    }
                }
            }
            closedir(dp);
        }
        dir = strtok(NULL, ":");
    }
    free(path_copy);
}

void print_prompt() {
    time_t now;
    time(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%H:%M:%S", localtime(&now));

    char cwd[MAX_PATH_SIZE];
    getcwd(cwd, sizeof(cwd));

    printf("[%s] %s%s%s> ", time_str, COLOR_GREEN, cwd, COLOR_RESET);
}

void execute_program(char **args) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Ошибка при создании процесса");
        return;
    }

    if (pid == 0) {
        if (execv(args[0], args) == -1) {
            perror("Ошибка выполнения программы");
        }
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }
}

int main() {
    setlocale(LC_ALL, "");

    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];
    pid_t pid;

    while (1) {
        print_prompt();
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = 0;

        parse_input(input, args);

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        if (strcmp(args[0], "help") == 0) {
            get_commands_list();
            continue;
        }

        if (strcmp(args[0], "cd") == 0) {
            execute_cd(args);
            continue;
        }

        if (args[0][0] == '/' || args[0][0] == '.') {
            if (access(args[0], X_OK) == 0) {
                execute_program(args);
            } else {
                printf("Ошибка: программа '%s' не найдена или недоступна для выполнения.\n", args[0]);
            }
            continue;
        }

        char *full_path = find_command(args[0]);
        if (full_path == NULL) {
            printf("Команда '%s' не найдена.\n", args[0]);
            continue;
        }

        pid = fork();
        if (pid < 0) {
            perror("Ошибка при создании процесса");
            continue;
        }

        if (pid == 0) {
            if (execv(full_path, args) == -1) {
                perror("Ошибка выполнения команды");
            }
            free(full_path);
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
            free(full_path);
        }
    }

    printf("Выход из интерпретатора.\n");
    return 0;
}
