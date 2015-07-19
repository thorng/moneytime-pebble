/*
 *   Demonstrates iterative operations on  singly linked lists
 *
 *   Muhammed Othman
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

void insertAtHead(void);
void insertAtTail(void);
void insertAtPosition(void);
void delete(void);
void traverse(void);
void reverse(void);
void bubbleSort(void);
void insertionSort(void);
void selectionSort(void);
void search(void);
void swap(void);
void removeNthFromEnd(int n);

node* list = NULL;

int main(void)
{
    int c;
    do
    {
        printf("\nMENU\n\n"
                "1 - insert at head\n"
                "2 - insert at tail\n"
                "3 - insert at position\n"
                "4 - bubble sort\n"
                "5 - insertion sort\n"
                "6 - selection sort\n"
                "7 - delete\n"
                "8 - traverse\n"
                "9 - reverse\n"
                "0 - quit\n");
        printf("\nCommand: ");
        scanf("%d", &c);
        switch (c)
        {
            case 1: insertAtHead(); break;
            case 2: insertAtTail(); break;
            case 3: insertAtPosition(); break;
            case 4: delete(); break;
            case 5: traverse(); break;
            case 9: reverse(); break;
            case 10: removeNthFromEnd(1); break;
        }
        printf("\n");
        traverse();
        printf("\n");
    }
    while(c != 0);

    node *temp = list;

    while(list != NULL)
    {
        list = list->next;
        free(temp);
        temp = list;
    }
}

// inserts a new node at the begininnig of the list
void insertAtHead(void)
{
    int x;
    printf("\nEnter data: ");
    scanf("%d", &x);
    node *temp = malloc(sizeof(node));
    temp->data = x;
    temp->next = list;
    list = temp;
}

// inserts a new node at the end of the list
// using double pointers to handle all the cases
void insertAtTail(void)
{
    int x;
    printf("\nEnter data: ");
    scanf("%d", &x);
    node *newNode = malloc(sizeof(node));
    newNode->data = x;
    newNode->next = NULL;
    node **temp = &list;
    while(*temp != NULL)
    {
        temp = &((*temp)->next);
    }

    (*temp)= newNode;
}

// inserts a new node at a certain position in the list
// using double pointers to handle all the cases
void insertAtPosition(void)
{
    int p, x;
    printf("Enter position: ");
    scanf("%d", &p);
    printf("Enter data: ");
    scanf("%d", &x);
    node **temp = &list;
    node *newNode = malloc(sizeof(node));
    newNode->data = x;
    newNode->next = NULL;
    for (int i = 0; (i < p) && ((*temp) != NULL); i++)
    {
        temp = &((*temp)->next);
    }

    newNode->next = (*temp);
    (*temp) = newNode;
}


// traverses through a list, printing all it's nodes
void traverse(void)
{
    node *temp = list;
    printf("List is:");
    while(temp != NULL)
    {
        printf(" %d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// deletes a certain node with certain data value in the list
// using double pointers to handle all the cases
void delete(void)
{
    /*
     * All cases are handleded except if last node == x
     * Another version handles last node == x but doesn't handle multiple
     * equavilant nodes.
     * */
    int x;
    printf("Enter data: ");
    scanf("%d", &x);
    node *current = list;
    node **temp = &list;
    while (current != NULL)
    {
        if (current->data == x)
        {
            *temp = (*temp)->next;
            free(current);
            current = *temp;
            
        }
        
        if (current->data != x)
        {
            current =  current->next;
        }
        temp = &((*temp)->next);
    }
}


// without reference pointers
void reverse(void)
{
    node* current = list;
    node* next;
    node* prev = NULL;
    while(current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list = prev;
}

// problem solving

void removeNthFromEnd(int n)
{
    node* current = list;
    node* prev = list;
    node* next;
    node* countList = list;
    int countL = 1;
    int count = 1;
    while(countList != NULL)
    {
        countList = countList->next;
        countL++;
    }
    
    int x = countL - n;
    while(current != NULL)
    {
        if (x == count)
        {
            prev->next = current->next;
            free(current);
        }
        prev = current;
        current = current->next;
        count++;
    }
    
    traverse();
}