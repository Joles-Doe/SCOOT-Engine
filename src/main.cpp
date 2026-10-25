#include <SDL.h>
#include <memory>

#include "Foundation/Foundation.h"

int main(int argc, char* argv[])
{
    auto foundation = std::make_shared<Foundation>();

    foundation->SwapWindow();

    return 0;
}


/* Todo
Make window class (will be encapsulated by Foundation (Foundation will handle swapwindow) )
*/