#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/random.hpp>
#include <boost/random.hpp>
#include <stack>
#include <iostream>
#include <vector>

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

graph_t graph;
std::vector<vertex_t> vertices;

int nn = 5;
std::vector<bool> visited(nn, false);
std::vector<int> r_index(nn, 0);
std::vector<bool> inComponent(nn, false);
std::stack<int> S;
int vindex = 0;
int c = 0; // component number


//==============================================================================
void print_graph(const graph_t &graph)
{
  std::cout << "Graph:" << std::endl;
  auto edges = boost::edges(graph);
  for (auto it = edges.first; it != edges.second; ++it)
  {
    std::cout << boost::source(*it, graph) << " -> "
              << boost::target(*it, graph) << std::endl;
  }
}

//==============================================================================
void print_components(const graph_t &graph)
{
  std::cout << "\nComponents: "
            << graph[boost::graph_bundle].number_of_components << std::endl;
  auto nodes = boost::vertices(graph);
  for (auto it = nodes.first; it != nodes.second; ++it)
  {
    std::cout << "Node: " << *it << " component: " << graph[*it].component
              << std::endl;
  }
}

//==============================================================================
void strong_components(graph_t &graph)
{
  std::vector<edge_t> temp_edges;

  auto edges = boost::edges(graph);

  for (auto it = edges.first; it != edges.second; ++it)
  {
    auto pair = boost::add_edge(boost::target(*it, graph),
                                boost::source(*it, graph),
                                graph);
    temp_edges.push_back(pair.first);
  }

  graph[boost::graph_bundle].number_of_components =
      boost::strong_components(graph,
                               boost::get(&node_properties::component, graph));

  for (const auto &e : temp_edges)
  {
    boost::remove_edge(e, graph);
  }
}

//==============================================================================



void visit(int v)
{
  bool root = true;
  visited[v] = true;
  r_index[v] = vindex;
  vindex = vindex + 1;
  inComponent[v] = false;
  auto edges = boost::edges(graph);
  for (auto it = edges.first; it != edges.second; ++it)
  {
    int w = boost::target(*it, graph);
    int s = boost::source(*it, graph);

    if (v == s)
    {
      //std::cout << "\n Visit for node: " << v << ", edge: " << s << "->" << w << "\n";
      if (!visited[w])
      {
        visit(w);
      }

      for (auto i = r_index.begin(); i != r_index.end(); ++i)
        //bool check = !(inComponent[w]) && (r_index[w] < r_index[v]);
        if (!(inComponent[w]) && (r_index[w] < r_index[v]))
        {
          r_index[v] = r_index[w];
          root = false;
        }
    }
  }

  if (root)
  {
    inComponent[v] = true;
    while (!S.empty())
    {
      while ((!S.empty()) && (r_index[v] <= r_index[S.top()]))
      {
        int w = S.top();
        S.pop();
        r_index[w] = c;
        inComponent[w] = true;
      }
    }
    r_index[v] = c;
    c = c + 1;
  }
  else
  {
    S.push(v);
  }
}

//==============================================================================
int main()
{

  //random generation;
  nn = 5;
  int e = 10;
  boost::mt19937 rng;
  boost::generate_random_graph(graph, nn, e, rng);
  // size_t e = boost::num_edges(graph);
  // size_t n = boost::num_vertices(graph);

  
  for (int i = 0; i < nn; i++)
  {
    if (!visited[i])
    {
      visit(i);
    }
  }

  std::cout << "\nComponents number SCC1: ----------" << c << std::endl;
  for (auto i = r_index.begin(); i != r_index.end(); ++i)
    std::cout << *i << ' ';
  //std::cout << "\n ***************************************" << std::endl;
  //std::cout << "\nTrue boost graph implementation : \n----------------------" << std::endl;
  
  print_graph(graph);
 


  return 0;
}