#include "EventManager.h"

PollResponse EventManager::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            // Early return if event is program quit
            return PollResponse::QUIT;
        }
        
    }
    
    std::memcpy(previousKeyboardState, currentKeyboardState, sizeof(currentKeyboardState));

    const Uint8* state = SDL_GetKeyboardState(nullptr);
    std::memcpy(currentKeyboardState, state, sizeof(currentKeyboardState));

    return PollResponse::CONTINUE;
}

bool EventManager::KeyDown(SDL_Scancode key) const
{
    return currentKeyboardState[key];
}

bool EventManager::KeyUp(SDL_Scancode key) const
{
    return !currentKeyboardState[key] && previousKeyboardState[key];
}

bool EventManager::KeyHeld(SDL_Scancode key) const
{
    return currentKeyboardState[key] && previousKeyboardState[key];
}

bool EventManager::KeyPressed(SDL_Scancode key) const
{
    return currentKeyboardState[key] && !previousKeyboardState[key];
}
