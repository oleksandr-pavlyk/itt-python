#ifndef ITT_PYTHON_H
#define ITT_PYTHON_H

#include <Python.h>
#include <ittnotify.h>

static char docstring[] =
    "Provide an interface to the ITT collection control API.";

static char pause_docstring[] =
    "FIXME";

static char resume_docstring[] =
    "FIXME";

static char detach_docstring[] =
    "FIXME";

static PyObject* itt_pause(PyObject* self, PyObject* args);

static PyObject* itt_resume(PyObject* self, PyObject* args);

static PyObject* itt_detach(PyObject* self, PyObject* args);

#endif
