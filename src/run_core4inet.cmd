@echo off
if exist %~dp0\CoRE4INET.exe (
    %~dp0\CoRE4INET -n %~dp0\..\examples;%~dp0 %*
) else (
    opp_run -l %~dp0\CoRE4INET -n %~dp0\..\examples;%~dp0 %*
)
