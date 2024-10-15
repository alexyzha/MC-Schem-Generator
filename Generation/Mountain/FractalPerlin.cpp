#include "FractalPerlin.h"

FPerlin::FPerlin() {};

float FPerlin::noise(float x, float y, int octaves) {
    float amp = 1.0f;
    float freq = 1.0f;
    float ret = 0.0f;
    for(;octaves;--octaves) {
        ret += bilinear_interpolation(x*freq,y*freq)*amp;
        amp *= 0.5f;
        freq *= 2.0f;
    }
    return ret;
}

pff FPerlin::unit_vector(int x, int y) {
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = x, b = y;
    a *= 3284157443;
    b ^= a << s | a >> w-s;
    b *= 1911520717;
    a ^= b << s | b >> w-s;
    a *= 2048419325;
    float random = a * (3.14159265/~(~0u >> 1));
    return {std::cos(random),std::sin(random)};
}

float FPerlin::fade_function(float x) {
    return (6.0f*std::pow(x,5))
          -(15.0f*std::pow(x,4))
          +(10.0f*std::pow(x,3));
}

float FPerlin::dot_product(int corner_x, int corner_y, float cont_x, float cont_y) {
    float vec_x = cont_x-corner_x;
    float vec_y = cont_y-corner_y;
    pff uvec = unit_vector(corner_x,corner_y);
    return uvec.first*vec_x + uvec.second*vec_y;
}

float FPerlin::bilinear_interpolation(float x, float y) {
    //  Bounding box low/high x coords
    int low_x = static_cast<int>(x);
    int high_x = low_x+1;
    int low_y = static_cast<int>(y);
    int high_y = low_y+1;
    //  Fractional obtained from fade function
    float frac_x = fade_function(x-low_x);
    float frac_y = fade_function(y-low_y);
    //  Dot product for all 4 bounding box corners
    float dot_ll = dot_product(low_x,low_y,x,y),
          dot_lh = dot_product(low_x,high_y,x,y),
          dot_hl = dot_product(high_x,low_y,x,y),
          dot_hh = dot_product(high_x,high_y,x,y);
    //  Interpolate
    float interpolate_bottom = (1.0f-frac_x)*dot_ll + frac_x*dot_hl;
    float interpolate_top = (1.0f-frac_x)*dot_lh + frac_x*dot_hh;
    return (1.0f-frac_y)*interpolate_bottom + frac_y*interpolate_top;
}