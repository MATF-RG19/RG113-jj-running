igra: main.cpp runnning_enviroment.o cube3.o cube.o player.o
	g++ -o igra main.cpp runnning_enviroment.o cube3.o cube.o player.o -lglut -lGL -lGLU
runnning_enviroment.o: runnning_enviroment.cpp runnning_enviroment.hpp
	gcc -c runnning_enviroment.cpp
cube3.o: cube3.cpp cube3.hpp
	gcc -c cube3.cpp
cube.o: cube.cpp cube.hpp
	gcc -c cube.cpp
player.o: player.cpp player.hpp
	gcc -c player.cpp

