#if INTERFACE

#include "engine.h"
typedef struct {
  void (*pre_update)(GameState *state, double dt);
  void (*post_update)(GameState *state, double dt);
  void (*pre_draw)(GameState *state);
  void (*post_draw)(GameState *state);
  bool (*pre_event)(GameState *state, ALLEGRO_EVENT event);
  bool (*post_event)(GameState *state, ALLEGRO_EVENT event);
  Engine* engine;
  GameObject* objects;
  unsigned int objectCount;
} GameState;
#endif

void gamestate_draw(GameState *state) {

}

void gamestate_event(GameState *state, ALLEGRO_EVENT event) {

}

void gamestate_update(GameState *state, double dt) {


}
