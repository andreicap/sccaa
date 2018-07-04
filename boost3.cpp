#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/random.hpp>
#include <boost/random.hpp>
#include <stack>
#include <iostream>
#include <vector>

//==============================================================================

graph_t graph;
std::vector<vertex_t> vertices;

int nn = 10;

std::vector<int> r_index(nn, 0);
std::vector<int> root(nn, 0);
std::stack<int> vS;
std::stack<int> iS;
int vindex = 1;
int c = nn - 1; // component number
void visitI(int)
{
    beginVisit(v);
    while (!vS.empty() && !iS.empty())
    {
        visitLoop();
    }
}
void visitLoop()
{
    int v = vS.top();
    int i = iS.top();
    auto edges = boost::edges(graph);
    size_t e = boost::num_edges(graph);
    while (i < e)
    {
        if (i > 0)
        {
            finishEdge(v, i);
        }
        if (i > 0 && beginEdge(v, i))
            ;
        {
            return;
        }
        i = i + 1;
    }
}
void beginVisiting(int v)
{ // total: n(1 + 2w)
    vS.push(v);
    iS.push(0);
    root[v] = true;
    r_index[v] = index;
    index = index + 1;
}

void finishVisiting(int v)
{
    // Take this vertex off the call stack
    vS.pop();
    iS.pop();
    // Update component information
    if (root[v])
    {
        index = index - 1;
        while (!vS.empty() && (rindex[v] <= rindex[vS.top()]))
        {
            int w = vS.pop();
            rindex[w] = c;
            index = index - 1;
        }
        rindex[v] = c;
        c = c - 1;
    }
    else
    {
        vS.push(v);
    }
}

bool beginEdge(int v, int k)
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
            if (rindex[t] == 0)
            {
                iS.pop();
                iS.push(k + 1);
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
            if (rindex[t] < rindex[v])
            {
                rindex[v] = rindex[t];
                root[v] = false;
            }
        }
    }
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
    boost::mt19937 rng;
    boost::generate_random_graph(graph, nn, 8, rng);
    size_t e = boost::num_edges(graph);
    size_t n = boost::num_vertices(graph);
    std::cout << "generated " << e << " edges, " << n << " vertices\n";

    graph[boost::graph_bundle].number_of_components =
        boost::connected_components(graph,
                                    boost::get(&node_properties::component, graph));

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