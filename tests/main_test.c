#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../brick_game/tetris/backend.h"
#include "../gui/cli/frontend.h"

START_TEST(figures_test_1) {
  Figure figure;

  figure = create_figure(I);
  ck_assert_int_eq(figure.type, I);
  ck_assert_int_eq(figure.width, 4);
  ck_assert_int_eq(figure.height, 1);
  ck_assert_int_eq(figure.start_x, 4);
  ck_assert_int_eq(figure.start_y, 1);
  ck_assert_int_eq(figure.block[1][0], 1);
  ck_assert_int_eq(figure.block[1][1], 1);
  ck_assert_int_eq(figure.block[1][2], 1);
  ck_assert_int_eq(figure.block[1][3], 1);
  free_block(figure.block);

  figure = create_figure(O);
  ck_assert_int_eq(figure.type, O);
  ck_assert_int_eq(figure.width, 2);
  ck_assert_int_eq(figure.height, 2);
  ck_assert_int_eq(figure.start_x, 4);
  ck_assert_int_eq(figure.start_y, 0);
  ck_assert_int_eq(figure.block[0][0], 1);
  ck_assert_int_eq(figure.block[0][1], 1);
  ck_assert_int_eq(figure.block[1][0], 1);
  ck_assert_int_eq(figure.block[1][1], 1);
  free_block(figure.block);

  figure = create_figure(S);
  ck_assert_int_eq(figure.type, S);
  ck_assert_int_eq(figure.width, 3);
  ck_assert_int_eq(figure.height, 2);
  ck_assert_int_eq(figure.start_x, 4);
  ck_assert_int_eq(figure.start_y, 0);
  ck_assert_int_eq(figure.block[0][1], 1);
  ck_assert_int_eq(figure.block[0][2], 1);
  ck_assert_int_eq(figure.block[1][0], 1);
  ck_assert_int_eq(figure.block[1][1], 1);
  free_block(figure.block);

  figure = create_figure(Z);
  ck_assert_int_eq(figure.type, Z);
  ck_assert_int_eq(figure.width, 3);
  ck_assert_int_eq(figure.height, 2);
  ck_assert_int_eq(figure.start_x, 4);
  ck_assert_int_eq(figure.start_y, 0);
  ck_assert_int_eq(figure.block[0][0], 1);
  ck_assert_int_eq(figure.block[0][1], 1);
  ck_assert_int_eq(figure.block[1][1], 1);
  ck_assert_int_eq(figure.block[1][2], 1);
  free_block(figure.block);

  figure = create_figure(J);
  ck_assert_int_eq(figure.type, J);
  ck_assert_int_eq(figure.width, 3);
  ck_assert_int_eq(figure.height, 2);
  ck_assert_int_eq(figure.start_x, 4);
  ck_assert_int_eq(figure.start_y, 0);
  ck_assert_int_eq(figure.block[0][0], 1);
  ck_assert_int_eq(figure.block[1][0], 1);
  ck_assert_int_eq(figure.block[1][1], 1);
  ck_assert_int_eq(figure.block[1][2], 1);

  free_block(figure.block);

  figure = create_figure(L);
  ck_assert_int_eq(figure.type, L);
  ck_assert_int_eq(figure.width, 3);
  ck_assert_int_eq(figure.height, 2);
  ck_assert_int_eq(figure.start_x, 4);
  ck_assert_int_eq(figure.start_y, 0);
  ck_assert_int_eq(figure.block[0][2], 1);
  ck_assert_int_eq(figure.block[1][0], 1);
  ck_assert_int_eq(figure.block[1][1], 1);
  ck_assert_int_eq(figure.block[1][2], 1);
  free_block(figure.block);

  figure = create_figure(T);
  ck_assert_int_eq(figure.type, T);
  ck_assert_int_eq(figure.width, 3);
  ck_assert_int_eq(figure.height, 2);
  ck_assert_int_eq(figure.start_x, 4);
  ck_assert_int_eq(figure.start_y, 0);
  ck_assert_int_eq(figure.block[0][1], 1);
  ck_assert_int_eq(figure.block[1][0], 1);
  ck_assert_int_eq(figure.block[1][1], 1);
  ck_assert_int_eq(figure.block[1][2], 1);

  free_block(figure.block);
}
END_TEST

START_TEST(test_game_info) {
  GameInfo_t *game_info = getGameInfo();

  ck_assert_int_eq(game_info->score, 0);
  ck_assert_int_eq(game_info->level, 1);
  ck_assert_int_eq(game_info->speed, 1);
  ck_assert_int_eq(game_info->pause, 0);
  ck_assert_ptr_nonnull(game_info->next);
  clean_gameInfo();
  clean_gameData();
}
END_TEST

START_TEST(test_update_game_info) {
  GameInfo_t *game_info = getGameInfo();
  GameData *game_data = getGameData();
  int y = game_data->current->start_y;
  *game_info = updateCurrentState();

  ck_assert_int_eq(game_data->current->start_y, y + 1);
  clean_gameInfo();
  clean_gameData();
}
END_TEST

START_TEST(test_game_data) {
  GameData *game_data = getGameData();
  ck_assert_ptr_nonnull(game_data);
  ck_assert_ptr_nonnull(game_data->current);
  ck_assert_ptr_nonnull(game_data->next);
  clean_gameData();
}
END_TEST

START_TEST(move_left_test) {
  GameInfo_t *game_info = getGameInfo();
  GameData *game_data = getGameData();
  int x = game_data->current->start_x;
  move_figure(game_info, game_data->current, Left);

  ck_assert_int_eq(game_data->current->start_x, x - 1);

  clean_gameInfo();
  clean_gameData();
}
END_TEST

START_TEST(move_right_test) {
  GameInfo_t *game_info = getGameInfo();
  GameData *game_data = getGameData();
  int x = game_data->current->start_x;
  move_figure(game_info, game_data->current, Right);

  ck_assert_int_eq(game_data->current->start_x, x + 1);

  clean_gameInfo();
  clean_gameData();
}
END_TEST

START_TEST(copy_figure_test) {
  Figure *fig = (Figure *)malloc(sizeof(Figure));
  Figure *copy = (Figure *)malloc(sizeof(Figure));

  *fig = create_figure(T);
  *copy = copyFigure(*fig);

  ck_assert_int_eq(fig->width, copy->width);
  ck_assert_int_eq(fig->height, copy->height);
  ck_assert_int_eq(fig->start_x, copy->start_x);
  ck_assert_int_eq(fig->start_y, copy->start_y);
  ck_assert_int_eq(fig->block_x, copy->block_x);
  ck_assert_int_eq(fig->block_y, copy->block_y);
  ck_assert_int_eq(fig->position, copy->position);
  ck_assert_int_eq(fig->type, copy->type);

  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    for (int k = 0; k < FIGURE_WIDTH; k++) {
      ck_assert_int_eq(fig->block[i][k], copy->block[i][k]);
    }
  }
  clean_figure(fig);
  clean_figure(copy);
}
END_TEST

START_TEST(test_rotate_all) {
  GameInfo_t *game_info = getGameInfo();
  GameData *game_data = getGameData();
  Figure *check = (Figure *)malloc(sizeof(Figure));

  while (game_data->current->type == I || game_data->current->type == O) {
    del_figure(game_info, *game_data->current);
    handle_spawn(game_info, game_data);
  }

  *check = create_figure(game_data->current->type);
  int x = 2;
  int y = 3;

  for (int n = 0; n < 3; n++) {
    for (int i = 0; i < y; i++) {
      for (int k = 0; k < y; k++) {
        check->block[k][x - i] = game_data->current->block[i][k];
      }
    }
    userInput(Action, true);

    for (int i = 0; i < 4; i++) {
      for (int k = 0; k < 4; k++) {
        ck_assert_int_eq(game_data->current->block[i][k], check->block[i][k]);
      }
    }
  }

  clean_gameInfo();
  clean_figure(check);
  clean_gameData();
}
END_TEST

START_TEST(test_rotate_I) {
  GameInfo_t *game_info = getGameInfo();
  GameData *game_data = getGameData();
  Figure *check = (Figure *)malloc(sizeof(Figure));

  while (game_data->current->type != I) {
    del_figure(game_info, *game_data->current);
    handle_spawn(game_info, game_data);
  }

  *check = create_figure(game_data->current->type);
  int x = 3;
  int y = 4;

  for (int n = 0; n < 4; n++) {
    for (int i = 0; i < y; i++) {
      for (int k = 0; k < y; k++) {
        check->block[k][x - i] = game_data->current->block[i][k];
      }
    }
    userInput(Action, true);

    for (int i = 0; i < 4; i++) {
      for (int k = 0; k < 4; k++) {
        ck_assert_int_eq(game_data->current->block[i][k], check->block[i][k]);
      }
    }
  }

  clean_gameInfo();
  clean_figure(check);
  clean_gameData();
}
END_TEST

START_TEST(test_state) {
  getGameInfo();
  GameData *game_data = getGameData();
  GameState state = WAITING;

  game(&state, Start);
  ck_assert_int_eq(state, WAITING);

  game(&state, Pause);
  updateGameState(&state);
  ck_assert_int_eq(state, PAUSE);

  game(&state, Start);
  updateGameState(&state);
  ck_assert_int_eq(state, WAITING);

  game_data->current->start_y = 18;
  game(&state, Down);
  updateGameState(&state);
  ck_assert_int_eq(state, LANDING_DELAY);

  clean_gameInfo();
  clean_gameData();
}
END_TEST

START_TEST(test_state_check) {
  GameInfo_t *game_info = getGameInfo();
  userInput(Down, true);
  userInput(Down, true);
  userInput(Down, true);

  ck_assert_ptr_ne(game_info, NULL);
  ck_assert_ptr_ne(game_info->field, NULL);
  GameState state = CHECK;

  for (int i = 0; i < WIDTH; i++) {
    game_info->field[HEIGHT - 1][i] = 1;
    game_info->field[HEIGHT - 2][i] = 1;
    game_info->field[HEIGHT - 3][i] = 1;
    game_info->field[HEIGHT - 4][i] = 1;
  };
  updateGameState(&state);

  for (int i = 0; i < WIDTH; i++) {
    ck_assert_int_eq(game_info->field[HEIGHT - 1][i], 0);
    ck_assert_int_eq(game_info->field[HEIGHT - 2][i], 0);
    ck_assert_int_eq(game_info->field[HEIGHT - 3][i], 0);
    ck_assert_int_eq(game_info->field[HEIGHT - 4][i], 0);
  }

  ck_assert_int_eq(game_info->score, 1500);

  clean_gameInfo();
  clean_gameData();
}
END_TEST

START_TEST(test_state_game_over) {
  GameInfo_t *game_info = getGameInfo();
  ck_assert_ptr_ne(game_info, NULL);
  ck_assert_ptr_ne(game_info->field, NULL);
  GameState state = CHECK;

  for (int i = 0; i < WIDTH; i++) {
    game_info->field[2][i] = 1;
  }

  updateGameState(&state);
  ck_assert_int_eq(state, GAME_OVER);
}
END_TEST

START_TEST(test_state_spawn) {
  getGameInfo();
  GameData *game_data = getGameData();
  userInput(Down, true);
  userInput(Down, true);
  userInput(Down, true);
  userInput(Down, true);
  userInput(Down, true);

  Figure *check = (Figure *)malloc(sizeof(Figure));
  *check = create_figure(game_data->next->type);
  GameState state = SPAWN;
  updateGameState(&state);

  ck_assert_int_eq(game_data->current->width, check->width);
  ck_assert_int_eq(game_data->current->height, check->height);
  ck_assert_int_eq(game_data->current->start_x, check->start_x);
  ck_assert_int_eq(game_data->current->start_y, check->start_y);
  ck_assert_int_eq(game_data->current->block_x, check->block_x);
  ck_assert_int_eq(game_data->current->block_y, check->block_y);
  ck_assert_int_eq(game_data->current->position, check->position);
  ck_assert_int_eq(game_data->current->type, check->type);

  ck_assert_int_eq(state, WAITING);
  clean_figure(check);
  clean_gameInfo();
  clean_gameData();
}
END_TEST

START_TEST(test_score) {
  GameInfo_t *game_info = getGameInfo();
  GameState state = CHECK;

  userInput(Down, true);
  userInput(Down, true);
  userInput(Down, true);
  userInput(Down, true);

  for (int i = 0; i < WIDTH; i++) {
    game_info->field[HEIGHT - 1][i] = 1;
  }
  updateGameState(&state);
  ck_assert_int_eq(game_info->score, 100);

  state = CHECK;
  for (int i = 0; i < WIDTH; i++) {
    game_info->field[HEIGHT - 1][i] = 1;
    game_info->field[HEIGHT - 2][i] = 1;
  }
  updateGameState(&state);
  ck_assert_int_eq(game_info->score, 400);

  state = CHECK;
  for (int i = 0; i < WIDTH; i++) {
    game_info->field[HEIGHT - 1][i] = 1;
    game_info->field[HEIGHT - 2][i] = 1;
    game_info->field[HEIGHT - 3][i] = 1;
  }
  updateGameState(&state);
  ck_assert_int_eq(game_info->score, 1100);

  state = CHECK;
  for (int i = 0; i < WIDTH; i++) {
    game_info->field[HEIGHT - 1][i] = 1;
    game_info->field[HEIGHT - 2][i] = 1;
    game_info->field[HEIGHT - 3][i] = 1;
    game_info->field[HEIGHT - 4][i] = 1;
  }
  updateGameState(&state);
  ck_assert_int_eq(game_info->score, 2600);

  clean_gameInfo();
  clean_gameData();
}
END_TEST

START_TEST(test_high_score) {
  GameInfo_t *game_info = getGameInfo();
  GameState state = GAME_OVER;

  FILE *file = fopen("max_score.txt", "r");
  int high_score = 0;
  if (file != NULL) {
    fscanf(file, "%d", &high_score);
  }
  fclose(file);

  ck_assert_int_eq(high_score, game_info->high_score);

  int new_value = game_info->high_score + 100;
  game_info->score = new_value;

  updateGameState(&state);

  FILE *file2 = fopen("max_score.txt", "r");
  if (file2 != NULL) {
    fscanf(file2, "%d", &high_score);
  }
  fclose(file2);

  ck_assert_int_eq(high_score, new_value);
}
END_TEST

START_TEST(test_pause) {
  GameInfo_t *game_info = getGameInfo();
  GameState state = WAITING;
  userInput(Pause, true);

  ck_assert_int_eq(game_info->pause, 1);

  updateGameState(&state);
  ck_assert_int_eq(state, PAUSE);

  clean_gameInfo();
  clean_gameData();
}
END_TEST

START_TEST(test_terminate) {
  GameInfo_t *game_info = getGameInfo();
  GameState state = WAITING;
  userInput(Terminate, true);

  ck_assert_int_eq(game_info->pause, 2);

  updateGameState(&state);
  ck_assert_int_eq(state, GAME_OVER);
}
END_TEST

START_TEST(test_handle_delay) {
  GameState state = WAITING;
  handle_delay(&state);
  ck_assert_int_eq(state, WAITING);

  struct timespec req = {0, 300000000};
  nanosleep(&req, NULL);

  handle_delay(&state);
  ck_assert_int_eq(state, CHECK);
  state = WAITING;

  handle_delay(&state);
  ck_assert_int_eq(state, WAITING);

  req.tv_nsec = 200000000;
  nanosleep(&req, NULL);

  handle_delay(&state);
  ck_assert_int_eq(state, WAITING);

  req.tv_nsec = 100000000;
  nanosleep(&req, NULL);

  handle_delay(&state);
  ck_assert_int_eq(state, CHECK);
}

Suite *s21_main_suite(void) {
  Suite *suite = suite_create("tetris_tests");
  TCase *tcase_core = tcase_create("tetris_test_1");
  tcase_add_test(tcase_core, figures_test_1);
  tcase_add_test(tcase_core, test_game_info);
  tcase_add_test(tcase_core, test_game_data);
  tcase_add_test(tcase_core, test_update_game_info);
  tcase_add_test(tcase_core, move_right_test);
  tcase_add_test(tcase_core, move_left_test);
  tcase_add_test(tcase_core, copy_figure_test);
  tcase_add_test(tcase_core, test_rotate_all);
  tcase_add_test(tcase_core, test_rotate_I);
  tcase_add_test(tcase_core, test_state);
  tcase_add_test(tcase_core, test_state_check);
  tcase_add_test(tcase_core, test_state_game_over);
  tcase_add_test(tcase_core, test_state_spawn);
  tcase_add_test(tcase_core, test_score);
  tcase_add_test(tcase_core, test_high_score);
  tcase_add_test(tcase_core, test_pause);
  tcase_add_test(tcase_core, test_terminate);
  tcase_add_test(tcase_core, test_handle_delay);

  suite_add_tcase(suite, tcase_core);

  return suite;
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;

  if (counter_testcase > 0) {
    putchar('\n');
  }
  counter_testcase++;

  SRunner *sr = srunner_create(testcase);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

void run_tests(void) {
  Suite *list_cases[] = {s21_main_suite(), NULL};

  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

int main(void) {
  run_tests();
  return 0;
}