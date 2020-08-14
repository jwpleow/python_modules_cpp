/*
Python - C++ module example with OpenMP
*/
#include <Python.h> ///< Python-C/C++ API
#include <omp.h> ///< OpenMPI


//<------------------------- Declare functions ----------------------------->
static PyObject* example_function(PyObject* self, PyObject* args);


//<---------- Define available functions/methods in the module ------------->
static PyMethodDef ExampleModule[] = 
{
	{"example_function", example_function, METH_VARARGS, "example_function(input_data) -> (output_data) \n \n This function processes the input and makes some output"},
	// {"another_function", another_function, METH_VARARGS, "put quick documentation here"},
	{NULL, NULL, 0, NULL}
};


//<----------------------- Python module initialisation -------------------->
#if PY_MAJOR_VERSION >= 3
/* Python version 3*/
static struct PyModuleDef cModPyDem =
{
    PyModuleDef_HEAD_INIT,
    "example_module", "This module has many amazing functions",
    -1,
    ExampleModule
};

PyMODINIT_FUNC
PyInit_example_module(void)
{
    return PyModule_Create(&cModPyDem);
}

#else
/* Python version 2 */
PyMODINIT_FUNC
initexample_module(void)
{
    (void) Py_InitModule("example_module", ExampleModule);
}

#endif


//<-------------------------- Functions/Methods -------------------------->


// example_function(indices: List[int], values: List[float]) -> int:
static PyObject* example_function(PyObject* self, PyObject* args){

	PyObject *py_indices;
	PyObject *py_values;
	Py_ssize_t a, b;
	PyObject *returnlist;
	int *indices;
	double *values;

	/* 
	Here you can define the input expected for the function. This example 
	makes the function expect 2 list input arguments, placing them into 
	py_indices and py_values. Always make sure to have a & in front of 
	every argument expected!
	*/
	if (!PyArg_ParseTuple(args, "O!O!", &PyList_Type, &py_indices, &PyList_Type, &py_values)){ 
        PyErr_SetString(PyExc_TypeError, "Could not parse input arguments.\n");
        return (PyObject*) NULL;
	}


	// Get sizes of arrays needed and allocate memory (i originally wrote this for C and am too lazy to change it now)
	a = PyList_Size(py_indices);
	indices = (int*) malloc((int) a * sizeof(int));

	b = PyList_Size(py_values);
	values = (double*) malloc((int) b * sizeof(double));

	returnlist = PyList_New(a); // Make correctly sized python list to place processed values into

	Py_BEGIN_ALLOW_THREADS; // Unlock Python's GIL
	#pragma omp parallel
	{
		#pragma omp sections // Use sections to process the lists into arrays simultaneously
		{
			#pragma omp section
			{
				// Place stuff from python list into a C++ array (converting from Python integer to C++ long)
				for (int i = 0; i < (int) a; ++i){
					indices[i] = (int) PyLong_AsLong(PyList_GetItem(py_indices, i));
				}
			}

			#pragma omp section
			{
				// Place values from python list into a C++ array (converting from Python float to C++ double)
				for (int i = 0; i < (int) b; ++i){
					values[i] = PyFloat_AsDouble(PyList_GetItem(py_values, i));
				}
			}
		}

		#pragma omp for ordered schedule(dynamic) // weeeeeeee
		for (int i = 0; i < (int) a; ++i){
			double value = values[indices[i]];
			double processed_value = value * value * 3.141592653589793238 / 180.0;

			#pragma omp ordered
			PyList_SET_ITEM(returnlist, i, Py_BuildValue("d", processed_value)); ///< Convert C++ double to python float and place in returnlist
		}
	}
	Py_END_ALLOW_THREADS;
	// you can do all of this without needing to convert to C++ datatypes
	free(indices);
	free(values);
	return returnlist;
}





