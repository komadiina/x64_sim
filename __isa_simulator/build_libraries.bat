@echo off

mkdir build
mkdir build\obj
mkdir build\bin

echo Created build directories.

set out_dir=%CD%\build\obj\
set binaries=%CD%\build\bin\

setlocal EnableDelayedExpansion
FOR %%f IN (%CD%\src\*) DO (g++ -c "%%f" -o "%out_dir%%%~nf.o" -g)

@echo on