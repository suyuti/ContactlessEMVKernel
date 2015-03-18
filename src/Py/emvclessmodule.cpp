#include <boost/python.hpp>
extern "C" {
    #include "../Base/kernel.h"
}

BOOST_PYTHON_MODULE(emvclessmodule)
{
    using namespace boost::python;
    def("initialize",   initialize);
    def("start",        start);
    def("version",      getVersion);
}