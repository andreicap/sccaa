#include "definitions.hpp"
#include "pearce_recursive_1.hpp"


int main(int argc, char const *argv[])
{
  graph_t g;
  vector<vertex_t> vertices;

  int v_number = 15;
  int e_number = v_number*2;
  boost::mt19937 rng;
  rng.seed(uint32_t(time(0)));
  boost::generate_random_graph(g, v_number, e_number, rng);
  // size_t e = boost::num_edges(graph);
  // size_t n = boost::num_vertices(graph);
  

  print_graph(g);
  //boost implementation
  readSCC(g);
  
  //pearce recursive first implementation
  pr1 (g);

  return 0;
  
}