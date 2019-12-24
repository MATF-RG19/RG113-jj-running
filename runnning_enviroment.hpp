#ifndef R_E
#define R_E
#include "peaceofpath.hpp"
#define NumOfVisiblePath 6
class Player;
class RunningPath {
private:
		  PeaceOfPath** paths;
		  Player* _player;
		  int _distance_between_paths= 1;
		  bool _should_change = true;
public:
		  float position = 0;
		  RunningPath(Player* player);
		  void advance();
		  void make_path()const;
		  void reorder_new_path();
		  static float granica;
};
#endif
