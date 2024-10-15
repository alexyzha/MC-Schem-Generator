#include <vector>
#include <utility>
#include <ctime>
#include <stack>
#include "Default.h"

#ifndef MAT_MACRO
#define MAT_MACRO
#define vcA template<class A
vcA> using V = std::vector<A>;
vcA> using MAT = V<V<A>>;
using pi = std::pair<int,int>;
using u8 = uint8_t;
#endif

#ifndef DIR
#define DIR
const pi dir[4] = {{0,-1},{1,0},{0,1},{-1,0}};
#endif

class Maze {
public:
    Maze(int seed = (int)time(0));
    void set_width(int width);
    void set_height(int height);
    MAT<u8> make_maze(int seed);
private:
    int WIDTH;
    int HEIGHT;
    int SEED;
    void random_walk(std::stack<pi>& walk);
    void clean_path(std::stack<pi>& walk);
    bool valid(pi cur);
    bool valid(int x, int y);
    bool pi_comp(pi& a, pi& b);
    pi get_next(int x, int y);
};