#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


#define AVERAGE_CAPACITY 12700	//bytes
#define CAPACITY_ERROR 200		//bytes

#define AVG_BYTES_PER_PACKET 64	//bytes
#define AVG_PACK_PER_TRANSMIT 5	//packets
#define APPT_ERROR 5			//packets

#define MAX_PACKET_LATENCY 3.0f	//maksymalne opoznienie pakietow w sieci

#define PROBABILITY 0.9f		//probability that edge is not broken

#define VERTEX_AMOUNT 20
#define EDGE_AMOUNT 29



typedef struct Vertex
{
	int id;
}vert;

typedef struct GraphEdge
{
	vert x;
	vert y;

	int max;	//bytes
	int actual;	//packets
	int lost;	//packets
	bool broken;	// 0 - not broken	
}edge;

typedef struct Graph
{
	vert v[VERTEX_AMOUNT];
	edge e[EDGE_AMOUNT];
	int transmition[VERTEX_AMOUNT][VERTEX_AMOUNT];	//packets
	int G_pack;		//packets (sum of all transmition[i][j] elements)
	
}graph;

typedef enum 
{
	not_visited,//nie odwiedzony
	in_queue,	// w kolejce
	visited		// odwiedzony
} search;


void rand_trans(graph* grptr);
void my_trans(graph* grptr);
void rand_capacity(graph* grptr);

int capacity(graph* grptr, int index);
int bit_rate(graph* grptr, int index);
int G(graph* grptr);
float avg_pack_latency(graph* grptr);	//srednie opoznienie pakietu w sieci

void transmit_RE(graph* grptr);
void transmit(graph* grptr);
void clear_graph(graph* grptr);
void broke_graph(graph* grptr);

bool attempt(graph* grptr, float T_max);

void change_edge(graph* grptr, int index, int a, int b);
int edge_by_vert(graph* grptr, int a, int b);

void path(graph* grptr, int** walk, int ind_A, int ind_B);
void adj(graph* grptr, int** ptr, int index);
bool connected(graph* grptr);
bool queue_is_empty(search* arr);
bool all_visited(search* arr);


void printer(graph* grptr, int A, int B);



int main()
{
	graph* grptr;
	graph gr;
	grptr = &gr;
	gr = (graph)
	{
		.v[0]={.id=0},
		.v[1]={.id=1},
		.v[2]={.id=2},
		.v[3]={.id=3},
		.v[4]={.id=4},
		.v[5]={.id=5},
		.v[6]={.id=6},
		.v[7]={.id=7},
		.v[8]={.id=8},
		.v[9]={.id=9},
		.v[10]={.id=10},
		.v[11]={.id=11},
		.v[12]={.id=12},
		.v[13]={.id=13},
		.v[14]={.id=14},
		.v[15]={.id=15},
		.v[16]={.id=16},
		.v[17]={.id=17},
		.v[18]={.id=18},
		.v[19]={.id=19},
		
		.e[0]={.x={.id=0},.y={.id=1}},
		.e[1]={.x={.id=2},.y={.id=1}},
		.e[2]={.x={.id=3},.y={.id=2}},
		.e[3]={.x={.id=4},.y={.id=3}},
		.e[4]={.x={.id=5},.y={.id=4}},
		.e[5]={.x={.id=6},.y={.id=5}},
		.e[6]={.x={.id=6},.y={.id=7}},
		.e[7]={.x={.id=7},.y={.id=8}},
		.e[8]={.x={.id=8},.y={.id=9}},
		.e[9]={.x={.id=9},.y={.id=10}},
		.e[10]={.x={.id=0},.y={.id=10}},
		.e[11]={.x={.id=0},.y={.id=11}},
		.e[12]={.x={.id=12},.y={.id=10}},
		.e[13]={.x={.id=13},.y={.id=9}},
		.e[14]={.x={.id=9},.y={.id=14}},
		.e[15]={.x={.id=13},.y={.id=15}},
		.e[16]={.x={.id=12},.y={.id=16}},
		.e[17]={.x={.id=11},.y={.id=16}},
		.e[18]={.x={.id=2},.y={.id=16}},
		.e[19]={.x={.id=16},.y={.id=17}},
		.e[20]={.x={.id=4},.y={.id=17}},
		.e[21]={.x={.id=17},.y={.id=18}},
		.e[22]={.x={.id=6},.y={.id=18}},
		.e[23]={.x={.id=18},.y={.id=19}},
		.e[24]={.x={.id=15},.y={.id=19}},
		.e[25]={.x={.id=7},.y={.id=19}},
		.e[26]={.x={.id=7},.y={.id=14}},
		.e[27]={.x={.id=14},.y={.id=15}},
		.e[28]={.x={.id=15},.y={.id=16}}
	};

	srand(time(NULL));
	rand_capacity(grptr);
	
	
	int counter = 0;
	int amount = 1000;
	for(int i=0;i<amount;i++)
	{
		if(attempt(grptr, MAX_PACKET_LATENCY))
			counter++;
	}
	printf("probability: %.2f%%\n", 100*(float)counter/(float)amount);

	
	free(grptr);
	return 0;
}


void rand_trans(graph* grptr)
{
	int G_ = 0;
	for(int i=0;i<VERTEX_AMOUNT;i++)
	{
		for(int k=0;k<VERTEX_AMOUNT;k++)
		{
			if(i!=k)
			{
				int err = rand() % (2*APPT_ERROR);
				grptr->transmition[i][k] = (AVG_PACK_PER_TRANSMIT-APPT_ERROR+err);
				G_ += (AVG_PACK_PER_TRANSMIT-APPT_ERROR+err);
			}
			else 
			{
				grptr->transmition[i][k] = 0;
			}
		}
	}
	grptr->G_pack=G_;
	return;
}

void my_trans(graph* grptr)
{
	for(int i=0;i<VERTEX_AMOUNT;i++)
	{
		for(int k=0;k<VERTEX_AMOUNT;k++)
		{
			grptr->transmition[i][k] = 0;		
		}
	}
	grptr->transmition[14][16] = 7;	
	grptr->transmition[14][2] = 7;	
	return;
}


void rand_capacity(graph* grptr)
{
	for(int i=0;i<EDGE_AMOUNT;i++)
	{
		int err = rand() % (2*CAPACITY_ERROR);
		grptr->e[i].max = (AVERAGE_CAPACITY-CAPACITY_ERROR+err);
	}
}

int capacity(graph* grptr, int index)
{
	return (grptr->e[index].max);
}

int bit_rate(graph* grptr, int index)
{
	return (grptr->e[index].actual);
}

int G(graph* grptr)
{
	return (grptr->G_pack);
}

float avg_pack_latency(graph* grptr)
{
	float ret = 0;
	for(int i=0;i<EDGE_AMOUNT;i++)
	{
		float temp = AVG_BYTES_PER_PACKET*bit_rate(grptr, i);
		ret+=(temp/(capacity(grptr, i)-temp));
	}
	return ((1/(float)G(grptr))*ret);
}

void transmit_RE(graph* grptr)
{
	for(int i=0;i<VERTEX_AMOUNT;i++)
	{
		for(int j=0;j<VERTEX_AMOUNT;j++)
		{
			if(grptr->transmition[i][j])
			{
				bool alter = false;
				int temp_X, temp_Y, temp_E;
				
				int* my_path;
				path(grptr, &my_path, i, j);
				
				for(int k=0;k<my_path[0];k++)
				{
					
					int t = edge_by_vert(grptr, my_path[k+1], my_path[k+2]);
					
					if((grptr->e[t].actual)*AVG_BYTES_PER_PACKET >= grptr->e[t].max)
					{
						
						temp_E = t;
						temp_X = my_path[k+1];	//grptr->e[t].x.id 
						temp_Y = my_path[k+2];	//grptr->e[t].y.id 
						grptr->e[t].x.id = -1; 
						grptr->e[t].y.id = -1;
						
						alter = true;
						break;
					}
					grptr->e[t].actual += grptr->transmition[i][j];
				}
				if(alter)
				{
					printf("Alter: from %d to %d, stop in %d \n", i, j, temp_X);
					int* my_path2;
					path(grptr, &my_path2, temp_X, j);
					
					for(int l=0;l<my_path2[0];l++)
					{
						int t = edge_by_vert(grptr, my_path2[l+1], my_path2[l+2]);
						
						grptr->e[t].actual += grptr->transmition[i][j];
					}
					grptr->e[temp_E].x.id = temp_X; 
					grptr->e[temp_E].y.id = temp_Y; 
					free(my_path2);
				}
				free(my_path);
			}
		}
	}
}

void transmit(graph* grptr)
{
	for(int i=0;i<VERTEX_AMOUNT;i++)
	{
		for(int j=0;j<VERTEX_AMOUNT;j++)
		{
			if(grptr->transmition[i][j])
			{			
				int* my_path;
				path(grptr, &my_path, i, j);
				
				for(int k=0;k<my_path[0];k++)
				{
					
					int t = edge_by_vert(grptr, my_path[k+1], my_path[k+2]);
					int packets = grptr->transmition[i][j];
					for(int l=0;l<packets;l++)
					{
						if((bit_rate(grptr, t)+1)*AVG_BYTES_PER_PACKET<capacity(grptr, t))
						{
							(grptr->e[t].actual)++;
						}
						else
						{
							grptr->transmition[i][j]--;
							grptr->e[t].lost++;
						}
					}
				}
				free(my_path);
			}
		}
	}
}

void clear_graph(graph* grptr)
{
	for(int i=0;i<EDGE_AMOUNT;i++)
	{
		grptr->e[i].actual = 0;
		grptr->e[i].lost = 0;
		grptr->e[i].broken = false;
	}
	return;
}

void broke_graph(graph* grptr)
{
	for(int i=0;i<EDGE_AMOUNT;i++)
	{
		if(rand()%1000 > PROBABILITY*1000)
		{
			grptr->e[i].broken = true;
		}
	}
}

bool attempt(graph* grptr, float T_max)
{
	clear_graph(grptr);
	rand_trans(grptr);
	broke_graph(grptr);
	if(!connected(grptr))
		return false;
	transmit(grptr);
	if(avg_pack_latency(grptr)<T_max)
		return true;
	return false;
}

void change_edge(graph* grptr, int index, int a, int b)
{
	if(a<VERTEX_AMOUNT && b<VERTEX_AMOUNT)
	{
		grptr->e[index].x.id = a;
		grptr->e[index].y.id = b;
	}
	return;
}

int edge_by_vert(graph* grptr, int a, int b)
{
	for(int i=0;i<EDGE_AMOUNT;i++)
	{
		if(grptr->e[i].x.id==a && grptr->e[i].y.id==b)
		{
			return i;
		}
		else if(grptr->e[i].x.id==b && grptr->e[i].y.id==a)
		{
			return i;
		}
	}
	return -1;
}

void path(graph* grptr, int** walk, int ind_A, int ind_B)
{
	search q[VERTEX_AMOUNT];
	int d[VERTEX_AMOUNT];
	for(int i=0;i<VERTEX_AMOUNT;i++)
	{
		q[i]=not_visited;
		d[i]=VERTEX_AMOUNT;
	}
	q[ind_A]=in_queue;
	d[ind_A]=0;
	int distance=0;
	
	while(q[ind_B]==not_visited)
	{
		distance++;
		search temp[VERTEX_AMOUNT];
		for(int j=0;j<VERTEX_AMOUNT;j++)
		{
			temp[j]=q[j];
		}
		for(int k=0;k<VERTEX_AMOUNT;k++)
		{
			if(temp[k]==in_queue)
			{
				int* adj_V;
				adj(grptr, &adj_V, k);
				for(int i=0;i<adj_V[0];i++)
				{
					if(q[adj_V[i+1]]==not_visited)
					{
						q[adj_V[i+1]]=in_queue;
						d[adj_V[i+1]]=distance;
					}
				}	
				q[k] = visited;
				free(adj_V);
			}
		}
	}
	
    *walk = malloc((distance+2) * sizeof(int));
    if (*walk == NULL)
	{
        return;
	}	
	for(int i=0;i<distance+2;i++)
	{
		(*walk)[i]=0;
	}
	
	(*walk)[0]=distance;
	(*walk)[distance+1]=ind_B;
	int temp_dist = distance;
	int neighbour = -1;
	
	while(temp_dist!=0)
	{
		int* adj_V;
		adj(grptr, &adj_V, (*walk)[temp_dist+1]);	
		temp_dist--;
		
		for(int i=0;i<adj_V[0];i++)
		{
			//printf("temp_dist: %d, adj_V[%d]: %d\n", temp_dist, i+1, adj_V[i+1]);
			if(d[adj_V[i+1]]==temp_dist)
			{
				neighbour=adj_V[i+1];
				break;
			}
		}
		if(neighbour == -1)
		{
			printf("This wasn't supposed to happen!(void path())!\n");
		}
		(*walk)[temp_dist+1]=neighbour;
	}
	return;
}

void adj(graph* grptr, int** ptr, int index)
{
	int temp[EDGE_AMOUNT];
	int counter = 0;
	for(int i=0;i<EDGE_AMOUNT;i++)
	{
		if(grptr->e[i].x.id==index && !grptr->e[i].broken)
		{
			temp[counter]=grptr->e[i].y.id;
			counter++;
		}
		else if(grptr->e[i].y.id==index && !grptr->e[i].broken)
		{
			temp[counter]=grptr->e[i].x.id;
			counter++;			
		}
	}
	
    *ptr = malloc((counter+1) * sizeof(int));
    if (*ptr == NULL)
	{
        return;
	}

	(*ptr)[0]=counter;	// pierwszy element - rozmiar tablicy
	for(int i=0;i<counter;i++)
	{
		(*ptr)[i+1]=temp[i];
	}
}

bool connected(graph* grptr)
{
	search q[VERTEX_AMOUNT];
	for(int i=0;i<VERTEX_AMOUNT;i++)
	{
		q[i]=not_visited;
	}
	q[0]=in_queue;

	while(!queue_is_empty(q))
	{
		for(int k=0;k<VERTEX_AMOUNT;k++)
		{
			if(q[k]==in_queue)
			{
				int* adj_V;
				adj(grptr, &adj_V, k);
				for(int i=0;i<adj_V[0];i++)
				{
					if(q[adj_V[i+1]]==not_visited)
					{
						q[adj_V[i+1]]=in_queue;
					}
				}	
				q[k] = visited;
				free(adj_V);
			}
		}
	}
	if(all_visited(q))
	{
		return true;
	}
	return false;
}

bool queue_is_empty(search* arr)
{
	for(int i=0;i<VERTEX_AMOUNT;i++)
	{
		if(arr[i]==in_queue)
		{
			return false;
		}
	}
	return true;
}



bool all_visited(search* arr)
{
	for(int i=0;i<VERTEX_AMOUNT;i++)
	{
		if(arr[i]==in_queue || arr[i]==not_visited)
		{
			return false;
		}
	}
	return true;
}

void printer(graph* grptr, int A, int B)
{
	if(connected(grptr))
	{
		printf("\nconnected graph\n");
	}
	else
	{
		printf("\ngraph is not connected\n");
	}
	
	printf("Capacity in bytes: \n");
	for (int i=0;i<EDGE_AMOUNT;i++)
	{
		char s[16] = "";
		if(grptr->e[i].broken)
		{
			strcpy(s, "[broken!]");
		}
		float lost_pack = (float)(grptr->e[i].lost)/(float)(grptr->e[i].actual+grptr->e[i].lost);
		printf("(edge %2d): max - %6d, actual - %6d (%d packets, %.1f%% lost) %s \n", 
			i, grptr->e[i].max, (grptr->e[i].actual)*AVG_BYTES_PER_PACKET, grptr->e[i].actual, lost_pack*100, s);
	}	
	printf("All packets: %d\n", G(grptr));
	printf("Srednie opoznienie pakietu: %f\n", avg_pack_latency(grptr));
	
	/*
	int* my_path;
	path(grptr, &my_path, A, B);
	printf("path from %d to %d: ", A, B);
	for(int i=0;i<my_path[0];i++)
	{
		printf("%d, ", my_path[i+1]);
	}	
	printf("%d\n", my_path[my_path[0]+1]);
	*/
	/*
	printf("Transmition from i to j in packets: \n");
	for(int i=0;i<VERTEX_AMOUNT;i++)
	{
		for(int k=0;k<VERTEX_AMOUNT;k++)
		{
			
			printf("%2d ", grptr->transmition[i][k]);
		}
		printf("\n");
	}	
	*/
	return;
}













