#include <ncurses.h>

int main()
{
        initscr();              /* start curses mode */
        printw("Hello World!"); /* print hello world */
        refresh();              /* print it on to real screen */
        getch();                /* wait for user input */
        endwin();               /* end curses mode */

        return 0;
}
