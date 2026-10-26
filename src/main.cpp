#include <SDL.h>
#include <memory>

#include "Core/Core.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    
    auto core = std::make_unique<Core>();

    bool quit = false;
    while (!quit)
    {
        //do stuff

    }

    return 0;
}