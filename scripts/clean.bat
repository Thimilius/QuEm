@echo off
pushd %~dp0\..\
if exist build ( rd /S /Q build )
popd
