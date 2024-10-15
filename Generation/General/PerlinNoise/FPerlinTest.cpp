#include "FractalPerlin.h"
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main(int argc, char* argv[]) {
    FPerlin P;
    int seed;
    std::cout << "seed?" << std::endl;
    std::cin >> seed;
    srand(seed);
    int div = rand() % 150 + 150;
    int x_offset = rand() % 0x0003ffff;
    int y_offset = rand() % 0x0003ffff;

    const float step = 1.0f/static_cast<float>(div);
    //  RGBA, 800x600 x/y
    sf::Uint8* display = new sf::Uint8[800*600*4];
    for(int i = 0; i < 800; ++i) {
        for(int j = 0; j < 600; ++j) {
            int ind = (j*800+i)*4;
            //  Up contrast, prune
            float col = P.noise((i+1+x_offset)*step,(j+1+y_offset)*step,7)*1.3f;
            if(col > 1.0f)
                col = 1.0f;
            if(col < -1.0f)
                col = -1.0f;
            //  Assign color
            int color = (int)((col+1.0f)*0.5f*255);
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

    //  Pass to py for 3D vis
    if(argc > 1) {
        std::ofstream file(argv[1]);
        if(!file) {
            std::cerr << "invalid file path" << std::endl;
            return -1;
        }
        for(int i = 0; i < 800; ++i) {
            for(int j = 0; j < 600; ++j) {
                float col = P.noise((i+1+x_offset)*step,(j+1+y_offset)*step,5)*0.47f;
                if(col > 1.0f)
                    col = 1.0f;
                if(col < -1.0f)
                    col = -1.0f;
                col += 1.0f;
                col *= 0.5f;
                file << col << std::endl;
            }
        }
        file.close();
    }

    return 0;
}