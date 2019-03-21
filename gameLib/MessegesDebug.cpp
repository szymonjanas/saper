#include "MessegesDebug.hpp"

static bool isDebugOn = false;
void debug::debugOn()
{
    isDebugOn = true;
}

void debug::debugOff()
{
    isDebugOn = false;
}

bool debug::getDebugStatus()
{
    return isDebugOn;
}
void debug::cerr(std::string error)
{
    if (getDebugStatus())
        std::cerr << "GAME DEBUG ERROR: " << std::endl << error << std::endl;
}

void debug::cout(std::string echo)
{
    if (getDebugStatus())
        std::cout << "GAME DEBUG ECHO:" << std::endl << echo << std::endl;
}



