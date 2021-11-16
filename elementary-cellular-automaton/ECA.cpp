//
//  ECA.cpp
//  elementary-cellular-automaton
//
//  Created by Stephen Jaud on 16/11/2021.
//

#include "ECA.hpp"

std::vector<bool> getExplicitRule(int n);

ECA::ECA(sf::Vector2u resolution) {
    computation.create(resolution.x, resolution.y);
    drawable_computation.setTexture(computation.getTexture());
    drawable_computation.setScale(3, 3);
    width = resolution.x;
    height = resolution.y;
    
    initial_state.setPrimitiveType(sf::Points);
    initial_state.resize(width);
    
    computation_shader.loadFromFile("computation_step.frag", sf::Shader::Fragment);
    computation_shader.setUniform("width", static_cast<float>(width));
    
    setFixedInitialState(0.5);
    setRule(0);
}

void ECA::setRule(int r) {
    rule = getExplicitRule(r);
        
    computation_shader.setUniform("rule000", rule[0]);
    computation_shader.setUniform("rule001", rule[1]);
    computation_shader.setUniform("rule010", rule[2]);
    computation_shader.setUniform("rule011", rule[3]);
    computation_shader.setUniform("rule100", rule[4]);
    computation_shader.setUniform("rule101", rule[5]);
    computation_shader.setUniform("rule110", rule[6]);
    computation_shader.setUniform("rule111", rule[7]);
}

void ECA::setRandomInitialState(float prob) {
    sf::Vertex active_cell, inactive_cell;
    active_cell.color = sf::Color::Black;
    inactive_cell.color = sf::Color::White;
    
    for (int i = 0; i < width; i++) {
        float select = static_cast<float>(static_cast<float>(std::rand())/RAND_MAX);
        if (select < prob) {
            active_cell.position = sf::Vector2f(i, 0);
            initial_state[i] = active_cell;
        } else {
            inactive_cell.position = sf::Vector2f(i, 0);
            initial_state[i] = inactive_cell;
        }
    }
}

void ECA::setFixedInitialState(float pos) {
    if (pos <= 0) pos = 0;
    else if (pos > 1) pos = 1;
    
    sf::Vertex active_cell, inactive_cell;
    active_cell.color = sf::Color::Black;
    inactive_cell.color = sf::Color::White;
    
    for (int i = 0; i < width; i++) {
        inactive_cell.position = sf::Vector2f(i, 0);
        initial_state[i] = inactive_cell;
    }
    
    int index = static_cast<float>(pos*(width-1));
    active_cell.position = sf::Vector2f(index, 0);
    initial_state[index] = active_cell;
}

void ECA::runComputation() {
    computation.clear();
    
    sf::RenderTexture computation_state;
    computation_state.create(width, 1);
    sf::Sprite computation_state_sprite;
    computation_state_sprite.setTexture(computation_state.getTexture());
    computation_state.clear();
    computation_state.draw(initial_state);
    computation_state.display();
    
    sf::Texture empty_texture;
    empty_texture.create(width, 1);
    sf::Sprite empty_sprite;
    empty_sprite.setTexture(empty_texture);
    
    
    computation.draw(computation_state_sprite);
    for (int row = 1; row < height; row++) {
        computation_state_sprite.setPosition(0, 0);
        computation_shader.setUniform("previous", computation_state.getTexture());
        computation_state.draw(computation_state_sprite, &computation_shader);
        computation_state.display();
        
        computation_state_sprite.setPosition(0, row);
        computation.draw(computation_state_sprite);
    }
    
    computation.display();
}

void ECA::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(drawable_computation, states);
}


std::vector<bool> getExplicitRule(int n) {
    std::vector<bool> rule(8, false);
    
    if (n > 256 || n <= 0) return rule;
    
    int i = 0;
    while (n > 0) {
        int r = n%2;
        
        rule[i] = r;
        
        n = (n-r)/2;
        i++;
    }
    
    return rule;
}
