# Python modules in C/C++
Boilerplate of a Python module written in C/C++, with OpenMP, for Windows and Linux as Python documentation's example of how to build it didn't work for Windows... (specifically the use of setup.py)

## For Windows
To compile (the current Makefile is configured for Windows), in a shell, type:
```
make
```

## For Linux

```
python setup.py build_ext --inplace
```

Only the .pyd file (Windows) or .so (for Linux) file is required for using the module in Python.

