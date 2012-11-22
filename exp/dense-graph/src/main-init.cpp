#include "graph.hpp"
#include "func.hpp"
#include <memory>
#include <iostream>
#include <boost/progress.hpp>

int main( int argc, char* args[] ) {
  boost::progress_timer timer;


  Large arraySize = GRAPH_THETA * GRAPH_HEIGHT * GRAPH_WIDTH * 3;
  std::cout << "Edge Array Size: " << arraySize << "." << std::endl;
  Large arrayByteSize = sizeof( EdgeArray );
  std::cout << "Edge Array Byte Size: " << arrayByteSize << " bytes." << std::endl;
  Edge** edgesArray = (Edge**)new EdgeArray*;

  std::auto_ptr< Edge > edgesBetweenThatArray( (Edge*)(*edgesArray) );

  fillEdges( edgesArray );
  std::cout << "In file: " << __FILE__ << std::endl;
  std::cout << "Execution Time for \"" << __FUNCTION__ << "\": ";
  return 0;
}
