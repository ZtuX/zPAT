#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct _nodo {
   char valor;
   struct _nodo *siguiente;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Pila;

Pila crearPila(){
    Pila tope = NULL;
    return tope;
}

void push(Pila *pila, char v) {
   pNodo nuevo;

   /* Crear un nodo nuevo */
   nuevo = (pNodo)malloc(sizeof(tipoNodo));
   nuevo->valor = v;

   /* Añadimos la pila a continuación del nuevo nodo */
   nuevo->siguiente = *pila;
   /* Ahora, el comienzo de nuestra pila es en nuevo nodo */
   *pila = nuevo;
}

char pop(Pila *pila) {
   pNodo nodo; /* variable auxiliar para manipular nodo */
   char v;      /* variable auxiliar para retorno */

   /* Nodo apunta al primer elemento de la pila */
   nodo = *pila;
   if(!nodo) return 0; /* Si no hay nodos en la pila retornamos 0 */
   /* Asignamos a pila toda la pila menos el primer elemento */
   *pila = nodo->siguiente;
   /* Guardamos el valor de retorno */
   v = nodo->valor;
   /* Borrar el nodo */
   free(nodo);
   return v;
}

/*
    Regresa 1 si no hay nodos en la lista ligada y cero en caso contrario
    *pila es el apuntador que apunta al primer nodo de la lista ligada (la cima de la pila)
*/
int pila_vacia(Pila *pila)
{
 return (*pila == NULL ? 1:0);
}

/*Vacia el contenido de una pila a otra pila de forma invertida*/
void copiarAPila(Pila pilaA, Pila *pilaB){
    pNodo nodo;
    for (nodo=pilaA;nodo!=NULL;nodo=nodo->siguiente){
        push(pilaB,nodo->valor);
    }
}

/*Vacia el contenido de una pila en una cadena*/
char * vaciarACadena(Pila P){
    char * cadena;
    //pNodo nodo = P;
    int i=0;
    cadena = (char*)calloc(1,sizeof(char));
    if (cadena==NULL){
        printf("Insufficient Memory!");
        return NULL;
    }
    while(P!=NULL){
        cadena[i]=pop(&P);
        cadena = (char*)realloc(cadena,i+2);
        i++;
        cadena[i]='\0';
    }
    return cadena;
}

/*Muestra el contenido de cada nodo de la pila*/
void mostrarPila(Pila pila){
    pNodo n;
    for (n = pila;n!=NULL;n=n->siguiente){
        printf("|%c|\n",n->valor);
    }
}

/*Regresa el valor que esta en el tope, pero no lo borra de la pila*/
char tope(Pila P){
    if(pila_vacia(&P)==1){
        return '-';
    }
    char top;
    top = P->valor;
    return top;
}

#endif // STACK_H_INCLUDED
