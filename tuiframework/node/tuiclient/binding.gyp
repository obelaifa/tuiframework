{
  'targets': [
    {
      'target_name': "tuiclient",
      'sources': [
        "cpp/tuiclient.cpp",
        "cpp/Init.cpp",
        "cpp/MyTUIObject.cpp",
        "cpp/TUIClientWrap.cpp",
        "cpp/AttachedObjectsWrap.cpp",
        "cpp/EventConverter.cpp",
        "cpp/NodeEventEmitter.cpp",
        "cpp/NodeEventEmitterCommon.cpp",
        "cpp/NodeEventEmitterFactory.cpp",
        "cpp/TFEventEmitter.cpp",
        "cpp/TFEventEmitterFunc.cpp",
      ],
	  'conditions': [
        ['OS=="mac"', {
                'include_dirs': [
                    "<!(node -e \"require('nan')\")",
                    "$(LOCALINST_DIR)/include",
                ],
                "libraries": [
                    "-lCommonTUITypes",
                    "-lTUIFrameworkClient",
                    "-lTUIFrameworkCore",
                    "-lpthread",
                    "-L$(LOCALINST_DIR)/lib"
                ],
                'cflags!': [ '-fno-exceptions' ],
                'cflags_cc!': [ '-fno-exceptions' ],
                'cflags_cc': [
                    '-fPIC',
                    '-rdynamic'
                ],
                'xcode_settings': {
                    'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++', '-v'],
                    'OTHER_LDFLAGS': ['-stdlib=libc++'],
                    'MACOSX_DEPLOYMENT_TARGET': '10.7',
                    'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
                },
            },
        ],
        ['OS=="win"', {
                'include_dirs': [
                    "<!(node -e \"require('nan')\")",
                    "$(TUIFRAMEWORK_CPP_DIR)",
                    "$(TUIFRAMEWORK_CPP_DIR)/Windows/netsrc/Pre-built.2/include",
                ],
                "libraries": [
                    "$(TUIFRAMEWORK_CPP_DIR)/Windows/Release/TUILibTUITypes.lib",
                    "$(TUIFRAMEWORK_CPP_DIR)/Windows/Release/TUIFrameworkClient.lib",
                    "$(TUIFRAMEWORK_CPP_DIR)/Windows/Release/TUIFrameworkCore.lib",
                    "$(TUIFRAMEWORK_CPP_DIR)/Windows/netsrc/Pre-built.2/lib/pthreadVCE2",
                    "Ws2_32.lib",
                ],
                'msvs_settings': {
                    'VCCLCompilerTool': {
                        'standalone_static_library': 0,
                        'AdditionalOptions': [
                            "/DHAVE_STRUCT_TIMESPEC",
                            "/MD", #Seems to be a bug - it results in many warnings about the setting /MT has been overwritten
                            #The other way using RuntimeLibrary = 2 does not work - the settings will be ignored
                        ],
                    },
                },
            },
        ],
	  ],
    },
  ],
}
