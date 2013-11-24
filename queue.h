#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
   char * value;
   struct _node *next;
} nodeType;

typedef nodeType *pNode;

/* Queue functions */

void add(pNode *first, pNode * last, char * value) {
   pNode newNode;

   /*Make a new node */
   newNode = (pNode)malloc(sizeof(nodeType));
   newNode->value = (char*)calloc(strlen(value)+1,sizeof(char)+1);
   /*Copy the value from argument*/
   strncat(newNode->value,value,strlen(value)+1);

   /* Last node, points to NULL */
   newNode->next = NULL;

   /* If the queue is not empty, we'll append the new node after last node*/
   if(*last) (*last)->next = newNode;
   *last = newNode;
   if(!*first) *first = newNode;
}

char * read(pNode *first, pNode *last) {
   pNode node; /* auxiliary variable to go over the node */
   char * value;    /* return auxiliary variable */

   /* Node points to the first element */
   node = *first;
   if(!node) return 0; /*If there aren't nodes, we'll return 0*/
   *first = node->next;
   /* Save the return value */
   value = (char*)calloc(strlen(node->value)+1,sizeof(char)+1);
   strncat(value,node->value,strlen(node->value)+1);
   /* Delete the node */
   free(node);
   /* If the queue is empty, the last element points to NULL*/
   if(!*first) *last = NULL;
   return value;
}

void showQueue(pNode first, pNode last){
    pNode aux;
    int i=1;
    for(aux = first;aux!=NULL;aux=aux->next){
        printf("[%d] %s\n",i,aux->value);
        i++;
    }
}
#endif // QUEUE_H_INCLUDED
