#include "Window.h"

Window::Window(int windowWidth, int windowHeight, const char* windowName)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw std::runtime_error("SDL_Init failed");
    }

    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) != 0 ||
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5) != 0 ||
        SDL_GL_SetAttribute(
            SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE) != 0)
    {
        throw std::runtime_error(
            std::string("Failed to request OpenGL 4.5 Core: ") + SDL_GetError());
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // DEV: Disabled for now - may need to re-enable for GCP?
    //SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    window = SDL_CreateWindow(
        windowName,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_OPENGL |
        SDL_WINDOW_SHOWN |
        SDL_WINDOW_RESIZABLE
    );

    if (window == nullptr)
    {
        throw std::runtime_error(std::string("SDL_CreateWindow failed: ") + SDL_GetError());
    }
    
    glContext = SDL_GL_CreateContext(window);
    if (glContext == nullptr)
    {
        const std::string error = SDL_GetError();
        SDL_DestroyWindow(window);
        window = nullptr;
        throw std::runtime_error("SDL_GL_CreateContext failed (OpenGL 4.5 Core required): " + error);
    }

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("GLEW init failed");
    }
}

Window::~Window()
{
	if (glContext != nullptr) SDL_GL_DeleteContext(glContext);
	if (window != nullptr) SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::SwapWindow()
{
    SDL_GL_SwapWindow(window);
}

std::pair<int, int> Window::GetSize()
{
    int width, height = 0;

    SDL_GetWindowSize(window, &width, &height);

    return std::pair<int, int>(width, height);
}
