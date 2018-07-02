#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/strong_components.hpp>
#include <stack>

#include <iostream>
#include <vector>

//==============================================================================
struct node_properties {
  int component;
};
struct edge_properties {
};
struct graph_properties {
  int number_of_components;
};

//--------------------------------------
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
    node_properties, edge_properties, graph_properties>          graph_t;
typedef typename boost::graph_traits<graph_t>::vertex_descriptor vertex_t;
typedef typename boost::graph_traits<graph_t>::edge_descriptor   edge_t;

//==============================================================================
void print_graph(const graph_t &graph) {
  std::cout << "Graph:" << std::endl;
  auto edges = boost::edges(graph);
  for (auto it = edges.first; it != edges.second; ++it) {
    std::cout << boost::source(*it, graph) << " -> "
              << boost::target(*it, graph) << std::endl;
  }
}

//==============================================================================
void print_components(const graph_t &graph) {
  std::cout << "\nComponents: "
            << graph[boost::graph_bundle].number_of_components << std::endl;
  auto nodes = boost::vertices(graph);
  for (auto it = nodes.first; it != nodes.second; ++it) {
    std::cout << "Node: " << *it << " component: " << graph[*it].component
              << std::endl;
  }
}

//==============================================================================
void strong_components(graph_t &graph) {
  std::vector<edge_t> temp_edges;

  auto edges = boost::edges(graph);

  for (auto it = edges.first; it != edges.second; ++it) {
    auto pair = boost::add_edge(boost::target(*it, graph),
                                boost::source(*it, graph),
                                graph);
    temp_edges.push_back(pair.first);
  }

  graph[boost::graph_bundle].number_of_components = 
      boost::strong_components(graph, 
                               boost::get(&node_properties::component, graph));

  for (const auto & e : temp_edges) {
    boost::remove_edge(e, graph);
  }    
}
// visit pearce
// 
//

graph_t graph;
std::vector<vertex_t> vertices;


std::vector<bool> visited(10000);
std::vector<int> r_index(100000);
std::vector<bool> inComponent(10000);
std::stack<vertex_t> S;
int vindex = 0;
int c = 0; // component number

int pearce_strong_components(int v) {
  bool root = true;
  visited[v] = true;
  // std::cout<<"\n Check! \n"<<visited[v]<<"\n";
  r_index[v] = vindex; 
  vindex++;
  inComponent[v] = false;

  std::vector<edge_t> temp_edges;
  auto edges = boost::edges(graph);
  
  for (auto it = edges.first; it != edges.second; ++it) {
    if (!visited[boost::target(*it, graph)]) {
      pearce_strong_components(boost::target(*it, graph));
    }
    if (inComponent[boost::target(*it, graph)])
    {
      /* code */
    }
  }


  
  return 0; 
}



//==============================================================================
int main() {


  vertices.push_back(boost::add_vertex(graph));
  vertices.push_back(boost::add_vertex(graph));
  vertices.push_back(boost::add_vertex(graph));
  vertices.push_back(boost::add_vertex(graph));
  vertices.push_back(boost::add_vertex(graph));

  boost::add_edge(vertices.at(0), vertices.at(1), graph);
  boost::add_edge(vertices.at(0), vertices.at(2), graph);
  boost::add_edge(vertices.at(1), vertices.at(2), graph);
  boost::add_edge(vertices.at(4), vertices.at(3), graph);

  graph[boost::graph_bundle].number_of_components = 
      boost::connected_components(graph, 
                                  boost::get(&node_properties::component, graph));

  std::cout << "Without adaption:\n-----------------" << std::endl;
  print_graph(graph);
  print_components(graph);

  strong_components(graph);
  pearce_strong_components(0);

  std::cout << "\nWith additional edges:\n----------------------" << std::endl;
  print_graph(graph);  
  print_components(graph);
}