#ifndef PEARCE_REC_1
#define PEARCE_REC_1

vector<bool> visited(1, false);
vector<int> r_index(1, 0);
vector<bool> inComponent(1, false);
stack<int> S;
int vindex = 0;
int c = 0; // component number.
void pearce_recursive_1(int v);
graph_t *g;

void pr1(graph_t graph_local)
{
  g = &graph_local;
  size_t nn = boost::num_vertices(graph_local);  

  visited.resize(nn, false); 
  r_index.resize(nn, 0);
  inComponent.resize(nn, false);

  for (int i = 0; i < nn; i++)
  {
    if (!visited[i])
    {
      pearce_recursive_1(i);
    }
  }
  cout << "\nPearce recursive::components: " << c << endl;
  // for (auto i = r_index.begin(); i != r_index.end(); ++i)
  //   cout << ++iter << " : "  << *i <<" | ";
  for (int comps=0; comps<c; comps++)
  {
    int counter = 0;
    for (auto i = r_index.begin(); i != r_index.end(); ++i)
    {
      if (comps == *i)
        counter++;
    }
    cout << "Compenent " << comps  << ": " <<counter;
    cout<<endl;
  }   
  cout<<endl;

}


void pearce_recursive_1(int v)
{
  bool root = true;
  visited[v] = true;
  r_index[v] = vindex;
  vindex = vindex + 1;
  inComponent[v] = false;
  auto edges = boost::edges(*g);
  for (auto it = edges.first; it != edges.second; ++it)
  {
    int w = boost::target(*it, *g);
    int s = boost::source(*it, *g);

    if (v == s)
    {
      //cout << "\n Visit for node: " << v << ", edge: " << s << "->" << w << "\n";
      if (!visited[w])
      {
        pearce_recursive_1(w);
      }

      for (auto i = r_index.begin(); i != r_index.end(); ++i)
        //bool check = !(inComponent[w]) && (r_index[w] < r_index[v]);
        if (!(inComponent[w]) && (r_index[w] < r_index[v]))
        {
          r_index[v] = r_index[w];
          root = false;
        }
    }
  }

  if (root)
  {
    inComponent[v] = true;
    while (!S.empty())
    {
      while ((!S.empty()) && (r_index[v] <= r_index[S.top()]))
      {
        int w = S.top();
        S.pop();
        r_index[w] = c;
        inComponent[w] = true;
      }
    }
    r_index[v] = c;
    c = c + 1;
  }
  else
  {
    S.push(v);
  }
}



#endif

