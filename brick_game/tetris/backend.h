#ifndef _BACKEND_H_
#define _BACKEND_H_

#define WIDTH 10
#define HEIGHT 20
#define FIGURE_WIDTH 5
#define FIGURE_HEIGHT 5

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef enum {
  START,
  GAME,
  WAITING,
  LANDING_DELAY,
  CHECK,
  SPAWN,
  PAUSE,
  GAME_OVER
} GameState;

typedef enum { I, O, S, Z, J, L, T } FigureTypes;

typedef struct {
  int **block;
  int width;
  int height;
  int start_x;
  int start_y;
  int block_x;
  int block_y;
  int position;
  FigureTypes type;
} Figure;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct {
  Figure *current;
  Figure *next;
} GameData;

// Game logic
void init_game_info(GameInfo_t *game_info);
void init_game_data(GameData *game_data);
GameData *getGameData();
GameInfo_t *getGameInfo();
void game(GameState *state, UserAction_t user_action);
GameInfo_t updateCurrentState();
void updateGameState(GameState *state);
void userInput(UserAction_t action, bool hold);
long get_new_interval(int speed);  // Bonus_3

void handle_spawn(GameInfo_t *game_info, GameData *game_data);
void handle_check(GameInfo_t *game_info, GameState *state);
void handle_gameOver(GameInfo_t *game_info);
void handle_delay(GameState *state);

void change_figure(GameData *game_data);
bool check_field(GameInfo_t *game_info);
bool check_place(GameInfo_t game_info, Figure figure, Figure rotate_figure);
bool is_down(GameInfo_t game_info, GameData game_data);
int drop_lines(GameInfo_t *game_info);

// Score | Bonus_2
int get_high_score();
void write_new_hight_score(int score);

// cleaners
void clean_figure(Figure *figure);
void clean_gameInfo();
void clean_gameData();
void free_block(int **m);

// Figures
int get_figure(int index_fig, int y, int x);
Figure create_figure(FigureTypes type);
void create_block(Figure *figure);
void move_figure(GameInfo_t *game_info, Figure *figure, UserAction_t action);
Figure copyFigure(Figure original);
void copyFigureData(Figure *copy, Figure original);

void rotate(GameInfo_t *game_info, Figure *figure);
void updateFigure(Figure *figure);
void update_I(Figure *figure);
void swap_size(Figure *figure);
FigureTypes get_random_figureType();
void add_figure(GameInfo_t *game_info, Figure figure);
void del_figure(GameInfo_t *game_info, Figure figure);
int drop_lines(GameInfo_t *game_info);

#endif