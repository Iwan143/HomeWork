#include "manager.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

WINDOW *left_wnd, *right_wnd;

FileInfo left_data[MAX_FILES];
FileInfo right_data[MAX_FILES];

int left_file_count;
int right_file_count;

int left_selected_row;
int right_selected_row;
int left_start_row;
int right_start_row;

window curr_window;
window prev_window;

char left_path[MAX_PATH] = ".";
char right_path[MAX_PATH] = ".";

// Функция для получения размеров экрана
void get_screen_size(int *rows, int *cols) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  *rows = w.ws_row;
  *cols = w.ws_col;
}

// Функция для принудительного изменения размеров окна
void resize_to_full_screen() {
  int screen_rows, screen_cols;
  get_screen_size(&screen_rows, &screen_cols);

  // Изменяем размеры окон на весь экран
  wresize(left_wnd, screen_rows, screen_cols / 2);
  mvwin(left_wnd, 0, 0);
  wresize(right_wnd, screen_rows, screen_cols / 2);
  mvwin(right_wnd, 0, screen_cols / 2);

  // Обновляем отображение окон
  box(left_wnd, 0, 0);
  box(right_wnd, 0, 0);
  display_table(left_wnd, left_data, left_file_count, left_start_row,
                left_selected_row, curr_window == LEFT);
  display_table(right_wnd, right_data, right_file_count, right_start_row,
                right_selected_row, curr_window == RIGHT);
  wrefresh(left_wnd);
  wrefresh(right_wnd);
}

// Обработка изменения размеров окна
void sig_winch(int signum) {
  endwin(); // Завершаем работу ncurses
  refresh(); // Обновляем экран
  clear(); // Очищаем экран

  // Получаем новые размеры экрана
  int screen_rows, screen_cols;
  get_screen_size(&screen_rows, &screen_cols);

  // Пересоздаём окна с новыми размерами
  left_wnd = newwin(screen_rows, screen_cols / 2, 0, 0);
  right_wnd = newwin(screen_rows, screen_cols / 2, 0, screen_cols / 2);

  // Обновляем интерфейс
  resize_to_full_screen();
}

// Основная функция для запуска файлового менеджера
void run_file_manager() {
  initscr();
  signal(SIGWINCH, sig_winch); // Устанавливаем обработчик сигнала SIGWINCH
  noecho();
  curs_set(FALSE);
  keypad(stdscr, TRUE);
  start_color();
  refresh();
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);

  curr_window = LEFT;
  prev_window = RIGHT;

  // Получение текущих размеров экрана
  int screen_rows, screen_cols;
  get_screen_size(&screen_rows, &screen_cols);

  // Создание окон с максимальными размерами
  left_wnd = newwin(screen_rows, screen_cols / 2, 0, 0);
  wattron(left_wnd, COLOR_PAIR(2));
  wattron(stdscr, COLOR_PAIR(2));
  box(left_wnd, 0, 0);

  right_wnd = newwin(screen_rows, screen_cols / 2, 0, screen_cols / 2);
  wattron(right_wnd, COLOR_PAIR(2));
  box(right_wnd, 0, 0);

  // Загрузка данных и отображение окон
  load_directory(left_path, left_data, &left_file_count);
  load_directory(right_path, right_data, &right_file_count);

  display_table(left_wnd, left_data, left_file_count, left_start_row,
                left_selected_row, curr_window == LEFT);
  display_table(right_wnd, right_data, right_file_count, right_start_row,
                right_selected_row, curr_window == RIGHT);

  wrefresh(left_wnd);
  wrefresh(right_wnd);

  // Принудительное изменение размеров на весь экран
  resize_to_full_screen();

  while (true) {
    int ch = wgetch(stdscr);
    if (ch == 'q') {
      break;
    } else if (ch == KEY_RESIZE) {
      sig_winch(0); // Обрабатываем изменение размеров
    } else {
      handle_keyboard_event(ch, left_path, right_path);
      // Обновляем интерфейс после обработки события
      display_table(left_wnd, left_data, left_file_count, left_start_row,
                    left_selected_row, curr_window == LEFT);
      display_table(right_wnd, right_data, right_file_count, right_start_row,
                    right_selected_row, curr_window == RIGHT);
      wrefresh(left_wnd);
      wrefresh(right_wnd);
    }
  }

  delwin(left_wnd);
  delwin(right_wnd);
  endwin();
  exit(EXIT_SUCCESS);
}

// Отображение таблицы с файлами и папками
void display_table(WINDOW* win,
                   FileInfo* data,
                   int total_rows,
                   int start_row,
                   int selected_row,
                   int is_focused) {
  int height = getmaxy(win);
  int width = getmaxx(win);
  int name_width = width / 2;
  int size_width = width / 4 - 3;

  werase(win);
  box(win, 0, 0);

  mvwprintw(win, 1, 1, "%-*s %-*s %s", name_width, "--Name--", size_width,
            "--Size--", "--Modify time");

  for (int i = 0; i < height - 3 && (i + start_row) < total_rows; ++i) {
    if (is_focused && (i + start_row) == selected_row) {
      wattron(win, A_REVERSE);
    }
    int color_pair = data[i + start_row].is_dir ? 1 : 2;
    wattron(win, COLOR_PAIR(color_pair));
    mvwprintw(win, i + 2, 1, "%-*s | %-*ld | %s", name_width,
              data[i + start_row].filename, size_width,
              data[i + start_row].is_dir ? 0 : data[i + start_row].size,
              data[i + start_row].mod_date);
    wattroff(win, COLOR_PAIR(color_pair));
    if (is_focused && (i + start_row) == selected_row) {
      wattroff(win, A_REVERSE);
    }
  }

  // Вывод списка функций внизу окна (только для левого окна)
  if (win == left_wnd) {
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, height - 1, 1, "Tab:Switch | Enter:Open | q:Quit");
    wattroff(win, COLOR_PAIR(2));
  }

  wrefresh(win);
}

// Загрузка содержимого директории
void load_directory(const char* path, FileInfo* data, int* file_count) {
  DIR* dir;
  struct dirent* entry;
  struct stat statbuf;
  struct tm* timeinfo;

  *file_count = 0;

  if ((dir = opendir(path)) == NULL) {
    perror("opendir");
    return;
  }

  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0) {
      continue;
    }

    FileInfo file_info;
    snprintf(file_info.filename, sizeof(file_info.filename), "%s",
             entry->d_name);

    char fullpath[512];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
    stat(fullpath, &statbuf);

    file_info.size = statbuf.st_size;
    file_info.is_dir = S_ISDIR(statbuf.st_mode);

    timeinfo = localtime(&statbuf.st_mtime);
    strftime(file_info.mod_date, sizeof(file_info.mod_date), "%Y-%m-%d %H:%M",
             timeinfo);

    data[*file_count] = file_info;
    (*file_count)++;
  }

  closedir(dir);

  qsort(data, *file_count, sizeof(FileInfo), compare_file_info);
}

// Навигация по директориям
void navigate_directory(FileInfo* data, int selected_row, char* current_path) {
  if (data[selected_row].is_dir) {
    strcat(current_path, "/");
    strcat(current_path, data[selected_row].filename);
    load_directory(
        current_path, data,
        (curr_window == LEFT) ? &left_file_count : &right_file_count);
    if (curr_window == LEFT) {
      left_start_row = left_selected_row = 0;
    } else {
      right_start_row = right_selected_row = 0;
    }
  }
}

void open_file_in_editor(const char* path) {
  // Проверяем, существует ли файл
  if (access(path, F_OK) != 0) {
      mvwprintw(stdscr, LINES - 1, 1, "Ошибка: Файл не найден.");
      wrefresh(stdscr);
      return;
  }

  // Проверяем, доступен ли файл для чтения
  if (access(path, R_OK) != 0) {
      mvwprintw(stdscr, LINES - 1, 1, "Ошибка: Нет прав на чтение файла.");
      wrefresh(stdscr);
      return;
  }

  // Создаём новый процесс
  pid_t pid = fork();
  if (pid == 0) {
      // Дочерний процесс: запускаем редактор
      execlp("nano", "nano", path, NULL);
      // Если execlp завершился с ошибкой
      perror("execlp");
      exit(EXIT_FAILURE);
  } else if (pid > 0) {
      // Родительский процесс: ждём завершения редактора
      int status;
      waitpid(pid, &status, 0);

      // После завершения редактора возвращаем управление
      mvwprintw(stdscr, LINES - 1, 1, "Редактор закрыт. Возврат в файловый менеджер.");
      wrefresh(stdscr);
  } else {
      // Ошибка при создании процесса
      mvwprintw(stdscr, LINES - 1, 1, "Ошибка: Не удалось запустить редактор.");
      wrefresh(stdscr);
  }
}




void handle_keyboard_event(int ch, char* left_path, char* right_path) {
  int height_left = getmaxy(left_wnd) - 5;
  int height_right = getmaxy(right_wnd) - 5;

  switch (ch) {
    case '\t': // Переключение между окнами
      prev_window = curr_window;
      curr_window = (curr_window == LEFT) ? RIGHT : LEFT;
      display_table(left_wnd, left_data, left_file_count, left_start_row,
                    left_selected_row, curr_window == LEFT);
      display_table(right_wnd, right_data, right_file_count, right_start_row,
                    right_selected_row, curr_window == RIGHT);
      break;
    case KEY_UP: // Перемещение вверх
      if (curr_window == LEFT) {
        if (left_selected_row > 0) {
          left_selected_row--;
          if (left_selected_row < left_start_row) {
            left_start_row--;
          }
        }
        display_table(left_wnd, left_data, left_file_count, left_start_row,
                      left_selected_row, curr_window == LEFT);
      } else {
        if (right_selected_row > 0) {
          right_selected_row--;
          if (right_selected_row < right_start_row) {
            right_start_row--;
          }
        }
        display_table(right_wnd, right_data, right_file_count, right_start_row,
                      right_selected_row, curr_window == RIGHT);
      }
      break;
    case KEY_DOWN: // Перемещение вниз
      if (curr_window == LEFT) {
        if (left_selected_row < left_file_count - 1) {
          left_selected_row++;
          if (left_selected_row >= left_start_row + height_left) {
            left_start_row++;
          }
        }
        display_table(left_wnd, left_data, left_file_count, left_start_row,
                      left_selected_row, curr_window == LEFT);
      } else {
        if (right_selected_row < right_file_count - 1) {
          right_selected_row++;
          if (right_selected_row >= right_start_row + height_right) {
            right_start_row++;
          }
        }
        display_table(right_wnd, right_data, right_file_count, right_start_row,
                      right_selected_row, curr_window == RIGHT);
      }
      break;
      case '\n': // Открытие директории или файла
      if (curr_window == LEFT) {
        if (left_data[left_selected_row].is_dir) {
          navigate_directory(left_data, left_selected_row, left_path);
        } else {
          char file_path[MAX_PATH];
          snprintf(file_path, sizeof(file_path), "%s/%s", left_path, left_data[left_selected_row].filename);
          open_file_in_editor(file_path);
        }
        display_table(left_wnd, left_data, left_file_count, left_start_row,
                      left_selected_row, curr_window == LEFT);
      } else {
        if (right_data[right_selected_row].is_dir) {
          navigate_directory(right_data, right_selected_row, right_path);
        } else {
          char file_path[MAX_PATH];
          snprintf(file_path, sizeof(file_path), "%s/%s", right_path, right_data[right_selected_row].filename);
          open_file_in_editor(file_path);
        }
        display_table(right_wnd, right_data, right_file_count, right_start_row,
                      right_selected_row, curr_window == RIGHT);
      }
      break;
    
  }

  // Обновление данных после выполнения операции
  load_directory(left_path, left_data, &left_file_count);
  load_directory(right_path, right_data, &right_file_count);
  display_table(left_wnd, left_data, left_file_count, left_start_row,
                left_selected_row, curr_window == LEFT);
  display_table(right_wnd, right_data, right_file_count, right_start_row,
                right_selected_row, curr_window == RIGHT);
}


// Сравнение файлов для сортировки
int compare_file_info(const void* a, const void* b) {
  FileInfo* file1 = (FileInfo*)a;
  FileInfo* file2 = (FileInfo*)b;

  if (file1->is_dir != file2->is_dir) {
    return file2->is_dir - file1->is_dir;
  }
  return strcmp(file1->filename, file2->filename);
}
