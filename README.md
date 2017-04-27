# itt-python

Includes Python bindings to instrumentation and tracing technology (ITT) APIs for VTune.

Intel VTune Amplifier works great on Python code.
This package exposes some limited features of the ITT API in Python to help focus analysis.
Right now it only has the collection and control API.

## Synopsis

### Basic Idea

    import itt
    itt.pause()
    # ... some uninteresting code
    itt.resume()
    # ... some more interesting code
    itt.detach()
    # ... some uninteresting code again...

### More Useful Example

    import itt
    # ... uninteresting code
    itt.resume()
    # ... very interesting code
    itt.detach()
    # ... uninteresting code

where one actually runs

    > amplxe-cl -start-paused ... python script.py ...

So execution begins with collection paused and only the interesting code is profiled.

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

## References

* [Intel Developer Zone page on the ITT Collection Control API](https://software.intel.com/en-us/node/544204)
* [Performance Analysis of Python with Intel VTune Amplifier](https://software.intel.com/en-us/videos/performance-analysis-of-python-applications-with-intel-vtune-amplifier)
* [Intel Distribution for Python](https://software.intel.com/en-us/intel-distribution-for-python)

## Thanks

* Sergey Maidanov and Vasilij Litvinov at Intel
* Brian Friesen at NERSC
