# itt-python

Includes Python bindings to instrumentation and tracing technology (ITT) APIs for VTune.

Intel VTune Amplifier works great on Python code.
This package exposes some limited features of the ITT API in Python to help focus analysis.
Right now it only has the collection and control API and some of the user task API.

## Synopsis

### Collection and Control

    import itt
    # ... uninteresting code
    itt.resume()
    # ... very interesting code
    itt.pause()
    # ... boring stuff again
    itt.resume()
    # ... interesting code
    itt.detach()
    # ... uninteresting code like writing output (sheesh)

Here one would actually run

    > amplxe-cl -start-paused ... python script.py ...

So execution begins with collection paused and only the interesting code is profiled.

### User Task Labels

    import itt
    # ... 
    domain = itt.domain_create("domain")
    itt.task_begin(domain, "awesome")
    # ... do the awesome ...
    itt.task_end(domain)

To get the user task labels into your VTune timeline you need to add `enable-user-task` knob

    > amplxe-cl -collect hotspots -knob enable-user-tasks ... python script.py

## Installation

    python setup.py build_ext [--vtune=PATH_TO_VTUNE_ROOT]
    python setup.py install

By default `setup.py` looks for a VTune installation directory at the environment variable

    VTUNE_AMPLIFIER_XE_2017_DIR

This is not likely to be useful everywhere, so the `--vtune` option can be used to specify the right path.
We assume:

    PATH_TO_VTUNE_ROOT/include
    PATH_TO_VTUNE_ROOT/lib64/libittnotify.a

## Functions

### pause()

Run without collecting data.
Reduces overhead from collection.

### resume()

Resume data collection. 

### detach()

Detaches all collectors from all processes. 
Application continues to work but no data is collected for the running collection.

### domain\_create(name)

Create domain with the given name `name`.
URI naming style is recommended.
No mechanism to destroy domain (expected to be static over execution).
Returns a domain, which is just a [Capsule](https://docs.python.org/3/c-api/capsule.html).

### task\_begin(domain, name)

Create task instance on a thread called `name`. 
Becomes current task instance for that thread. 
Call `task_end()` on same thread to end current task instance.

### task\_begin\_fn()

_Not implemented._

### task\_end(domain)

End a task instance on a thread.

## References

* [Intel Developer Zone page on the ITT Collection Control API](https://software.intel.com/en-us/node/544204)
* [Performance Analysis of Python with Intel VTune Amplifier](https://software.intel.com/en-us/videos/performance-analysis-of-python-applications-with-intel-vtune-amplifier)
* [Intel Distribution for Python](https://software.intel.com/en-us/intel-distribution-for-python)
* [ITT Task API Reference](https://software.intel.com/en-us/node/544206)

## Thanks

* Sergey Maidanov and Vasilij Litvinov at Intel
* Brian Friesen and Brandon Cook at NERSC
