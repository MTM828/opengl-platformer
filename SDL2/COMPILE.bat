g++ Main.cpp -o Platformer.exe -mwindows -lmingw32 -lSDL2main -lSDL2 -I"C:\mingw-w64\SDL2\include" -L"C:\mingw-w64\SDL2\lib"
pause

Platformer.exe
echo %errorlevel%
pause