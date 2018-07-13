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
  int e_number = v_number * 2;

  //boost random generator
  
  boost::mt19937 rng;
  rng.seed(uint32_t(time(0)));
  boost::generate_random_graph(g, v_number, e_number, rng);
  

  // erdos random graph generator 
  
  // float epsilon = 0.1;
  // boost::minstd_rand gen;
  // gen.seed(uint32_t(time(0)));
  // graph_t gr(ERGen(gen, v_number, epsilon), ERGen(), v_number);
  // g = gr;


  /* *************************************************  */
  /* * creates random graph without parallel edges and self lopps */
  // srand(time(NULL));
  // //void srand(int seed);
  // int floor, num;

  // for (int i = 0; i < v_number; i++)
  // {
  //   //cout << "create vertix " << i << endl;
  //   vertices.push_back(boost::add_vertex(g));
  // }
  // for (int source = 0; source < v_number; source++)
  // {
  //   floor = 0;
  //   do
  //   {
  //     // the target node is always greater thant the previous one
  //     // no parallel loops
  //     floor = rand() % v_number + floor;
  //     // the vertex index cannot be greater than number of vertices
  //     if (floor < v_number)
  //     {
  //       add_edge(vertices.at(source), vertices.at(floor), g);
  //       // disallow self loops
  //       floor++;
  //     }
  //   } while (floor <= v_number);
  // }

  /* *************************************************  */
  size_t e = boost::num_edges(g);
  size_t n = boost::num_vertices(g);
  cout << "generated " << e << " edges, " << n << " vertices\n";

  print_graph(g);

  //boost implementation
  readSCC(g);

  //pearce recursive first implementation
  pr1 (g);
  
  //pearce improved
  pr2 (g);


  //nuutila implementaion
  nuutila_recursive(g);

  tarjan_recursive(g);
  

  return 0;
}