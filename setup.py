from setuptools import setup, Extension

import os
import sys

kwargs = dict()
itt_lib_dir = os.environ.get("ITT_LIB_DIR", None)
if itt_lib_dir:
    kwargs["library_dirs"] = [itt_lib_dir]
else:
    itt_lib_dir = os.environ.get("ITT_LIBRARY_DIR", None)
    if itt_lib_dir:
        kwargs["library_dirs"] = [itt_lib_dir]
    elif sys.platform == "linux":
        import sysconfig
        itt_lib_dir = os.path.join(sysconfig.get_path("stdlib"), "..")

itt_include_dir = os.environ.get("ITT_INCLUDE_DIR", None)
if itt_include_dir:
    kwargs["include_dirs"] = [itt_include_dir]

if sys.platform == "linux":
    kwargs["extra_objects"] = [os.path.join(itt_lib_dir, "libittnotify.a")]
else:
    kwargs["extra_objects"] = ["ittnotify"]

extension = Extension(
    "itt", 
    sources = ["itt/itt-python.c"],
    **kwargs
)

setup(name = 'itt',
        version = '0.0.4',
        description = 'ITT API bindings for Python',
        ext_modules = [extension])
