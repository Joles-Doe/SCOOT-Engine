#include "Input.h"

bool Input::KeyDown(SDL_Scancode key) const
{
    return currentKeyboardState[key];
}

bool Input::KeyUp(SDL_Scancode key) const
{
    return !currentKeyboardState[key] && previousKeyboardState[key];
}

bool Input::KeyHeld(SDL_Scancode key) const
{
    return currentKeyboardState[key] && previousKeyboardState[key];
}

bool Input::KeyPressed(SDL_Scancode key) const
{
    return currentKeyboardState[key] && !previousKeyboardState[key];
}