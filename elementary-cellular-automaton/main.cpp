//
//  main.cpp
//  elementary-cellular-automaton
//
//  Created by Stephen Jaud on 16/11/2021.
//


#include "Program.hpp"

int main(int argc, const char * argv[]) {
    const sf::Vector2u WINDOW_RESOLUTION(2200, 1500);
    const sf::Vector2u TEXTURE_RESOLUTION(512, 512);
    
    Program program(WINDOW_RESOLUTION, TEXTURE_RESOLUTION);
    program.run();
    
    return EXIT_SUCCESS;
}
