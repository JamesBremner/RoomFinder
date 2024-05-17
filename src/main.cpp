#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <wex.h>
#include "cGUI.h"
#include "cxyz.h"
#include "cBuilding.h"



main()
{

    if (!cBuild::unitTest())
    {
        std::cout << "unit test failed\n";
        exit(1);
    }
    std::cout << "all unit tests passed\n";

    cGUI gui;
}
