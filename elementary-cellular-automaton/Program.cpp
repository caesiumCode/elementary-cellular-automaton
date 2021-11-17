//
//  Program.cpp
//  elementary-cellular-automaton
//
//  Created by Stephen Jaud on 17/11/2021.
//

#include "Program.hpp"

Program::Program(const sf::Vector2u & w_size, const sf::Vector2u & c_size)
:   WINDOW_SIZE(w_size)
,   COMPUTATION_SIZE(c_size)
,   DEFAULT_RECT(sf::FloatRect(0.25f*float(COMPUTATION_SIZE.x),
                               0.f,
                               0.5f*float(COMPUTATION_SIZE.x),
                               0.5f*float(COMPUTATION_SIZE.x)/float(WINDOW_SIZE.x)*float(WINDOW_SIZE.y)))
{
    rule = 0;
    p_active = 0.05f;
    moving = false;
    randomized = false;
    
    // Set view
    view.reset(DEFAULT_RECT);
    view.zoom(1.f);
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    
    // Set cursor
    cursor.loadFromSystem(sf::Cursor::Arrow);
    
    // Set window
    window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), TITLE);
    window.setFramerateLimit(30);
    window.setView(view);
    window.setMouseCursor(cursor);
    updateTitle();
    
    // Set eca
    eca.setConfig(COMPUTATION_SIZE);
    eca.setRule(rule);
    eca.setFixedInitialState(0.5f);
    eca.runComputation();
}

void Program::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) handleEvent(event);
        
        window.clear();
        window.draw(eca);
        window.display();
    }
}

void Program::handleEvent(const sf::Event & event) {
    if (event.type == sf::Event::Closed) window.close();
    
    handleMouseEvent(event);
    handleKeyboardEvent(event);
}

void Program::handleMouseEvent(const sf::Event & event) {
    switch (event.type) {
        case sf::Event::MouseWheelScrolled: {
            float factor = event.mouseWheelScroll.delta;
            view.zoom(std::exp(-0.05f*factor));
            window.setView(view);
        } break;
            
        case sf::Event::MouseButtonReleased:
            moving = false;
            cursor.loadFromSystem(sf::Cursor::Arrow);
            window.setMouseCursor(cursor);
            break;
            
        case sf::Event::MouseButtonPressed:
            moving = true;
            previous_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            cursor.loadFromSystem(sf::Cursor::Hand);
            window.setMouseCursor(cursor);
            break;
            
        case sf::Event::MouseMoved:
            if (moving) {
                sf::Vector2f new_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                view.move(previous_position - new_position);
                window.setView(view);
            }
            break;
            
        default:
            break;
    }
}

void Program::handleKeyboardEvent(const sf::Event & event) {
    if (event.type != sf::Event::KeyReleased) return;
    
    switch (event.key.code) {
        case sf::Keyboard::Left:
            rule = (rule+256-1)%256;
            eca.setRule(rule);
            eca.runComputation();
            window.setTitle(TITLE + " (" + std::to_string(rule) + ")");
            break;
            
        case sf::Keyboard::Right:
            rule = (rule+1)%256;
            eca.setRule(rule);
            eca.runComputation();
            window.setTitle(TITLE + " (" + std::to_string(rule) + ")");
            break;
            
        case sf::Keyboard::BackSpace:
            view.reset(DEFAULT_RECT);
            view.zoom(1.f);
            window.setView(view);
            break;
            
        case sf::Keyboard::R:
            eca.setRandomInitialState(p_active);
            eca.runComputation();
            randomized = true;
            break;
            
        case sf::Keyboard::F:
            eca.setFixedInitialState(0.5f);
            eca.runComputation();
            randomized = false;
            break;
            
        case sf::Keyboard::Return: {
            std::string filename = "ECA-" + std::to_string(rule) + "-";
            if (randomized) filename += "R";
            else            filename += "F";
            filename += ".png";
            
            std::string filepath = PATH + "/" + filename;
            
            sf::Texture texture;
            texture.create(window.getSize().x, window.getSize().y);
            texture.update(window);
            if (texture.copyToImage().saveToFile(filepath))
            {
                std::cout << "screenshot saved to " << filepath << std::endl;
            }
        }
            
        default:
            break;
    }
}

void Program::updateTitle() {
    window.setTitle(TITLE + " (" + std::to_string(rule) + ")");
}
