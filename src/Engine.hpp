#ifndef ENGINE_HPP
#define ENGINE_HPP

class Engine {
public:
  enum GameStatus {
    STARTUP,
    IDLE,
    NEW_TURN,
    VICTORY,
    DEFEAT
  } gameStatus;
  int fovRadius;
  TCODList<Actor *> actors;
  Actor *player;
  Map *map;

  Engine();
  ~Engine();
  void update();
  void render();
private:
  bool computeFov;
};

extern Engine engine;
#endif
