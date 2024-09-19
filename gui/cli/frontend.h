#ifndef _FRONTEND_H_
#define _FRONTEND_H_

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../brick_game/tetris/backend.h"

typedef struct {
  WINDOW *game_window;
  WINDOW *info_window;
} GameWindows;

void init_gui();
void render(GameInfo_t game_info, GameWindows *windows);
void update_info_window(GameInfo_t game_info, WINDOW *info_window);
void draw_game(GameWindows *windows);
void draw_start_window();
void updateGameWindows(GameState *state, GameWindows *windows);
UserAction_t getUserInput();
void init_start(GameState *state);
long get_new_interval(int speed);

#endif