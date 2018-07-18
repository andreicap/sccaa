#ifndef PEARCE_REC_2
#define PEARCE_REC_2

/* ----------------------------------------------------------------------------------------  
SCC detection by Pearce. 
Based on Pearce, David. "A Space Efficient Algorithm for Detecting Strongly Connected Components".
Goal is to find SCC given a graph  
 ----------------------------------------------------------------------------------------  */

void pearce_recursive_2(int v);

void pr2(graph_t graph_local)
{
  g = &graph_local;
  size_t nn = boost::num_vertices(graph_local);

  r_index.resize(0);
  r_index.resize(nn, 0);
  // used to distiguish whether a vertex has been assigned to a component
  // assigned to component id in case
  // used to keep track of already visited vertices
  vindex = 1;
  c = nn - 1;
  S = stack<int>();

  for (int i = 0; i < nn; i++)
  {
    if (i % 500 == 0) cout<<i<<" "<<flush;
    if (r_index[i] == 0)
    {
      pearce_recursive_2(i);
    }
  }

  /* *************************************************  */
  // Used to show the SCC
  // cout << "\nPearce 2  recursive::components: " << nn - c - 1 << endl;
  // for (int comps = 0; comps < nn - c - 1; comps++)
  // {
  //   cout << "Component " << comps << ": ";
  //   for (int i = 0; i < nn; i++)
  //   {
  //     if (nn - 1 - comps == r_index[i])
  //       { cout<<i<<" ";}

  //   }
  //   cout << endl;
  // }
  //   /* *************************************************  */
  // cout << endl;
}

void pearce_recursive_2(int v)
{
  bool root = true;
    // keeps track of visited
  r_index[v] = vindex;
  vindex = vindex + 1;
  auto edges = boost::edges(*g);
  for (auto it = edges.first; it != edges.second; ++it)
  {
    int w = boost::target(*it, *g);
    int s = boost::source(*it, *g);
    if (v == s)
    {
        // std::cout << "\n Visit for node: " << v << ", edge: " << s << "->" << w << "\n";
        // if not visited
      if (r_index[w] == 0)
      {
        pearce_recursive_2(w);
      }
        // decide whether is a local root or not based on the visitation
      if (r_index[w] < r_index[v])
      {
        r_index[v] = r_index[w];
        root = false;
      }
    }
  }
  if (root)
  {
    vindex = vindex - 1;
      // all nodes are SCC with the local root until the visitation is grater
      //rindex[x] holds the visitation index of x’s local root
    while (!S.empty() && (r_index[v] <= r_index[S.top()]))
    {
      int w = S.top();
      S.pop();
      r_index[w] = c;
      vindex = vindex - 1;
    }
      // assign the component to the r_index of the vertex
    r_index[v] = c;
    c = c - 1;
  }
    //If vertex v is not a local root, v and all the scc of the same scc are stored in the stack
  else
  {
    S.push(v);
  }
}

#endif
