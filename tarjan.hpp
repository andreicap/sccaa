#ifndef TARJAN
#define TARJAN


vector<int> root;
void tarjan(int v);
void tarjan2(int v);
int iter;

vector<bool> visit(10, false);
vector<bool>  instk(10, false);
vector<int>  low(10,0);
int I=0;
vector<int>  ind(10,0);
stack<int> stk;



void tarjan_recursive(graph_t graph_local)
{
  iter = 0;
  g = &graph_local;

  size_t nn = boost::num_vertices(graph_local);  
  visited.resize(0); 
  visited.resize(nn, false); 
  root.resize(0);
  root.resize(nn, 0);
  inComponent.resize(0);
  inComponent.resize(nn, false);
  S = stack<int>();
  c = 0;
  vindex = 0;


  for (int i = 0; i < nn; i++)
  {
    if (visited[i]) continue;
    tarjan(i);
  }


  vector<int> scc;
  
  scc = root; 
  
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

    if (v == s )
    {
    // cout << v << "->" <<w << endl;
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
    int w;
    do 
    {
      w = S.top();
      S.pop();
      inComponent[w] = true;
    } while (w != v);
    iter ++;
  }
}





// void tarjan2( int u )
// {
//   visit[u] = true;
//   // instk[u] = true;
//   ind[u] = I;
//   low[u] = I++;
//   stk.push(u);
//   int min = low[u];

//   auto edges = boost::edges(*g);
//   for (auto it = edges.first; it != edges.second; ++it)
//   {
//     int w = boost::target(*it, *g);
//     int s = boost::source(*it, *g);

//     if (u == s)
//     {
//       cout << u << "->" << w << endl;
//       if( !visit[w] ){
//         tarjan2( w );
//         if (low[w] < min) min = low[w];
//       }
//     }
//   }

//   if( min < low[u] ){
//     low[u] = min;
//     return;
//   }

//   int w;
//   do
//   {
//     w = stk.top();
//     stk.pop();
//     instk[w] = false;
//     ind[w] = c;
//     low[w] = u;
//     // cout<< w << " ";
//   } while( w !=u );
//   c++;
//   cout<<"\n c= "<< c <<endl;
//   // instk[u] = false;  
// }

#endif