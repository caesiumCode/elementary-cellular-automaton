//
//  main.cpp
//  elementary-cellular-automaton
//
//  Created by Stephen Jaud on 16/11/2021.
//

#include <iostream>
#include <SFML/Graphics.hpp>

std::vector<bool> getExplicitRule(int n);

int main(int argc, const char * argv[]) {
    const sf::Vector2u WINDOW_RESOLUTION(2200, 1500);
    const sf::Vector2u TEXTURE_RESOLUTION(512, 512);
    float scale = 10;
    
    std::vector<bool> rule = getExplicitRule(30);
    
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y), "Elementary Cellular Automaton");
    window.setFramerateLimit(30);
    
    sf::RenderTexture texture;
    texture.create(TEXTURE_RESOLUTION.x, TEXTURE_RESOLUTION.y);
    texture.clear(sf::Color::White);
    
    sf::Sprite sprite;
    sprite.setOrigin(TEXTURE_RESOLUTION.x/2, 0);
    sprite.setPosition(WINDOW_RESOLUTION.x/2, 0);
    sprite.setScale(scale, scale);
    sprite.setTexture(texture.getTexture());
    
    sf::Shader shader;
    shader.loadFromFile("computation_step.frag", sf::Shader::Fragment);
    shader.setUniform("width", static_cast<float>(TEXTURE_RESOLUTION.x));
    shader.setUniform("rule000", rule[0]);
    shader.setUniform("rule001", rule[1]);
    shader.setUniform("rule010", rule[2]);
    shader.setUniform("rule011", rule[3]);
    shader.setUniform("rule100", rule[4]);
    shader.setUniform("rule101", rule[5]);
    shader.setUniform("rule110", rule[6]);
    shader.setUniform("rule111", rule[7]);
    
    
    sf::RenderTexture computation_texture;
    computation_texture.create(TEXTURE_RESOLUTION.x, 1);
    computation_texture.clear(sf::Color::White);
    sf::Vertex point(sf::Vector2f(TEXTURE_RESOLUTION.x/2, 0), sf::Color::Black);
    computation_texture.draw(&point, 1, sf::Points);
    computation_texture.display();
    
    sf::Sprite computation_sprite;
    computation_sprite.setTexture(computation_texture.getTexture());
    
    computation_sprite.setPosition(0, 0);
    texture.draw(computation_sprite);
    
    sf::Texture empty_texture;
    empty_texture.create(TEXTURE_RESOLUTION.x, 1);
    sf::Sprite empty_sprite;
    empty_sprite.setTexture(empty_texture);
    
    for (int row = 1; row < TEXTURE_RESOLUTION.y; row++) {
        computation_sprite.setPosition(0, 0);
        shader.setUniform("previous", computation_texture.getTexture());
        computation_texture.draw(computation_sprite, &shader);
        computation_texture.display();
        
        computation_sprite.setPosition(0, row);
        texture.draw(computation_sprite);
    }
    
    
    
    texture.display();
    
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        
        window.clear();
        window.draw(sprite);
        window.display();
    }
    
    return EXIT_SUCCESS;
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
