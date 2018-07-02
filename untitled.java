
    public void visit(int v) {
      boolean root = true;
      visited[v] = true;
      rindex[v] = index;
      index = index + 1;
      inComponent[v] = false;

      for (int w : graph.edges(v)) {
        if (!visited[w]) {
          visit(w);
        }
        if (!inComponent[w] && rindex[w] < rindex[v]) {
          rindex[v] = rindex[w];
          root = false;
        }
      }

      if (root) {
        inComponent[v] = true;
        while (!S.isEmpty() && rindex[v] <= rindex[S.top()]) {
          int w = S.pop();
          rindex[w] = c;
          inComponent[w] = true;
        }
        rindex[v] = c;
        c = c + 1;
      } else {
        S.push(v);
      }
    }
  

  // ==============================================================
  // Imperative Version
  // ==============================================================

  /**
   * A simple imperative version of the algorithm PeaFindScc1
   * 
   * @author David J. Pearce
   *
   */
  public static class Imperative extends Base {
    Stack vS;
    Stack iS;
    boolean[] root;
    
    public Imperative(Digraph g) {
      super(g);
      vS = new Stack(graph.size());         // n words
      iS = new Stack(graph.size());         // n words
      root = new boolean[graph.size()]; // n bits
    }

    public void visit(int v) {
      // Represents the call stack      
      beginVisiting(v);
      
      while (!vS.isEmpty()) {
        visit(root);
      }
    }
    
    public void visit(boolean[] root) {     
      int v = vS.top();
      int i = iS.top();
      
      int[] g_edges = graph.edges(v); 
      
      // Continue traversing out-edges until none left.
      while(i <= g_edges.length){     
        // Continuation
        if(i > 0) { finishEdge(v, i); }         
        if (i < g_edges.length && beginEdge(v, i)) {
          return;
        } 
        i = i + 1;        
      }
      
      finishVisiting(v);    
    }

    public void beginVisiting(int v) {
      // First time this node encountered     
      vS.push(v);                          // total: n(1 + 2w)
      iS.push(0);
      root[v] = true;
      visited[v] = true;
      rindex[v] = index;
      index = index + 1;
      inComponent[v] = false;
    }
    
    public void finishVisiting(int v) {
      // Take this vertex off the stack
      vS.pop();
      iS.pop();
      // Finished traversing out edges, update component info
      if (root[v]) {
        inComponent[v] = true;
        while (!S.isEmpty() && rindex[v] <= rindex[S.top()]) {
          int w = S.pop();
          rindex[w] = c;
          inComponent[w] = true;
        }
        rindex[v] = c;
        c = c + 1;
      } else {
        S.push(v);
      }         
    }

    public boolean beginEdge(int v, int i) {
      int[] g_edges = graph.edges(v);
      int w = g_edges[i];         
      if (!visited[w]) {
        iS.pop();
        iS.push(i+1);
        beginVisiting(w);
        return true;
      } else {
        return false;
      }
    }

    public void finishEdge(int v, int k) {
      int[] g_edges = graph.edges(v); 
      // Update status for previously traversed out-edge
      int w = g_edges[k-1];
      if (!inComponent[w] && rindex[w] < rindex[v]) {
        rindex[v] = rindex[w];
        root[v] = false;
      }
    }

  }