#ifndef R_E
#define R_E
#include "peaceofpath.hpp"
#define NumOfVisiblePath 5
class Player;
class RunningPath {
private:
		  PeaceOfPath** paths;
		  Player* _player;
		  float position = 0;
		  bool _should_change = true;
public:
		  RunningPath(Player* player);
		  void advance();
		  void make_path()const;
		  void reorder_new_path();
		  static float granica;
};
#endif
