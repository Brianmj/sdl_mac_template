//
//  knu_game.hpp
//  game_programming1
//
//  Created by Brian Jones on 1/21/19.
//  Copyright © 2019 Brian Jones. All rights reserved.
//

#ifndef knu_game_hpp
#define knu_game_hpp

#include <memory>
#include <functional>

struct SDL_Window;
struct SDL_Renderer;

class Game
{
public:
    Game();
    ~Game();
    bool initialize();
    void run_loop();
    void shutdown();
    
private:
    void process_input();
    void update_game();
    void generate_output();
    
private:
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window;
    std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> renderer;
    bool is_running;
    std::uint32_t ticks_count;
};

#endif /* knu_game_hpp */
