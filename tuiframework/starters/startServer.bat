@Echo off

::Reciever Port of the Server
set recieverPort=7998

::Sender Port of the Server
set senderPort=7999

::XML-Configuration-file
ECHO Press 0 to set the BedienApp only config, 1 to set the WinMOD config, other to set test config
SET /P xmlchoice=

IF %xmlchoice%==0 (
	set xmlConfiguration=./xmlconfig/TUI_BedienApp.xml
) ELSE IF %xmlchoice%==1 (
	set xmlConfiguration=./xmlconfig/TUI_WinMOD_Button.xml
) ELSE (
	set xmlConfiguration=./xmlconfig/TUI_BedienApp_ButtonTest.xml
)

::Path to DLL-Libaries
set libPath=../cpp/Windows/Release

:: The Execution of the TUI-Server
start "TUI Server" ../cpp/Windows/Release/TUIBinTUIServer2.exe %recieverPort% %senderPort% %xmlConfiguration% %libPath%