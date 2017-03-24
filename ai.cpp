#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

int depth = 0;

typedef struct Tree1
{
	char str[10];
	int hst, d;
	struct Tree1 *left, *middle, *right;
} Tree;

typedef struct
{
	Tree *arr[5000];
	int f, r;
	int count;
} Queue;

void init(Queue *q)
{
	q->r = q->f = q->count = 0;
}

void add(Queue *q, Tree* d)
{
	q->arr[q->r++] = d;
	q->count++;
}

Tree* del(Queue *q)
{
	if(q->f == q->r)
	{
		printf("\nQueue empty!");
		return NULL;
	}
	q->count--;
	return q->arr[q->f++];
}

Tree* createNode(const char *str, int hst, int d) 
{
	Tree* node = (Tree*) malloc(sizeof(Tree));
	node->hst = hst;
	node->d = d;
	strcpy(node->str, str);
	node->middle = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

int contains(const char *str1, const char *str2)
{
	return (strstr(str1, str2) != NULL);
}	

void insert(Tree **node, Tree *child, int ch)
{
	switch(ch)
	{
		case 1:
			(*node)->left = child;
			break;
		case 2:
			(*node)->middle = child;
			break;
		case 3:
			(*node)->right = child;
			break;
	}
}

void printTree(Tree *root)
{
	if(root == NULL)
		return;
	printTree(root->left);
	printTree(root->middle);
	printTree(root->right);
	if(!strcmp(root->str, ""))
		printf("\nNone %d %d", root->hst, root->d);
	else
		printf("\n%s %d %d", root->str, root->hst, root->d);
}	

//Adds C, but makes it hot

void roller(Tree **node)
{
	char str[10];
	strcpy(str, (*node)->str);
	int len = strlen(str);
	if(len == 0)
	{
		str[0] = 'c';
		str[1] = '\0';
	}
	else if(!contains(str, "c"))
	{
		str[len] = 'c';
		str[len+1] = '\0';
	}
	Tree* child = createNode(str, 3 - strlen(str), depth);
	insert(node, child, 1);
	//printTree(*node);
}

//Adds smooth surface, removes paint

void grinder(Tree **node)
{
	char str[10];
	strcpy(str, (*node)->str);
	int len = strlen(str);
	if(len == 0)
	{
		str[0] = 's';
		str[1] = '\0';
	}
	else
	{
		if(str[len-1] == 'p')
		{
			str[len-1] = '\0';
		}
		len = strlen(str);
		if(!contains(str, "s"))
		{	
			str[len] = 's';
			str[len+1] = '\0';
		}
	}
	Tree* child = createNode(str, 3 - strlen(str), depth);
	insert(node, child, 2);
	//printTree(*node);
}

//Adds paint, requires object to be cool

void painter(Tree **node)
{
	fflush(stdout);
	char str[10];
	int add = 0;
	strcpy(str, (*node)->str);
	int len = strlen(str);
	if(len == 0)
	{
		str[0] = 'p';
		str[1] = '\0';
	}
	else
	{
		if(str[len-1] == 'c')
		{
			add++;
		}
		if(!contains(str, "p"))
		{	
			str[len] = 'p';
			str[len+1] = '\0';
		}
	}
	Tree* child = createNode(str, 3 - strlen(str) + add, depth);
	insert(node, child, 3);
	//printTree(*node);
}

void goal(Tree* node)
{
	printf("\n\nGoal state reached!");
	printf("\n\nCorrect order of actions : \n");
	int i, len = strlen(node->str);
	for(i=0;i<len;i++)
	{
		switch(node->str[i])
		{
			case 'c':
				printf("\n%d) Roller", i+1);
				break;
			case 's':
				printf("\n%d) Grinder", i+1);
				break;
			case 'p':
				printf("\n%d) Painter", i+1);
				break;
		}
	}
	printf("\n\n");
	exit(0);
}

void gen(Queue *q)
{
	depth = 0;
	while(1)
	{
		printf("\n\nDepth %d\n", depth);
		int count = q->count;
		if(count == 0)
			return;
		else
			depth++;
		while(count > 0)
		{
			Tree* temp = del(q);
			printf("\nNode : %s %d %d", temp->str, temp->hst, temp->d);
			if(temp->hst == 0)
			{
				goal(temp);
			}
			roller(&temp);
			grinder(&temp);
			painter(&temp);
			add(q, temp->left);
			add(q, temp->middle);
			add(q, temp->right);
			count--;
		}
	}
}

int main()
{
	Tree *root = createNode("", 3, 0);
	Queue q;
	init(&q);
	depth = 0;
	add(&q, root);
	gen(&q);
	printf("\n\nTree : \n\n");
	printTree(root);
	printf("\n");
	return 0;
}