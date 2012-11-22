#include <iostream>
#include <fstream>
#include <boost/config.hpp>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include <boost/progress.hpp>
#include "graph.hpp"
#include "func.hpp"
#include <cassert>

using namespace boost;

int main( int argc, char** argv ) {

  typedef adjacency_list < listS, vecS, directedS,
    no_property, property < edge_weight_t, int > > graph_t;
  typedef graph_traits < graph_t >::vertex_descriptor vertex_descriptor;
  typedef graph_traits < graph_t >::edge_descriptor edge_descriptor;
  typedef std::pair<int, int> Edge;

  Large arraySize = GRAPH_THETA * GRAPH_HEIGHT * GRAPH_WIDTH * 3;
    std::cout << "Edge Array Size: " << arraySize << "." << std::endl;
    Large arrayByteSize = sizeof( EdgeArray );
    std::cout << "Edge Array Byte Size: " << arrayByteSize << " bytes." << std::endl;
    std::cout << "CHECKPOINT: " << __LINE__ << std::endl;
    Edge* edgesArray = (Edge*)new EdgeArray;

    std::auto_ptr< Edge > edgesBetweenThatArray( (Edge*)(edgesArray) );
    std::cout << "CHECKPOINT: " << __LINE__ << std::endl;

    fillEdges( edgesArray );
    std::cout << "CHECKPOINT: " << __LINE__ << std::endl;
    assert( edgesArray->first == 0 );
    assert( edgesArray->second == 1 );
    assert( (edgesArray + 1)->first == 1 );
    assert( (edgesArray + 1)->second == 2 );
    assert( getDenseGraphLookup( 0, 1, 0 ) == GRAPH_WIDTH );

    assert( (edgesArray + getEdgeLookup( 0, 0, 1, 0 ) )->first == getDenseGraphLookup( 0, 1, 0 ) );
    assert( (edgesArray + getEdgeLookup( 0, 0, 1, 0 ) )->second == getDenseGraphLookup( 1, 1, 0 ) );

    assert( (edgesArray + getEdgeLookup( 0, 1, 1, 0 ) )->first == getDenseGraphLookup( 1, 1, 0 ) );
    assert( (edgesArray + getEdgeLookup( 0, 1, 1, 0 ) )->second == getDenseGraphLookup( 2, 1, 0 ) );

    assert( (edgesArray + getEdgeLookup( 0, 0, 0, 1 ) )->first == getDenseGraphLookup( 0, 0, 1 ) );
    assert( (edgesArray + getEdgeLookup( 0, 0, 0, 1 ) )->second == getDenseGraphLookup( 1, 0, 1 ) );

    assert( (edgesArray + getEdgeLookup( 0, 1, 0, 1 ) )->first == getDenseGraphLookup( 1, 0, 1 ) );
    assert( (edgesArray + getEdgeLookup( 0, 1, 0, 1 ) )->second == getDenseGraphLookup( 2, 0, 1 ) );

    assert( (edgesArray + getEdgeLookup( 1, 0, 0, 0 ) )->first == getDenseGraphLookup( 0, 0, 0 ) );
    assert( (edgesArray + getEdgeLookup( 1, 0, 0, 0 ) )->second == getDenseGraphLookup( 0, 1, 0 ) );

    assert( (edgesArray + getEdgeLookup( 1, 1, 0, 0 ) )->first == getDenseGraphLookup( 1, 0, 0 ) );
    assert( (edgesArray + getEdgeLookup( 1, 1, 0, 0 ) )->second == getDenseGraphLookup( 1, 1, 0 ) );

    // create graph
    graph_t g(GRAPH_THETA * GRAPH_HEIGHT * GRAPH_WIDTH);
    property_map<graph_t, edge_weight_t>::type weightmap = get(edge_weight, g);
    std::cout << "CHECKPOINT: " << __LINE__ << std::endl;
    {
        boost::progress_timer timerWM;
        for ( int type = 0; type < 3; ++type ) {
            boost::progress_timer timerTheta;
            for ( int t = 0; t < GRAPH_THETA - ( (type == 2)?1:0 ); ++t ) {
                for ( int r = 0; r < GRAPH_HEIGHT - ( (type == 1)?1:0 ); ++r ) {
                    for ( int c = 0; c < GRAPH_WIDTH - ( (type == 0)?1:0 ); ++c ) {
                        Edge* current = edgesArray + getEdgeLookup( type, c, r, t );
                        edge_descriptor e;
                        bool inserted;
//            cout << "current->first: " << current->first << std::endl;
//            cout << "current->second: " << current->second << std::endl;
                        tie(e, inserted) = add_edge( current->first,
                                                     current->second, g);
                        // Treat all weights the same for now.
                        weightmap[e] = 1;
                    }
                }
            }
            std::cout << "In file: " << __FILE__ << std::endl;
            std::cout << "Execution Time for filling weightmap - THETA LOOP: ";
        }
        std::cout << "In file: " << __FILE__ << std::endl;
        std::cout << "Execution Time for filling weightmap: ";
    }

  std::vector<vertex_descriptor> p(num_vertices(g));
  std::vector<int> d(num_vertices(g));
  vertex_descriptor s = vertex(0, g);
{
 boost::progress_timer timerAStar;
#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
  // VC++ has trouble with the named parameters mechanism
  property_map<graph_t, vertex_index_t>::type indexmap = get(vertex_index, g);
  dijkstra_shortest_paths(g, s, &p[0], &d[0], weightmap, indexmap,
                          std::less<int>(), closed_plus<int>(),
                          (std::numeric_limits<int>::max)(), 0,
                          default_dijkstra_visitor());
#else
  dijkstra_shortest_paths(g, s, predecessor_map(&p[0]).distance_map(&d[0]));
#endif
  std::cout << "In file: " << __FILE__ << std::endl;
    std::cout << "Execution Time for A* search: ";
}

  std::cout << "distances and parents:" << std::endl;
  graph_traits < graph_t >::vertex_iterator vi, vend;
  int count = 0;
  for (boost::tie(vi, vend) = vertices(g); vi != vend; ++vi) {
    std::cout << "distance(" << *vi << ") = " << d[*vi] << ", ";
    std::cout << "parent(" << *vi << ") = " << p[*vi] << std::
      endl;
    if( count++ > GRAPH_WIDTH + 24 )
      return 0;
  }
  std::cout << std::endl;

  std::ofstream dot_file("./figs/dijkstra-eg.dot");

  dot_file << "digraph D {\n"
    << "  rankdir=LR\n"
    << "  size=\"4,3\"\n"
    << "  ratio=\"fill\"\n"
    << "  edge[style=\"bold\"]\n" << "  node[shape=\"circle\"]\n";

  graph_traits < graph_t >::edge_iterator ei, ei_end;
  for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
    graph_traits < graph_t >::edge_descriptor e = *ei;
    graph_traits < graph_t >::vertex_descriptor
      u = source(e, g), v = target(e, g);
    dot_file << u << " -> " << v
      << "[label=\"" << get(weightmap, e) << "\"";
    if (p[v] == u)
      dot_file << ", color=\"black\"";
    else
      dot_file << ", color=\"grey\"";
    dot_file << "]";
  }
  dot_file << "}";

  std::cout << "In file: " << __FILE__ << std::endl;
    std::cout << "Execution Time for \"" << __FUNCTION__ << "\": ";
  return EXIT_SUCCESS;
}
