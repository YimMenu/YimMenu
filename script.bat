@echo off
git submodule update --init

echo Updating current branch and submodules
git pull && git submodule update

echo Generating project files
cmake -S. -Bbuild

if ["%~1"]==["--build"] (
    cmake --build build --config Release
)
else
(
    echo "Opening project..."
    tasklist /FI "WINDOWTITLE eq BigBaseV2 - Microsoft Visual Studio" /FI "STATUS eq running" 2>NUL | find /I /N "devenv.exe" >NUL
    IF %ERRORLEVEL% NEQ 0 (start build/BigBaseV2.sln) ELSE (echo Visual Studio is already open, doing nothing. && PAUSE)
)
