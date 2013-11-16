#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char * string; // New variable called "string", to read dynamic strings

char * readString(){
    //To read a dynamic string
    int counter=0;
    char * String;
    char c;
    String = (char*)calloc(1,sizeof(char));
    if (String==NULL){
        printf("Insufficient Memory!");
        return NULL;
    }
    while((c = getchar())!='\n'){
        String[counter]=c;
        String = (char*)realloc(String,counter+2);
        counter++;
        String[counter]='\0';
    }
    return String;
}

/*
char **split(char * string_toSplit,char *symbol){
    //To Split Strings

    //0x0000
    char * string_toSPLIT = NULL;
	string_toSPLIT = (char*)calloc(strlen(string_toSplit),sizeof(char)+1);
    strcpy(string_toSPLIT,string_toSplit);
    //0x000A
    int n_spaces = 0;
    char **stringArray = NULL;
    char *  p = strtok (string_toSPLIT,symbol);
    while (p){
        stringArray = (char**)realloc (stringArray, sizeof (char*) * ++n_spaces);
        if (stringArray == NULL)
            exit (-1); //memory allocation failed
        stringArray[n_spaces-1] = p;
        p = strtok (NULL,symbol);
    }
    //realloc one extra element for the last NULL
    stringArray = (char**)realloc (stringArray, sizeof (char*) * (n_spaces+1));
    stringArray[n_spaces] = NULL;
    //[IGNORAR] for (i = 0; i < (n_spaces+1); ++i)
    //[IGNORAR]    printf ("stringArray[%d] = %s\n", i, stringArray[i]);

    return stringArray;
}*/

char **split(char * string_toSplit,char *symbol){
    //To Split Strings

    /*0x0000*/
    char * string_toSPLIT = NULL;
	string_toSPLIT = (char*)calloc(strlen(string_toSplit),sizeof(char)+1);
    strcpy(string_toSPLIT,string_toSplit);
    /*0x000A*/

    int n_spaces = 0;
    char **stringArray = NULL;

    //Si el primer caracter es el simbolo:
    if(string_toSPLIT[0]==symbol[0]){
        stringArray = (char**)realloc(stringArray,sizeof(char*)*++n_spaces);
        stringArray[n_spaces-1] = (char*)calloc(2,sizeof(char));
        strcpy(stringArray[n_spaces-1]," ");
    }

    char *  p = strtok (string_toSPLIT,symbol);
    while (p){
        stringArray = (char**)realloc (stringArray, sizeof (char*) * ++n_spaces);
        if (stringArray == NULL)
            exit (-1); /* memory allocation failed */
        stringArray[n_spaces-1] = p;
        p = strtok (NULL,symbol);
    }
    /* realloc one extra element for the last NULL */
    stringArray = (char**)realloc (stringArray, sizeof (char*) * (n_spaces+1));
    stringArray[n_spaces] = NULL;
    //for (i = 0; i < (n_spaces+1); ++i)
    //    printf ("stringArray[%d] = %s\n", i, stringArray[i]);

    return stringArray;
}

int stringArraySize(char **arrayToCount){
    //printf("ARRAY TO COUNT\n");
    //Calculates the number of strings in an array
    int counter=0;
    char ** aux = arrayToCount;
    while(aux[counter]!=NULL){
        //printf("COUNTER: %d\n",counter);
        counter++;
    }
    return counter;

}

void showArray(char **arrayToShow){
    //printf("ARRAY TO SHOW\n");
    //This function shows the elements (Strings) from an array
    int index;
    int string_size=stringArraySize(arrayToShow);
    for(index=0;index<string_size;index++){
        printf("%s\n",arrayToShow[index]);
    }
}

char *split_chars(char * A,char *symbol){
    //To Split Strings

    /*0x0000*/
    char * string_toSPLIT = NULL;
	string_toSPLIT = (char*)calloc(strlen(A),sizeof(char));
    strcpy(string_toSPLIT,A);
    /*0x000A*/
    int n_spaces = 0;
    char * string = NULL;
    char *  p = strtok (string_toSPLIT,symbol);
    while (p){
        string = (char*)realloc (string, sizeof (char) * ++n_spaces);
        if (string == NULL)
            exit (-1); /* memory allocation failed */
        string[n_spaces-1] = *p;
        p = strtok (NULL,symbol);
    }
    /* realloc one extra element for the last NULL */
    string = (char*)realloc (string, sizeof (char) * (n_spaces+1));
    string[n_spaces] = '\0';
    /*for (i = 0; i < (n_spaces+1); ++i)

        printf ("stringArray[%d] = %s\n", i, stringArray[i]);
    */
    return string;
}


#endif // FUNCTIONS_H_INCLUDED

/*Jesús Alfredo (ZtuX) =) */
