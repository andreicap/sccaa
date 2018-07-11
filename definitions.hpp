
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


//==============================================================================
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
  vector<int>::iterator i;

  for (int comps=0; comps<num; comps++)
  {
    int counter = 0;
    for (i = cc.begin(); i != cc.end(); ++i)
    {
      if (comps == *i)
        counter++;
    }
    cout << "Compenent " << comps  << ": " <<counter;
    cout<<endl;
  }   
  cout<<endl;
}

#endif