# GDEV41-Hitlog
Final project for GDEV 41

g++ file.cpp -o programname -I raylib/ -L raylib/ -lraylib -lopengl32 -lgdi32 -lwinmm

//Compile all .cpp files
g++ -c main.cpp -I raylib/
g++ -c Player.cpp -I raylib/
g++ -c Bullet.cpp -I raylib/
g++ -c Stage1.cpp -I raylib/
g++ main.o Player.o Bullet.o Stage1.o -o game -L raylib/ -lraylib -lopengl32 -lgdi32 -lwinmm

raylib  documentation: https://www.raylib.com/cheatsheet/cheatsheet.html
