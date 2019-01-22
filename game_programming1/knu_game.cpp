//
//  knu_game.cpp
//  game_programming1
//
//  Created by Brian Jones on 1/21/19.
//  Copyright © 2019 Brian Jones. All rights reserved.
//

#include "knu_game.hpp"
#include <SDL2/SDL.h>
#include <vector>


Game::Game():
window(nullptr, SDL_DestroyWindow),
renderer(nullptr, SDL_DestroyRenderer),
is_running(true),
ticks_count(0)
{
    
}

Game::~Game()
{
    
}

bool Game::initialize()
{
    int result = SDL_Init(SDL_INIT_VIDEO);
    
    if (0 != result) {
        SDL_Log("Unable to initialize sdl: %s", SDL_GetError());
        
        return false;
    }
    int x_start = 100, y_start = 100, window_width = 1024, window_height = 768, flags = 0;
    window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(
                                    SDL_CreateWindow("Game Programming in C++",
                                    x_start, y_start, window_width, window_height, flags),
                                                                       SDL_DestroyWindow);
    
    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        
        return false;
    }
    
    int renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *temp_renderer = SDL_CreateRenderer(window.get(), -1, renderer_flags);
    renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>
    (temp_renderer, SDL_DestroyRenderer);
    
    temp_renderer = nullptr;
    
    ticks_count = SDL_GetTicks();
    
    return true;
}

void Game::run_loop()
{
    while(is_running)
    {
        process_input();
        update_game();
        generate_output();
    }
}

void Game::shutdown()
{
    renderer.reset(nullptr);
    window.reset(nullptr);
    SDL_Quit();
}

void Game::process_input()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:{ is_running = false;} break;
        }
    }
    

    const Uint8 *temp = SDL_GetKeyboardState(nullptr);
    std::vector<Uint8> key_state(temp, temp + SDL_NUM_SCANCODES);
    
    if(key_state[SDL_SCANCODE_ESCAPE])
        is_running = false;
}

void Game::update_game()
{
    
    // Wait exactly 16 millis before processing the next frame
    std::uint32_t timeout = ticks_count + 16;
    while(!(SDL_TICKS_PASSED(SDL_GetTicks(), timeout)));
    
    std::uint32_t new_time = SDL_GetTicks();
    float delta_time = (new_time - ticks_count) / 1000.0f;
    ticks_count = new_time;
    
    
    // clamps the max delta time
    if(delta_time > 0.05f)
        delta_time = 0.05f;
    // update game objects as function of time using delta time
    
}

void Game::generate_output()
{
    SDL_SetRenderDrawColor(renderer.get(), 0, 255, 240, 240);
    SDL_RenderClear(renderer.get());
    
    
    SDL_RenderPresent(renderer.get());
}
