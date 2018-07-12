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

  r_index.resize(nn, 0);
  inComponent.resize(nn, false);
  vindex = 1;
  c = nn - 1; 
  S = stack<int>();

  for (int i = 0; i < nn; i++)
  {
    if (r_index[i] == 0)
    {
      pearce_recursive_2(i);
    }
  }

/* *************************************************  */
// Used to show the strong the SCC 
  cout << "\nPearce 2  recursive::components: " << nn-c-1 << endl;
  for (int comps=0; comps<nn-c-1; comps++)
  {
    cout << "Component " << comps  << ": ";
    for (int i = 0; i < nn; i++)
    { 
      if (nn-1-comps == r_index[i])
      {
        cout<<i<<" ";}
      }
      cout<<endl;
    }
/* *************************************************  */
    cout<<endl;

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
        if (r_index[w] == 0)
        {
          pearce_recursive_2(w);
        }
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
      while (!S.empty() && (r_index[v] <= r_index[S.top()]))
      {
        int w = S.top();
        S.pop();
        r_index[w] = c;
        vindex = vindex - 1;
      }
      r_index[v] = c;
      c = c - 1;
    }
    else
    {
      S.push(v);
    }
  }


#endif

