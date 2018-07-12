#include "definitions.hpp"
#include "pearce_recursive_1.hpp"
#include "pearce_recursive_2.hpp"
#include "tarjan.hpp"
#include "nuutila.hpp"

int main(int argc, char const *argv[])
{
  graph_t g;
  vector<vertex_t> vertices;

  int v_number = strtol(argv[1], NULL, 10);
  int e_number = v_number*2;
  
  //boost random generator
  
  // boost::mt19937 rng;
  // rng.seed(uint32_t(time(0)));
  // boost::generate_random_graph(g, v_number, e_number, rng);
  

  //erdos generator
  float epsilon = 0.14;
  boost::minstd_rand gen;
  gen.seed(uint32_t(time(0)));
  graph_t gr(ERGen(gen, v_number, epsilon), ERGen(), v_number);
  g = gr;





  print_graph(g);
  
  //boost implementation
  readSCC(g);

  //nuutila implementaion
  nuutila_recursive(g);
  
  //pearce recursive first implementation
  pr1 (g);

  //pearce improved
  pr2 (g);

  //tarjan implementation
  tarjan_recursive(g);

  return 0;
  
}