@echo off
premake5 vs2022
IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)
