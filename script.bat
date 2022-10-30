@echo off
git submodule update --init

echo "Updating current branch and submodules"
git pull && git submodule update

echo "Generating project files"
premake5 vs2022
IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)

echo "Opening project..."
start BigBaseV2.sln