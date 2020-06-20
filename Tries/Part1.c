#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

static int nodes = 1;// count number of nodes
static int count =0;
typedef struct trienode{

bool isEndOfWord; // to check weather the node is an end of a word
struct trienode* children[26]; // since each node have 26 children according to alphabet size

}TrieNode;

//create new node
TrieNode* createNode(bool isEnd){ 

TrieNode* newNode = (TrieNode *)malloc(sizeof(TrieNode));
newNode->isEndOfWord = isEnd ;
int i;
for(i=0;i<26;i++){
newNode->children[i] = NULL;
} 

return newNode;
}

// insert word
TrieNode* insertWord(TrieNode* root,char word[]){ 

TrieNode* tempNode = root; // root as start


int i;
for(i=0; i< strlen(word);i++){

if(65<= word[i] && 90 >= word[i]){
word[i] = word[i] + 32;
}
int indexOfChild = word[i] - 97 ; // find node index

if(i+1 != strlen(word) && !(tempNode->children[indexOfChild])){ // not the end of word

tempNode->children[indexOfChild] = createNode(false);
nodes++;

}else if(i+1 != strlen(word) ){

}
else{ // end of word
if(!(tempNode->children[indexOfChild])){// node null
tempNode->children[indexOfChild] = createNode(true);
nodes++;

}else{//node not null
tempNode->children[indexOfChild]->isEndOfWord = true;
}
}
tempNode = tempNode->children[indexOfChild]; 
}
return tempNode;
}

// find node
TrieNode* findNode(TrieNode* root,char word[]){

TrieNode* tempNode = root; // root as start

int i;
for(i=0; word[i] != '\0';i++){

int indexOfChild = word[i] - 97 ; // find node index
if(!(tempNode->children[indexOfChild])){
tempNode = NULL;
break;
}else{
tempNode = tempNode->children[indexOfChild];
}
}
return tempNode ;
}

//give suggesitions to print
int printSuggestions(TrieNode* startNode,char word[],int wordSize){

if(startNode->isEndOfWord){// print word if user typed word parse is a word in this trie
count++;
printf("%s\n",word);
}
// traverse through all the paths from the starting node finding end of words
int i;
for(i=0;i<26;i++){
// if node is not null, then create new word with including the letter in the edge to that children from the start node
if(startNode->children[i] != NULL){
char newWord[wordSize+2]; 
int j;
for(j=0;j< wordSize ;j++){
newWord[j] = word[j];
}
newWord[wordSize] = i+ 97;
newWord[wordSize+1] = '\0';
printSuggestions(startNode->children[i],newWord,strlen(newWord)); //recurse same function to find end of a word
}
}
return 0;
}
//read file and insert words to the trie
int insertListOfWords(TrieNode* root,char* fileName){
char word[50];

FILE *fp = fopen(fileName,"r");
if(fp == NULL){
printf("ERROR!!-can not open file\n");
}

double time_difference;
clock_t startTime = clock();
while(1){
fgets(word,50,fp);
char newWord[50];// since different wordlists have different word formats
int i;
int j=0;
for(i=0;i< strlen(word);i++){
if(65<= word[i] && 90 >= word[i] || 97<= word[i] && 122 >= word[i] ){
newWord[j] = word[i];
j++;
}
}
newWord[j] = '\0';
insertWord(root,newWord);

if(feof(fp)){
break;
}

}
clock_t endTime = clock();
time_difference = (double)(endTime - startTime )/ CLOCKS_PER_SEC;
printf("Time taken to insert dictionary is: %f\n",time_difference);
fclose(fp);
return 0;
}

int main(){
TrieNode* root = createNode(false);
insertListOfWords(root,"wordlist10000.txt");
printf("nodes : %d\n",nodes);
while(1){
char wordPart[100];
printf("Enter word with lowercase letters : ");
scanf("%s",wordPart);
double time_difference;
clock_t startTime = clock();
TrieNode* checkNode = findNode(root,wordPart); //find end node of user typed word part or word

if(checkNode == NULL){
printf("No such word exist and no suggestions for you.\n");
}else{
printf("Suggestions: \n");
count=0;
printSuggestions(checkNode,wordPart,strlen(wordPart));
clock_t endTime = clock();
time_difference = (double)(endTime - startTime )/ CLOCKS_PER_SEC;
printf("number of suggestions: %d\n",count);
printf("Time taken to give suggestions is: %f\n",time_difference);

}
}
return 0;
}