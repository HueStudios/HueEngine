#if INTERFACE
#include "engine.h"
#include "gamestate.h"
typedef struct Engine Engine;
typedef struct GameState GameState;

typedef struct GameObject {
  void (*on_update) (GameObject* object, double dt);
  void (*on_draw) (GameObject* object);
  bool (*on_event) (GameObject* object, ALLEGRO_EVENT event);
  int depth;
  void *data;
  Engine *engine;
  GameState *state;
} GameObject;
#endif

#include "gamestate.h"

GameObject *createGameObject(GameState *state, int depth) {
  GameObject *object = malloc(sizeof(*object));
  object->state = state;
  object->depth = depth;
  object->data = NULL;
  object->engine = state->engine;
  object->on_update = NULL;
  object->on_draw = NULL;
  object->on_event = NULL;
  return object;
}
