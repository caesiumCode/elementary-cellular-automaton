//
//  Program.hpp
//  elementary-cellular-automaton
//
//  Created by Stephen Jaud on 17/11/2021.
//

#ifndef Program_hpp
#define Program_hpp

#include <cmath>
#include "ECA.hpp"

class Program {
public:
    Program(const sf::Vector2u &, const sf::Vector2u &);
    
    void run();
    
private:
    
    void updateTitle();
    void handleEvent(const sf::Event &);
    void handleMouseEvent(const sf::Event &);
    void handleKeyboardEvent(const sf::Event &);
    
    const std::string TITLE = "Elementary Cellular Automaton";
    const sf::Vector2u WINDOW_SIZE, COMPUTATION_SIZE;
    const sf::FloatRect DEFAULT_RECT;
    
    int rule;
    float p_active;
    bool moving;
    sf::Vector2f previous_position;
    
    sf::View view;
    sf::RenderWindow window;
    sf::Cursor cursor;
    
    ECA eca;
};

#endif /* Program_hpp */
