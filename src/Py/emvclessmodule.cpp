#include <boost/python.hpp>
extern "C" {
    #include "../Base/kernel.h"
    #include "../EntryPoint/entryPoint.h"
}

BOOST_PYTHON_MODULE(emvclessmodule)
{
    using namespace boost::python;
    //def("initialize",   initialize);
    def("release",      release);
    //def("start",        start, args("amount", "amountOther"), "Start EMV Contactless transaction.");
    def("version",      getVersion);
    //def("setCardOpen",    setCardOpen);
}