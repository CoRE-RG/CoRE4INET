@echo off
if exist %~dp0\TTEthernetModel.exe (
    %~dp0\TTEthernetModel -n %~dp0\..\examples;%~dp0 %*
) else (
    opp_run -l %~dp0\TTEthernetModel -n %~dp0\..\examples;%~dp0 %*
)
