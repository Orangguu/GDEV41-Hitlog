# GDEV41-Hitlog
Final project for GDEV 41

Commands to compile all files
```bash
g++ -c main.cpp -I raylib/
g++ -c globals.cpp -I raylib/
g++ -c Player.cpp -I raylib/
g++ -c Bullet.cpp -I raylib/
g++ -c UILibrary.cpp -I raylib/
g++ -c Stage1.cpp -I raylib/
g++ -c MainMenu.cpp -I raylib/
g++ -c SceneManager.cpp -I raylib/
g++ -c ResourceManager.cpp -I raylib/
g++ main.o globals.o Player.o Bullet.o UILibrary.o Stage1.o MainMenu.o SceneManager.o ResourceManager.o -o game -L raylib/ -lraylib -lopengl32 -lgdi32 -lwinmm
```

raylib documentation: https://www.raylib.com/cheatsheet/cheatsheet.html
