#ifndef NUUTILA
#define NUUTILA

#include "definitions.hpp"


void nuutila(int v);

void nuutila_recursive(graph_t graph_local)
{
  g = &graph_local;

  size_t nn = boost::num_vertices(graph_local);  
  visited.resize(0); 
  visited.resize(nn, false); 
  root.resize(0);
  root.resize(nn, 0);
  inComponent.resize(0);
  inComponent.resize(nn, false);
  S = stack<int>();
  vindex = 0;
  c = 0;



  cout << "\nNuutila recursive::components: " <<  endl;
  for (int i = 0; i < nn; i++)
  {
    if (!visited[i])
    {
      nuutila(i);
    }
  }
  cout<<endl;
}

int component_iterator = 0;

void nuutila(int v)
{
    visited[v] = true;
    root[v] = v;
    inComponent[v] = false;
    auto edges = boost::edges(*g);
    for (auto it = edges.first; it != edges.second; ++it)
    {

        int w = boost::target(*it, *g);
        int s = boost::source(*it, *g);
        if (v == s)
        {
            if (!visited[w])
            {
                nuutila(w);
            }
            if (!inComponent[w])
            {
                root[v] = min(root[v], root[w]);
            }
        }
    }
    if (root[v] == v)
    {
        inComponent[v] = true;
        cout << "Component "<< component_iterator<<":";
        while (!S.empty() && (S.top() >= v))
        {

            int w = S.top();
            S.pop();
            cout << " "<< w;
            inComponent[w] = true;
        }
        cout << " " << v << "\n";
    }
    else
    {
        S.push(v);
    }
}




#endif