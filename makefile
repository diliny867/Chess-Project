
# to hide console: -mwindows

chess:
	g++ main.c -o main -O2 -std=c++11 -Wall -Wno-parentheses -Wno-narrowing -Wno-write-strings -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

release:
	g++ main.c -o main -O3 -std=c++11 -mwindows -Wall -Wno-parentheses -Wno-narrowing -Wno-write-strings -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

debug:
	g++ main.c -o main -g -O0 -std=c++11 -Wall -Wno-parentheses -Wno-narrowing -Wno-write-strings -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm