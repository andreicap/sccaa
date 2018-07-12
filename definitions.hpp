#ifndef _DEFINITIONS
#define _DEFINITIONS

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/random.hpp>
#include <boost/random.hpp>
#include <stack>
#include <iostream>
#include <vector>

//erdos dependencies
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp> 

using namespace std;

//==============================================================================
struct node_properties
{
  int component;
};
struct edge_properties
{
};
struct graph_properties
{
  int number_of_components;
};

//--------------------------------------
typedef boost::adjacency_list<
  boost::vecS, 
  boost::vecS, 
  boost::directedS,
  node_properties, 
  edge_properties, 
  graph_properties> graph_t;
  
typedef typename boost::graph_traits<graph_t>::vertex_descriptor vertex_t;
typedef typename boost::graph_traits<graph_t>::edge_descriptor edge_t;

//erdos generator type
typedef boost::erdos_renyi_iterator<boost::minstd_rand, graph_t> ERGen;


//vars used in all agorithms
vector<bool> visited;
vector<int> r_index;
vector<bool> inComponent;
stack<int> S;
int vindex;
int c; // component number.

graph_t *g;



//====utils==================================================================

//print graph
void print_graph(const graph_t &graph)
{
  cout << "Graph ->" << "vertices: "<< boost::num_vertices(graph) << ", edges: " << boost::num_edges(graph) << endl;
  auto edges = boost::edges(graph);
  for (auto it = edges.first; it != edges.second; ++it)
  {
    cout << boost::source(*it, graph) << " -> "
              << boost::target(*it, graph) << endl;
  }
}


//show boost component detection
void readSCC(graph_t graph_in)
{
  int nn = boost::num_vertices(graph_in);
  vector<int> cc(nn);
  int num = strong_components(graph_in, make_iterator_property_map(cc.begin(), get(boost::vertex_index, graph_in), cc[0]));

  cout << "Boost:: Total number of components: " << num << endl;

  for (int comps=0; comps<num; comps++)
  {

    cout << "Compenent " << comps  << ": ";
    for (int i = 0; i < cc.size(); i++)
    {
      if (comps == cc[i])
         cout<<i<<' ';
    }
    cout<<endl;
  }   
  cout<<endl;
}

#endif