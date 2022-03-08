# -*- coding: utf-8 -*-
# file: setup.py
# date: 2022-02-25


import os
import sys
import subprocess
from setuptools import setup, Extension, find_packages
from setuptools.command.build_ext import build_ext
from typing import List, Tuple


CURR_DIR: str = os.path.abspath(
    os.path.dirname(__file__))


def get_py_cmake() -> str:
    py_path: str = os.path.abspath(
        os.readlink(sys.executable))
    py_bin_path: str = os.path.dirname(py_path)
    py_cmake: str = os.path.join(py_bin_path, "cmake")
    if not os.path.isfile(py_cmake):
        raise Exception(
            "'{}' does not exist.".format(py_cmake))
    return py_cmake


def get_install_deps() -> Tuple[List[str], List[str] ]:
    dependency_links: List[str] = []
    install_requires: List[str] = []
    requirements: List[str] = open(
        os.path.join(CURR_DIR, "requirements.txt"), "r")\
                .read().strip("\n").strip(" ").split("\n")

    for dep in requirements:
        if "git@" in dep or "://" in dep:
            dependency_links.append(dep)
        else:
            install_requires.append(dep)
    return (install_requires, dependency_links)


PLAT_TO_CMAKE = {
    "win32": "Win32",
    "win-amd64": "x64",
    "win-arm32": "ARM",
    "win-arm64": "ARM64",
}


PYTHON3_PATH = os.popen("which python3").read().strip("\n")
EXECUTABLE_PYTHON = sys.executable
PYTHON_ENV = PYTHON3_PATH
if (PYTHON_ENV == "" or "python" not in PYTHON_ENV):
    PYTHON_ENV = EXECUTABLE_PYTHON
print("PYTHON_ENV: %s" % PYTHON_ENV)


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=""):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))

        # required for auto-detection & inclusion of auxiliary "native" libs
        if not extdir.endswith(os.path.sep):
            extdir += os.path.sep

        debug = int(os.environ.get("DEBUG", 0)) if self.debug is None else self.debug
        cfg = "Debug" if debug else "Release"

        # CMake lets you override the generator - we need to check this.
        # Can be set with Conda-Build, for example.
        cmake_generator = os.environ.get("CMAKE_GENERATOR", "")

        # Set Python_EXECUTABLE instead if you use PYBIND11_FINDPYTHON
        # EXAMPLE_VERSION_INFO shows you how to pass a value into the C++ code
        # from Python.
        cmake_args = [
            "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={}".format(extdir),
            "-DPYTHON_EXECUTABLE={}".format(sys.executable),
            "-DCMAKE_BUILD_TYPE={}".format(cfg),  # not used on MSVC, but no harm
        ]
        build_args = []
        # Adding CMake arguments set as environment variable
        # (needed e.g. to build for ARM OSx on conda-forge)
        if "CMAKE_ARGS" in os.environ:
            cmake_args += [item for item in os.environ["CMAKE_ARGS"].split(" ") if item]

        # In this example, we pass in the version to C++. You might not need to.
        cmake_args += [
            "-DEXAMPLE_VERSION_INFO={}".format(self.distribution.get_version())
        ]

        if self.compiler.compiler_type != "msvc":
            # Using Ninja-build since it a) is available as a wheel and b)
            # multithreads automatically. MSVC would require all variables be
            # exported for Ninja to pick it up, which is a little tricky to do.
            # Users can override the generator with CMAKE_GENERATOR in CMake
            # 3.15+.
            if not cmake_generator:
                try:
                    import ninja  # noqa: F401

                    cmake_args += ["-GNinja"]
                except ImportError:
                    pass

        else:
            build_args = build_args + ["-DPYTHON_EXECUTABLE={}".format(sys.executable)]

            # Single config generators are handled "normally"
            single_config = any(x in cmake_generator for x in {"NMake", "Ninja"})

            # CMake allows an arch-in-generator style for backward compatibility
            contains_arch = any(x in cmake_generator for x in {"ARM", "Win64"})

            # Specify the arch if using MSVC generator, but only if it doesn't
            # contain a backward-compatibility arch spec already in the
            # generator name.
            if not single_config and not contains_arch:
                cmake_args += ["-A", PLAT_TO_CMAKE[self.plat_name]]

            # Multi-config generators have a different way to specify configs
            if not single_config:
                cmake_args += [
                    "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}".format(cfg.upper(), extdir)
                ]
                build_args += ["--config", cfg]

        if sys.platform.startswith("darwin"):
            # Cross-compile support for macOS - respect ARCHFLAGS if set
            archs = re.findall(r"-arch (\S+)", os.environ.get("ARCHFLAGS", ""))
            if archs:
                cmake_args += ["-DCMAKE_OSX_ARCHITECTURES={}".format(";".join(archs))]

        # Set CMAKE_BUILD_PARALLEL_LEVEL to control the parallel build level
        # across all generators.
        if "CMAKE_BUILD_PARALLEL_LEVEL" not in os.environ:
            # self.parallel is a Python 3 only way to set parallel jobs by hand
            # using -j in the build_ext call, not supported by pip or PyPA-build.
            if hasattr(self, "parallel") and self.parallel:
                # CMake 3.12+ only.
                build_args += ["-j{}".format(self.parallel)]

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)

        print("CMake Arguments: ", cmake_args)
        # Depreciated: Using external cmake
        #subprocess.check_call(
        #    ["cmake", ext.sourcedir] + cmake_args, cwd=self.build_temp
        #)
        #subprocess.check_call(
        #    ["cmake", "--build", "."] + build_args, cwd=self.build_temp
        #)
        subprocess.check_call(
            [sys.executable, get_py_cmake(), ext.sourcedir] + cmake_args, 
            cwd=self.build_temp
        )
        subprocess.check_call(
            [sys.executable, get_py_cmake(), "--build", "."] + build_args, 
            cwd=self.build_temp
        )




if __name__ == "__main__":
    setup(
        name="keytext4py",
        version="0.0.0",
        author="innerNULL",
        author_email="",
        description="**KEY TEXT** Extractor for **PY**thon",
        url="https://github.com/innerNULL/keytext4py", 
        install_requires=get_install_deps()[0], 
        dependency_links=get_install_deps()[1],
        packages=find_packages(), 
        cmdclass={"build_ext": CMakeBuild}, 
        zip_safe=False, 
        ext_modules=[CMakeExtension("keytext4py_ext_cpp")]
    )
