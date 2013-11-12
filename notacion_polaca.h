#include "stack.h"

int getValorSimbolo(char a){
    /*Obtiene el valor de la jerarquia del simbolo*/
    int value=-1;
    int index;
    //counter=0;
    for (index=0;index<5;index++){
        if(a==ops[index]){
            value = opsValor[index];
        }
    }
    return value;
}

char symbcmp(char a,char b){
    /*ES - Regresa 1 si a es mayor que b
                   0 si son iguales
                   -1 si a es menor que b
    Compara por jerarquia.
    */
    int aVal, bVal;
    aVal = getValorSimbolo(a);
    bVal = getValorSimbolo(b);
    if (aVal>bVal)
        return 1;
    else if (aVal<bVal)
        return -1;
    else
        return 0;
}

int identificar(char c){
    /*Regresa:
    0 Si es operando
    1 Si es operador
    -1 Si es parentesis que abre
    -2 Si es parentesis que cierra
    */
    int i;
    for (i=0;i<5;i++){
        if(c==ops[i]){
            //printf("ES OPERADOR\n");
            return 1;
        }
    }
    if(c=='('){
        //printf("Es parentesis que abre\n");
        return -1;
       }
    if(c==')'){
        //printf("Es parentesis que cierra\n");
        return -2;
    }
    //printf("ES OPERANDO\n");
    return 0;
}

char * notacionPolaca(char * expresion){
	char * auxExpresion = NULL;
	auxExpresion = (char*)calloc(strlen(expresion),sizeof(char));
	strcpy(auxExpresion,expresion);
    //printf("EXPRESION: %s\n\n\n",expresion);
    char MARCA = '#';
    Pila P1,P2,aux;
    int i=0;
    char car,c;
    P1=P2=aux=crearPila();
    while(auxExpresion[i]!='\0'){
        //printf("EXPRESION[%d]: %c\n",i,expresion[i]);
        car = auxExpresion[i];
        /*Si car es operando*/
        if(identificar(car)==0){
            push(&P1,car);
        }
        /*Si car es operador*/
        else if (identificar(car)==1){
            while(symbcmp(tope(aux),car)==1 || symbcmp(tope(aux),car)==0){
                c = pop(&aux);
                push(&P1,c);
            }
            push(&aux,car);
        }
        /*Si car es "("*/
        else if (identificar(car)==-1){
            push(&aux,MARCA);
        }
        /*Si car es ")"*/
        else{
            while(tope(aux)!=MARCA){
                c = pop(&aux);
                push(&P1,c);
            }
            c = pop(&aux); //Para quitar la marca
        }
        i++;
    }
    /*Mientras aux no este vacia*/
    while((pila_vacia(&aux))==0){
        c = pop(&aux);
        push(&P1,c);
    }
    //printf("MOSTRAR PILA:\n");
    //mostrarPila(P1);
    //printf("MOSTRAR PILA2:\n");
    copiarAPila(P1,&P2);
    //mostrarPila(P2);
    char *a = vaciarACadena(P2);
    //printf("RESULTADO NOTACION POLACA: %s\n",a);
    return a;
}

