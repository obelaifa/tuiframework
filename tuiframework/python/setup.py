# -*- coding: utf-8 -*-
from distutils.core import setup, Extension

module1 = Extension('tuiclient',
                    libraries = ['TUIFrameworkClient', 'TUIFrameworkCore'],
                    include_dirs = ['/usr/local/include'],
                    library_dirs = ['/usr/local/lib'],
                    sources = ['TUIClientPythonModule.cpp', 'TUIClient.cpp', 'EventDelegationFactory.cpp', 'eventDelegationRegistration.cpp'])

setup (name = 'TUIClient',
       version = '1.0',
       description = 'TUI Client',
       ext_modules = [module1])
       