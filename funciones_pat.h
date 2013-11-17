/*funciones_pat.h

[Descripcion]: Contiene funciones para mostrar los razonamientos correctamente, asi como
funciones para contar operadores, buscar simbolos, etc...

*/
#include "variables.h"
#include "notacion_polaca.h"

void mostrarInfoRazonamiento(RAZONAMIENTO R){
    printf("ANTECEDENTE: %s\n",R->Antecedente);
    printf("CONSECUENTE: %s\n",R->Consecuente);
    printf("NO. DE OPARADRES EN EL ANTECEDENTE: %d\n",R->A);
    printf("NO. DE OPARADRES EN EL CONSECUENTE: %d\n",R->C);
    printf("FLAG: %c\n",R->flag);
    printf("nFlag: %d\n",R->nFlag);
    printf("OPERADOR CON EL QUE SE TRABAJA: %c\n",R->opTrabajando);
    printf("CADENA CON LA QUE SE TRABAJA: %s\n",R->trabajando);
    printf("MS Antecedente: %c\n",R->AntecedenteOp);
    printf("MS Consecuente: %c\n",R->ConsecuenteOp);
}


void mostrarRazonamiento(char *antecedent,char *consequent){
    if (antecedent==NULL)
        printf("\n\t=> %s\n",consequent);
    else if (consequent==NULL)
        printf("\n\t%s =>\n",antecedent);
    else
        printf("\n\t%s => %s\n",antecedent,consequent);
}


int contarSimbolos(char *str){
    //Cuenta los simbolos (OPERADORES), que hay en una cadena
    char * aux = NULL;
    aux = (char*)calloc(strlen(str),sizeof(char));
    strcpy(aux,str);
    int index,index2,counter=0;
    for(index=0;index<strlen(aux);index++){
        for (index2=0;index2<5;index2++){
            if(str[index]==ops[index2]){
                counter++;
            }
        }
    }
    //printf("Valor de counter final: %d\n",counter);
    return counter;
}

int identificarMasOperadores(int A, int C){
    /*Regresa 1 si A>C, 0 si A=C y -1 A<C
      Identifica quien tiene mas operadores
    */
    if(A>C){
        //printf("Antecedente tiene mas operadores que el Consecuente\n");
        return 1;
    }
    else if (A<C){
        //printf("Antecedente tiene menos operadores que el Consecuente\n");
        return -1;
    }
    else{
        //printf("Antecedente tiene igual operadores que el Consecuente\n");
        return 0;
    }
}

char * limpiarParentesis(char *cadena){
    //Quita los parentesis del inicio y del final de una cadena
    char * nueva;
    int i;
    if(cadena[0]=='(' && cadena[strlen(cadena)-1]==')'){
        nueva = (char*)calloc(strlen(cadena)-1,sizeof(char));
        for(i=0;i<strlen(cadena)-2;i++){
            nueva[i]=cadena[i+1];
        }
        return nueva;
    }
    return cadena;
}

char getUltimoOperador(char * str){
    /*Regresa el ultimo caracter de una cadena*/
    //printf("CADENA A OBTENER EL ULTIMO OP: %s\n",str);
    int i;
    char c;
    for (i=0;i<strlen(str);i++){
        if(i==(strlen(str)-1)){
            c = str[i];
        }
    }
    /*Si se obtiene el mismo caracter, quiere decir que no habia operadores*/
    if(c==str[0]){
    	return '-';
    }
    return c;
}

char masSignificativo(char * Ops){
    /*Regresa el oprador con mayor jerarquía*/
    char current=Ops[0],aux;
    int i;
    for(i=1;i<strlen(Ops);i++){
        aux=Ops[i];
        if(symbcmp(current,aux)==0 || symbcmp(current,aux)==-1){
            current=aux;
        }
    }
    return current;
}


char identificarSimbolos(char *str){

    /*Regresa el operador Mas Significativo (MS) de una cadena*/
	char * auxStr = NULL;
	auxStr = (char*)calloc(strlen(str),sizeof(char));
	strcpy(auxStr,str); //TRABAJAMOS CON UNA COPIA DE LA CADENA
    char MS='-';
    int i,nSymbols;
    char * aux;
    char ** newArray = split(auxStr,","); /*Separamos por coma*/
    char * Symbols = NULL; //Arreglo que contendra los simbolos encontrados de cada hipotesis
    /*Meter los operadores de cada hipotesis en el arrelo Symbols*/
    for(i=0;i<stringArraySize(newArray);i++){
        //BUSCAMOS UN OPERADOR en newArray[i]
        nSymbols = contarSimbolos(newArray[i]); //Contamos cuantos simbolos hay en la cadena i del arraglo "newArray"
        Symbols = (char*)realloc(Symbols,sizeof(char)*(i+1));
        //Si no hay simbolos
        if(nSymbols==0){
            Symbols[i] = '-';
        }else{
            aux = notacionPolaca(newArray[i]);
            Symbols[i]=getUltimoOperador(aux);
        }
    }
    Symbols[i]='\0';
    //printf("TEST :O\n");

    /*for(i=0;i<strlen(Symbols);i++){
        printf("| %c |\n",Symbols[i]);
    }
    */
    MS = masSignificativo(Symbols);
    //printf("MS= %c\n",MS);
    return MS;
}

char getOperadorTrabajar(char * str){
	//Regresa el operador con el que se va a trabajar...
    char * cadena = NULL,* cadena_s = NULL;
	cadena = (char*)calloc(strlen(str)+1,sizeof(char)+1);
	strncpy(cadena,str,strlen(str)+1);
	cadena_s = notacionPolaca(cadena);
	//printf("cadena_s: %s\n",cadena_s);
    char c = getUltimoOperador(cadena_s);
    //printf("\nULTIMO OP: %c\n",c);
    return c;
}

int posSimbolo(char * arreglo , char simbolo){
    /*Regresa las posicion del operador con mayor jerarquía en la primer coincidencia*/
    char current;
    int pos;
    for(pos=0;pos<strlen(arreglo);pos++){
        current = arreglo[pos];
        if(current==simbolo){
            return pos;
        }
    }
    return -1; /*Si no se encontro un simbolo*/
}

char * identificarSimbolosEnArreglo(char *str){
    /*Funcion que regresa un arreglo de operadores*/
	char * auxStr = NULL;
	auxStr = (char*)calloc(strlen(str),sizeof(char));
	strcpy(auxStr,str);
	//printf("Identificando simbolos de la cadena: %s\n",auxStr);
    //char MS='-';
    int i,nSymbols;
    char * aux;
    char ** newArray = split(auxStr,","); /*Separamos por coma*/
    //MOSTRAMOS EL ARRAY DE LOS RAZONAMIENTOS ENCONTRADOS
    //showArray(newArray);
    char * Symbols = NULL; //Arreglo que contendra los simbolos encontrados de cada hipotesis
    /*Meter los operadores de cada hipotesis en el arrelo Symbols*/
    for(i=0;i<stringArraySize(newArray);i++){
        nSymbols = contarSimbolos(newArray[i]); //Contamos cuantos simbolos hay en la cadena i del arraglo "newArray"
        Symbols = (char*)realloc(Symbols,sizeof(char)*(i+1));
        if(nSymbols==0){
            Symbols[i] = '-';
        }
        else{
            aux = notacionPolaca(newArray[i]);
            Symbols[i]=getUltimoOperador(aux);

        }
    }
    Symbols[i]='\0';
    //printf("ARREGLO DE SIMBOLOS\n");
    //printf("STRLEN Symbols: %d\n",strlen(Symbols));
    //for(i=0;i<strlen(Symbols);i++){
    //    printf("| %c |\n",Symbols[i]);
    //}
    return Symbols;
}

int esValido(char *A, char *C){
    //Verifica si el razonamiento es valido o no.
    //Regresa el valor de 1 si es valido, en caso contrario regresa 0
    char **variables_A, **variables_C, *aux=NULL;
    variables_A = split(A,",");
    variables_C = split(C,",");
    //showArray(variables_A);
    //showArray(variables_C);
    /*Aplicar a cada elemento la notacion polaca para quitar parentesis*/
    int i,j;
    for(i=0;i<stringArraySize(variables_A);i++){
        aux = (char*)realloc(aux,sizeof(char)*strlen(variables_A[i]));
        strcpy(aux,variables_A[i]);
        strcpy(variables_A[i],notacionPolaca(aux));
    }
    for(i=0;i<stringArraySize(variables_C);i++){
        aux = (char*)realloc(aux,sizeof(char)*strlen(variables_C[i]));
        strcpy(aux,variables_C[i]);
        strcpy(variables_C[i],notacionPolaca(aux));
    }
    /*Verificamos que exista por lo menos una vez una variable en A y C*/
    for(i=0;i<stringArraySize(variables_A);i++){
        for(j=0;j<stringArraySize(variables_C);j++){
            if(variables_A[i][0]==variables_C[j][0]){
                return 1;
            }
        }
    }
    return 0;
}


//FUNCIONES PARA OBTENER A X y a Y:
const char operarSN[5] = {'>','^','v','&'}; //Arreglo sin incluir el negado

int esOperadorSN(char c){
    /*Regresa el valor de 1 si el caracter c es operador o parentesis ( ó )
      en caso contrario es una variable y regresa 0.*/
    int i;
    for(i=0;i<strlen(operar);i++){
        if(c==operarSN[i]){
            //printf("Encontre %c\n",operar[i]);
            return 1;
        }
    }
    return 0;
}

/*Separa la cadena en array de caracteres,agrega comas*/
char * separaCadenaComas(char * cadena){
    int i,contador=0,j=0;
    char * cadenaSeparada = NULL;
    for(i=1;i<=strlen(cadena);i++){
        contador=contador+2;
        //printf("Contador: %d\n",contador);
        cadenaSeparada = (char*)realloc(cadenaSeparada,sizeof(char)*(contador+1));
        memset(cadenaSeparada+contador-1,'\0',1);
        //printf("LO QUE Se VA A CAPTURAR: Cadena[i-1]: %c\n",cadena[i-1]);
        cadenaSeparada[i+j-1]=cadena[i-1];
        //printf("LO QUE SE TIENE: Cadena[i+j-1]: %c\n",cadenaSeparada[i+j-1]);
        if(i!=strlen(cadena))
            strcat(cadenaSeparada,",");
        //printf("LO QUE SE TIENE: Cadena[i+j-1]: %s\n",cadenaSeparada);
        j++;
    }
    //printf("MOSTRAR CADENA NUEVA: %s\n",cadenaSeparada);
    //printf("TAMANIO: %d\n",strlen(cadenaSeparada));
    return cadenaSeparada;
}

char ** recorreDesdePosicion(char ** fuente,int inicio){
    /*Recorre los elementos de una cadena dos en dos*/
    int i,tamanio;
    char ** copia = NULL;
    tamanio = stringArraySize(fuente);
    copia = (char**)calloc((tamanio-2)+1,sizeof(char*)+1);


    for(i=inicio;i<tamanio-2;i++){
        //printf("Copiando %s en el lugar de %s\n", fuente[i+2],fuente[i]);
        fuente[i] =  (char*)calloc(strlen(fuente[i+2]),sizeof(char)+1);
        strcpy(fuente[i],fuente[i+2]);
    }
    for(i=0;i<tamanio-2;i++){
        copia[i] = (char*)calloc(strlen(fuente[i]),sizeof(char));
        strcpy(copia[i],fuente[i]);
    }
    copia[i]=NULL;
    return copia;

}

char **recorreDesdePosicionUnoEnUno(char ** fuente,int inicio){
    /*Recorre los elementos de una cadena, uno en uno*/
    //printf("RECORRIENDO UNO EN UNO\n");
    int i,tamanio;
    char ** copia = NULL;
    tamanio = stringArraySize(fuente);
    //printf("TAMANIO: %d\n",tamanio);
    copia = (char**)calloc((tamanio-1)+1,sizeof(char*)+1);

    for(i=inicio;i<tamanio-1;i++){
        //printf("Copiando %s en el lugar de %s\n", fuente[i+1],fuente[i]);
        fuente[i] =  (char*)calloc(strlen(fuente[i+1]),sizeof(char)+1);
        strcpy(fuente[i],fuente[i+1]);
    }
    for(i=0;i<tamanio-1;i++){
        copia[i] = (char*)calloc(strlen(fuente[i]),sizeof(char));
        strcpy(copia[i],fuente[i]);
    }
    copia[i]=NULL;
    return copia;
}

char ** bloqueA(char ** arreglo){
    //Nueva cadena auxiliar
    //printf("BLOQUE A\n");
    char * newString = NULL;
    char bandera = 'C'; //Bandera para continuar o detener el ciclo
    int tamanio, i=0;
    while(bandera=='C'){
        //Analizar si existe var-negado en todo el arreglo
        if((esOperadorSN(arreglo[i][0])==0) && (arreglo[i+1][0]=='~') ){
            tamanio = strlen(arreglo[i+1])+strlen(arreglo[i])+5;
            newString = (char*)calloc(tamanio,sizeof(char));
            strcat(newString,"(");
            strcat(newString,arreglo[i+1]);
            strcat(newString,arreglo[i]);
            strcat(newString,")");
            arreglo[i] = (char*)calloc(strlen(newString),sizeof(char));
            strcpy(arreglo[i],newString);
            //printf("ANTES:\n");
            //showArray(arreglo);
            recorreDesdePosicionUnoEnUno(arreglo,i+1);
            //printf("DESPUES:\n");
            //showArray(arreglo);
        }else{
            i++; if(i==stringArraySize(arreglo)) bandera='S';
        }
    }
    return arreglo;
}

char ** bloqueB(char ** arreglo){
    //Nueva cadena auxiliar
    printf("BLOQUE B \n");
    char * newString = NULL;
    char bandera = 'C'; //Bandera para continuar o detener el ciclo
    int tamanio, i=0;
    while(bandera=='C'){
        //Analizar si existe var-negado en todo el arreglo
        printf("Arreglo[%d][0]= %c \t Arreglo[%d+1][0]= %c\n",i,arreglo[i][0],i,arreglo[i+1][0]);
        if(( (esOperadorSN(arreglo[i][0])==1) && (arreglo[i][0]!='~') ) && (arreglo[i+1][0]=='~') ){
            tamanio = strlen(arreglo[i-2])+strlen(arreglo[i])+strlen(arreglo[i-1])+3;
            newString = (char*)calloc(tamanio,sizeof(char)+1);
            strcat(newString,"(");
            strcat(newString,arreglo[i-2]);
            strcat(newString,arreglo[i]);
            strcat(newString,arreglo[i-1]);
            strcat(newString,")");
            printf("NEW STRING = %s\n",newString);
            arreglo[i-2] = (char*)realloc(arreglo[i-2],strlen(newString)*sizeof(char));
            strcpy(arreglo[i-2],newString);
            printf("ANTES:\n");
            showArray(arreglo);
            recorreDesdePosicion(arreglo,i+1);
            printf("DESPUES:\n");
            showArray(arreglo);
        }else{
            i++; if(i==stringArraySize(arreglo)-1) bandera='S';
        }
    }
    return arreglo;
}

int contadorNegados(char ** arr){
    int i=0,j=0,negados=0;
    for(i=0;i<stringArraySize(arr);i++){
        for(j=0;j<strlen(arr[i]);j++){
            if(arr[i][j]=='~') negados++;
        }
    }
    return negados;
}

int contarNegados(char * cadena){
    //Cuenta negados de una cadena
    int i=0,contador=0;
    for(i=0;i<strlen(cadena)-1;i++){
        if(cadena[i]=='~'){
            contador++;
        }
    }
    return contador;
}

/*Identifica a X y a Y*/
char ** identificaXY(char * cadena_np,int n_operadores){
    char **XY,**XY_aux,bandera='S';
    char *X=NULL,*Y=NULL,*X_aux;
    int contadorOperadores=0;
    XY = split(cadena_np,",");
    int i=0,j;
    if(n_operadores==1){
        return XY;
    }else{
        //BLOQUE A
        //Busca los negados
        XY = bloqueA(XY);
        n_operadores = n_operadores-contadorNegados(XY);
        //printf("FIN BLOQUE A\n");
        //XY = bloqueB(XY);
        //printf("FIN BLOQUE B\n");
        //BLOQUE C
        X = (char*)calloc(1,sizeof(char)+1);
        while(contadorOperadores<=n_operadores-2){
        //Colocarme en la posicion 0, 1 y 2
        //Si 0,1 son variables y 2 es operador se guarda en X
            //Si es variable-variable-operador
            if( (esOperadorSN(XY[i][0])==0) && (esOperadorSN(XY[i+1][0])==0) && (esOperadorSN(XY[i+2][0])==1) ){
                //Obtener el valor de X
                X = (char*)calloc(strlen(XY[i])+strlen(XY[i+1])+strlen(XY[i+2]),sizeof(char)+1);
                memset(X,'\0',strlen(X));
                strcat(X,"(");
                strcat(X,XY[i]);
                strcat(X,XY[i+2]);
                strcat(X,XY[i+1]);
                strcat(X,")");
                //printf("VALOR DE X: %s\n",X);

                //Ingresar el valor de X en XY..
                //printf("VALOR DE X EN EL ARREGLO XY\n");
                XY[i] = (char*)calloc(strlen(X),sizeof(char));
                strcpy(XY[i],X);
                //showArray(XY);
                //printf("RECORRIENDO ARREGLO XY\n");
                XY = recorreDesdePosicion(XY,i+1);
                //printf("VALOR DE X EN EL ARREGLO XY 2\n");
                //showArray(XY);
                //printf("SALI\n");
                contadorOperadores++;
                i=0;
                //return XY;

            //Si hay un negado: variable-negado
            }else{
                i++;
            }
        }
        XY = bloqueA(XY);
    }
    printf("MARCA\n");
    return XY;

}

char ** buscarXY(char * cadena){
    char *np;
    np = notacionPolaca(cadena);
    char * nuevaCadena = separaCadenaComas(np); //Cadena donde se agregan comas
    char ** elementos = split(nuevaCadena,",");
    char **XY=NULL;
    //showArray(elementos);
    int no_simbolos = contarSimbolos(np);
    //printf("HAY %d operdores\n",no_simbolos); //Cuenta cuantos operadores hay en la notacion polaca
    XY = identificaXY(nuevaCadena,no_simbolos);
    //printf("VALOR DE X: %s\nValor de Y: %s\nOperacion a realizar: %s\n",XY[0],XY[1],XY[2]);
    return XY;
}


//THE END[?]
