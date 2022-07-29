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

Provide the `build_ext` step with the path to the root VTune install directory.
For instance,

    python setup.py build_ext --vtune=$VTUNE_PROFILER_DIR
    python setup.py install --vtune=$VTUNE_PROFILER_DIR

The build assumes:

    $VTUNE_PROFILER_DIR/include
    $VTUNE_PROFILER_DIR/lib64/libittnotify.a

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

## ITT API for Anomaly Detection

### itt\_pt\_region\_create(name)

Create itt pt region with the given name `name`.
URI naming style is recommended.
No mechanism to destroy region (expected to be static over execution).
Returns a region integer value

### itt\_pt\_region\_begin(region)

Create pt region instance instance on a thread.
Becomes current pt region instance for that thread. 
Call `itt_pt_region_end()` on same thread to end current pt region instance.

### itt\_pt\_region\_end(region)

## References

* [Intel Developer Zone page on the ITT Collection Control API](https://software.intel.com/en-us/node/544204)
* [Performance Analysis of Python with Intel VTune Amplifier](https://software.intel.com/en-us/videos/performance-analysis-of-python-applications-with-intel-vtune-amplifier)
* [Intel Distribution for Python](https://software.intel.com/en-us/intel-distribution-for-python)
* [ITT Task API Reference](https://software.intel.com/en-us/node/544206)

## Thanks

* Sergey Maidanov and Vasilij Litvinov at Intel
* Brian Friesen and Brandon Cook at NERSC
