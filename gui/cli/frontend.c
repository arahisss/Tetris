#include "frontend.h"

#include <string.h>
#include <time.h>
#include <unistd.h>

void init_gui() {
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  nodelay(stdscr, TRUE);
  curs_set(0);
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_GREEN);
  init_pair(2, COLOR_WHITE, COLOR_WHITE);
  init_pair(3, COLOR_BLUE, COLOR_BLUE);
  init_pair(4, COLOR_BLACK, COLOR_WHITE);
}

void render(GameInfo_t game_info, GameWindows *windows) {
  refresh();
  wrefresh(windows->game_window);
  wrefresh(windows->info_window);

  for (int i = 0; i < HEIGHT; i++) {
    for (int k = 0; k < WIDTH; k++) {
      if (game_info.field[i][k] == 1) {
        wattron(windows->game_window, COLOR_PAIR(1));
        mvwprintw(windows->game_window, i + 1, k * 2 + 1, "  ");
        wattroff(windows->game_window, COLOR_PAIR(1));

      } else {
        wattron(windows->game_window, COLOR_PAIR(2));
        mvwprintw(windows->game_window, i + 1, k * 2 + 1, "  ");
        wattron(windows->game_window, COLOR_PAIR(2));
      }
    }
  }

  update_info_window(game_info, windows->info_window);
  wrefresh(windows->game_window);
}

void update_info_window(GameInfo_t game_info, WINDOW *info_window) {
  wattron(info_window, COLOR_PAIR(2));

  for (int i = 1; i < HEIGHT + 1; i++) {
    for (int k = 1; k < WIDTH + 9; k++) {
      mvwprintw(info_window, i, k, " ");
    }
  }
  wattroff(info_window, COLOR_PAIR(2));

  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    for (int k = 0; k < FIGURE_WIDTH; k++) {
      if (game_info.next[i][k] == 1) {
        wattron(info_window, COLOR_PAIR(3));
        mvwprintw(info_window, i + 2, k * 2 + 5, "  ");
        wattroff(info_window, COLOR_PAIR(3));

      } else {
        wattron(info_window, COLOR_PAIR(2));
        mvwprintw(info_window, i + 2, k * 2 + 5, " ");
        wattroff(info_window, COLOR_PAIR(2));
      }
    }
  }
  wattron(info_window, COLOR_PAIR(4));

  mvwprintw(info_window, 7, 2, "Score: %d", game_info.score);
  mvwprintw(info_window, 9, 2, "Record: %d", game_info.high_score);
  mvwprintw(info_window, 11, 2, "Level: %d", game_info.level);
  mvwprintw(info_window, 13, 2, "Speed: %d", game_info.speed);
  if (game_info.pause == 0) {
    mvwprintw(info_window, 2, WIDTH + 5, "|>");
  } else {
    mvwprintw(info_window, 2, WIDTH + 5, "||");
  }
  wattroff(info_window, COLOR_PAIR(4));
  wrefresh(info_window);
}

void draw_game(GameWindows *windows) {
  int console_width = getmaxx(stdscr);
  int console_height = getmaxy(stdscr);

  windows->game_window =
      newwin(HEIGHT + 2, WIDTH * 2 + 2, console_height / 2 - 10,
             console_width / 2 - 10);
  box(windows->game_window, 0, 0);
  int x, y;
  getbegyx(windows->game_window, y, x);
  windows->info_window = newwin(HEIGHT + 2, WIDTH + 10, y, x + WIDTH * 2 + 1);
  box(windows->info_window, 0, 0);
  curs_set(0);
}

void updateGameWindows(GameState *state, GameWindows *windows) {
  if (*state == GAME) {
    wclear(stdscr);
    render(*getGameInfo(), windows);
  }
}

UserAction_t getUserInput() {
  int ch = getch();
  UserAction_t result;

  switch (ch) {
    case '\n':
      result = Start;
      break;
    case 'p':
      result = Pause;
      break;
    case 'q':
      result = Terminate;
      break;
    case KEY_LEFT:
      result = Left;
      break;
    case KEY_RIGHT:
      result = Right;
      break;
    case KEY_DOWN:
      result = Down;
      break;
    case ' ':
      result = Action;
      break;
    default:
      break;
  }
  return result;
}

void init_start(GameState *state) {
  draw_start_window();
  UserAction_t user_action = getUserInput();

  while (user_action != Start) {
    user_action = getUserInput();
  }
  wclear(stdscr);
  *state = WAITING;
}
