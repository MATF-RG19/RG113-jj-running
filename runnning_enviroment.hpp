#ifndef R_E
#define R_E

#define NumOfVisiblePath 5
class Cube3;
class Player;
class RunningPath {
private:
		  Cube3 **paths;
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
