#ifndef TARJAN
#define TARJAN
/* ----------------------------------------------------------------------------------------  
Tarjan DFS by Nuutilla. 
Based on Nuutila, Esko. "On Finding the Strongly Connected Components in a Directed Graph".
Goal is to find local roots of the components 
 ----------------------------------------------------------------------------------------  */

vector<int> root;
void tarjan(int v);
void tarjan2(int v);
//int iter;


/* original tarjan algorithm 
vector<bool> visit(10, false);
vector<bool>  instk(10, false); 
vector<int>  low(10,0);
int I=0;
vector<int>  ind(10,0);
stack<int> stk;
*/


void tarjan_recursive(graph_t graph_local)
{
  //iter = 0;
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

/* *************************************************  */

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

  /*cout <<"\n tarjan root \n";
  for (auto i = root.begin(); i != root.end(); ++i)
    std::cout << *i << ' ';
  */
/* *************************************************  */
  cout<<endl;
}



void tarjan(int v)
{
  visited[v] = true;
  // vertex v is root candidate 
  root[v] = v;
  // used to distingish between  nodes belonging to the same component
  inComponent[v] = false;
  // push visited vertices to the stack S
  S.push(v);
  // retrieves all edges from the graph 
  auto edges = boost::edges(*g);
  // iterates over the edges 
  for (auto it = edges.first; it != edges.second; ++it)
  {
    int w = boost::target(*it, *g);
    int s = boost::source(*it, *g);
    // if vertex v is equal to source node of the edge 
    if (v == s )
    {
      // visit in DF order if not visited already
      if (!visited[w])
      {
        tarjan(w);
      }
      if (!inComponent[w])
      {
        // set root vertex v to the minimum between the own value and target vertex 
        root[v] = min(root[v], root[w]);
      }
    }
  }
  // vertex v is the root
  // the stack contains the scc 
  if (root[v] == v)
  {
    int w;
    do 
    {
      // remove SCC from the stack 
      w = S.top();
      S.pop();
      inComponent[w] = true;
    } while (w != v);
    //iter ++;
  }
}




/*
original tarjan algorithm implementation 
 */
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
