#ifndef R_E
#define R_E
#include "peaceofpath.hpp"
#define NumOfVisiblePath 8
#define NumOfStoredPath 20
class Player;
class RunningPath {
private:
		  /* stored_path promenljiva cuva 
			* delove puta*/
		  PeaceOfPath** stored_path;
		  /* paths promenljiva cuva
			* delove puta iz stored_ptah koji 
			* se koriste*/
		  PeaceOfPath** paths;
		  int* currents;
		  Player* _player;
public:
		  RunningPath(Player* player);
		  void advance();
		  void make_path()const;
		  void reorder_new_path();
};
#endif
