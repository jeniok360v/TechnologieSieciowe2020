#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



#define VERTEX_AMOUNT 20
#define EDGE_AMOUNT 29



typedef struct Vertex
{
	int id;
}vert;

typedef struct GraphEdge
{
	vert* x;
	vert* y;
}edge;

typedef struct Graph
{
	vert* v[VERTEX_AMOUNT];
	edge* e[EDGE_AMOUNT];
}graph;


void init_graph(graph* my_graph);
void add_vert(graph* my_graph, int index, int a);
void add_edge(graph* my_graph, int index, int a, int b);




int main()
{
	graph* my_graph ;
	init_graph(my_graph);
	printf("hi");
	vert* ver = (vert*)malloc(sizeof(vert*));
	ver = my_graph->v[0];
	printf("hi");
	for (int i=0;i<VERTEX_AMOUNT;i++)
	{
		//printf("", i, my_graph->(*v)[i].id);
	}
	printf("hi");
	printf("0 - %d\n", ver->id);	
	
	/*
	{printf("hi");
		add_vert(my_graph, i, i);
	}

	for (int i=0;i<VERTEX_AMOUNT;i++)
	{
		printf("%d - %d\n", i, my_graph->v[i]->id);
	}
*/
	return 0;
}

void init_graph(graph* my_graph)
{

	vert ve[VERTEX_AMOUNT];// = (vert)malloc(sizeof(vert[VERTEX_AMOUNT]));
	for(int i=0;i<VERTEX_AMOUNT;i++)
	{	
		ve[i].id = i;
	}
	memcpy(&my_graph->v, ve, sizeof(&my_graph->v));
	
	edge ed[EDGE_AMOUNT];
	for(int i=0;i<EDGE_AMOUNT;i++)
	{
		ed[i].x = my_graph->v[0];
		ed[i].y = my_graph->v[0];
	}
	memcpy(&my_graph->e, ed, sizeof(&my_graph->e));
}


void add_vert(graph* my_graph, int index, int a)
{
	printf("hi");
	vert* v = (vert*)malloc(sizeof(vert));
	printf("hi");
	v->id = a;
	printf("hi");
	my_graph->v[index]=v;
	printf("hi");
}


void add_edge(graph* my_graph, int index, int a, int b)
{
	my_graph->e[index]->x->id = a;
	my_graph->e[index]->y->id = b;	
}




