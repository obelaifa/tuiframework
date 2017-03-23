@Echo off

::Reciever Port of the Server
set recieverPort=7998

::Sender Port of the Server
set senderPort=7999

::XML-Configuration-file
ECHO Press 0 to set the winMOD config, other to set the mouse config
SET /P xmlchoice=
set xmlchoice= 0
IF %xmlchoice%==0 (
	set xmlConfiguration=./xmlconfig/TUIConfig_wayInOut.xml
) ELSE (
	::for now we do not have any config for the mouse, this part of the if is never used as we bypassed temporarily the choice
	set xmlConfiguration=./xmlconfig/TUIConfig_wayIn.xml
	:: The Execution of the Mouse Server
	:: start ../../bin/Win32/14.0/x86/Debug/extensions/MouseServer/MouseServer.exe
)

::Path to DLL-Libaries
set libPath=../cpp/Windows/Debug

:: The Execution of the TUI-Server
start "TUI Server" ../cpp/Windows/Debug/TUIBinTUIServer2.exe %recieverPort% %senderPort% %xmlConfiguration% %libPath%

:: The Execution of the Python Interface
start "Python Interface Output" python_d python_interface_JSON_UDP.py %xmlConfiguration%