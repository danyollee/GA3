#include <iostream>
#include <fstream>

using namespace std;

void Kruskals(int, int, int, int, int*, int*, int, int, int, int, int*);
int find(int, int[]);
int uni(int, int, int[]);

int main(){
  int a, b, min, mincost=0, ne=1, u, v;
  // Opens the input.txt file to read data and the output.txt for MST outputs
  ifstream input;
  ofstream output;

  input.open("input2.txt");
  output.open("output.txt");

  if(!input.is_open()){
    cout << "Error in opening the input file.\n";
  }

  // Reads the first line of the input file. This gives us the size of the graph to make
  int sizeOfGraph;
  input >> sizeOfGraph;
  // cout << "Size\t" << sizeOfGraph << "\n";

  // Creates 2, 2D arrays from sizeOfGraph
  int graph[sizeOfGraph][sizeOfGraph];
  int graph2[sizeOfGraph][sizeOfGraph];

  int parent[sizeOfGraph];
  for(int i=0; i<sizeOfGraph; i++){
    parent[i] = 0;
  }

  int storeInd[sizeOfGraph][sizeOfGraph];

  // Inputs the data from the input file to the graph to create the graph.
  for(int i=0; i<sizeOfGraph; i++){
    for(int j=0; j<sizeOfGraph; j++){
      input >> graph[i][j];
      input.ignore(1, ',');
    }
  }

  for(int i=0; i<sizeOfGraph; i++){
    for(int j=0; j<sizeOfGraph; j++){
      graph2[i][j] = graph[i][j];
      if(graph2[i][j]==0){
        graph2[i][j] = 4294967295;
      }
    }
  }

  // Just prints the 2D array
  for(int i=0; i<sizeOfGraph; i++){
    for(int j=0; j<sizeOfGraph; j++){
      cout << graph2[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;

  Kruskals(ne, sizeOfGraph, min, mincost, (int *)graph2, (int *)storeInd, a, b, u, v, parent);

  // while(ne < sizeOfGraph){
  //   min = 4294967295;
  //   for(int i=0; i<sizeOfGraph; i++){
  //     for(int j=0; j<sizeOfGraph; j++){
  //       if(graph2[i][j]<min){
  //         // cout << "moving " << graph2[i][j] << " to min\n";
  //         min = graph2[i][j];
  //         a = u = i;
  //         b = v = j;
  //       }
  //     }
  //   }
  //   cout << "a=" << a << ", b=" << b << endl;
  //   u = find(u, parent);
  //   v = find(v, parent);
  //   if(uni(u, v, parent)){
  //     storeInd[ne-1][ne-1] = u;
  //     storeInd[ne-1][ne] = v;
  //     cout << ne++ << " edge (" << a << ", " << b << ") = " << min << endl;
  //     mincost += min;
  //     cout << "mincost is now " << mincost << endl;
  //   }
  //   graph2[a][b] = graph2[b][a] = 4294967295;
  // }

  // for(int i=0; i<sizeOfGraph; i++){
  //   for(int j=0; j<sizeOfGraph; j++){
  //     cout << graph2[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  // cout << endl;

  cout << "Minimum cost = " << mincost << endl;

  int MSTTrack[ne--];
  MSTTrack[0] = mincost;

  for(int i=0; i<sizeOfGraph-1; i++){
    cout << storeInd[i][i] << " " << storeInd[i][i+1] << endl;
  }

}

void Kruskals(int ne, int sizeOfGraph, int min, int mincost, int **graph2, int** storeInd, int a, int b, int u, int v, int parent[]){
  while(ne < sizeOfGraph){
    min = 4294967295;
    for(int i=0; i<sizeOfGraph; i++){
      for(int j=0; j<sizeOfGraph; j++){
        if(graph2[i][j]<min){
          // cout << "moving " << graph2[i][j] << " to min\n";
          min = graph2[i][j];
          a = u = i;
          b = v = j;
        }
      }
    }
    cout << "a=" << a << ", b=" << b << endl;
    u = find(u, parent);
    v = find(v, parent);
    if(uni(u, v, parent)){
      storeInd[ne-1][ne-1] = u;
      storeInd[ne-1][ne] = v;
      cout << ne++ << " edge (" << a << ", " << b << ") = " << min << endl;
      mincost += min;
      cout << "mincost is now " << mincost << endl;
    }
    graph2[a][b] = graph2[b][a] = 4294967295;
  }

}



int find(int i, int parent[]){
  if(parent[i]){
    i = parent[i];
  }
  return i;
}

int uni(int i, int j, int parent[]){
  if(i!=j){
    parent[j] = i;
    return 1;
  }
  return 0;
}
