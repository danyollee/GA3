#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

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
  unsigned long int graph2[sizeOfGraph][sizeOfGraph];

  int parent[sizeOfGraph];
  for(int i=0; i<sizeOfGraph; i++){
    parent[i] = 0;
  }

  int storeInd[sizeOfGraph][sizeOfGraph];

  // Inputs the data from the input file to the graph to create the original graph.
  for(int i=0; i<sizeOfGraph; i++){
    for(int j=0; j<sizeOfGraph; j++){
      input >> graph[i][j];
      input.ignore(1, ',');
    }
  }

  // Transfers the original graph to a secondary graph where we will use our algorithm on.
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


  // This is the kruskal's algorithm.
  while(ne < sizeOfGraph){
    min = 4294967295;
    for(int i=0; i<sizeOfGraph; i++){
      for(int j=0; j<sizeOfGraph; j++){
        if(i==3 && j==0){
        }
        if(graph2[i][j]<min){
          // cout << "moving " << graph2[i][j] << " to min\n";
          min = graph2[i][j];
          a = u = i;
          b = v = j;
        }
      }
    }
    // cout << "a=" << a << ", b=" << b << endl;
    u = find(u, parent);
    v = find(v, parent);
    if(uni(u, v, parent)){
      storeInd[ne-1][ne-1] = u;
      storeInd[ne-1][ne] = v;
      // ne++;
      cout << ne++ << " edge (" << a << ", " << b << ") = " << min << endl;
      mincost += min;
      // cout << "mincost is now " << mincost << endl;
    }
    graph2[a][b] = graph2[b][a] = 4294967295;
  }
  // End of while loop



  int MSTsize = ne--;
  int MSTTrack[MSTsize];
  for(int i=0; i<MSTsize; i++){
    MSTTrack[i] = 0;
  }

  cout << "NE IS " << ne << endl;

  MSTTrack[0] = mincost;
  cout << "Minimum cost = " << MSTTrack[0] << endl;

  for(int i=0; i<MSTsize; i++){
    cout << storeInd[i][i] << " " << storeInd[i][i+1] << endl;
  }




  // Finding the next MST's
  for(int x=0; x<sizeOfGraph; x++){
    ne = 1;
    mincost = 0;

    for(int i=0; i<sizeOfGraph; i++){
      for(int j=0; j<sizeOfGraph; j++){
        graph2[i][j] = graph[i][j];
        cout << storeInd[x][x] << " " << storeInd[x][x+1] << endl;
        if(i==storeInd[x][x] && j==storeInd[x][x+1]){
          // if(storeInd[x][x] == 1 && storeInd[x][x+1] == 3){
          //   cout << "i is 1 and j is 3\n";
          // }
          // cout << "\n\n\ni is " << storeInd[x][x] << ", and j is " << storeInd[x][x+1] << ". Changed " << graph[i][j] << " to 0\n\n\n";
          graph2[i][j] =  0;
        }
        if(graph2[i][j]==0){
          graph2[i][j] = 4294967295;
        }
      }
    }

    for(int i=0; i<sizeOfGraph; i++){
      for(int j=0; j<sizeOfGraph; j++){
        if((i!=j) && graph2[i][j]==4294967295){
          graph2[j][i] = 4294967295;
        }
      }
    }


    // Just prints the 2D array
    cout << "Printing the next array\n";
    for(int i=0; i<sizeOfGraph; i++){
      for(int j=0; j<sizeOfGraph; j++){
        cout << graph2[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;

    while(ne < sizeOfGraph){
      min = 4294967295;
      for(int i=0; i<sizeOfGraph; i++){
        for(int j=0; j<sizeOfGraph; j++){
          if(graph2[i][j]<min){
            min = graph2[i][j];
            a = u = i;
            b = v = j;
          }
        }
      }
      // cout << "a=" << a << ", b=" << b << endl;
      u = find(u, parent);
      v = find(v, parent);
      if(uni(u, v, parent)){
        ne++;
        // cout << ne++ << " edge (" << a << ", " << b << ") = " << min << endl;
        mincost += min;
      }
      graph2[a][b] = graph2[b][a] = 4294967295;
    }

    MSTTrack[x+1] = mincost;
    // cout << "Minimum cost = " << MSTTrack[x+1] << endl;


  }
  // End of finding the rest of the MST's


  // Sort the MSTTrack array
  int p = sizeof(MSTTrack)/sizeof(MSTTrack[0]);
  sort(MSTTrack, MSTTrack+p);

  // Print the second and third MST
  output << MSTTrack[0] << "\n";
  output << MSTTrack[1] << "\n";
  output << MSTTrack[2] << "\n";

  input.close();
  output.close();


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
