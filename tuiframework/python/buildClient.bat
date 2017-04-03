@Echo off

rmdir /S /Q build

:: Build of the Python Interface
title Python Build
python3 setup.py build install
pause