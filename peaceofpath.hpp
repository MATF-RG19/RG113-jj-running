#ifndef _POP_
#define _POP_
class Player;
/* Abstraktna klasa koja predstavlja deo
 * puta.*/
class PeaceOfPath {
protected:
	/* broj kocki koje sadrzi */	  
	int n;
	/* za svaku kocku informacija
	 * dali je igrac iznad kocke*/
	bool *is_player_uppers;
	/*kordinate kocaka*/
	float *_xCoords, *_yCoords, *_zCoords;
	/*kretnja kocki*/
	float _dx = 0, _dz = 0, _dy = 0;
	float _width, _height, _length;
	float length_of_path = 10;
	bool check_if_player_is_on_this_X(Player&, int i);
	bool check_if_player_is_on_this_Z(Player&, int i);
	virtual void action_when_player_colide(Player& p, int i);
	void make_cubes(int n);
	bool is_player_on_ground = false;
public:
	int getLength()const { return length_of_path;}
	/* Metod inicijalizuje broj kocki
	 * njihove kordinate i njihovu kretnju*/
	virtual void init();
	/* Metod koji pomera kocke
	 * kako prolazi vreme*/
	virtual void advance(){}
	virtual void make()const;
	void check_if_player_is_on_this_and_update(Player& p, int i);
	void check_if_player_is_on_this_and_update(Player &p);
};
#endif
