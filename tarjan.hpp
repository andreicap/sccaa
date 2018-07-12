#ifndef TARJAN
#define TARJAN

#include "definitions.hpp"

vector<int> root;
void tarjan(int v);

void tarjan_recursive(graph_t graph_local)
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


  cout << "\nTarjan recursive::components: " <<  endl;
  // // for (auto i = r_index.begin(); i != r_index.end(); ++i)
  // //   cout << ++iter << " : "  << *i <<" | ";
  // for (int comps=0; comps<c; comps++)
  // {
  //   int counter = 0;
  //   for (auto i = r_index.begin(); i != r_index.end(); ++i)
  //   {
  //     if (comps == *i)
  //       counter++;
  //   }
  //   cout << "Compenent " << comps  << ": " <<counter;
  //   cout<<endl;
  // }   
  // cout<<endl;
  // 
  for (int i = 0; i < nn; i++)
  {
    if (!visited[i])
    {
      tarjan(i);
    }
  }
  cout << "Nr. of components: " << c << endl;
}

void tarjan(int v)
{
  
  visited[v] = true;
  root[v] = v;
  inComponent[v] = false;
  S.push(v);
  auto edges = boost::edges(*g);
  for (auto it = edges.first; it != edges.second; ++it)
  {
    int w = boost::target(*it, *g);
    int s = boost::source(*it, *g);
    if (v == s)
    {
      if (!visited[w])
      {
        tarjan(w);
      }
      if (!inComponent[w])
      {
        root[v] = min(root[v], root[w]);
      }
    }
  }
  if (root[v] == v)
  {
    cout << "Component "<< c<<":";
    while (!S.empty() && (S.top() > v))
    {
      int w = S.top();
      S.pop();
      inComponent[w] = true;
      cout << " " << w;
    }
    cout << " " << v << "\n";
    c++;
  }
}




#endif