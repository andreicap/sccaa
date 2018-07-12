#ifndef TARJAN
#define TARJAN


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


  vector<int> scc;
  
  scc =root; 
  
  sort(scc.begin(), scc.end());
  
  scc.erase(std::unique(scc.begin(), scc.end()), scc.end());

  cout << "\nTarjan recursive::components: " <<scc.size() << endl;
  for (auto ip = scc.begin(); ip != scc.end(); ++ip) {
    std::cout << '\n';
    cout << "Component: ";
    for (int i = 0; i < nn; i++)
    {  
      if (*ip == root[i]){
        cout << i << ' ';
      }
    }
  }
  cout <<"\n tarjan root \n";
  for (auto i = root.begin(); i != root.end(); ++i)
    std::cout << *i << ' ';

  cout<<endl;
}

int iter = 0;


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
    while (!S.empty() && (S.top() >= v))
    {
      int w = S.top();
      S.pop();
      inComponent[w] = true; 
    }
    iter++;

  }
}




#endif