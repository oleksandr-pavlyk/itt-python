#include "itt-python.h"

static PyMethodDef itt_methods[] = {
    {"pause"        , itt_pause         , METH_VARARGS,         pause_docstring},
    {"resume"       , itt_resume        , METH_VARARGS,        resume_docstring},
    {"detach"       , itt_detach        , METH_VARARGS,        detach_docstring},
    {"domain_create", itt_domain_create , METH_VARARGS, domain_create_docstring},
    {"task_begin"   , itt_task_begin    , METH_VARARGS,    task_begin_docstring},
    {"task_end"     , itt_task_end      , METH_VARARGS,      task_end_docstring},
    {"pt_region_create", itt_pt_region_create , METH_VARARGS, pt_region_create_docstring},
    {"pt_region_begin"   , itt_pt_region_begin    , METH_VARARGS,    pt_task_begin_docstring},
    {"pt_region_end"     , itt_pt_region_end      , METH_VARARGS,      pt_task_end_docstring},
    {NULL, NULL, 0, NULL}
};

// Note for future modifications, please see this link for INITERROR defines
// https://docs.python.org/3.3/howto/cporting.html#module-initialization-and-state

static struct PyModuleDef itt_module =
{
    PyModuleDef_HEAD_INIT, "itt._itt", docstring, -1, itt_methods
};

PyMODINIT_FUNC PyInit__itt(void)
{
    return PyModule_Create(&itt_module);
}

static PyObject* itt_pause(PyObject* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS;
    __itt_pause();
    Py_END_ALLOW_THREADS;
    Py_RETURN_NONE;
}

static PyObject* itt_resume(PyObject* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS;
    __itt_resume();
    Py_END_ALLOW_THREADS;
    Py_RETURN_NONE;
}

static PyObject* itt_detach(PyObject* self, PyObject* args)
{
    Py_BEGIN_ALLOW_THREADS;
    __itt_detach();
    Py_END_ALLOW_THREADS;
    Py_RETURN_NONE;
}

static PyObject* itt_domain_create(PyObject* self, PyObject* args)
{

    const char* name; 
    __itt_domain* domain;

    if(!PyArg_ParseTuple(args, "s", &name))
        return NULL;

    Py_BEGIN_ALLOW_THREADS;
    domain = __itt_domain_create(name);
    Py_END_ALLOW_THREADS;
    return PyCapsule_New(domain, "itt.domain", NULL);

}

static PyObject* itt_task_begin(PyObject* self, PyObject* args)
{

    PyObject* capsule;
    const char* name;

    if(!PyArg_ParseTuple(args, "Os", &capsule, &name))
        return NULL;

    Py_BEGIN_ALLOW_THREADS;
    __itt_string_handle* handle = __itt_string_handle_create(name);
    __itt_domain* domain = (__itt_domain*)PyCapsule_GetPointer(capsule, "itt.domain");
    __itt_task_begin(domain, __itt_null, __itt_null, handle);
    Py_END_ALLOW_THREADS;
    Py_RETURN_NONE;

}

static PyObject* itt_task_end(PyObject* self, PyObject* args)
{

    PyObject* capsule;

    if(!PyArg_ParseTuple(args, "O", &capsule))
        return NULL;

    Py_BEGIN_ALLOW_THREADS;
    __itt_domain* domain = (__itt_domain*)PyCapsule_GetPointer(capsule, "itt.domain");
    __itt_task_end(domain);
    Py_END_ALLOW_THREADS;
    Py_RETURN_NONE;

}

static PyObject* itt_pt_region_create(PyObject* self, PyObject* args)
{

    const char* name; 
    __itt_pt_region region;

    if(!PyArg_ParseTuple(args, "s", &name))
        return NULL;

    Py_BEGIN_ALLOW_THREADS;
    region = __itt_pt_region_create(name);
    Py_END_ALLOW_THREADS;
    return Py_BuildValue("i", (unsigned char)region);
}

static PyObject* itt_pt_region_begin(PyObject* self, PyObject* args)
{

    int capsule;

    if(!PyArg_ParseTuple(args, "i", &capsule))
        return NULL;

    Py_BEGIN_ALLOW_THREADS;
    __itt_pt_region region = (__itt_pt_region)capsule;
    __itt_mark_pt_region_begin(region);
    Py_END_ALLOW_THREADS;
    Py_RETURN_NONE;
}

static PyObject* itt_pt_region_end(PyObject* self, PyObject* args)
{

    int capsule;

    if(!PyArg_ParseTuple(args, "i", &capsule))
        return NULL;

    Py_BEGIN_ALLOW_THREADS;
    __itt_pt_region region = (__itt_pt_region)capsule;
    __itt_mark_pt_region_end(region);
    Py_END_ALLOW_THREADS;
    Py_RETURN_NONE;

}
