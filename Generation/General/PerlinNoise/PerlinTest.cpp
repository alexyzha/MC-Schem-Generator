#include "PerlinNoise.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main() {
    Perlin P = Perlin(4,3,200,0xDEADBEEF);
    MAT<float>& ret = P.get_noise();
    //  RGBA, 800x600 x/y
    sf::Uint8* display = new sf::Uint8[800*600*4];
    for(int i = 0; i < 800; ++i) {
        for(int j = 0; j < 600; ++j) {
            int ind = (j*800+i)*4;
            int color = (int)((ret[i][j]+1.0f)*0.5f*255);
            display[ind] = color;
            display[ind+1] = color;
            display[ind+2] = color;
            display[ind+3] = 255;            
        }
    }
    
    //  Make sprite and window
    sf::Texture texture;
    sf::Sprite sprite;
    texture.create(800,600); 
    texture.update(display);
    sprite.setTexture(texture);
    sf::RenderWindow window(sf::VideoMode(800,600),"test");

    //  Main window loop
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    return 0;
}