@echo off

set filepath=%1
set filename=%2
set objdir=%CD%\build\obj\
set bindir=%CD%\build\bin\
set tempdir=%CD%\build\temp\

mkdir build\temp

REM Output the built object file to ./build/temp/
g++ -c "%1" -o "%tempdir%%~n1.o" -g

REM Link & compile ./build/obj/*.o and ./build/temp/arg2.o
g++ "%objdir%*.o" "%tempdir%%~n2.o" -o "%bindir%%filename%" -g

@echo on