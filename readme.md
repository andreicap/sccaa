## C++ implementation for Strong Components Detection 
**Using boost library**

**Algorithms used: D. Pearce (2 versions), Nuutila and Tarjan**

#### Prerequisities: C++11 compiler and Boost Library installed.

The program generates random graphs using Boost random generator.
Optionally, there are implemented Erdos Randomg graph generator and a simple generator written by us.

How to run: 

```
make
./main 10
```

The argument specifies the number of the graph nodes. The number of edges is created deterministically or at random, depending on the selected generator.

In the output one also can find the Boost library implementation for detecting strong components.

#### Output example:
```
generated 20 edges, 10 vertices

Graph ->vertices: 10, edges: 20
0 -> 8
0 -> 4
0 -> 2
1 -> 7
1 -> 0
1 -> 4
2 -> 8
2 -> 1
2 -> 6
4 -> 7
4 -> 8
5 -> 7
6 -> 5
6 -> 0
7 -> 6
7 -> 0
8 -> 3
8 -> 5
9 -> 1
9 -> 8

Boost:: Total number of components: 3
Compenent 0: 3 
Compenent 1: 0 1 2 4 5 6 7 8 
Compenent 2: 9 


Pearce recursive::components: 3
Component 0: 3 
Component 1: 0 1 2 4 5 6 7 8 
Component 2: 9 


Pearce 2  recursive::components: 3
Component 0: 3 
Component 1: 0 1 2 4 5 6 7 8 
Component 2: 9 


Nutilla ::components: 3
Component: 0 1 2 4 5 6 7 8 
Component: 3 
Component: 9 

Tarjan recursive::components: 3
Component: 0 1 2 4 5 6 7 8 
Component: 3 
Component: 9 


```
