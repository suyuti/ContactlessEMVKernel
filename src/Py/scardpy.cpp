#include "./scard.hpp"
#include <boost/python.hpp>

BOOST_PYTHON_MODULE(scardreadermodule)
{
    using namespace boost::python;
    def("GetReaderList",    GetReaderList);
    def("SelectReader",     SelectReader);
    def("ResetCard",        ResetCard);
    def("Disconnect",       Disconnect);
    def("Transmit",         Transmit2);
}