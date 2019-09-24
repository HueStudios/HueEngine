#if INTERFACE

#include "engine.h"
#include "gameobject.h"

typedef struct Engine Engine;
typedef struct GameObject GameObject;

typedef struct GameState {
  void (*pre_update)(GameState *state, double dt);
  void (*post_update)(GameState *state, double dt);
  void (*pre_draw)(GameState *state);
  void (*post_draw)(GameState *state);
  bool (*pre_event)(GameState *state, ALLEGRO_EVENT event);
  bool (*post_event)(GameState *state, ALLEGRO_EVENT event);
  Engine *engine;
  GameObject **objects;
  void *data;
  unsigned int objectCount;
} GameState;
#endif

#include "gamestate.h"

GameState *newGameState (Engine *engine) {
  GameState *state = malloc(sizeof(*state));
  state->engine = engine;
  state->pre_update = NULL;
  state->post_update = NULL;
  state->pre_draw = NULL;
  state->post_draw = NULL;
  state->pre_event = NULL;
  state->post_event = NULL;
  state->engine = engine;
  return state;
}

void gamestate_draw(GameState *state) {
  if(state->pre_draw != NULL) {
    state->pre_draw(state);
  }
  for (unsigned int i = 0; i < state->objectCount; i++) {
    if (state->objects[i]->on_draw != NULL) {
      state->objects[i]->on_draw(state->objects[i]);
    }
  }
  if(state->post_draw != NULL) {
    state->post_draw(state);
  }
}

void gamestate_event(GameState *state, ALLEGRO_EVENT event) {
  if(state->pre_event != NULL) {
    state->pre_event(state, event);
  }
  for (unsigned int i = 0; i < state->objectCount; i++) {
    if (state->objects[i]->on_event != NULL) {
      state->objects[i]->on_event(state->objects[i], event);
    }
  }
  if(state->post_event != NULL) {
    state->post_event(state,event);
  }
}

void gamestate_update(GameState *state, double dt) {
  if(state->pre_update != NULL) {
    state->pre_update(state, dt);
  }
  for (unsigned int i = 0; i < state->objectCount; i++) {
    if (state->objects[i]->on_event != NULL) {
      state->objects[i]->on_update(state->objects[i], dt);
    }
  }
  if(state->post_update != NULL) {
    state->post_update(state, dt);
  }
}
