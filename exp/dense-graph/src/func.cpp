#include "func.hpp"
#include <boost/progress.hpp>
#include <iostream>

void fillEdges( Edge* edgesArray ) {
  boost::progress_timer timer;
  // Connections going horizontal.
  for( int t = 0; t < GRAPH_THETA; ++t ) {
    for( int r = 0; r < GRAPH_HEIGHT; ++r ) {
      for( int c = 0; c < GRAPH_WIDTH - 1; ++c ) {
        Large firstNodeIndex = getDenseGraphLookup( c, r, t );
        Large secondNodeIndex = getDenseGraphLookup( c + 1, r, t );
//        std::cout << "c: " << c << std::endl;
//        std::cout << "r: " << r << std::endl;
//        std::cout << "t: " << t << std::endl;
//        std::cout << "firstNodeIndex: " << firstNodeIndex << std::endl;
//        std::cout << "secondNodeIndex: " << secondNodeIndex << std::endl;
//        std::cout << "getEdgeLookup( 0, c, r, t ): " << getEdgeLookup( 0, c, r, t ) << std::endl;

        // Call the constructor on previously allocated memory
        *(edgesArray + getEdgeLookup( 0, c, r, t ) ) = Edge( firstNodeIndex, secondNodeIndex );
        // OR
        new (edgesArray + getEdgeLookup( 0, c, r, t ) ) Edge( firstNodeIndex, secondNodeIndex );

      }

    }
  }

  // Connections going horizontal.
  for( int t = 0; t < GRAPH_THETA; ++t ) {
    for( int r = 0; r < GRAPH_HEIGHT - 1; ++r ) {
      for( int c = 0; c < GRAPH_WIDTH; ++c ) {
        Large firstNodeIndex = getDenseGraphLookup( c, r, t );
        Large secondNodeIndex = getDenseGraphLookup( c, r + 1, t );
        *(edgesArray + getEdgeLookup( 1, c, r, t ) ) = Edge( firstNodeIndex, secondNodeIndex );
      }
    }
  }

  // Connections going horizontal.
  for( int t = 0; t < GRAPH_THETA - 1; ++t ) {
    for( int r = 0; r < GRAPH_HEIGHT; ++r ) {
      for( int c = 0; c < GRAPH_WIDTH; ++c ) {
        Large firstNodeIndex = getDenseGraphLookup( c, r, t );
        Large secondNodeIndex = getDenseGraphLookup( c, r, t + 1 );
        *(edgesArray + getEdgeLookup( 2, c, r, t ) ) = Edge( firstNodeIndex, secondNodeIndex );
      }
    }
  }
  std::cout << "In file: " << __FILE__ << std::endl;
  std::cout << "Execution Time for \"" << __FUNCTION__ << "\": ";
}

Large getDenseGraphLookup( Large c, Large r, Large t ) {
  return t * GRAPH_WIDTH * GRAPH_HEIGHT + r * GRAPH_WIDTH + c;
}

Large getEdgeLookup( Large type, Large c, Large r, Large t ) {
  return type * GRAPH_WIDTH * GRAPH_HEIGHT * GRAPH_THETA + t * GRAPH_WIDTH * GRAPH_HEIGHT + r * GRAPH_WIDTH + c;
}
