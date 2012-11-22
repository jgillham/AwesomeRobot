#ifndef INCLUDED_FUNC
#define INCLUDED_FUNC
#include "graph.hpp"
#include <iostream>// For pair
typedef long long Large;
typedef std::pair<int, int> Edge;
typedef Edge (EdgeArray)[3][GRAPH_THETA][GRAPH_HEIGHT][GRAPH_WIDTH];

void fillEdges( Edge* edgesArray );
Large getDenseGraphLookup( Large c, Large r, Large t );
Large getEdgeLookup( Large type, Large c, Large r, Large t );


#endif // INCLUDED_FUNC

