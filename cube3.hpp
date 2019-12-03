#ifndef __CUBE3__
#define __CUBE3__

class Cube;

class Cube3 {
	enum TypeOfCube3 {ORDINARY, SWITCHING, MOVING};
	TypeOfCube3 _type = ORDINARY;
	Cube *cubes;
	float _num = 1.;
	float _mv = 0;
public:
	Cube3();
	void make_cube3() const;
	bool is_visible(int n);
	void reorder_cube3();
	void advance();
};

#endif
