#include "frontend.h"

void draw_start_window() {
  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);
  int y = max_y / 4;
  int x = max_x / 4;
  mvwprintw(stdscr, y, x, " _______");
  mvwprintw(stdscr, y + 1, x, "|__   __|");
  mvwprintw(stdscr, y + 2, x, "   | | ");
  mvwprintw(stdscr, y + 3, x, "   | | ");
  mvwprintw(stdscr, y + 4, x, "   | | ");
  mvwprintw(stdscr, y + 5, x, "   |_| ");

  x += 10;
  mvwprintw(stdscr, y, x, " ______");
  mvwprintw(stdscr, y + 1, x, "|  ____|");
  mvwprintw(stdscr, y + 2, x, "| |____");
  mvwprintw(stdscr, y + 3, x, "|  ____|");
  mvwprintw(stdscr, y + 4, x, "| |____");
  mvwprintw(stdscr, y + 5, x, "|______|");
  x += 9;

  mvwprintw(stdscr, y, x, " _______");
  mvwprintw(stdscr, y + 1, x, "|__   __|");
  mvwprintw(stdscr, y + 2, x, "   | | ");
  mvwprintw(stdscr, y + 3, x, "   | | ");
  mvwprintw(stdscr, y + 4, x, "   | | ");
  mvwprintw(stdscr, y + 5, x, "   |_| ");

  x += 10;

  mvwprintw(stdscr, y, x, " ____");
  mvwprintw(stdscr, y + 1, x, "|  _  \\");
  mvwprintw(stdscr, y + 2, x, "| |_|  |");
  mvwprintw(stdscr, y + 3, x, "|     /");
  mvwprintw(stdscr, y + 4, x, "| | \\ \\");
  mvwprintw(stdscr, y + 5, x, "|_|  \\_\\");

  x += 10;

  mvwprintw(stdscr, y, x, " _");
  mvwprintw(stdscr, y + 1, x, "| |");
  mvwprintw(stdscr, y + 2, x, "| |");
  mvwprintw(stdscr, y + 3, x, "| |");
  mvwprintw(stdscr, y + 4, x, "| |");
  mvwprintw(stdscr, y + 5, x, "|_|");

  x += 5;

  mvwprintw(stdscr, y, x, " ______");
  mvwprintw(stdscr, y + 1, x, "|  ___/");
  mvwprintw(stdscr, y + 2, x, " \\ \\  ");
  mvwprintw(stdscr, y + 3, x, "  \\ \\");
  mvwprintw(stdscr, y + 4, x, " __\\ \\");
  mvwprintw(stdscr, y + 5, x, "|_____\\");

  mvwprintw(stdscr, max_y - 10, max_x / 3, "Press Enter to start the game");
  refresh();
}