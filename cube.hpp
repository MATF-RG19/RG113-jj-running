#ifndef __CUBE__
#define __CUBE__


class Cube {
		 	bool _is_visible = true;
public:
		  void make_cube() const;
		  void set_visible(bool visible);
		  bool is_visible() const; 
};


#endif
