# -*- coding: utf-8 -*-
from distutils.core import setup
from distutils.extension import Extension

module = Extension('tuiclient',
                    libraries = ['TUIFrameworkClient', 'TUIFrameworkCore', 'pthreadVCE2','Ws2_32','TUILibTUITypes'],
                    include_dirs = ['../cpp',
                    '../cpp/tuilibs',
                    '../cpp/Windows/netsrc/Pre-built.2/include'],
                    library_dirs = ['../cpp/Windows/Release',
                    '../cpp/Windows/netsrc/Pre-built.2/lib'],
					define_macros=[('HAVE_STRUCT_TIMESPEC', None),
									('WIN32', None),
									('NDEBUG',None),
									('_WINDOWS', None),
									('_MBCS', None)],
                    sources = ['./src/TUIClientPythonModule.cpp',
                    './src/TUIClient.cpp',
                    './src/EventDelegationFactory.cpp',
                    './src/eventDelegationRegistration.cpp'],
                    language = "c++")

setup (name = 'tuiclient',
       version = '1.0',
       description = 'TUI Client',
       ext_modules = [module])