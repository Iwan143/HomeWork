#include <ncurses.h>
#include "calc.h"
#include <stdlib.h>

#define WIDTH 30
#define HEIGHT 10

void draw_menu(int highlight) {
    clear(); // Очищаем экран
    refresh(); // Обновляем основной экран
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);

    int start_y = (LINES - HEIGHT) / 2;
    int start_x = (COLS - WIDTH) / 2;

    WINDOW *menu_win = newwin(HEIGHT, WIDTH, start_y, start_x);
    wbkgd(menu_win, COLOR_PAIR(1));
    box(menu_win, 0, 0);

    const char *items[] = {
        "1. Addition",
        "2. Subtraction",
        "3. Multiplication",
        "4. Division",
        "5. Exit"
    };

    for(int i = 0; i < 5; i++) {
        if(highlight == i)
            wattron(menu_win, A_REVERSE); // Подсвечиваем выбранный пункт
        mvwprintw(menu_win, i+2, 2, "%s", items[i]);
        wattroff(menu_win, A_REVERSE);
    }

    mvwprintw(menu_win, HEIGHT-2, 2, "Use arrows and Enter");
    wrefresh(menu_win); // Обновляем окно меню
}

void input_numbers(int *a, int *b) {
    echo(); // Включаем отображение ввода
    curs_set(1); // Показываем курсор

    WINDOW *input_win = newwin(5, 30, (LINES-5)/2, (COLS-30)/2);
    box(input_win, 0, 0);
    mvwprintw(input_win, 1, 1, "Enter first number: ");
    wrefresh(input_win);
    mvwscanw(input_win, 1, 20, "%d", a);

    mvwprintw(input_win, 2, 1, "Enter second number: ");
    wrefresh(input_win);
    mvwscanw(input_win, 2, 20, "%d", b);

    delwin(input_win);
    noecho(); // Отключаем отображение ввода
    curs_set(0); // Скрываем курсор
}

void show_result(int res) {
    WINDOW *res_win = newwin(5, 30, (LINES-5)/2, (COLS-30)/2);
    box(res_win, 0, 0);
    mvwprintw(res_win, 2, 2, "Result: %d", res);
    mvwprintw(res_win, 3, 2, "Press any key...");
    wrefresh(res_win);
    getch();
    delwin(res_win);
}

int main() {
    initscr(); // Инициализация ncurses
    cbreak(); // Режим cbreak
    noecho(); // Отключение автоматического вывода нажатых клавиш
    keypad(stdscr, TRUE); // Включение поддержки функциональных клавиш
    curs_set(0); // Скрытие курсора

    int choice = 0; // Текущий выбранный пункт
    int running = 1;

    while(running) {
        draw_menu(choice); // Отрисовываем меню с текущим выбором
        int ch = getch(); // Получаем нажатую клавишу

        switch(ch) {
            case KEY_UP: // Стрелка вверх
                choice--;
                if(choice < 0) choice = 4; // Переход к последнему пункту
                break;

            case KEY_DOWN: // Стрелка вниз
                choice++;
                if(choice > 4) choice = 0; // Переход к первому пункту
                break;

            case 10: // Клавиша Enter
                if(choice == 4) { // Если выбран пункт "5. Exit"
                    running = 0;
                    break;
                }

                int a, b;
                input_numbers(&a, &b); // Ввод чисел
                int result = 0;

                switch(choice + 1) { // Выполнение операции
                    case 1: result = add(a, b); break;
                    case 2: result = sub(a, b); break;
                    case 3: result = mul(a, b); break;
                    case 4: 
                        if(b == 0) {
                            show_result(0);
                            break;
                        }
                        result = divs(a, b); 
                        break;
                }

                show_result(result); // Показ результата
                break;
        }
    }

    endwin(); // Завершение работы с ncurses
    return 0;
}