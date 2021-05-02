g++ Main.cpp -o Platformer.exe -mwindows -static -static-libgcc -fno-threadsafe-statics -lfreeglut -lopengl32 -I"C:\mingw-w64\freeglut\include" -L"C:\mingw-w64\freeglut\lib"
pause

Platformer.exe
echo %errorlevel%
pause