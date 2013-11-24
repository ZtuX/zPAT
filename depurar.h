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


const char opsVerificar[5] = {'>','^','v','&'}; //Arreglo sin incluir el negado

int opValido(char c){
    /*Regresa el valor de 1 si el caracter c es operador o parentesis ( ó )
      en caso contrario es una variable y regresa 0.*/
    int i;
    for(i=0;i<strlen(opsVerificar);i++){
        if(c==opsVerificar[i]){
            //printf("Encontre %c\n",operar[i]);
            return 1;
        }
    }
    return 0;
}

int verificaCadena(char * cadena){
    //Verifica si una cadena es valida, regresa 1 si es valida,
    // en caso contrario regresa 0
    int tamanio = strlen(cadena);
    int i=0;
    do{
        if(opValido(cadena[i])==1){
            //Si es un operador
            cadena[i]='Y';
            i--;
        }
        else if( cadena[i]!='v' && (cadena[i]>=97 &&cadena[i]<=122) ){
            //Si es una variable
            cadena[i]='X';
            i++;
        }
        else if(cadena[i]=='X'){
            i++;
        }
        else if(cadena[i]=='Y'){
            i++;
        }
        else if(cadena[i]=='~'){
            cadena[i]=32;
            i++;
        }
        else if(cadena[i]=='(' || cadena[i]==')'){
            cadena[i]=32;
            i++;
        }
        else if(cadena[i]==32){
            i++;
        }else{
            return 0; //Si no es ninguno de esos caracteres en automatico dice que es invalido
        }
    }while(i>=0 && i<tamanio);
    //Recorremos el arreglo para verificar que este intercalado con X y Y
    quitarEspaciosBlanco(cadena);
    tamanio = strlen(cadena);
    //printf("TAMANIO: %d\n",tamanio);
    //printf("Cadena al final: %s\n",cadena);
    for(i=0;i<tamanio-1;i++){
        //Si no estan alternados con X y Y esntonces es invalida...
        //printf("Cadena[i]: %c\n",cadena[i]);
        //printf("ANALIZANDO cadena[%d]:%c y cadena[%d+1]:%c\n",i,cadena[i],i,cadena[i+1]);
        //printf("i:%d\n",i);
        //printf("Tamanio: %d\n",tamanio);
        if(i==0 && cadena[i]=='Y'){
            return 0;
        }
        if(i==tamanio-2 && cadena[i+1]=='Y'){
            return 0;
        }
        if(cadena[i]=='X' && cadena[i+1]!='Y'){
                return 0;
        }
        else if (cadena[i]=='Y' && cadena[i+1]!='X'){
                return 0;
        }
        //printf("i:%d\n",i);
    }
    return 1;
}
