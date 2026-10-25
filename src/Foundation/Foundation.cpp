#include "Foundation.h"

Foundation::Foundation()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw std::runtime_error("SDL_Init failed");
    }

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MAJOR_VERSION, 3
    );

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MINOR_VERSION, 3
    );

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // DEV: Disabled for now - may need to re-enable for GCP?
    //SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    window = SDL_CreateWindow(
        "SCOOT Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280,
        720,
        SDL_WINDOW_OPENGL |
        SDL_WINDOW_SHOWN |
        SDL_WINDOW_RESIZABLE
    );
    
    if (!SDL_GL_CreateContext(window))
	{
		throw std::runtime_error("SDL_GL_CreateContext failed");
	}

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("GLEW init failed");
    }
}

Foundation::~Foundation()
{
    SDL_GL_DeleteContext(window);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Foundation::SwapWindow()
{
    SDL_GL_SwapWindow(window);
}