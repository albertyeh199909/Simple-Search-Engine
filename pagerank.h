#include "readData.c"


void calculatePageRank(Graph g, double d, double diffPR, int maxIterations, double *firstArr, double *secondArr, double* urlPG); 
double calculateWout (Graph g, int src, int dest);
double calculateWin (Graph g, int src, int dest);
void arrayInitializer (Graph g, double *arr);
double calculateSum (Graph g , int v, double *arr);
double difference (Graph g, double *first, double *second);
void arrayCopy (Graph g, double *first, double *second);
int cmpfunc (const void * a, const void * b);
void printList (Graph g, LinkedList list);
void insert(Graph g, double *arr, LinkedList list);
double outgoing (Graph g, int i);
double incoming (Graph g, int i);
