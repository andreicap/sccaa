// Copyright (C) 2006-2009 Dmitry Bufistov and Andrey Parfenov

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <ctime>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/graph/howard_cycle_ratio.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/random.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp> 
#include <boost/random.hpp>
#include <boost/config.hpp>
#include <stack>
#include <iostream>
#include <vector>

/**
 * @author Dmitry Bufistov
 * @author Andrey Parfenov
 */

using namespace boost;

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

// --------------------------------------
// typedef boost::adjacency_list<
//   boost::vecS, 
//   boost::vecS, 
//   boost::directedS,
//   node_properties, 
//   edge_properties, 
//   graph_properties> graph_t;


typedef adjacency_list<
    vecS, vecS, directedS,
    node_properties,
    property<
        edge_weight_t, double, 
        property<edge_weight2_t, double> >,
    graph_properties
> graph_t;

template <typename TG>
void gen_rand_graph(TG &g, size_t nV, size_t nE)
{
    g.clear();
    mt19937 rng;
    rng.seed(uint32_t(time(0)));
    boost::generate_random_graph(g, nV, nE, rng, true, true);
    boost::uniform_real<> ur(-1,10);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<> >   ew1rg(rng, ur);
    randomize_property<edge_weight_t>(g, ew1rg);
    boost::uniform_int<size_t> uint(1,5);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<size_t> >      ew2rg(rng, uint);
    randomize_property<edge_weight2_t>(g, ew2rg);
}



  
typedef typename boost::graph_traits<graph_t>::vertex_descriptor vertex_t;
typedef typename boost::graph_traits<graph_t>::edge_descriptor edge_t;

graph_t graph_local;
std::vector<vertex_t> vertices;

int  nn = 100;
int e = 15;
std::vector<bool> visited(nn, false);
std::vector<int> r_index(nn, 0);
std::vector<bool> inComponent(nn, false);
std::stack<int> S;
int vindex = 0;
int c = 0; // component number


//==============================================================================
void print_graph(const graph_t &graph_local)
{
  std::cout << "graph_local:" << std::endl;
  auto edges = boost::edges(graph_local);
  for (auto it = edges.first; it != edges.second; ++it)
  {
    std::cout << boost::source(*it, graph_local) << " -> "
              << boost::target(*it, graph_local) << std::endl;
  }
}

void readSCC(graph_t graph_in, int nn)
{
  std::vector<int> cc(nn);
  int num = strong_components(graph_in, make_iterator_property_map(cc.begin(), get(boost::vertex_index, graph_in), cc[0]));

  std::cout << "Total number of components: " << num << std::endl;
  std::vector<int>::iterator i;
  for (i = cc.begin(); i != cc.end(); ++i)
    std::cout << "Vertex " << i - cc.begin()
              << " is in component " << *i << std::endl;
  //std::cout << "" << i - cc.begin();
}


void visit(int v)
{
  bool root = true;
  visited[v] = true;
  r_index[v] = vindex;
  vindex = vindex + 1;
  inComponent[v] = false;
  auto edges = boost::edges(graph_local);
  for (auto it = edges.first; it != edges.second; ++it)
  {
    int w = boost::target(*it, graph_local);
    int s = boost::source(*it, graph_local);

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
typedef boost::erdos_renyi_iterator<boost::minstd_rand, graph_t> ERGen;

//==============================================================================
int main()
{

  const double epsilon = 0.02;
  // double min_cr, max_cr; ///Minimum and maximum cycle ratio
  // typedef std::vector<graph_traits<graph_t>::edge_descriptor> ccReal_t;
  // ccReal_t cc; ///critical cycle

  // graph_t tgr;
  // property_map<graph_t, vertex_index_t>::type vim = get(vertex_index, tgr);
  // property_map<graph_t, edge_weight_t>::type ew1 = get(edge_weight, tgr);
  // property_map<graph_t, edge_weight2_t>::type ew2 = get(edge_weight2, tgr);

  // gen_rand_graph(tgr, nn, e);
  // std::cout << "Vertices number: " << num_vertices(tgr) << std::endl;
  // std::cout << "Edges number: " << num_edges(tgr) << std::endl;

  std::cout<<"test";
  // graph_local = tgr;
  // Create graph with nn nodes and edges with probability p
  boost::minstd_rand gen;
  graph_t gr(ERGen(gen, nn, epsilon), ERGen(), nn);
  graph_local = gr;
  // print_graph(graph_local);
  //random generation;
  // boost::mt19937 rng;
  // boost::generate_random_graph(graph_local, nn, e, rng);
  // size_t e = boost::num_edges(graph_local);
  // size_t n = boost::num_vertices(graph_local);

  // boost implementation
  // graph_local[boost::graph_bundle].number_of_components =
  //     boost::connected_components(graph_local,
  //                                 boost::get(&node_properties::component, graph_local));
  readSCC(graph_local, nn);

  for (int i = 0; i < nn; i++)
  {
    std::cout<<"\n i="<<i<<"\n";
    if (!visited[i])
    {
      visit(i);
    }
  }

  std::cout << "\nComponents : ----------" << c << std::endl;

  for (auto i = r_index.begin(); i != r_index.end(); ++i)
    std::cout << *i << ' ';
  //std::cout << "\n ***************************************" << std::endl;
  //std::cout << "\nTrue boost graph_local implementation : \n----------------------" << std::endl;



  return 0;
}