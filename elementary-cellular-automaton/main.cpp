//
//  main.cpp
//  elementary-cellular-automaton
//
//  Created by Stephen Jaud on 16/11/2021.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ECA.hpp"

std::vector<bool> getExplicitRule(int n);

int main(int argc, const char * argv[]) {
    const sf::Vector2u WINDOW_RESOLUTION(2200, 1500);
    const sf::Vector2u TEXTURE_RESOLUTION(512, 512);
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y), "Elementary Cellular Automaton");
    window.setFramerateLimit(30);
    
    ECA eca(TEXTURE_RESOLUTION);
    eca.setRule(150);
    eca.setRandomInitialState(0.01);
    eca.runComputation();
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) {
                eca.setRandomInitialState(0.01);
                eca.runComputation();
            }
        }
        
        window.clear();
        window.draw(eca);
        window.display();
    }
    
    return EXIT_SUCCESS;
}
