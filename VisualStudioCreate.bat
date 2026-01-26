@echo off
rem Update the generator string if you use a different Visual Studio version.
cmake -S . -B build -G "Visual Studio 2026" -A x64
if errorlevel 1 goto :eof
cmake --open build
pause
