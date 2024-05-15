#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <wex.h>
#include "cStarterGUI.h"
#include "cxyz.h"
#include "cBuilding.h"

class cGUI : public cStarterGUI
{
public:
    cGUI()
        : cStarterGUI(
              "Starter",
              {50, 50, 1000, 500}),
          lb(wex::maker::make<wex::label>(fm))
    {
        lb.move(50, 50, 100, 30);
        lb.text("Hello World");

        show();
        run();
    }

private:
    wex::label &lb;
};

main()
{
    if (!cxyz::unitTest())
    {
        std::cout << "unit test failed\n";
        exit(1);
    }

    cBuild B;
    B.selectHull( cxyz( 0.5,0.5,0.5 ));

    cGUI theGUI;
    return 0;
}
