#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
#include <limits.h>

/*
 *  Matrix typing convenience
 */
#ifndef MAT_MACRO
#define MAT_MACRO
#define vcA template<class A
vcA> using V = std::vector<A>;
vcA> using MAT = V<V<A>>;
using pff = std::pair<float,float>;
#endif

class Perlin {
public:
    /*
     *  @param discrete_x discrete grid width
     *  @param discrete_y discrete grid height
     *  @param split resolution multiplier (root)
     */
    Perlin(int discrete_x, int discrete_y, int split, int seed = static_cast<unsigned>(time(0)));

    /*
     *  Returns true_resolution grid
     */
    MAT<float>& get_noise();

private:
    /*
     *  Discrete grid
     */
    MAT<pff> lattice;

    /*
     *  True resolution (output)
     */
    MAT<float> true_resolution;

    /*
     *  For angle generation
     */
    std::mt19937 gen;
    std::normal_distribution<float> dist;

    /*
     *  Returns a pair<float,float>
     *  x = sin(num), y = cos(num)
     *  Since sin^2 + cos^2 = 1
     *  - {x,y}
     */
    pff rand_vector();

    /*
     *  Returns dot product between unit vector 
     *  at (corner_x,corner_y) and vector from 
     *  (corner_x,corner_y) to (cont_x,cont_y)
     */
    float dot_product(int corner_x, int corner_y, float cont_x, float cont_y);

    /*
     *  Quadratic function for smoother values.
     *  - 6x^5-15x^4+10x^3
     */
    float fade_function(float x);

    /*
     *  Combine results from dot product for all 4 corners
     *  and fade function results to generate one final
     *  nose value.
     *  @param x continuous x value
     *  @param y continuous y value
     *  - Interpolate both bottom and top rows
     *  - Interpolate both rows for a final value
     */
    float bilinear_interpolation(float x, float y);

};