#include "EventManager.h"

EventManager::EventManager()
{
    inputModule = std::make_shared<Input>();
}

EventManager::~EventManager()
{
    inputModule.reset();
}

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
    
    std::memcpy(inputModule->previousKeyboardState, inputModule->currentKeyboardState, sizeof(inputModule->currentKeyboardState));
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    std::memcpy(inputModule->currentKeyboardState, state, sizeof(inputModule->currentKeyboardState));

    return PollResponse::CONTINUE;
}

std::shared_ptr<Input> EventManager::GetInputModule()
{
    return inputModule;
}
