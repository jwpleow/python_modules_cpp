# -*- coding: utf-8 -*-

# build the module:
# python setup.oy build_ext --inplace
# only works for Linux when I tested it

from distutils.core import setup, Extension

example_module = Extension(
                "example_module",
                sources=["example_module.cpp"],
                extra_compile_args=["-O2", "-fopenmp"],
                )


# run the setup
setup(ext_modules=[example_module])


