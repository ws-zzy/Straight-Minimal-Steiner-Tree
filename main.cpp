#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>

#include "matplotlibcpp.h"
#include "smt.h"
namespace plt = matplotlibcpp;


int main( int argc, char** argv)
{
    if ( argc != 2 )
        return -1;

    std::ifstream file(argv[1]);
    if (!file.is_open()) throw "Cant open file / Wrong way";

    plt::title("steiner tree");
    int grid_size;
    int pin_count;
    file >> grid_size >> pin_count;
    plt::xlim(0, grid_size);
    plt::ylim(0, grid_size);
    SMT smt( grid_size, pin_count);

    int x, y;
    while (file >> x >> y) {
        smt.AddPin(x, y);
        plt::scatter(std::vector<int>({x}), std::vector<int>({y}), 20.0, {{"color", "k"}});
    }

    int len = smt.BuildSMT();
    std::cout << len << std::endl;

    std::list<SMT::Point> sol_points = smt.GetPointsList();
    std::list<SMT::Edge> sol_edges = smt.GetEdgesList();

    std::ofstream output(argv[2]);


    for ( auto it = sol_edges.begin();
          it != sol_edges.end();
          ++it)
    {
        int x1 = ( *it).GetPosX1();
        int y1 = ( *it).GetPosY1();
        int x2 = ( *it).GetPosX2();
        int y2 = ( *it).GetPosY2();

        plt::plot({x1, x2}, {y1, y2}, {{"color", "c"}, {"linewidth", "2.0"}});
    }
    plt::save("./output/n" + std::to_string(grid_size)+"_m"+std::to_string(pin_count)+".png");
    plt::show();

    return 0;
}
