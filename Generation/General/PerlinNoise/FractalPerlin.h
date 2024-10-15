#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>

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

class FPerlin {
public:
    /*
     *  @param discrete_x discrete grid width
     *  @param discrete_y discrete grid height
     *  @param split resolution multiplier (root)
     */
    FPerlin();

    /*
     *  Generate float values at continuous point
     *  @param x continuous x val
     *  @param y continuous y val
     *  @param octaves layers
     */
    float noise(float x, float y, int octaves = 1);

private:

    /*
     *  Returns a pair<float,float>
     *  x = sin(num), y = cos(num)
     *  Since sin^2 + cos^2 = 1
     *  - {x,y}
     *  - Deterministic PRNG
     */
    pff unit_vector(int x, int y);

    /*
     *  Quadratic function for smoother values.
     *  - 6x^5-15x^4+10x^3
     */
    float fade_function(float x);

    /*
     *  Returns dot product between unit vector 
     *  at (corner_x,corner_y) and vector from 
     *  (corner_x,corner_y) to (cont_x,cont_y)
     */
    float dot_product(int corner_x, int corner_y, float cont_x, float cont_y);

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