#include <SDL.h>
#include <memory>

#include "Core/Core.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    
    auto core = std::make_unique<Core>();

    do
    {
        core->Update();
    } while (!core->QuitProgram());

    return 0;
}