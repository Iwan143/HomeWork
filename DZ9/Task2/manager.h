#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <curses.h>
#include <dirent.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_FILES 256
#define MAX_PATH 512

typedef struct {
  char filename[256];
  long size;
  char mod_date[20];
  int is_dir;
  char permissions[11];
} FileInfo;

typedef enum { LEFT, RIGHT } window;

extern WINDOW *left_wnd, *right_wnd;

extern FileInfo left_data[MAX_FILES];
extern FileInfo right_data[MAX_FILES];

extern int left_file_count;
extern int right_file_count;

extern int left_selected_row;
extern int right_selected_row;
extern int left_start_row;
extern int right_start_row;

extern window curr_window;
extern window prev_window;

extern char left_path[MAX_PATH];
extern char right_path[MAX_PATH];

void display_table(WINDOW* win,
                   FileInfo* data,
                   int total_rows,
                   int start_row,
                   int selected_row,
                   int is_focused);

void run_file_manager();

void sig_winch();
int compare_file_info(const void* a, const void* b);
void load_directory(const char* path, FileInfo* data, int* file_count);
void navigate_directory(FileInfo* data, int selected_row, char* current_path);
void handle_keyboard_event(int ch, char* left_path, char* right_path);
void open_file_in_editor(const char* path);
void get_screen_size(int *rows, int *cols);
void resize_to_full_screen();

#endif  // FILE_MANAGER_H