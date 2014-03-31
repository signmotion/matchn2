#include "../include/stdafx.h"
#include "../include/Console.h"


namespace matchn {


Console*  Console::mInstance = nullptr;

boost::mutex  Console::mtxInstance;
boost::recursive_mutex  Console::mtx;


} // matchn
