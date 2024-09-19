#include "backend.h"

int get_figure(int index_fig, int y, int x) {
  static const int figures[7][5][5] = {{{0, 0, 0, 0, 0},
                                        {1, 1, 1, 1, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0}},  // I
                                       {{1, 1, 0, 0, 0},
                                        {1, 1, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0}},  // O
                                       {{0, 1, 1, 0, 0},
                                        {1, 1, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0}},  // S
                                       {{1, 1, 0, 0, 0},
                                        {0, 1, 1, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0}},  // Z
                                       {{1, 0, 0, 0, 0},
                                        {1, 1, 1, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0}},  // J
                                       {{0, 0, 1, 0, 0},
                                        {1, 1, 1, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0}},  // L
                                       {{0, 1, 0, 0, 0},
                                        {1, 1, 1, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0}}};  // T

  return figures[index_fig][y][x];
}

Figure create_figure(FigureTypes type) {
  Figure figure;
  create_block(&figure);
  int index = 0;
  figure.width = 3;
  figure.height = 2;
  figure.position = 0;

  figure.block_x = 0;
  figure.block_y = 0;

  figure.start_x = 4;
  figure.start_y = 0;

  switch (type) {
    case I:
      figure.width = 4;
      figure.height = 1;
      figure.block_y = 1;
      figure.start_y = 1;
      index = 0;
      figure.type = I;
      break;
    case O:
      figure.width = 2;
      figure.height = 2;
      figure.type = O;
      index = 1;
      break;
    case S:
      figure.type = S;
      index = 2;
      break;
    case Z:
      figure.type = Z;
      index = 3;
      break;
    case J:
      figure.type = J;
      index = 4;
      break;
    case L:
      figure.type = L;
      index = 5;
      break;
    case T:
      figure.type = T;
      index = 6;
      break;
    default:
      break;
  }

  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    for (int k = 0; k < FIGURE_WIDTH; k++) {
      figure.block[i][k] = get_figure(index, i, k);
    }
  }
  return figure;
}

void move_figure(GameInfo_t *game_info, Figure *figure, UserAction_t action) {
  Figure copy = copyFigure(*figure);

  if (action == Down) {
    copy.start_y += 1;
  } else if (action == Left) {
    copy.start_x -= 1;
  } else if (action == Right) {
    copy.start_x += 1;
  }

  if (check_place(*game_info, *figure, copy)) {
    del_figure(game_info, *figure);
    figure->start_x = copy.start_x;
    figure->start_y = copy.start_y;

    add_figure(game_info, *figure);
  }
  free_block(copy.block);
}

void copyFigureData(Figure *copy, Figure original) {
  copy->width = original.width;
  copy->height = original.height;
  copy->start_x = original.start_x;
  copy->start_y = original.start_y;
  copy->block_x = original.block_x;
  copy->block_y = original.block_y;
  copy->position = original.position;
  copy->type = original.type;

  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    for (int k = 0; k < FIGURE_WIDTH; k++) {
      copy->block[i][k] = original.block[i][k];
    }
  }
}

Figure copyFigure(Figure original) {
  Figure copy;
  copy.width = original.width;
  copy.height = original.height;
  copy.start_x = original.start_x;
  copy.start_y = original.start_y;
  copy.block_x = original.block_x;
  copy.block_y = original.block_y;
  copy.position = original.position;
  copy.type = original.type;

  copy.block = (int **)calloc(FIGURE_HEIGHT, sizeof(int *));
  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    copy.block[i] = (int *)calloc(FIGURE_WIDTH, sizeof(int));
  }

  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    for (int k = 0; k < FIGURE_WIDTH; k++) {
      copy.block[i][k] = original.block[i][k];
    }
  }

  return copy;
}

void rotate(GameInfo_t *game_info, Figure *figure) {
  if (figure->type != O) {
    int x = 2;
    int y = 3;
    if (figure->type == I) {
      x = 3;
      y = 4;
    }

    Figure *temp = (Figure *)malloc(sizeof(Figure));
    *temp = copyFigure(*figure);

    for (int i = 0; i < y; i++) {
      for (int k = 0; k < y; k++) {
        temp->block[k][x - i] = figure->block[i][k];
      }
    }

    if (figure->type == I) {
      update_I(temp);
    } else {
      updateFigure(temp);
    }

    if (check_place(*game_info, *figure, *temp)) {
      del_figure(game_info, *figure);
      copyFigureData(figure, *temp);
      add_figure(game_info, *figure);
    }

    clean_figure(temp);
  }
}

void update_I(Figure *figure) {
  int position = figure->position;
  switch (position) {
    case 0:
      figure->block_x += 2;
      figure->start_x += 2;
      figure->block_y -= 1;
      figure->start_y -= 1;
      break;
    case 1:
      figure->block_x -= 2;
      figure->start_x -= 2;
      figure->block_y += 2;
      figure->start_y += 2;
      break;
    case 2:
      figure->block_x += 1;
      figure->start_x += 1;
      figure->block_y -= 2;
      figure->start_y -= 2;
      break;
    case 3:
      figure->block_x -= 1;
      figure->start_x -= 1;
      figure->block_y += 1;
      figure->start_y += 1;
      break;
    default:
      break;
  }

  if (position == 3) {
    position = 0;
  } else {
    position += 1;
  }

  swap_size(figure);
  figure->position = position;
}

void updateFigure(Figure *figure) {
  int position = figure->position;

  if (position == 0) {
    figure->block_x += 1;
    figure->start_x += 1;
  } else if (position == 1) {
    figure->block_x -= 1;
    figure->block_y += 1;
    figure->start_x -= 1;
    figure->start_y += 1;
  } else if (position == 2) {
    figure->block_y -= 1;
    figure->start_y -= 1;
  }

  if (position == 3) {
    position = 0;
  } else {
    position += 1;
  }

  swap_size(figure);
  figure->position = position;
}

void swap_size(Figure *figure) {
  int width = figure->width;
  figure->width = figure->height;
  figure->height = width;
}

FigureTypes get_random_figureType() {
  int randomIndex = rand() % (T + 1);
  FigureTypes figureType = (FigureTypes)randomIndex;
  return figureType;
}

void del_figure(GameInfo_t *game_info, Figure figure) {
  for (int i = figure.start_y; i < figure.start_y + figure.height; i++) {
    for (int k = figure.start_x; k < figure.start_x + figure.width; k++) {
      if (figure.block[i - figure.start_y + figure.block_y]
                      [k - figure.start_x + figure.block_x] == 1) {
        game_info->field[i][k] = 0;
      }
    }
  }
}

void add_figure(GameInfo_t *game_info, Figure figure) {
  for (int i = figure.start_y; i < figure.start_y + figure.height; i++) {
    for (int k = figure.start_x; k < figure.start_x + figure.width; k++) {
      if (figure.block[i - figure.start_y + figure.block_y]
                      [k - figure.start_x + figure.block_x] == 1) {
        game_info->field[i][k] = 1;
      }
    }
  }
}

void create_block(Figure *figure) {
  figure->block = (int **)calloc(FIGURE_HEIGHT, sizeof(int *));

  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    figure->block[i] = (int *)calloc(FIGURE_WIDTH, sizeof(int));
  }
}