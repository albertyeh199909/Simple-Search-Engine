#include <stdio.h>

#include "graph.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define BUF 100

void readPage (Graph g, char *url);
struct linkedList{
    char *url;
    double pagerank;
    int outgoing;
    struct linkedList *next;
 };

typedef struct linkedList *LinkedList;

LinkedList newLL();

LinkedList createNode (char *url);
LinkedList insertion (LinkedList list, LinkedList node);
LinkedList getCollection (char*collectionFileName);
int countNodes (LinkedList list);
Graph GetGraph (LinkedList list);
void readPage (Graph g, char *url);




