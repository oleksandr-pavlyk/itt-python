#include "itt-python.h"

static PyMethodDef itt_methods[] = {
    {"pause" , itt_pause , METH_VARARGS,  pause_docstring},
    {"resume", itt_resume, METH_VARARGS, resume_docstring},
    {"detach", itt_detach, METH_VARARGS, detach_docstring},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef itt_module =
{
    PyModuleDef_HEAD_INIT, "itt", docstring, -1, itt_methods
};

PyMODINIT_FUNC PyInit_itt(void)
{
    return PyModule_Create(&itt_module);
}

static PyObject* itt_pause(PyObject* self, PyObject* args)
{
    __itt_pause();
    Py_RETURN_NONE;
}

static PyObject* itt_resume(PyObject* self, PyObject* args)
{
    __itt_resume();
    Py_RETURN_NONE;
}

static PyObject* itt_detach(PyObject* self, PyObject* args)
{
    __itt_detach();
    Py_RETURN_NONE;
}
