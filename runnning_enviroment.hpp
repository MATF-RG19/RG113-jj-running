#ifndef R_E
#define R_E

#define NumOfVisiblePath 5
class Cube3;
class RunningPath {
private:
		  Cube3 **paths;
		  float position = 0;
public:
		  RunningPath();
		  void advance();
		  void make_path()const;
		  void reorder_new_path();
		  static float granica;
};
#endif
