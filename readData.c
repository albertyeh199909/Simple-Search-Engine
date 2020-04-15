#include <stdio.h>

#include "graph.c"
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

LinkedList newLL() {
        return NULL;
}

LinkedList createNode (char *url) {
        LinkedList newNode = malloc(sizeof(struct linkedList));
        char *copy = malloc(sizeof(char)*BUF);
        newNode->url = strcpy(copy, url);
        newNode->pagerank = 0;
        newNode->outgoing = 0;
        newNode->next = NULL;
        return newNode;
}

LinkedList insertion (LinkedList list, LinkedList node) {
        LinkedList curr = list;
        if (list == NULL) {
        		printf("33\n");
                list = node;
                list->next = NULL;
        }
        else {
            while (curr->next != NULL) {
                    curr = curr->next;
            }
            curr->next = node;
            node->next = NULL;
        }
        return list;
}        
        

LinkedList getCollection (char*collectionFileName) {
        LinkedList list = newLL();
        char *url = malloc(sizeof(char)*BUF);
        FILE *collection = fopen(collectionFileName, "r");
        while (fscanf(collection, "%s", url) == 1) {
            list = insertion(list,createNode (url)); 
        }
        return list;
}

int countNodes (LinkedList list) {
		if (list == NULL) {
        	return 0;
    	}
        int count = 1;
        LinkedList curr = list;
        
    	
        while (curr->next != NULL) {
            curr = curr->next;
            count++;
        }                
        return count;
}
Graph GetGraph (LinkedList list) {
        Graph g = newGraph(countNodes(list));
        if (list == NULL) {
        	printf("list is empty\n");
        	return NULL;
    	}
        LinkedList curr = list; 
        if (curr->next == NULL) {
        	readPage(g, curr->url);
    	}
    	else {
		    while (curr->next != NULL) {
				readPage(g, curr->url);
				curr = curr->next;
		  	}
	  	}
	  	return g;
}                                    
                    
  

void readPage (Graph g, char *url) {
	char *suffix = ".txt";
	char *file = malloc(strlen(suffix)+strlen(url)+1); 
	strcpy(file,url);
	strcat(file, suffix);
	FILE *fp = fopen(file, "r");
	if (fp == NULL) {
		perror("file not found");
	}
	//printf("83\n");
	char *outLink = malloc(sizeof(char)*BUF);
	while (fscanf(fp, "%s", outLink) == 1) {
		if (strstr(outLink, "url") != NULL) {
			// check if self-loop or parallel edge
        	if (strcmp (outLink, url) != 0 && (!isConnected(g, url, outLink))) {
        		printf("added edge between %s and %s\n", outLink, url);
    	    	if (addEdge(g, url, outLink) == 0) {
    	    		perror("maximum nodes added");
	    		}	
    		}
		}
	}                
}        
                                
