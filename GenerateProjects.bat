@echo off
premake5 vs2019
IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)
