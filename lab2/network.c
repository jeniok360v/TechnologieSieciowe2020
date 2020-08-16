#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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



void add_edge(graph* my_graph, int index, int a, int b);


int main()
{
	graph* my_graph;
	
	vert v0;
	vert *v0ptr;
	v0ptr = &v0;
	vert v1;
	vert *v1ptr;
	v1ptr = &v1;
	
	printf("hi");
	v0ptr->id = 0;
	v1ptr->id = 1;
	printf("hi");
	
	edge e0;
	edge *e0ptr;
	e0ptr = &e0;
	
	printf("hi");
	e0ptr->x=v0ptr;
	printf("hi");
	e0ptr->y=v1ptr;
	printf("hi");
	
	for (int i=0;i<VERTEX_AMOUNT;i++)
	{printf("hi");
		vert v00;
		vert *v00ptr;
		v0ptr = &v00;
		my_graph->v[i]->id=i;
	}
	
	/*
	for (int i=0;i<VERTEX_AMOUNT;i++)
	{
		printf("%d - %d\n", i, my_graph->v[i].id);
	}

	for (int i=0;i<EDGE_AMOUNT;i++)
	{
		my_graph->e[i].x.id = -1;
		my_graph->e[i].y.id = -1;	
	}
	
	
	//add_edge(my_graph, 0, 0, 1);
	
	
	
	
	for (int i=0;i<EDGE_AMOUNT;i++)
	{
		printf("(%d, %d)\n", my_graph->e[i].x.id, my_graph->e[i].y.id );
	}
	
	*/
	return 0;
}

void add_edge(graph* my_graph, int index, int a, int b)
{
	my_graph->e[index]->x->id = a;
	my_graph->e[index]->y->id = b;	
}




