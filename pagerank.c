#include <math.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "pagerank.h"


int main ( int argc, char *argv[]) {
	//printf("check\n");
	double d = atof(argv[1]);
	double diffPR = atof(argv[2]);
	int max = atoi(argv[3]);
	LinkedList list = getCollection ("collection.txt");
	
	
	
	Graph g = GetGraph(list);
	showGraph(g, 1);
		
	double *firstArr = (double *)malloc(sizeof(double)*(g->nV));// = {0};
	double *secondArr = (double *)malloc(sizeof(double)*(g->nV)); 	
	double* urlPG = (double *)malloc(sizeof(double)*(g->nV)); 
	calculatePageRank (g, d, diffPR, max, firstArr, secondArr, urlPG);
	//qsort(urlPG, g->nV, sizeof(double), cmpfunc);

	

	insert(g, urlPG, list);
	printList (g, list);
	free(firstArr);
	free(secondArr);
	free(urlPG);
	
} 
void insert(Graph g, double *arr, LinkedList list) {
	int i = 0;
	while (i < g->nV) {
		list->pagerank = arr[i];
		list->outgoing = outgoing (g, i);
		list = list->next;
		i++;
	}
	
}
void printList (Graph g, LinkedList list) {
	FILE *fp = fopen ("pagerankList.txt", "w");
	
	while (list != NULL) {
		fprintf(fp, "%s, 	%d,	   %.7f\n",list->url, list->outgoing, list->pagerank);
		list = list->next;

	}
}

// taken from https://stackoverflow.com/questions/19191595/how-to-obtain-the-descending-order-ordinality-of-an-integer-array
int cmpfunc (const void * a, const void * b) {
   return ( *(double*)b - *(double*)a );
}

void calculatePageRank(Graph g, double d, double diffPR, int maxIterations, double *firstArr, double *secondArr, double* urlPG) {
	arrayInitializer (g, firstArr);
	int iteration = 0;
    double diff = diffPR; 
	while (iteration < maxIterations && diff >= diffPR) {
		int i = 0;
		while (i < g->nV) {
			double frac = (1 - d)/g->nV;
			double prevPR= d *calculateSum(g, i, firstArr);
			secondArr[i] = frac + prevPR;
			i++;
		}
		diff = difference (g, firstArr, secondArr); 
		arrayCopy (g, firstArr, secondArr); 
		iteration++;
	}
	arrayCopy (g, urlPG, secondArr);

}

void arrayCopy (Graph g, double *first, double *second) {
	int i = 0;
	while (i < g-> nV) {
		first[i] = second[i];
		i++;
	}
}
double difference (Graph g, double *first, double *second) {
	double sum = 0;
	int i = 0;
	while (i < g->nV) {
		sum += fabs(second[i] - first[i]);
		i++;
	}
	return sum;
}
	

double calculateSum (Graph g , int v, double *arr) {
	int i = 0;
	double sum = 0;
	while (i < g->nV) {
		if (g->edges[i][v] == 1) {
			double in = calculateWin (g, i, v);
			double out = calculateWout (g, i, v);
			sum += arr[i] * in * out;
		}
		i++;
	}
	return sum;
} 
				
// initialize first iteration array to 1/N
void arrayInitializer (Graph g, double *arr) {
	int i = 0;
	while (i < g->nV) {
		arr[i] = (1/g->nV);
		i++;
	}
}
	

double calculateWout (Graph g, int src, int dest) {
	double destOut = 0;
	double denominator = 0;
	int v = src;
	// loops through matrix representation and finds outgoing links from destination
	int i = 0;	
	while (i < g->nV) {
		if (g->edges[v][i] == 1) {
			double out = outgoing (g, i);
			if (out == 0) {
				out = 0.5;	
			}
			denominator += out;
		}
		i++;
	}
	int w = dest;
	destOut = outgoing (g, w);
	if (destOut == 0) {
		destOut == 0.5;
	}
	//printf("%lf\n", destOut);
	//printf("%lf\n", denominator);
	return destOut/denominator;
	
}

double outgoing (Graph g, int i) {
	int z = 0;
	double out = 0;
	while (z < g->nV) {
		if (g->edges[i][z] == 1) {
			out++;
		}
		z++;
	}
	return out;
}

// make a seperate function to calc inlinks (and outlinks as well)

double calculateWin (Graph g, int src, int dest) {
	double destIn = 0;
	double denominator = 0;	
	int i = 0;
	int v = src;
	while (i < g->nV) {
		if (g->edges[v][i] == 1) {
			double in = incoming(g, i);
			/*if (in == 0) {
				in = 0.5;	
			}*/
			denominator += in;
		}
			
		i++;
	}
	
	int w = dest;
	destIn = incoming (g, w);
	if (destIn == 0) {
		destIn == 0.5;
	}
	printf("%lf\n", destIn);
	printf("%lf\n", denominator);
	printf("%d to %d is %lf\n", src, dest, destIn/denominator);
	return destIn/denominator;	
}
double incoming (Graph g, int i) {
	int z = 0;
	double in = 0;
	while (z < g->nV) {
		if (g->edges[z][i] == 1) {
			in++;
		}
		z++;
	}
	return in;
}	
/*
void bubblesort (Graph g, LinkedList list) {
	int i = 0;
	while (i < g->nV) {
		LinkedList curr = list;
		while (curr != NULL) {
			if (curr->pagerank < curr->next->pagerank) {
					
			curr = curr->next;
		}
}
*/
