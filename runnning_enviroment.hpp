#ifndef R_E
#define R_E
#include "peaceofpath.hpp"
#define NumOfVisiblePath 8
#define NumOfStoredPath 20
class Player;
class RunningPath {
private:
		  int* currents;
		  PeaceOfPath** stored_path;
		  PeaceOfPath** paths;
		  Player* _player;
		  int _distance_between_paths= 1;
public:
		  RunningPath(Player* player);
		  void advance();
		  void make_path()const;
		  void reorder_new_path();
		  static float granica;
};
#endif
