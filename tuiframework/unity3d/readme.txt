TUIUnityClient needs as dependencies pthreadVC2, TUIFrameworkCore, TUIFrameworkClient and TUILibTUITypes.
If you want to use TUIUnityClient inside the Unity-Editor you need to compile the DLL in x64. Be aware that you also must compile 
TUIFrameworkCore,TUIFrameworkClient and TUILibTUITypes in x64 aswell.

Once compiled copy the TUIUnityClient.dll into the Plugin-Folder. Its recommended to create a "x86_x64"-folder inside and put the DLL there.
Also copying the x64-Version of pthreadVC2.dll into the Folder.