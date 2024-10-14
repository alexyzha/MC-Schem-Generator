#include "PerlinNoise.h"

Perlin::Perlin(int discrete_x, int discrete_y, int split, int seed) {
    //  Seeding + PRNG
    gen = std::mt19937(seed);
    dist = std::normal_distribution<float>(0.5f,0.15f);
    //  Make all grids
    //  discrete_x/y+1 because the upper bounds are inclusive, ex [0,8] inclusive, therefore 9 indices
    lattice = MAT<pff>(discrete_x+1,V<pff>(discrete_y+1));
    for(auto&vec:lattice)
        for(auto&pr:vec)
            pr = rand_vector();
    true_resolution = MAT<float>(discrete_x*split,V<float>(discrete_y*split));
    //  Steps between each discrete index
    float step = 1.0f/(split+1);
    //  Calculate all
    for(int i = 0; i < discrete_x; ++i) {
        for(int j = 0; j < discrete_y; ++j) {
            int base_x = i*split;
            int base_y = j*split;
            for(int k = 0; k < split; ++k) {
                for(int l = 0; l < split; ++l) {
                    float noise_val = bilinear_interpolation(i+(k+1)*step,j+(l+1)*step);
                    true_resolution[base_x+k][base_y+l] = noise_val;
                }
            }
        }
    }
}

MAT<float>& Perlin::get_noise() {
    return true_resolution;
}

pff Perlin::rand_vector() {
    float angle = dist(gen);
    //  Fix OOB
    if(angle < 0.0f)
        angle = 0.0f;
    if(angle > 1.0f)
        angle = 1.0f;
    angle *= 2.0f * M_PI;
    return {cos(angle),sin(angle)};
}

float Perlin::dot_product(int corner_x, int corner_y, float cont_x, float cont_y) {
    float vec_x = cont_x-corner_x;
    float vec_y = cont_y-corner_y;
    return lattice[corner_x][corner_y].first*vec_x + lattice[corner_x][corner_y].second*vec_y;
}

float Perlin::fade_function(float x) {
    return (6.0f*std::pow(x,5))
          -(15.0f*std::pow(x,4))
          +(10.0f*std::pow(x,3));
}

float Perlin::bilinear_interpolation(float x, float y) {
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