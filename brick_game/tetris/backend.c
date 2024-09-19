#include "backend.h"

#include <string.h>
#include <time.h>

void init_game_info(GameInfo_t *game_info) {
  srand(time(NULL));
  game_info->field = (int **)malloc(HEIGHT * sizeof(int *));

  for (int i = 0; i < HEIGHT; i++) {
    game_info->field[i] = (int *)malloc(WIDTH * sizeof(int));
  }

  for (int i = 0; i < HEIGHT; i++) {
    for (int k = 0; k < WIDTH; k++) {
      game_info->field[i][k] = 0;
    }
  }

  game_info->next = getGameData()->next->block;
  add_figure(game_info, *getGameData()->current);
  game_info->score = 0;
  game_info->level = 1;
  game_info->speed = 1;
  game_info->pause = 0;
  game_info->high_score = get_high_score();
}

void init_game_data(GameData *game_data) {
  game_data->current = (Figure *)malloc(sizeof(Figure));
  game_data->next = (Figure *)malloc(sizeof(Figure));

  *game_data->current = create_figure(get_random_figureType());
  *game_data->next = create_figure(get_random_figureType());
}

GameData *getGameData() {
  static GameData *game_data = NULL;
  if (game_data == NULL) {
    game_data = (GameData *)malloc(sizeof(GameData));
    init_game_data(game_data);
  }
  return game_data;
}

GameInfo_t *getGameInfo() {
  static GameInfo_t *game_info = NULL;
  if (game_info == NULL) {
    game_info = (GameInfo_t *)malloc(sizeof(GameInfo_t));
    init_game_info(game_info);
  }
  return game_info;
}

void game(GameState *state, UserAction_t user_action) {
  static struct timespec last_block_time;
  static long interval_nanoseconds = 1000000000;

  struct timespec current_time;
  clock_gettime(CLOCK_MONOTONIC, &current_time);

  if (*state == WAITING || *state == LANDING_DELAY || *state == PAUSE) {
    userInput(user_action, true);
  }

  if ((current_time.tv_sec - last_block_time.tv_sec) * 1000000000 +
              (current_time.tv_nsec - last_block_time.tv_nsec) >=
          interval_nanoseconds &&
      *state != PAUSE) {
    *getGameInfo() = updateCurrentState();
    last_block_time = current_time;
  }
  interval_nanoseconds = get_new_interval(getGameInfo()->speed);
}

long get_new_interval(int speed) {
  long result = 1000000000;
  if (speed <= 5) {
    result -= (speed - 1) * 100000000;
  } else {
    result -= 5 * 100000000 + 50000000 * (speed - 5);
  }
  return result;
}

GameInfo_t updateCurrentState() {
  GameInfo_t *game_info = getGameInfo();
  move_figure(game_info, getGameData()->current, Down);

  return *game_info;
}

void updateGameState(GameState *state) {
  GameInfo_t *game_info = getGameInfo();
  GameData *game_data = getGameData();

  if (game_info->pause == 1) {
    *state = PAUSE;
  } else if (game_info->pause == 2) {
    *state = GAME_OVER;
  }

  switch (*state) {
    case PAUSE:
      if (game_info->pause == 0) {
        *state = WAITING;
      }
      break;
    case WAITING:
      if (is_down(*game_info, *game_data)) {
        *state = LANDING_DELAY;
      }
      break;
    case LANDING_DELAY:
      handle_delay(state);
      break;
    case CHECK:
      handle_check(game_info, state);
      break;
    case SPAWN:
      handle_spawn(game_info, game_data);
      *state = WAITING;
      break;
    case GAME_OVER:
      handle_gameOver(game_info);
      break;
    default:
      break;
  }
}

void userInput(UserAction_t action, bool hold) {
  if (!hold) {
    printf("a");
  }
  GameInfo_t *game_info = getGameInfo();
  GameData *game_data = getGameData();

  switch (action) {
    case Start:
      game_info->pause = 0;
      break;
    case Pause:
      game_info->pause = 1;
      break;
    case Terminate:
      game_info->pause = 2;
      break;
    case Left:
    case Right:
    case Down:
      move_figure(game_info, game_data->current, action);
      break;
    case Action:
      rotate(game_info, game_data->current);
      break;
    default:
      break;
  }
}

// SPAWN
void handle_spawn(GameInfo_t *game_info, GameData *game_data) {
  FigureTypes type = get_random_figureType();
  change_figure(game_data);
  *game_data->next = create_figure(type);
  game_info->next = game_data->next->block;
  add_figure(game_info, *getGameData()->current);
}

void change_figure(GameData *game_data) {
  clean_figure(game_data->current);
  game_data->current = (Figure *)malloc(sizeof(Figure));
  *game_data->current = *game_data->next;
}

// GAME_OVER
void handle_gameOver(GameInfo_t *game_info) {
  if (game_info->score > game_info->high_score) {
    write_new_hight_score(game_info->score);
  }
  clean_gameInfo();
  clean_gameData();
}

void handle_delay(GameState *state) {
  static struct timespec start_time;
  static int delay_started = 0;

  if (!delay_started) {
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    delay_started = 1;
  } else {
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);

    long elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000000000 +
                        (current_time.tv_nsec - start_time.tv_nsec);

    if (elapsed_time >= 300000000) {
      *state = CHECK;
      delay_started = 0;
    }
  }
}

// LANDING STATE
bool is_down(GameInfo_t game_info, GameData game_data) {
  bool result = false;
  Figure copy = copyFigure(*game_data.current);
  copy.start_y += 1;

  if (!check_place(game_info, *game_data.current, copy)) {
    result = true;
  }

  free_block(copy.block);
  return result;
}

// CHECK STATE
void handle_check(GameInfo_t *game_info, GameState *state) {
  int remote_lines = drop_lines(game_info);

  switch (remote_lines) {
    case 1:
      game_info->score += 100;
      break;
    case 2:
      game_info->score += 300;
      break;
    case 3:
      game_info->score += 700;
      break;
    case 4:
      game_info->score += 1500;
      break;
    default:
      break;
  }

  game_info->level = game_info->score / 600 + 1;
  game_info->speed = game_info->level;

  if (!check_field(game_info)) {
    *state = GAME_OVER;
    updateGameState(state);
  } else {
    *state = SPAWN;
  }
}

int drop_lines(GameInfo_t *game_info) {
  int result = 0;
  bool is_full = true;
  for (int i = HEIGHT - 1; i >= 0; i--) {
    for (int k = 0; k < WIDTH; k++) {
      if (game_info->field[i][k] == 0) {
        is_full = false;
      }
    }
    if (is_full) {
      for (int y = i; y > 0; y--) {
        memcpy(game_info->field[y], game_info->field[y - 1],
               WIDTH * sizeof(int));
      }
      i = HEIGHT;
      result += 1;
    } else {
      is_full = true;
    }
  }
  return result;
}

bool check_field(GameInfo_t *game_info) {
  bool result = true;
  for (int x = 0; x < WIDTH; x++) {
    if (game_info->field[2][x] == 1) {
      result = false;
    }
  }

  return result;
}

bool check_place(GameInfo_t game_info, Figure figure, Figure next) {
  bool result = true;

  if (next.start_y + next.height > HEIGHT ||
      next.start_x + next.width > WIDTH || next.start_x < 0 ||
      next.start_y < 0) {
    result = false;
  } else {
    for (int i = next.start_y; i < next.start_y + next.height; i++) {
      for (int k = next.start_x; k < next.start_x + next.width; k++) {
        if (next.block[i - next.start_y + next.block_y]
                      [k - next.start_x + next.block_x] == 1 &&
            game_info.field[i][k] == 1) {
          if (figure.block[i - figure.start_y + figure.block_y]
                          [k - figure.start_x + figure.block_x] == 0) {
            result = false;
            break;
          }
        }
      }
    }
  }

  return result;
}

// SCORE
int get_high_score() {
  FILE *file = fopen("max_score.txt", "r");
  int high_score = 0;
  if (file != NULL) {
    fscanf(file, "%d", &high_score);
    fclose(file);
  }
  return high_score;
}

void write_new_hight_score(int score) {
  FILE *file = fopen("max_score.txt", "w");
  if (file == NULL) {
    perror("Error open file");
  }
  fprintf(file, "%d", score);
  fclose(file);
}

void clean_figure(Figure *figure) {
  if (figure == NULL) {
    return;
  }

  if (figure->block != NULL) {
    for (int i = 0; i < FIGURE_HEIGHT; i++) {
      free(figure->block[i]);
    }
    free(figure->block);
  }

  free(figure);
}

void clean_gameInfo() {
  GameInfo_t *game_info = getGameInfo();
  for (int i = 0; i < HEIGHT; i++) {
    free(game_info->field[i]);
  }
  free(game_info->field);
  free(game_info);
}

void clean_gameData() {
  GameData *game_data = getGameData();
  clean_figure(game_data->current);
  clean_figure(game_data->next);
  free(game_data);
}

void free_block(int **m) {
  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    free(m[i]);
  }
  free(m);
}