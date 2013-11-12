/*
---> depurar.h
[Descripcion]: Contiene funciones para verficar la validez de los razonamientos, y dar el
formato correcto para poder manejarlas en en el PAT
*/


/*Funcion para quitar espacios en blanco de una cadena*/
void quitarEspaciosBlanco(char * cadena){
    int indice,i=0,acomulador=1;
    char * cadenaAux = (char*)calloc(1,sizeof(char)+1);
    for(indice=0;indice<strlen(cadena)+1;indice++){
        if(cadena[indice]!=32){
            cadenaAux = (char*)realloc(cadenaAux,sizeof(char)*(acomulador));
            cadenaAux[i]=cadena[indice];
            i++;
            acomulador++;
        }
    }
    //printf("CADENA LIMPIA: %s\n",cadenaAux);
    strcpy(cadena,cadenaAux);
}

/*Funcion para pasar a minusculas toda una cadena*/
char * strlwr(char * string){
    while(*string)
       {
          if ( *string >= 'A' && *string <= 'Z' )
          {
             *string = *string + 32;
          }
          string++;
       }
}
