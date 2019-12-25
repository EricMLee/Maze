#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#define START (int)'S'
#define FINISH (int)'F'
int main(int argc, char* argv[]) {
	FILE* rPtr;
	rPtr = fopen(*(argv + 1), "r");
	FILE* fPtr;
	char* out = *(argv + 2);
	fPtr = fopen(out, "w");
	int height;
	int width;
	fscanf(rPtr, "%d", &width);
	fscanf(rPtr, "%d", &height);
	printf("\n%d %d\n", width, height);
	int start = 0; int finish = 0;
	char c;
	int** map = (int**)malloc(height * sizeof(int*));
	for (int i = 0; i < height; i++)
		map[i] = (int*)malloc(width * sizeof(int));
	int pathCounter = 0;
	for (int row = 0; row < 12; row++) {
		printf("\n");
		for (int col = 0; col < 12; col++) {
			
			fscanf(rPtr, "%c", &c);
			
			if (c == 'S') {
				printf("S ");
				map[row][col] = START;
				pathCounter++;
				start = row * width + col;
			}
			else if (c == 'F') {
				printf("F ");
				map[row][col] = FINISH;
				pathCounter++;
				finish = row * width + col;
			}
			else if (c == '.') {
				printf(". ");
				map[row][col] = 0;
				pathCounter++;
			}
			else if (c == '#') {
				printf("# ");
				map[row][col] = 1;
			}else{
				col--;
			}
		}
	}
	Graph maze = newGraph(height*width);
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (map[row][col] != 1) {
				if (row != 0 && map[row - 1][col] != 1) {
					addArc(maze, (row * width) + col, (row - 1) * width + col);
				}
				if (row != height-1 && map[row + 1][col] != 1) {
					addArc(maze, (row * width) + col, (row + 1) * width + col);
				}
				if (col != 0 && map[row][col - 1] != 1) {
					addArc(maze, (row * width) + col, row * width + col - 1);
				}
				if (col != width -1 && map[row][col + 1] != 1) {
					addArc(maze, (row * width) + col, row * width + col + 1);
				}
			}
		}
	}
	BFS(maze, start);
	List path = newList();
	getPath(path, maze, finish);
	moveFront(path);
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			map[row][col] = 0;
		}
	}
	int reader = 0;
	while (length(path) != 0) {
		moveFront(path);
		reader = get(path);
		map[reader / width][reader % height] = 1;
		deleteFront(path);
	}
	printf("\n\nThe solution for this maze is");
	for (int row = 0; row < height; row++) {
		printf("\n");
		for (int col = 0; col < width; col++) {
			if(row*width + col == start){
				printf("S ");
			}
			else if (row*width + col == finish) {
				printf("F ");
			}
			else if (map[row][col] == 0) {
				printf("# ");
			}
			else {
				printf(". ");
			}
		}
	}
	printf("\n\n");
	for(int i = 0; i < height; i++)
		free(map[i]);
	free(map);
	fclose(rPtr);
	fclose(fPtr);
	freeList(&path);
	freeGraph(&maze);
	return 0;
}