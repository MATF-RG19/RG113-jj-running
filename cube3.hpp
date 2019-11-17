#ifndef __CUBE3__
#define __CUBE3__

class Cube;

class Cube3 {
	Cube *cubes;
public:
	Cube3();
	void make_cube3() const;
	void set_visible(bool visible[3]);
	bool is_visible(int n);
	void reorder_cube3();
};

#endif
