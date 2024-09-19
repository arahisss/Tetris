#include "brick_game/tetris/backend.h"
#include "gui/cli/frontend.h"

int main() {
  init_gui();
  GameWindows windows;
  draw_game(&windows);

  GameState state = START;
  init_start(&state);

  while (state != GAME_OVER) {
    updateGameState(&state);
    UserAction_t user_action = getUserInput();

    game(&state, user_action);
    if (state != GAME_OVER) {
      render(*getGameInfo(), &windows);
    };
  }
  delwin(windows.game_window);
  delwin(windows.info_window);
  endwin();

  return 1;
}