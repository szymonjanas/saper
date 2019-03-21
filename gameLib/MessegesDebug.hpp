#pragma once
#include <iostream>
#include "FieldManagement.hpp"

namespace debug
{
    void debugOn();
    void debugOff();
    bool getDebugStatus();

    void cerr(std::string error);

    void cout(std::string echo);
}
