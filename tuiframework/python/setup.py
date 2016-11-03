# -*- coding: utf-8 -*-
from distutils.core import setup, Extension

import os

module1 = Extension('tuiclient',
                    libraries = ['CommonTUITypes', 'TUIFrameworkClient', 'TUIFrameworkCore'],
                    include_dirs = ['/usr/local/include', os.environ['LOCALINST_DIR'] + '/include'],
                    library_dirs = ['/usr/local/lib', os.environ['LOCALINST_DIR'] + '/lib'],
                    sources = ['TUIClientPythonModule.cpp', 'TUIClient.cpp', 'EventDelegationFactory.cpp', 'eventDelegationRegistration.cpp'])

setup (name = 'TUIClient',
       version = '1.0',
       description = 'TUI Client',
       ext_modules = [module1])
       