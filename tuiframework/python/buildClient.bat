@Echo off

rmdir /S /Q build

:: Build of the Python Interface
title Python Build
python setup.py build install
pause