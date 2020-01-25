#include "peaceofpath.hpp"
#include <GL/glut.h>

class SwitchCube : public PeaceOfPath {
	float speed_of_moving;
	float moving;
public:
	SwitchCube();
	void advance() override;
	void make()const override;
	void init() override;
};
