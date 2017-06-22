###################################################
########### How to start the program ##############
###################################################

In this folder, you have at your disposal three batch files:
	*	startServer: this batch file start the TUI Framework server
	*	startPythonInterface: it starts the python interface
	*	startBedianApp: it starts the BedienApp

We will explain in details how each works.

#####################
#### startServer ####
#####################

It is the most important batch file. When you start it, a command window pop up. You have to choose which configuration you want for the server, you have three choices:
	*	Press 0 and you will set the BedienApp configuration (4 HT, 1 LBR, 1 Gripper)
	* 	Press 1 for the WinMOD config (4 HT, 1 LBR, 1 emergency stop button)
	*	Press other to load a test config (configuration used to test the sending of booleans from Unity to the server)


Be sure that the configuration you set correspond to your scene to avoid errors or crashes...

#######################
### startBedienApp ####
#######################

It takes a bit of time to start the BedienApp, it is normal is nothing appear in the first ten seconds after the opening of the command window.
You can always start and connect the BedienApp to the server, even if the configuration you chose is not using directly the BedienApp, you'll have a nice control view but you'll not be able to modify the scene.

To connect the BedienApp to the server, you have to wait for it to start, and then go to http://localhost:3000/ with your web browser to interact with the application.

############################
### startPythonInterface ###
############################

The Python Interface is useful only if you want to connect the server to VRED.
After starting it, once the line INITIALISATION FINISHED has appeared, you just have to press Enter to connect to the server (be sure that the server has already started).