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

void generateUnitCube( cBuild& B )
{
    //front face
B.add({cxyz(0,0,0),cxyz(1,0,0),cxyz(1,1,0)});
B.add({cxyz(0,0,0),cxyz(0,1,0),cxyz(1,1,0)});

// // back face
B.add({cxyz(0,0,1),cxyz(1,0,1),cxyz(1,1,1)});
B.add({cxyz(0,0,1),cxyz(0,1,1),cxyz(1,1,1)});

// 0,0,1, 0,0,1, 1,0,1
// 0,0,1, 1,0,1, 1,0,1
// // bottom
// 0,0,0, 1,0,0, 1,0,1
// 0,0,0, 0,0,1, 1,0,1
// //top
// 0,1,0, 1,1,0, 1,1,1
// 0,1,0, 0,1,1, 1,1,1
// // sides
// 0,0,0, 0,0,1, 0,1,1
// 0,0,0, 0,1,0, 0,1,1
// 1,0,0, 1,0,1, 1,1,1
// 1,0,0, 1,1,0, 1,1,1
}

main()
{
    if (!cxyz::unitTest())
    {
        std::cout << "unit test failed\n";
        exit(1);
    }

    cBuild B;
    generateUnitCube( B );
    B.selectHull( cxyz( 0.5,0.5,0.5 ));

    cGUI theGUI;
    return 0;
}
