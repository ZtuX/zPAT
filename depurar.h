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

/*Funcion que verifica los parentesis de una cadena*/
int verificaParentesis(char * cadena){
    //Recibe un arreglo de parentesis, si al final se tienen
    //equis en todo el arreglo, la cadena es valida, en caso contrario
    //la cadena es invalida
    //Regresa 1 si es valida y 0 si es invalida
    int bandera=0;
    int banderaFin=0;
    int tamanio = strlen(cadena);
    int i=0;
    do{
		bandera =0;
		banderaFin=0;
        switch(cadena[i]){
            case '(':
                cadena[i] = '(';
                i++;
                break;
            case ')':
                cadena[i]='X';
                i--;
                /*Estado Q1*/
                do{
                    switch(cadena[i]){
                        case 'X':
                            cadena[i]='X';
                            i--;
                            break;
                        case ')':
                            cadena[i]=')';
                            i--;
                            break;
                        case 32:
                            cadena[i]=32;
                            i--;
                            banderaFin=1;
                            break;
                        case '(':
                            cadena[i]='X';
                            i++;
                            bandera = 1;
                            break;
                    }
                }while(i>=0 && i<tamanio && bandera==0 && banderaFin==0);
                break;
            case 'X':
                cadena[i]='X';
                i++;
                break;
            case 32:
                cadena[i]=32;
                i++;
                banderaFin=1;
                break;
            default:
                //printf("ERROR\n");
                break;
        }
    }while(i>=0 && i<tamanio && banderaFin==0);
    //Verifica si hay equis en todo el arreglo:
    int bValido=1;
    //printf("CADENA %s\n",cadena);
    for(i=0;i<tamanio;i++){
        //Si hay un caracter distinto a la X, entonces la cadena es invalida
        //printf("CADENA i: %c\n",cadena[i]);
        if(cadena[i]!='X'){
            bValido = 0;
            return bValido;
        }
    }
    return bValido;
}

char * obtenerParentesis(char * cadena){
    //Regresa un arreglo de parentesis}
    int i,contador=0;
    char * arregloParentesis=NULL;
    arregloParentesis = (char*)calloc(1,sizeof(char));
    for(i=0;i<strlen(cadena);i++){
        if(cadena[i]=='(' || cadena[i]==')'){
            arregloParentesis = (char*)realloc(arregloParentesis,sizeof(char)*++contador);
            arregloParentesis[contador-1] = cadena[i];
        }

    }
    return arregloParentesis;
}

int verificaVariables(char * cadena){
    int valido,i;
    //Regresa 1 si es valida la cadena, 0 en caso contrario
    for(i=0;i<strlen(cadena);i++){
        if(cadena[i]!='v'){
           //Verifica que no existan variables juntas
            if( (cadena[i]>=65 && cadena[i]<=90) ||  (cadena[i]>=97 && cadena[i]<=122) ){
                //Si es un caracter
                if( (cadena[i+1]>=65 && cadena[i+1]<=90) ||  (cadena[i+1]>=97 && cadena[i+1]<=122)){
                    valido = 0;
                    return valido;
                }
            }

        }
        if(cadena[i]=='v'){
            if(cadena[i+1]=='v'){
                return 0;
            }
        }
    }
    valido = 1;
    return valido;
}
