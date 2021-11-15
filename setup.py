from distutils.core import setup, Extension
from distutils.command.build_ext import build_ext as _build_ext
from distutils.command.install import install as _install

import os

class InstallCommand(_install):
    user_options = _install.user_options + [
        ('vtune=', None, 'specify VTune installation directory'),
        ]

    def initialize_options(self):
        _install.initialize_options(self)
        self.vtune = None

    def finalize_options(self):
        _install.finalize_options(self)

    def run(self):
        global vtune
        vtune = self.vtune
        _install.run(self)  # OR: install.do_egg_install(self)


class build_ext(_build_ext):

    _build_ext.user_options += [
        ('vtune=', None, 'specify VTune installation directory'),
    ]

    def initialize_options(self):
        _build_ext.initialize_options(self) 
        self.vtune = None

    def finalize_options(self):
        _build_ext.finalize_options(self) 
        if vtune is not None:
            self.vtune = vtune
        assert self.vtune is not None, "Undefined VTune installation directory"
        assert os.path.isdir(self.vtune), "VTune installation path not a directory"
        self.include_dirs.append(os.path.join(self.vtune, "include"))
        if self.link_objects is None:
            self.link_objects = list()
        self.link_objects.append(os.path.join(self.vtune, "lib64", "libittnotify.a"))

extension = Extension("itt", 
        sources = ["itt/itt-python.c"])

setup(name = 'itt',
        version = '0.0.4',
        description = 'ITT API bindings for Python',
        ext_modules = [extension],
        cmdclass={'build_ext': build_ext,  'install': InstallCommand})
