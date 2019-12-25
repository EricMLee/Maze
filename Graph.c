/*
Eric Lee
elee90
pa4
Graph.c for Programming Assignment 4
*/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"
typedef struct GraphObj {
	List* adj;
	int* color;
	int* parent;
	int* distance;
	int vertices;
	int edges;
	int source;
}GraphObj;
typedef GraphObj* Graph;

Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->adj = calloc(n + 1, sizeof(List));
	G->vertices = n;
	G->edges = 0;
	G->color = calloc(n + 1, sizeof(int));
	G->parent = calloc(n + 1, sizeof(int));
	G->distance = calloc(n + 1, sizeof(int));
	G->source = NIL;
	for (int i = 0; i <= n; i++) {
		G->adj[i] = newList();
		G->color[i] = 2;
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	return G;
}

void freeGraph(Graph* pG) {
	if (*pG != NULL && pG != NULL) {
		int n = getOrder(*pG);
		makeNull(*pG);
		for (int i = 0; i <= n; i++) {
			freeList(&(*pG)->adj[i]);
		}
		free((*pG)->adj);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->distance);
		free(*pG);
		*pG = NULL;
	}
}

int getOrder(Graph G) {
	return G->vertices;
}
int getSize(Graph G) {
	return G->edges;
}
int getSource(Graph G) {
	return G->source;
}
int getParent(Graph G, int u) {
	return G->parent[u];
}
int getDist(Graph G, int u) {
	return G->distance[u];
}
void getPath(List L, Graph G, int u) {

	if (G->source == u) {
		append(L, u);
		return;
	}
	if (G->parent[u] == NIL) {
		append(L, NIL);
		return;
	}
	int v = u;
	while (v != NIL) {
		prepend(L, v);
		v = G->parent[v];
	}

}
void makeNull(Graph G) {
	for (int i = 0; i <= G->vertices; i++) {
		clear(G->adj[i]);
		G->color[i] = 2;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->vertices = 0;
	G->source = 0;
	G->edges = 0;
}

void addEdge(Graph G, int u, int v) {
	if (length(G->adj[u]) == 0) {
		prepend(G->adj[u], v);
	}
	else {
		moveFront(G->adj[u]);
		while (get(G->adj[u]) < v && index(G->adj[u]) != -1) {
			moveNext(G->adj[u]);
		}
		if (index(G->adj[u]) == -1) {
			append(G->adj[u], v);
		}
		else {
			insertBefore(G->adj[u], v);
		}
	}
	if (length(G->adj[v]) == 0) {
		prepend(G->adj[v], u);
	}
	else {
		moveFront(G->adj[v]);
		while (get(G->adj[v]) < u && index(G->adj[v]) != -1) {
			moveNext(G->adj[v]);
		}
		if (index(G->adj[v]) == -1) {
			append(G->adj[v], u);
		}
		else {
			insertBefore(G->adj[v], u);
		}
	}
	G->edges++;
}


void addArc(Graph G, int u, int v) {
	if (length(G->adj[u]) == 0) {
		prepend(G->adj[u], v);
	}
	else {
		moveFront(G->adj[u]);
		while (get(G->adj[u]) < v && index(G->adj[u]) != -1) {
			moveNext(G->adj[u]);
		}
		if (index(G->adj[u]) == -1) {
			append(G->adj[u], v);
		}
		else {
			insertBefore(G->adj[u], v);
		}
	}
	G->edges++;
}

void BFS(Graph G, int s) {
	List Q = newList();
	for (int i = 1; i <= G->vertices; i++) {
		G->color[i] = 2;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->source = s;
	G->color[s] = 1;
	G->distance[s] = 0;
	prepend(Q, s);
	int x;
	int y;
	int distance = 1;
	while (length(Q) != 0) {
		moveFront(Q);
		x = get(Q);
		deleteFront(Q);
		moveFront(G->adj[x]);
		while (index(G->adj[x]) != -1) {
			y = get(G->adj[x]);
			if (G->color[y] == 2) {
				G->color[y] = 1;
				G->parent[y] = x;
				G->distance[y] = G->distance[x] + 1;
				append(Q, y);
			}
			moveNext(G->adj[x]);
		}
		G->color[x] = 0;
		distance++;
	}
	freeList(&Q);
}

void printGraph(FILE* out, Graph G) {
	for (int i = 1; i <= G->vertices; i++) {
		fprintf(out, "\n%d: ", i);
		fflush(out);
		if (length(G->adj[i]) != 0) {
			moveFront(G->adj[i]);
			while (index(G->adj[i]) != -1) {
				fprintf(out, " %d", get(G->adj[i]));
				fflush(out);
				moveNext(G->adj[i]);
			}
		}
	}
}

