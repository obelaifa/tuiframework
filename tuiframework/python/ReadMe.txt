### Setup needed ###

To run the Python Interface, you need Python 3.5.2 (32 bits) or Python 3.6.0 (32bits), and you may need also to have downloaded the debug binaries during the installation.

### Automatic build ###

Execute the bat file "buildClient.bat". If there is no error, the last modification hour of the build folder have changed (or a build folder suddently appeared).
If not, you can go to the "Build manually" section.

If the build is correctly done, go to the "Automatic test" section.

### Automatic test ###

To start the python interface, you have to click on startPI.bat in the "starters" folder, which is going to start the python interface, and probably follow the instruction contained in the ReadMe.txt of this folder.

### Build manually ###

Execute following comments in the console: (first line not obligatory if the build folder does not exist)
	
	rmdir /S /Q build
	python3 setup.py build install

This will generate a python-libary (*.pyd) in the build-folder created in the same working directory, and the same in the site-packages folder.
(example of path C:\Users\micka\AppData\Local\Programs\Python\Python35-32\Lib\site-packages)
If you do not add "install" to the execution line, then you have to copy the pyd file in the same directory than python_interface.py.

### Test manually ###

Execute following command in the console:
	
	python3 python_interface.py