#include "FractalPerlin.h"
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


int main(int argc, char* argv[]) {
    const int WIDTH = 60;
    const int LENGTH = 60;
    FPerlin P;
    int seed;
    std::cout << "seed?" << std::endl;
    std::cin >> seed;
    srand(seed);
    int div = rand() % 50 + 25;
    int x_offset = rand() % 0x0003ffff;
    int y_offset = rand() % 0x0003ffff;
    const float step = 1.0f/static_cast<float>(div);

    sf::Uint8* display = new sf::Uint8[WIDTH*LENGTH*4];

    for(int i = 0; i < WIDTH; ++i) {
        for(int j = 0; j < LENGTH; ++j) {
            int ind = (j*WIDTH+i)*4;
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
    texture.create(WIDTH,LENGTH); 
    texture.update(display);
    sprite.setTexture(texture);
    sf::RenderWindow window(sf::VideoMode(WIDTH,LENGTH),"test");

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
        std::vector<int> ret;
        int mn = 255;
        for(int i = 0; i < WIDTH; ++i) {
            for(int j = 0; j < LENGTH; ++j) {
                float col = P.noise((i+1+x_offset)*step,(j+1+y_offset)*step,5)*0.47f;
                if(col > 1.0f)
                    col = 1.0f;
                if(col < -1.0f)
                    col = -1.0f;
                col += 1.0f;
                col *= 0.5f;
                int TO_MC = (int)(col*255);
                mn = std::min(mn,TO_MC);
                ret.push_back(TO_MC);
            }
        }
        std::ofstream file(argv[1]);
        if(!file) {
            std::cerr << "invalid file path" << std::endl;
            return -1;
        }
        for(auto&i:ret)
            file << (i-(mn-10)) << std::endl;
        file.close();
    }

    return 0;
}