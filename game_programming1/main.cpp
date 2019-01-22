//
//  main.cpp
//  game_programming1
//
//  Created by Brian Jones on 1/21/19.
//  Copyright © 2019 Brian Jones. All rights reserved.
//

#include "knu_game.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    Game g;
    
    bool success = g.initialize();
    
    if(success)
        g.run_loop();
    
    g.shutdown();
    
    return 0;
}
