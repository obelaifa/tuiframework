### Setup needed ###

To run the Python Interface, you need Python 3.5.2 (32 bits) or Python 3.6.0 (32bits), and you need also to have downloaded the debug binaries during the installation.

### Automatic build ###

Execute the bat file "buildClient.bat". If there is no error, the last modification hour of the build folder have changed (or a build folder suddently appeared).
If not, you can go to the "Build manually" section.

If the build is correctly done, go to the "Automatic test" section.

### Automatic test ###

It exists two versions of the Python Interface:
	* the first one, "python_interface.py", uses only JSON file. To test it, double click on "startServer_PI.bat".
	If you do not have a real client, you can test it with "jsonClientTest.bat" stored in the example_clients folder.
	* the second one, "python_interface_JSON_TCP.py", uses JSON for the whole configuration, and then send the only values by a TCP connexion.
	To test it, double click on "startServer_PI_TCP.bat".
	If you do not have a real client, you can test it with "socketClientTest.bat" stored in the example_clients folder.

### Build manually ###

Execute following comments in the console: (first line not obligatory if the build folder does not exist)
	
	rmdir /S /Q build
	python_d setup.py build --debug install

This will generate a python-libary (*.pyd) in the build-folder created in the same working directory, and the same in the site-packages folder.
(example of path C:\Users\micka\AppData\Local\Programs\Python\Python35-32\Lib\site-packages)
If you do not add "install" to the execution line, then you have to copy the pyd file in the same directory than python_interface.py.

### Test manually ###

Test the builded Python-Libary with the python_inteogrface.py
Inside the TUI-Project opened in VS there two Projects TUIBinPythonClient and TUIBinVREDClient

TUIBinPythonClient is what actually is build inside the python-libary(*.pyd), it is not compiled in VS and instead 
with the setup.py script.

Execute following comment in the console:
	
	python_d python_interface.py (for the JSON version, or "python_d python_interface_JONS_TCP.py" for the TCP version)