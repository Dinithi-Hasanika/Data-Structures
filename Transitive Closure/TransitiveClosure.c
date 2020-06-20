
#include <stdio.h>
#include <stdbool.h> 

 #define nodes 7
bool isFrontierNotEmpty(int frontier[nodes]){ // check wheather the frontier is empty and return true if not empty

bool notEmpty = false;
for(int j=0; j< nodes; j++){
if(frontier[j] > 0 && frontier[j] < nodes+1){
notEmpty = true;
}
}

return notEmpty;
}


void transitiveClosure(int graph[nodes][nodes]){
 int transitive [nodes][nodes] ; // transitiveClosure matrix-final output
 for(int i=1; i<=nodes; i++){ // start to visit from all nodes in the graph
   int frontier[nodes] = {}; // frontier consist of nodes that will visit
   int k=0;
   int v =0;

   frontier[0] = i; 
   int visited[nodes]={}; // visited nodes
   int neighbours[nodes] ={}; // neighbours of a given node in frontier which is visiting

   while(isFrontierNotEmpty(frontier)){ 
   int pick = 0;
    for(int j=0;j<nodes; j++){ // pick node from frontier to visit
   if(frontier[j] > 0 && frontier[j] < nodes+1){
    pick = frontier[j];
	
    break;
}

}

 transitive[i-1][pick-1] = 1; //set this position in transitive closure matrix 1 as it can be visited from i


 for(int j=0;j<nodes; j++){ // remove that visited node from frontier
   if(frontier[j] == pick){
    frontier[j] = 0;
break;
}
}
visited[v] = pick; // add visited node to visited array
v++;
int p =0;
for(int r=0;r < nodes; r++){ // find neighbours of the visited node
if(graph[pick-1][r] == 1){
neighbours[p] = r+1;
p++;
}
}

for(int r=0; r< nodes;r++){ // update frontier with visted node's neighbours

if(neighbours[r] > 0 && neighbours[r] < nodes+1){

for(int j=0;j<nodes; j++){
   if(!(frontier[j] > 0 && frontier[j] < nodes+1)){
    frontier[j] = neighbours[r];
    break;
}
}
}
else{ 
break;
}

}

for(int r=0; r< nodes;r++){ // compare visited array and frontier array and remove common elements from the frontier

if(visited[r] > 0 && visited[r] < nodes+1){

for(int j=0;j<nodes; j++){
   if(frontier[j] == visited[r]){
    frontier[j] = 0;
   
}
}
}
else{ 
break;
}
}

} 
}

for(int q=0; q < nodes;q++){ // print transitive closure matrix
for(int e=0; e < nodes; e++){
if(transitive[q][e] != 1){
transitive[q][e] = 0;
} 
printf("%d ",transitive[q][e]);
}
printf("\n");
}



} ;


int main(){

int graph[nodes][nodes] = { {0, 1, 1, 0, 0, 0, 0}, 
{0, 0, 0, 0, 1, 0, 0}, 
{0, 0, 0, 0, 0, 1, 0}, 
{0, 1, 0, 0, 1, 0, 1}, 
{0, 0, 0, 0, 0, 0, 1}, 
{0, 0, 0, 1, 0, 0, 0}, 
{0, 1, 0, 0, 0, 0, 0}};

transitiveClosure(graph);



}


