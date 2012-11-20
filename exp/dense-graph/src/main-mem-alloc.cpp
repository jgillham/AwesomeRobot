//#include <boost/graph/adjacency_list.hpp>
#include <malloc.h>
#define GRAPH_THETA 160
#define GRAPH_WIDTH 192
#define GRAPH_HEIGHT 192

int main( int argc, char* args[] ) {
  int* reallyBigArray = new int[GRAPH_THETA][GRAPH_HEIGHT][GRAPH_WIDTH];
  int* reallyBigArray = new int[GRAPH_THETA][GRAPH_HEIGHT][GRAPH_WIDTH][3];
  Edge* edgesBetweenThatArray = new Edge[GRAPH_THETA][GRAPH_HEIGHT][GRAPH_WIDTH][3];
  free( reallyBigArray );
  free( edgesBetweenThatArray );
  return 0;
}


//// Connects from top to bottom
// (GRAPH_HEIGHT - 1)(GRAPH_WIDTH)(GRAPH_THETA) +
//// Connections from left to right
//   (GRAPH_WIDTH - 1)(GRAPH_HEIGHT)(GRAPH_THETA) +
//// Connects from surface to depth
//   (GRAPH_THETA - 1)(GRAPH_HEIGHT)(GRAPH_WIDTH)
