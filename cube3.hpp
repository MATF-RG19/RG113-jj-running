#ifndef __CUBE3__
#define __CUBE3__
#include "peaceofpath.hpp"
/* klasa koja predstavlja delove 
 * put od 3 kocke.*/
class Cube3 : public PeaceOfPath{
public:
	void init() override;
	Cube3();
	void make() const override;
};

#endif
