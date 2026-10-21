#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << '\n';
        return 1;
    }

    // Request an OpenGL 3.3 Core context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "SCOOT Engine - OpenGL Test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280,
        720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!window)
    {
        std::cerr << "SDL_CreateWindow failed: "
            << SDL_GetError() << '\n';

        SDL_Quit();
        return 1;
    }

    // Create OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    if (!glContext)
    {
        std::cerr << "SDL_GL_CreateContext failed: "
            << SDL_GetError() << '\n';

        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Enable VSync
    SDL_GL_SetSwapInterval(1);

    // Initialize GLEW
    glewExperimental = GL_TRUE;

    GLenum glewStatus = glewInit();

    if (glewStatus != GLEW_OK)
    {
        std::cerr << "GLEW initialization failed: "
            << glewGetErrorString(glewStatus) << '\n';

        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Print OpenGL information
    std::cout << "OpenGL Vendor: "
        << glGetString(GL_VENDOR) << '\n';

    std::cout << "OpenGL Renderer: "
        << glGetString(GL_RENDERER) << '\n';

    std::cout << "OpenGL Version: "
        << glGetString(GL_VERSION) << '\n';

    std::cout << "GLM test: "
        << glm::vec3(3, 6, 9).y << std::endl;

    // Main loop
    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_ESCAPE)
            {
                running = false;
            }
        }

        // Set viewport to the current drawable size
        int width, height;
        SDL_GL_GetDrawableSize(window, &width, &height);
        glViewport(0, 0, width, height);

        // Clear the screen to dark blue
        glClearColor(0.08f, 0.12f, 0.20f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Present the rendered frame
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}