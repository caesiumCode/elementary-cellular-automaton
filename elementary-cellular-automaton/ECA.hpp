//
//  ECA.hpp
//  elementary-cellular-automaton
//
//  Created by Stephen Jaud on 16/11/2021.
//

#ifndef ECA_hpp
#define ECA_hpp

#include <SFML/Graphics.hpp>

class ECA : public sf::Drawable {
public:
    ECA(sf::Vector2u resolution);
    
    void setRule(int r);
    void setRandomInitialState(float prob);
    void setFixedInitialState(float pos);
    void runComputation();
    
private:
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    unsigned int width, height;
    
    std::vector<bool>   rule;
    sf::VertexArray     initial_state;
    sf::RenderTexture   computation;
    sf::Shader          computation_shader;
    sf::Sprite          drawable_computation;
};

#endif /* ECA_hpp */
