#ifndef NUUTILA
#define NUUTILA

/* ----------------------------------------------------------------------------------------  
SCC detection algorithm by Nuutilla. 
Based on Nuutila, Esko. "On Finding the Strongly Connected Components in a Directed Graph".
Goal is to find local roots of the components 
 ----------------------------------------------------------------------------------------  */

void nuutila(int v);

void nuutila_recursive(graph_t graph_local)
{
  g = &graph_local;

  //initializers
  size_t nn = boost::num_vertices(graph_local);  
  
  visited.resize(0); 
  visited.resize(nn, false); 
  
  root.resize(0);
  root.resize(nn, 0);
  
  inComponent.resize(0);
  inComponent.resize(nn, false);

  discover_time.resize(nn, 0);

  S = stack<int>();
  c = 0;

  for (int i = 0; i < nn; i++)
  {
    if (!visited[i])
    {
      nuutila(i);
    }
  }

/* *************************************************  */
  
  vector<int> scc;
  scc = root; 
  sort(scc.begin(), scc.end());
  scc.erase(std::unique(scc.begin(), scc.end()), scc.end());
  cout << "\n Nutilla ::components: " << scc.size() << endl;
  for (auto ip = scc.begin(); ip != scc.end(); ++ip) {
    std::cout << '\n';
    cout << "Component "<< scc.end() - ip << ": ";
    for (int i = 0; i < nn; i++)
    {  
      if (*ip == root[i]){
        cout << i << ' ';
      }
    }
  }

  // cout <<endl << "inComponent "<<endl;
  // for (int i = 0; i < nn; i++)
  // {  
  //     cout << inComponent[i] << ' ';
  // }

    //cout <<"\n nutilla root \n";
  //for (auto i = root.begin(); i != root.end(); ++i)
  //   std::cout << *i << ' ';

/* *************************************************  */
  cout<<endl;

}

void nuutila(int v)
{
  visited[v] = true;
  discover_time[v] = dfs_time++;
  // cout<< "v = " << v << ", discover_time = " << dfs_time << endl;
  root[v] = v;
  inComponent[v] = false;
  auto edges = boost::edges(*g);
  typename boost::graph_traits<graph_t>::out_edge_iterator it, it_end;
  for (boost::tie(it, it_end) = out_edges(v, *g); it != it_end; ++it)
  {
    int w = boost::target(*it, *g);
    
    if (!visited[w])
    {
      nuutila(w);
    }
    if (!inComponent[w])
    {
      root[v] = (discover_time[v] < discover_time[w]) ? root[v] : root[w];
    }
  }
  if (root[v] == v)
  {
    inComponent[v] = true;
    // remove from the stack  until the top is greater then root node
    int w;
    while ( !S.empty() && S.top() > v)
    {
    // trivial component non root 
      w = S.top();
      S.pop();
      inComponent[w] = true;
     // cout << " "<< w;
    }
    //cout << " " << v << "\n";
    c++;
  }
  // push only non root nodes after processing all edges 
  else
  {
    S.push(v);
  }
}




#endif