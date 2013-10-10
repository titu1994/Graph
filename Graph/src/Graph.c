/*
 ============================================================================
 Name        : Graph.c
 Author      : Somshubra Majumdar
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 10

typedef struct Node{
	int data;
	struct Node *next;
}Node;

void createGraphArray(int a[N][N], int directed);
void createGraphList(Node* a[N], int directed);
void orderedInsert(Node **p, int v);
void DFSArrayRecursive(int a[N][N], int start, int visited[]);
void DFSArrayIterative(int a[][N], int start);
void DFSListIterative(Node* a[], int start);
void DFSListRecursive(Node* a[N], int start, int visited[]);
void BFSListIterative(Node *a[N], int start);
void BFSArrayIterative(int a[N][N], int start);


int main(void) {
	int choice = -1, directed;
	int visited[N] = {0};
	int a[N][N] = {{0}};
	Node *p[N] = {0};

	setbuf(stdout, NULL);

	printf("Enter choice :\n1 for create Array Graph\n2 for create List Graph\n3 to search DFS Array Graph Recursively\n4 to search DFS Array Graph Iteratively\n5 to search DFS List Graph Recursively\n6 to search DFS List Graph Iteratively\n7 for BFS Array Graph Iteratively\n8 for BFS List Graph Recursively\n");

	do{

		printf("Enter choice : ");
		scanf("%d",&choice);

		switch (choice) {
		case 1: //Create Array Graph
			printf("Choose whether Graph is directed : 1 for true, 0 for false : ");
			scanf("%d",&directed);

			createGraphArray(a, directed);

			break;
		case 2: //Create List Graph
			printf("Choose whether Graph is directed : 1 for true, 0 for false : ");
			scanf("%d",&directed);

			createGraphList(p, directed);

			break;
		case 3: //Search DFS Array Graph Recursively
			memset(visited, 0, N);

			DFSArrayRecursive(a, 0, visited);

			break;
		case 4: //Search DFS Array Graph Iteratively

			DFSArrayIterative(a, 0);

			break;
		case 5: //Search DFS List Graph Recursively
			memset(visited, 0, N);

			DFSListRecursive(p, 0, visited);

			break;
		case 6: //Search DFS List Graph Iteratively

			DFSListIterative(p, 0);

			break;
		case 7: //Search BFS Array Graph Iteratively

			BFSArrayIterative(a, 0);

			break;
		case 8: //Search BFS List Graph Iteratively

			BFSListIterative(p, 0);

			break;
		default: {
			choice = -1;
		}

		}

	}while(choice != -1);



	return EXIT_SUCCESS;
}

void createGraphArray(int a[N][N], int directed){

	int ch;
	char x,y;

	do{

		printf("Enter the edges : ");
		scanf("%c%c", &x, &y);

		x = toupper(x);
		y = toupper(y);

		a[x-65][y-65] = 1;

		if(!directed)
			a[y-65][x-65] = 1;

		printf("Enter 1 to continue : ");
		scanf("%d",&ch);

	}while(ch == 1);

}

void createGraphList(Node* a[N], int directed){

	int ch;
	char x,y;

	do{

		printf("Enter the edges : ");
		scanf("%c%c", &x, &y);

		x = toupper(x);
		y = toupper(y);

		orderedInsert(&a[x-65], y-65);

		if(!directed)
			orderedInsert(&a[y-65], x-65);

		printf("Enter 1 to continue : ");
		scanf("%d",&ch);

	}while(ch == 1);

}

void orderedInsert(Node **p, int v){
	Node *newNode = NULL;

	newNode = (Node*) calloc(1, sizeof(Node));
	newNode->data = v;

	Node *temp, *previous;
	temp = *p;

	while(temp != NULL){

		if(temp->data > v){
			break;
		}

		previous = temp;
		temp = temp->next;
	}

	if(temp == *p){
		newNode->next = *p;
		*p = newNode;
	}
	else{
		newNode->next = previous->next;
		previous->next = newNode;
	}

}

void DFSArrayRecursive(int a[N][N], int start, int visited[]){

	int i;
	visited[start] = 1;

	printf("%c\t", start+65);

	for(i = 0; i < N; i++){

		if(a[start][i] && !visited[i]){

			DFSArrayRecursive(a,i,visited);
		}
	}
}

void DFSArrayIterative(int a[][N], int start){
	int i;
	int visited[N] = {0};
	int stack[N], top = -1;

	visited[start] = 1;
	printf("%c\t", start+65);

	while(top != -1){

		start = stack[top];

		for(i = 0; i < N; i++){

			if(a[start][i] && !visited[i]){
				visited[i] = 1;
				printf("%c\t", start+65);
				stack[++top] = i;
				break;
			}

		}

		if(i == N){
			top--;
		}

	}

}

void DFSListIterative(Node* a[], int start){
	int i;
	Node *p;
	int visited[N] = {0};
	int stack[N], top = -1;

	visited[start] = 1;
	printf("%c\t", start+65);

	while(top != -1){

		start = stack[top];

		for(p = a[start]; p != NULL; p = p->next){
			i = p->data;

			if(!visited[i]){
				visited[i] = 1;
				printf("%c\t", start+65);
				stack[++top] = i;
				break;
			}

		}

		if(p == NULL){
			top--;
		}

	}

}



void DFSListRecursive(Node* a[N], int start, int visited[]){
	Node *p;
	int i;
	visited[start] = 1;

	printf("%c\t", start+65);

	for(p = a[start]; p != NULL; p=p->next){

		if(!visited[i]){
			i = p->data;
			DFSListRecursive(a,i,visited);
		}
	}
}

void BFSListIterative(Node *a[N], int start){
	Node *p;
	int visited[N] = {0}, rear = -1, front = -1;
	int queue[N], i;

	visited[start] = 1;

	printf("%c\t", start+65);
	queue[++rear] = start;

	while(front != rear){

		start = queue[++front];

		for(p = a[start], i; p != NULL; p=p->next){
			i = p->data;

			if(!visited[i]){
				queue[++rear] = i;
				printf("%c\t",i+65);
				visited[i] = 1;
			}
		}
	}

}

void BFSArrayIterative(int a[N][N], int start){
	int i;
	int visited[N] = {0}, rear = -1, front = -1;
	int queue[N];

	visited[start] = 1;

	printf("%c\t", start+65);
	queue[++rear] = start;

	while(front != rear){

		start = queue[++front];

		for(i = 0; i < N; i++){

			if(a[start][i] && !visited[i]){
				queue[++rear] = i;
				printf("%c\t",i+65);
				visited[i] = 1;
			}
		}
	}

}



