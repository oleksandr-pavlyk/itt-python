from distutils.core import setup, Extension
from distutils.command.build_ext import build_ext as _build_ext

import os

class build_ext(_build_ext):
    _build_ext.user_options += [
        ('vtune=', None, 'specify VTune installation directory'),
    ]
    def initialize_options(self):
        _build_ext.initialize_options(self) 
        self.vtune = os.environ.get("VTUNE_AMPLIFIER_XE_2017_DIR")

    def finalize_options(self):
        _build_ext.finalize_options(self) 
        assert self.vtune is not None, "Undefined VTune installation directory"
        assert os.path.isdir(self.vtune), "VTune installation path not a directory"
        self.include_dirs.append(os.path.join(self.vtune, "include"))
        if self.link_objects is None:
            self.link_objects = list()
        self.link_objects.append(os.path.join(self.vtune, "lib64", "libittnotify.a"))

extension = Extension("itt", 
        sources = ["itt/itt-python.c"])
#       extra_compile_args = ['-I/opt/intel/vtune_amplifier_xe_2017.2.0.499904/include'],
#       extra_objects = ["/opt/intel/vtune_amplifier_xe_2017.2.0.499904/lib64/libittnotify.a"])

setup(name = 'itt',
        version = '0.0.1',
        description = 'ITT API bindings for Python',
        ext_modules = [extension],
        cmdclass={'build_ext': build_ext})
