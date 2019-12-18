igra: main.cpp runnning_enviroment.o cube3.o player.o peaceofpath.o
	g++ -o igra main.cpp runnning_enviroment.o cube3.o  player.o peaceofpath.o -lglut -lGL -lGLU
runnning_enviroment.o: runnning_enviroment.cpp runnning_enviroment.hpp
	g++ -c runnning_enviroment.cpp
cube3.o: cube3.cpp cube3.hpp
	g++ -c cube3.cpp
player.o: player.cpp player.hpp
	g++ -c player.cpp
peaceofpath.o: peaceofpath.cpp peaceofpath.hpp
	g++ -c peaceofpath.cpp
