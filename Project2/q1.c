#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
	char data;
	struct Node* next;
} Node;


typedef struct Stack {
	Node* head;
}Stack;

void push(Stack* S, char n);
Node* addToHead(Node* head, Node* toAdd);
char pop(Stack* S);
char isEmpty(const Stack* S);
void rotate(Stack* s, int n);
int isPlindrom(Stack* s);
void reverseWord(char s[], int* position);
void reverseStr(char s[]);
int countStack(Stack* s);



void main()
{
	Stack s;
	Node* head = (Node*)malloc(10 * sizeof(Node*));
	Node* two = (Node*)malloc(10 * sizeof(Node*));
	Node* three = (Node*)malloc(10 * sizeof(Node*));
	Node* four = (Node*)malloc(10 * sizeof(Node*));
	Node* five = (Node*)malloc(10 * sizeof(Node*));
	char str[100];
	int rest = 0;

	strcpy(str, "Remem#reb# thi#carp s#tice");
	s.head = head;

	head->next = two;
	two->next = three;
	three->next = four;
	four->next = five;
	five->next = NULL;

	head->data = 'A';
	two->data = 'B';
	three->data = 'D';
	four->data = 'B';
	five->data = 'A';

	reverseStr(str);
	rest = isPlindrom(&s);
	s.head = head;

	isPlindrom(&s);
	rotate(&s, 3);

	printf("\n");
	printf("%d", rest);

}

void reverseStr(char s[])
{
	int length = strlen(s);

	for (int i = 0; i < length; i++)
	{
		while (s[i] != '#' && s[i] != '\0')
			i++;

		if (s[i] != '\0')
		{
			i++;
			reverseWord(s, &i);
		}
	}

	for (int i = 0; i < length; i++)
	{
		if (s[i] != '#')
			printf("%c", s[i]);
	}
}

void reverseWord(char s[], int* position)
{
	int begin, end, count = *position;
	char res;

	while (s[count] != '#')
		count++;

	end = count - 1;

	for (begin = *position; begin < end; begin++)
	{
		res = s[begin];
		s[begin] = s[end];
		s[end] = res;
		end--;
	}

	*position = count + 2;
}

void rotate(Stack* s, int n)
{
	Stack n1, n2;
	n1.head = NULL, n2.head = NULL;

	for (int i = 0; i < n; i++)
		push(&n1, pop(s));

	while (s->head != NULL)
		push(&n2, pop(s));

	for (int i = 0; i < n; i++)
		push(s, pop(&n1));

	while (n2.head != NULL)
		push(s, pop(&n2));

}


int isPlindrom(Stack* s)
{
	int count = countStack(s), decision = 1;
	char resChar, tempS, tempN1;
	Stack n1, resN1, resS;
	n1.head = NULL, resN1.head = NULL, resS.head = NULL;

	for (int i = 0; i < count / 2; i++)
		push(&n1, pop(s));

	if (count % 2)
		resChar = pop(s);


	while (s->head != NULL)
	{
		tempN1 = pop(&n1);
		tempS = pop(s);

		if (tempN1 != tempS)
			decision = 0;

		push(&resN1, tempN1);
		push(&resS, tempS);
	}


	while (resS.head != NULL)
		push(s, pop(&resS));

	if (count % 2)
		push(s, resChar);

	while (resN1.head != NULL)
		push(&n1, pop(&resN1));

	while (n1.head != NULL)
		push(s, pop(&n1));

	return decision;
}


int countStack(Stack* s)
{
	int count = 0;
	Stack n1;
	n1.head = NULL;

	while (s->head != NULL)
	{
		push(&n1, pop(s));
		count++;
	}

	while (n1.head != NULL)
		push(s, pop(&n1));

	return count;
}


void push(Stack* S, char n)
{
	Node* newnode = (Node*)malloc(sizeof(Node));
	if (newnode == NULL)
	{
		printf("push: memory allocation problem\n");
		return;
	}
	newnode->data = n;
	S->head = addToHead(S->head, newnode);
}

char pop(Stack* S)
{
	char res;
	Node* temp = S->head;
	if (S->head == NULL)
	{
		printf("\nSTACK IS EMPTY");
		return 0;
	}
	res = S->head->data;

	S->head = S->head->next;
	free(temp);

	return res;
}

char isEmpty(const Stack* S)
{
	return (!(S->head));
}

Node* addToHead(Node* head, Node* toAdd)
{
	toAdd->next = head;
	head = toAdd;
	return head;
}