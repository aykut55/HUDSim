#include <iostream>

#include "MyHudSim.h"

int _main_(int argc, char** argv)
{
    MyHudSim app(argc, argv);

    app.InitWindow(800, 600, "CHudSimExt Demo");
    app.Run();

    return 0;
}