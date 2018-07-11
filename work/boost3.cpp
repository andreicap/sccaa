#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/random.hpp>
#include <boost/random.hpp>
#include <stack>
#include <deque>
#include <iostream>
#include <vector>

//==============================================================================
//
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

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                              node_properties, 
                              edge_properties, 
                              graph_properties> 
                                graph_t;
typedef typename boost::graph_traits<graph_t>::vertex_descriptor vertex_t;
typedef typename boost::graph_traits<graph_t>::edge_descriptor edge_t;



graph_t graph;
std::vector<vertex_t> vertices;

int nn = 10;

std::vector<int> r_index(nn, 0);
std::vector<int> root(nn, 0);
std::deque<int> vS;
std::deque<int> iS;
int vindex = 1;
int c = nn - 1; // component number

void beginVisiting(int v)
{ // total: n(1 + 2w)
    vS.push_front(v);
    iS.push_front(0);
    root[v] = true;
    r_index[v] = vindex;
    vindex = vindex + 1;
}

void finishVisiting(int v)
{
    // Take this vertex off the call stacks
    vS.pop_front();
    iS.pop_front();
    // Update component information
    if (root[v])
    {
        vindex = vindex - 1;
        while (!vS.empty() && (r_index[v] <= r_index[vS.back()]))
        {
            int w = vS.back();
            vS.pop_back();
            r_index[w] = c;
            vindex = vindex - 1;
        }
        r_index[v] = c;
        c = c - 1;
    }
    else
    {
        vS.push_back(v);
    }
}

bool beginEdge(int v, int k)
{
    auto edges = boost::edges(graph);
    for (auto it = edges.first; it != edges.second; ++it)
    {
        int t = boost::target(*it, graph);
        int s = boost::source(*it, graph);
        if (v == s)
        {
            if (r_index[t] == 0)
            {
                iS.pop_front();
                iS.push_front(k + 1);
                beginVisiting(t);
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

void finishEdge(int v, int k)
{
    //int[] g_edges = graph.edges(v);
    //int w = g_edges[k];
    auto edges = boost::edges(graph);
    for (auto it = edges.first; it != edges.second; ++it)
    {
        int t = boost::target(*it, graph);
        int s = boost::source(*it, graph);
        if (v == s)
        {
            if (r_index[t] < r_index[v])
            {
                r_index[v] = r_index[t];
                root[v] = false;
            }
        }
    }
    return;
}

void visitLoop()
{
    int v = vS.front();
    int i = iS.front();
    auto edges = boost::edges(graph);
    size_t e = boost::num_edges(graph);
    while (i <= e)
    {
        if (i > 0)
        {
            finishEdge(v, i-1);
        }
        if (i < e && beginEdge(v, i))
        {
            return;
        }
        i++;
        std::cout<<"visitI \n" << i;
    }
    finishVisiting(v);
}

void visitI(int v)
{
    beginVisiting(v);

    while (!vS.empty())
    {
        visitLoop();
    }
    return;
}






//==============================================================================
int main()
{

    ///graph 1

    // vertices.push_back(boost::add_vertex(graph));
    // vertices.push_back(boost::add_vertex(graph));
    // vertices.push_back(boost::add_vertex(graph));
    // vertices.push_back(boost::add_vertex(graph));
    // vertices.push_back(boost::add_vertex(graph));
    // vertices.push_back(boost::add_vertex(graph));

    // boost::add_edge(vertices.at(0), vertices.at(1), graph);
    // boost::add_edge(vertices.at(1), vertices.at(2), graph);
    // boost::add_edge(vertices.at(2), vertices.at(0), graph);
    // boost::add_edge(vertices.at(2), vertices.at(3), graph);
    // boost::add_edge(vertices.at(3), vertices.at(4), graph);
    // boost::add_edge(vertices.at(4), vertices.at(5), graph);
    // boost::add_edge(vertices.at(5), vertices.at(3), graph);

    //graph2
    vertices.push_back(boost::add_vertex(graph));
    vertices.push_back(boost::add_vertex(graph));
    vertices.push_back(boost::add_vertex(graph));
    vertices.push_back(boost::add_vertex(graph));
    vertices.push_back(boost::add_vertex(graph));
    vertices.push_back(boost::add_vertex(graph));
    vertices.push_back(boost::add_vertex(graph));
    vertices.push_back(boost::add_vertex(graph));
    vertices.push_back(boost::add_vertex(graph));
    vertices.push_back(boost::add_vertex(graph));
    boost::add_edge(vertices.at(0), vertices.at(4), graph);
    boost::add_edge(vertices.at(0), vertices.at(1), graph);
    boost::add_edge(vertices.at(4), vertices.at(0), graph);
    boost::add_edge(vertices.at(4), vertices.at(1), graph);
    boost::add_edge(vertices.at(4), vertices.at(5), graph);
    boost::add_edge(vertices.at(5), vertices.at(6), graph);
    boost::add_edge(vertices.at(6), vertices.at(4), graph);
    boost::add_edge(vertices.at(1), vertices.at(2), graph);
    boost::add_edge(vertices.at(2), vertices.at(7), graph);
    boost::add_edge(vertices.at(2), vertices.at(3), graph);
    boost::add_edge(vertices.at(3), vertices.at(1), graph);
    boost::add_edge(vertices.at(8), vertices.at(9), graph);
    boost::add_edge(vertices.at(9), vertices.at(8), graph);

    /* boost::add_edge(vertices.at(0), vertices.at(1), graph);
    boost::add_edge(vertices.at(2), vertices.at(3), graph);
    boost::add_edge(vertices.at(3), vertices.at(4), graph);
    boost::add_edge(vertices.at(4), vertices.at(5), graph);
    boost::add_edge(vertices.at(7), vertices.at(8), graph);
    boost::add_edge(vertices.at(8), vertices.at(9), graph);
    boost::add_edge(vertices.at(9), vertices.at(7), graph);*/
   
    //random generation;
    boost::mt19937 rng;
    boost::generate_random_graph(graph, nn, 8, rng);
    size_t e = boost::num_edges(graph);
    size_t n = boost::num_vertices(graph);
    std::cout << "generated " << e << " edges, " << n << " vertices\n";

    // graph[boost::graph_bundle].number_of_components =
    //     boost::connected_components(graph,
    //                                 boost::get(&node_properties::component, graph));

    //std::cout << "Without adaption:\n-----------------" << std::endl;
    //print_graph(graph);
    //print_components(graph);
    visitI(0);

    std::cout
        << "\n Components number SCC1: ----------" << c << std::endl;
    std::cout << "r_index: ----------" << std::endl;
    for (auto i = r_index.begin(); i != r_index.end(); ++i)
        std::cout << *i << ' ';
}