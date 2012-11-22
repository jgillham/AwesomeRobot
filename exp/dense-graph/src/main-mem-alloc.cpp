//#include <boost/graph/adjacency_list.hpp>
#include <malloc.h>
#include <iostream>
#include "graph.hpp"
#include "func.hpp"
#include <boost/progress.hpp>


//// Connects from top to bottom
// (GRAPH_HEIGHT - 1)(GRAPH_WIDTH)(GRAPH_THETA) +
//// Connections from left to right
//   (GRAPH_WIDTH - 1)(GRAPH_HEIGHT)(GRAPH_THETA) +
//// Connects from surface to depth
//   (GRAPH_THETA - 1)(GRAPH_HEIGHT)(GRAPH_WIDTH)

int main( int argc, char* args[] ) {
  boost::progress_timer timer;
  Edge* edgesBetweenThatArray = (Edge*)new EdgeArray;
  free( edgesBetweenThatArray );
  std::cout << "In file: " << __FILE__ << std::endl;
  std::cout << "Execution Time for \"" << __FUNCTION__ << "\": ";
  return 0;
}



