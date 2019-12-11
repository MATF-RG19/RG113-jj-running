igra: main.cpp runnning_enviroment.o cube3.o cube.o player.o
	g++ -o igra main.cpp runnning_enviroment.o cube3.o cube.o player.o -lglut -lGL -lGLU
runnning_enviroment.o: runnning_enviroment.cpp runnning_enviroment.hpp
	g++ -c runnning_enviroment.cpp
cube3.o: cube3.cpp cube3.hpp
	g++ -c cube3.cpp
cube.o: cube.cpp cube.hpp
	g++ -c cube.cpp
player.o: player.cpp player.hpp
	g++ -c player.cpp

