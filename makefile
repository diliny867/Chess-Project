
# to hide console: -mwindows

chess:
	g++ main.c -o build/main.exe -O2 -std=c++11 -Wall -Wno-parentheses -Wno-narrowing -Wno-write-strings -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -static-libgcc -static-libstdc++

release:
	g++ main.c -o build/release.exe -O3 -std=c++11 -mwindows -Wall -Wno-parentheses -Wno-narrowing -Wno-write-strings -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -static-libgcc -static-libstdc++

debug:
	g++ main.c -o build/debug.exe -g -O0 -std=c++11 -Wall -Wno-parentheses -Wno-narrowing -Wno-write-strings -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -static-libgcc -static-libstdc++

gen_magics:
	g++ gen_magics.c -o build/gen_magics -O1 -std=c++11 -I ./include/