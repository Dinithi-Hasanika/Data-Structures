#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

static int nodes = 1;// count number of nodes
static int count =0;//count number of words in each prefix
static int findWordCount = 0;//count index of word prefix which user entered

typedef struct linkedList{ 
char character; // to keep letter
struct linkedList* branch;// to keep next letter linked list
}LinkedList;


typedef struct trienode{

bool isEndOfWord; // to check weather the node is an end of a word
bool haveChildren;// to check wheathe node have children or not
struct trienode* children[26]; // since each node have 26 children according to alphabet size
LinkedList* character_set;
}TrieNode;

//create new list of words
LinkedList* createLinkedList(char letter){
LinkedList* newList = (LinkedList*)malloc(sizeof(LinkedList));
newList->character = letter;
newList->branch = NULL;
return newList;
}

//create new node
TrieNode* createNode(bool isEnd,bool have){ 

TrieNode* newNode = (TrieNode *)malloc(sizeof(TrieNode));
newNode->isEndOfWord = isEnd ;
newNode->character_set = NULL;
newNode->haveChildren = have;
int i;
for(i=0;i<26;i++){
newNode->children[i] = NULL;
} 

return newNode;
}

int getIndex(char letter){

if(65<= letter && 90 >= letter){
letter = letter + 32;
}
int indexOfChild = letter - 97 ;
return indexOfChild;
}

//insert word into tree
TrieNode* insertWord(TrieNode* root,char word[]){
TrieNode* tempNode = root;

int i=0;
while(i< strlen(word)){
if(tempNode->children[getIndex(word[i])]){//node not null

if(!(tempNode->children[getIndex(word[i])]->character_set)){// not have list or character_set

if(tempNode->children[getIndex(word[i])]->haveChildren){//have children
if(i+1 != strlen(word)){// not end of word
tempNode = tempNode->children[getIndex(word[i])];
i++;
}else{//end of word
(tempNode->children[getIndex(word[i])])->isEndOfWord = true;
break;
}

}else{//not have children

if(i+1 != strlen(word)){// not end of word
LinkedList* startList = createLinkedList(word[i+1]);
tempNode->children[getIndex(word[i])]->character_set = startList;
int j = i+2;
for(j=i+2;j< strlen(word);j++ ){
startList->branch = createLinkedList(word[j]);
startList = startList->branch ;
}
break;
}else{//end of word
(tempNode->children[getIndex(word[i])])->isEndOfWord = true;
break;
}

}

}else{//have list
if(i+1 != strlen(word)){// not end of word
LinkedList* changeList = tempNode->children[getIndex(word[i])]->character_set ;
TrieNode * changeNode =tempNode->children[getIndex(word[i])];
changeNode->children[getIndex(changeList->character)] = createNode(false,false);
changeNode->haveChildren = true;
nodes++;
changeNode->character_set = NULL;
changeNode->children[getIndex(changeList->character)]->character_set = changeList->branch ;
if(!(changeList->branch)){
changeNode->children[getIndex(changeList->character)]->isEndOfWord = true;
}
tempNode = tempNode->children[getIndex(word[i])];
i++;
}else{//end of word
(tempNode->children[getIndex(word[i])])->isEndOfWord = true;
}

}

}else{// node null
tempNode->children[getIndex(word[i])] = createNode(false,false);
nodes++;

if(i+1 != strlen(word)){//node null- not end of word
LinkedList* startList = createLinkedList(word[i+1]);
tempNode->children[getIndex(word[i])]->character_set = startList;
int j = i+2;
for(j=i+2;j< strlen(word);j++ ){
startList->branch = createLinkedList(word[j]);
startList = startList->branch ;
}
break;
}else{ //node null-end of word
(tempNode->children[getIndex(word[i])])->isEndOfWord = true;
break;
}
}

}
return tempNode;
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

// find node
TrieNode* findNode(TrieNode* root,char word[]){

TrieNode* tempNode = root; // root as start

while(word[findWordCount] != '\0' ){
int indexOfChild = getIndex(word[findWordCount]) ; // find node index
if(!(tempNode->children[indexOfChild])){
tempNode = NULL;
break;
}else{
if((tempNode->children[indexOfChild])->character_set){
tempNode = tempNode->children[indexOfChild];
findWordCount++;
break;
}
else{
tempNode = tempNode->children[indexOfChild];
findWordCount++;
}
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
if(startNode->character_set){
count++;
printf("%s",word);

LinkedList* startList = startNode->character_set;
while(startList != NULL){
printf("%c",startList->character);
startList = startList->branch ; 

}
printf("\n");
return 0;
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

int main(){
TrieNode* root = createNode(false,false);
insertListOfWords(root,"wordlist10000.txt");
printf("Total nodes: %d\n",nodes);

while(1){
char wordPart[100];
printf("Enter word with lowercase letters : ");// input prefix
scanf("%s",wordPart);
double time_difference;
clock_t startTime = clock();
findWordCount = 0;
TrieNode* checkNode = findNode(root,wordPart); //find end node of user typed word part or word

if(wordPart[findWordCount] != '\0' && (checkNode != NULL)){

LinkedList* checkList = checkNode->character_set;
while(checkList != NULL){// check wheather the list in return node contain user entered word part

if(checkList->character == wordPart[findWordCount]){
if(wordPart[findWordCount+1] != '\0'){
checkList = checkList->branch ;
findWordCount++;
}else{
break;
}
}else{
checkNode = NULL;
break;
}

}

}
if(checkNode == NULL){
printf("No such word exist and no suggestions for you.\n");
}else{
printf("Suggestions:\n");
count=0;
printSuggestions(checkNode,wordPart,strlen(wordPart));
clock_t endTime = clock();
time_difference = (double)(endTime - startTime )/ CLOCKS_PER_SEC;
printf("Time taken to give suggestions is: %f\n",time_difference);
printf("number of suggestions %d\n",count);
}
}
return 0;
}