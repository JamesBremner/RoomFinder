#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <wex.h>
#include "cStarterGUI.h"
#include "cxyz.h"

class cGUI : public cStarterGUI
{
public:
    cGUI()
        : cStarterGUI(
              "Starter",
              {50, 50, 1000, 500}),
          lb(wex::maker::make < wex::label >(fm))
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
    cxyz t1(0,0,0), t2(1,0,0), t3(1,1,0);
    cxyz ap(0.7,0.7,0.5), outer(0.7,0.7,-10);
    cxyz intersect = cxyz::intersectLineTriangle(
        ap, outer,
        t1, t2, t3 );

    cGUI theGUI;
    return 0;
}
