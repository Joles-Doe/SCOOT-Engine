#include "InputModule.h"

bool InputModule::KeyDown(SDL_Scancode key) const
{
    return currentKeyboardState[key];
}

bool InputModule::KeyUp(SDL_Scancode key) const
{
    return !currentKeyboardState[key] && previousKeyboardState[key];
}

bool InputModule::KeyHeld(SDL_Scancode key) const
{
    return currentKeyboardState[key] && previousKeyboardState[key];
}

bool InputModule::KeyPressed(SDL_Scancode key) const
{
    return currentKeyboardState[key] && !previousKeyboardState[key];
}
