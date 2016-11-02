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
        "cpp/TFEventEmitterFunc.cpp"
      ],
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
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++', '-v'],
            'OTHER_LDFLAGS': ['-stdlib=libc++'],
            'MACOSX_DEPLOYMENT_TARGET': '10.7',
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          }
        }]
      ]
    }
  ]
}
