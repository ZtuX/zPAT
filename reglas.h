/*reglas.h

[Descripcion]: Contiene las reglas y algunas funciones exclsuivas paa  aplicar las reglas
en los razonamientos

*/

#include "funciones_pat.h"

/*Reglas del Antecedente*/

//NEGADO
char ** negadoA(char * antecedente,char * consecuente){
    char ** ante_conse; //Contendra el antecedente en la posicion 0 y el consecuente en la posicion 1
    //printf("ANTECEDENTE: %s\nCONSECUENTE: %s\n\n",antecedente,consecuente); //Mostramos el antecedente y el consecuente actual

    //Variables para alfa, beta, gama, X, Y
    char * alpha, *beta, *gamma, *X, *Y , **strAux;
    char *simbolos, **XY;
    int MS,indice,tamanioArreglo=0,tamanio=0,comas=0;

    //Variables locales que almacenaran el nuevo antecedente y consecuente
    char * nvoAntecedente=NULL, *nvoConsecuente;

    //Creamos arreglo para gamma (es igual al consecuente)
    gamma = (char*)calloc(strlen(consecuente)+1,sizeof(char));
    strncat(gamma,consecuente,strlen(consecuente)+1);

    //Hacemos una busqueda de donde se encuentre que el
    //operador ~ (MS), se guardara la primer coincidencia

    //Dividimos el antecedente en un arreglo (separado por comas)
    strAux = split(antecedente,",");
    tamanioArreglo = stringArraySize(strAux); //Calculamos el tamaño del arreglo
    simbolos = identificarSimbolosEnArreglo(antecedente); //Guardamos en un arreglo los simbolos
    MS = posSimbolo(simbolos,'~'); //Buscamos la posicion del Simbolo
    //printf("MS: %d\n",MS);
    //printf("\t-> Gama: %s\n",gamma); //Mostramos gamma

    //Guardamos a alpha:
    //Calculamos el tamanio de la nueva cadena:
    for(indice=0;indice<MS;indice++){
        tamanio += strlen(strAux[indice]);
    }
    //printf("NUEVO TAMANIO PARA ALPHA: %d\n",tamanio+indice); //Se suma indice para las comas
    alpha = (char*)calloc(tamanio+indice+1,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a alpha las cadenas:
    for(indice=0;indice<MS;indice++){
        strncat(alpha,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=MS-1){
            strncat(alpha,",",1);
        }
    }
    //printf("\t-> Alpha: %s\n",alpha);

    //Guardamos a beta:
    //Calculamos el tamanio de la nueva cadena:
    tamanio=0;
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        tamanio += strlen(strAux[indice]);
        comas++;
    }
    tamanio+=comas; //Se suma "comas" para las comas
    //printf("NUEVO TAMANIO PARA BETA: %d\n",tamanio);
    beta = (char*)calloc(tamanio,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a beta las cadenas:
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        strncat(beta,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=tamanioArreglo-1){
            strncat(beta,",",1);
        }
    }
    //printf("\t-> Beta: %s\n",beta);

    if(contarNegados(strAux[MS])==1){
        strAux[MS]=limpiarParentesis(strAux[MS]);
        //printf("STR: %s\n",strAux[MS]);
        X =(char*)calloc(strlen(strAux[MS])+1,sizeof(char));
        strncat(X,strAux[MS]+1,strlen(strAux[MS]));
        //printf("\t-> X: %s\n",X);
    }else{
        //Obtener a "X" y a "Y"
        XY = buscarXY(strAux[MS]);
        //printf("\t-> X: %s\n",XY[0]);
        X = (char*)calloc(strlen(XY[0])+1,sizeof(char));
        X = strncat(X,XY[0],strlen(XY[0])+1);
    }

    //Obtenemos al nuevo antecedente:
    tamanio = strlen(alpha)+strlen(beta)+1;
    //printf("NUEVO TAMANIO PARA NVOANTECEDENTE: %d\n",tamanio);
    nvoAntecedente = (char*)calloc(tamanio+3,sizeof(char));
    if(strlen(alpha)!=0) strncat(nvoAntecedente,alpha,strlen(alpha)+1);
    if(strlen(alpha)!=0 && strlen(beta)!=0) strncat(nvoAntecedente,",",1);
    if(strlen(beta)!=0) strncat(nvoAntecedente,beta,strlen(beta)+1);
    //printf("\t-> Nuevo Antecedente: %s\n",nvoAntecedente);

    //Nuevo consecuente:
    nvoConsecuente = (char*)calloc(strlen(consecuente)+strlen(X)+1,sizeof(char));
    strncat(nvoConsecuente,X,strlen(X)+1);
    if(strlen(X)!=0) strncat(nvoConsecuente,",",1);
    strncat(nvoConsecuente,gamma,strlen(gamma)+1);
    //printf("\t-> Nuevo Consecuente: %s\n",nvoConsecuente);

    //Copiamos al arreglo de cadenas
    ante_conse = (char**)calloc(1,sizeof(char));
    ante_conse[0] = (char*)calloc(strlen(nvoAntecedente)+1,sizeof(char));
    ante_conse[1] = (char*)calloc(strlen(nvoConsecuente)+1,sizeof(char));
    strncat(ante_conse[0],nvoAntecedente,strlen(nvoAntecedente)+1);
    strncat(ante_conse[1],nvoConsecuente,strlen(nvoConsecuente)+1);

    return ante_conse;

}

//CONJUNCION
char ** conjuncionA(char * antecedente,char * consecuente){
    char ** ante_conse; //Contendra el antecedente en la posicion 0 y el consecuente en la posicion 1
    //[*] printf("ANTECEDENTE: %s\nCONSECUENTE: %s\n\n",antecedente,consecuente); //Mostramos el antecedente y el consecuente actual

    //Variables para alfa, beta, gama, X, Y
    char * alpha, *beta, *gamma, *X, *Y , **strAux;
    char *simbolos, **XY;
    int MS,indice,tamanioArreglo=0,tamanio=0,comas=0;

    //Variables locales que almacenaran el nuevo antecedente y consecuente
    char * nvoAntecedente=NULL, *nvoConsecuente;

    //Creamos arreglo para gamma (es igual al consecuente)
    gamma = (char*)calloc(strlen(consecuente)+1,sizeof(char));
    //Copiamos a gamma el antecedente
    strncat(gamma,consecuente,strlen(consecuente)+1);

    //Hacemos una busqueda de donde se encuentre que el
    //operador ^ (MS), se guardara la primer coincidencia

    //Dividimos el antecedente en un arreglo (separado por comas)
    strAux = split(antecedente,",");
    tamanioArreglo = stringArraySize(strAux); //Calculamos el tamaño del arreglo
    simbolos = identificarSimbolosEnArreglo(antecedente); //Guardamos en un arreglo los simbolos
    MS = posSimbolo(simbolos,'^'); //Buscamos la posicion del Simbolo
    //printf("MS: %d\n",MS);
    //printf("\t-> Gama: %s\n",gamma); //Mostramos gamma


    //Guardamos a alpha:
    //Calculamos el tamanio de la nueva cadena:
    for(indice=0;indice<MS;indice++){
        tamanio += strlen(strAux[indice]);
    }
    //printf("NUEVO TAMANIO PARA ALPHA: %d\n",tamanio+indice); //Se suma indice para las comas
    alpha = (char*)calloc(tamanio+indice+1,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a alpha las cadenas:
    for(indice=0;indice<MS;indice++){
        strncat(alpha,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=MS-1){
            strncat(alpha,",",1);
        }
    }
    //printf("\t-> Alpha: %s\n",alpha);

    //Guardamos a beta:
    //Calculamos el tamanio de la nueva cadena:
    tamanio=0;
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        tamanio += strlen(strAux[indice]);
        comas++;
    }
    tamanio+=comas; //Se suma "comas" para las comas
    //printf("NUEVO TAMANIO PARA BETA: %d\n",tamanio);
    beta = (char*)calloc(tamanio,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a beta las cadenas:
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        strncat(beta,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=tamanioArreglo-1){
            strncat(beta,",",1);
        }
    }
    //printf("\t-> Beta: %s\n",beta);


    //Obtener a "X" y a "Y"
    XY = buscarXY(strAux[MS]);
    //printf("\t-> X: %s\n",XY[0]);
    //printf("\t-> Y: %s\n",XY[1]);
    X = (char*)calloc(strlen(XY[0])+1,sizeof(char));
    Y = (char*)calloc(strlen(XY[1])+1,sizeof(char));
    X = strncat(X,XY[0],strlen(XY[0])+1);
    Y = strncat(Y,XY[1],strlen(XY[1])+1);

    //Obtenemos al nuevo antecedente y el consecuente:
    tamanio = strlen(X)+strlen(Y)+strlen(alpha)+strlen(beta)+1;
    //printf("NUEVO TAMANIO PARA NVOANTECEDENTE: %d\n",tamanio);
    nvoAntecedente = (char*)calloc(tamanio+3,sizeof(char));

    strncat(nvoAntecedente,X,strlen(X)+1);
    strncat(nvoAntecedente,",",1);
    strncat(nvoAntecedente,Y,strlen(Y)+1);
    if(strlen(alpha)!=0){
        strncat(nvoAntecedente,",",1);
        strncat(nvoAntecedente,alpha,strlen(alpha)+1);
    }
    if(strlen(beta)!=0){
        strncat(nvoAntecedente,",",1);
        strncat(nvoAntecedente,beta,strlen(beta)+1);
    }
    //printf("\t-> Nuevo Antecedente: %s\n",nvoAntecedente);

    nvoConsecuente = (char*)calloc(strlen(consecuente)+1,sizeof(char));
    strncat(nvoConsecuente,consecuente,strlen(consecuente)+1);
    //printf("\t-> Nuevo Consecuente: %s\n",nvoConsecuente);

    //Copiamos al arreglo de cadenas
    ante_conse = (char**)calloc(1,sizeof(char));
    ante_conse[0] = (char*)calloc(strlen(nvoAntecedente)+1,sizeof(char)+1);
    ante_conse[1] = (char*)calloc(strlen(nvoConsecuente)+1,sizeof(char)+1);
    strncat(ante_conse[0],nvoAntecedente,strlen(nvoAntecedente)+1);
    strncat(ante_conse[1],nvoConsecuente,strlen(nvoConsecuente)+1);
    //[*]printf("\t-> Nuevo Consecuente D: : %s\n",ante_conse[1]);
    return ante_conse;
}

//DISYUNCION
char ** disyuncionA(char * antecedente, char * consecuente, pNode * primero, pNode * ultimo){
    char ** ante_conse; //Contendra el antecedente en la posicion 0 y el consecuente en la posicion 1
    //[*]printf("ANTECEDENTE: %s\nCONSECUENTE: %s\n\n",antecedente,consecuente); //Mostramos el antecedente y el consecuente actual

    //Variables para alfa, beta, gama, X, Y
    char * alpha, *beta, *gamma, *X, *Y , **strAux;
    char *simbolos, **XY;
    int MS,indice,tamanioArreglo=0,tamanio=0,comas=0;

    //Variables locales que almacenaran el nuevo antecedente y consecuente
    char * nvoAntecedente=NULL, *nvoConsecuente;

    //Creamos arreglo para gamma (es igual al consecuente)
    gamma = (char*)calloc(strlen(consecuente)+1,sizeof(char));
    //Copiamos a gamma el antecedente
    strncat(gamma,consecuente,strlen(consecuente)+1);

    //Hacemos una busqueda de donde se encuentre que el
    //operador v (MS), se guardara la primer coincidencia

    //Dividimos el antecedente en un arreglo (separado por comas)
    strAux = split(antecedente,",");
    tamanioArreglo = stringArraySize(strAux); //Calculamos el tamaño del arreglo
    simbolos = identificarSimbolosEnArreglo(antecedente); //Guardamos en un arreglo los simbolos
    MS = posSimbolo(simbolos,'v'); //Buscamos la posicion del Simbolo
    //printf("MS: %d\n",MS);
    //[*]printf("\t-> Gama: %s\n",gamma); //Mostramos gamma


    //Guardamos a alpha:
    //Calculamos el tamanio de la nueva cadena:
    for(indice=0;indice<MS;indice++){
        tamanio += strlen(strAux[indice]);
    }
    //printf("NUEVO TAMANIO PARA ALPHA: %d\n",tamanio+indice); //Se suma indice para las comas
    alpha = (char*)calloc(tamanio+indice+1,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a alpha las cadenas:
    for(indice=0;indice<MS;indice++){
        strncat(alpha,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=MS-1){
            strncat(alpha,",",1);
        }
    }
    //[*]printf("\t-> Alpha: %s\n",alpha);

    //Guardamos a beta:
    //Calculamos el tamanio de la nueva cadena:
    tamanio=0;
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        tamanio += strlen(strAux[indice]);
        comas++;
    }
    tamanio+=comas; //Se suma "comas" para las comas
    //printf("NUEVO TAMANIO PARA BETA: %d\n",tamanio);
    beta = (char*)calloc(tamanio,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a beta las cadenas:
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        strncat(beta,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=tamanioArreglo-1){
            strncat(beta,",",1);
        }
    }
    //[*]printf("\t-> Beta: %s\n",beta);


    //Obtener a "X" y a "Y"
    XY = buscarXY(strAux[MS]);
    //[*]printf("\t-> X: %s\n",XY[0]);
    //[*]printf("\t-> Y: %s\n",XY[1]);
    X = (char*)calloc(strlen(XY[0])+1,sizeof(char));
    Y = (char*)calloc(strlen(XY[1])+1,sizeof(char));
    X = strncat(X,XY[0],strlen(XY[0])+1);
    Y = strncat(Y,XY[1],strlen(XY[1])+1);

    //Obtenemos al nuevo antecedente y el consecuente:
    tamanio = strlen(X)+strlen(alpha)+strlen(beta)+1;
    //printf("NUEVO TAMANIO PARA NVOANTECEDENTE: %d\n",tamanio);
    nvoAntecedente = (char*)calloc(tamanio+3,sizeof(char));

    strncat(nvoAntecedente,X,strlen(X)+1);
    if(strlen(alpha)!=0){
        strncat(nvoAntecedente,",",1);
        strncat(nvoAntecedente,alpha,strlen(alpha)+1);
    }
    if(strlen(beta)!=0){
        strncat(nvoAntecedente,",",1);
        strncat(nvoAntecedente,beta,strlen(beta)+1);
    }
    //[*]printf("\n\t--> Razonamiento 1\n");
    //[*]printf("\t-> Nuevo Antecedente: %s\n",nvoAntecedente);

    nvoConsecuente = (char*)calloc(strlen(consecuente)+1,sizeof(char));
    strncat(nvoConsecuente,consecuente,strlen(consecuente)+1);
    //[*]printf("\t-> Nuevo Consecuente: %s\n",nvoConsecuente);

    //Copiamos al arreglo de cadenas
    ante_conse = (char**)calloc(1,sizeof(char));
    ante_conse[0] = (char*)calloc(strlen(nvoAntecedente)+1,sizeof(char));
    ante_conse[1] = (char*)calloc(strlen(nvoConsecuente)+1,sizeof(char));
    strncat(ante_conse[0],nvoAntecedente,strlen(nvoAntecedente)+1);
    strncat(ante_conse[1],nvoConsecuente,strlen(nvoConsecuente)+1);

    //Creamos la neva expresion 2
    //[*]printf("\n\t--> Razonamiento 2\n");
    //Obtenemos al nuevo antecedente y el consecuente:
    tamanio = strlen(Y)+strlen(alpha)+strlen(beta)+1;
    //printf("NUEVO TAMANIO PARA NVOANTECEDENTE: %d\n",tamanio);
    nvoAntecedente = (char*)calloc(tamanio+3,sizeof(char));

    strncat(nvoAntecedente,Y,strlen(Y)+1);
    if(strlen(alpha)!=0){
        strncat(nvoAntecedente,",",1);
        strncat(nvoAntecedente,alpha,strlen(alpha)+1);
    }
    if(strlen(beta)!=0){
        strncat(nvoAntecedente,",",1);
        strncat(nvoAntecedente,beta,strlen(beta)+1);
    }
    //[*]printf("\t-> Antecedente: %s\n",nvoAntecedente);

    nvoConsecuente = (char*)calloc(strlen(consecuente)+1,sizeof(char));
    strncat(nvoConsecuente,consecuente,strlen(consecuente)+1);
    //[*]printf("\t-> Consecuente: %s\n",nvoConsecuente);

    //Copiamos a una nueva cadena:
    tamanio = strlen(nvoAntecedente)+strlen(nvoConsecuente)+2;
    char * razonamientoPila = (char*)calloc(tamanio,sizeof(char));
    strncat(razonamientoPila,nvoAntecedente,strlen(nvoAntecedente)+1);
    strncat(razonamientoPila,"=",1);
    strncat(razonamientoPila,nvoConsecuente,strlen(nvoConsecuente)+1);
    //[*]printf("\t-> Razonamiento 2: %s => %s\n",nvoAntecedente,nvoConsecuente);
    add(primero,ultimo,razonamientoPila);
    return ante_conse;
}

//IMPLICACION
char ** implicacionA(char * antecedente, char * consecuente, pNode * primero, pNode * ultimo){
    char ** ante_conse; //Contendra el antecedente en la posicion 0 y el consecuente en la posicion 1
    //[*]printf("ANTECEDENTE: %s\nCONSECUENTE: %s\n\n",antecedente,consecuente); //Mostramos el antecedente y el consecuente actual

    //Variables para alfa, beta, gama, X, Y
    char * alpha, *beta, *gamma, *X, *Y , **strAux;
    char *simbolos, **XY;
    int MS,indice,tamanioArreglo=0,tamanio=0,comas=0;

    //Variables locales que almacenaran el nuevo antecedente y consecuente
    char * nvoAntecedente=NULL, *nvoConsecuente;

    //Creamos arreglo para gamma (es igual al consecuente)
    gamma = (char*)calloc(strlen(consecuente)+1,sizeof(char));
    //Copiamos a gamma el antecedente
    strncat(gamma,consecuente,strlen(consecuente)+1);

    //Hacemos una busqueda de donde se encuentre que el
    //operador v (MS), se guardara la primer coincidencia

    //Dividimos el antecedente en un arreglo (separado por comas)
    strAux = split(antecedente,",");
    tamanioArreglo = stringArraySize(strAux); //Calculamos el tamaño del arreglo
    simbolos = identificarSimbolosEnArreglo(antecedente); //Guardamos en un arreglo los simbolos
    MS = posSimbolo(simbolos,'>'); //Buscamos la posicion del Simbolo
    //printf("MS: %d\n",MS);
    //[*]printf("\t-> Gama: %s\n",gamma); //Mostramos gamma


    //Guardamos a alpha:
    //Calculamos el tamanio de la nueva cadena:
    for(indice=0;indice<MS;indice++){
        tamanio += strlen(strAux[indice]);
    }
    //printf("NUEVO TAMANIO PARA ALPHA: %d\n",tamanio+indice); //Se suma indice para las comas
    alpha = (char*)calloc(tamanio+indice+1,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a alpha las cadenas:
    for(indice=0;indice<MS;indice++){
        strncat(alpha,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=MS-1){
            strncat(alpha,",",1);
        }
    }
    //[*]printf("\t-> Alpha: %s\n",alpha);

    //Guardamos a beta:
    //Calculamos el tamanio de la nueva cadena:
    tamanio=0;
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        tamanio += strlen(strAux[indice]);
        comas++;
    }
    tamanio+=comas; //Se suma "comas" para las comas
    //printf("NUEVO TAMANIO PARA BETA: %d\n",tamanio);
    beta = (char*)calloc(tamanio,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a beta las cadenas:
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        strncat(beta,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=tamanioArreglo-1){
            strncat(beta,",",1);
        }
    }
    //[*]printf("\t-> Beta: %s\n",beta);


    //Obtener a "X" y a "Y"
    XY = buscarXY(strAux[MS]);
    //[*]printf("\t-> X: %s\n",XY[0]);
    //[*]printf("\t-> Y: %s\n",XY[1]);
    X = (char*)calloc(strlen(XY[0])+1,sizeof(char));
    Y = (char*)calloc(strlen(XY[1])+1,sizeof(char));
    X = strncat(X,XY[0],strlen(XY[0])+1);
    Y = strncat(Y,XY[1],strlen(XY[1])+1);

    //Obtenemos al nuevo antecedente y el consecuente:
    tamanio = strlen(Y)+strlen(alpha)+strlen(beta)+1;
    //printf("NUEVO TAMANIO PARA NVOANTECEDENTE: %d\n",tamanio);
    nvoAntecedente = (char*)calloc(tamanio+3,sizeof(char));

    strncat(nvoAntecedente,Y,strlen(Y)+1);
    if(strlen(alpha)!=0){
        strncat(nvoAntecedente,",",1);
        strncat(nvoAntecedente,alpha,strlen(alpha)+1);
    }
    if(strlen(beta)!=0){
        strncat(nvoAntecedente,",",1);
        strncat(nvoAntecedente,beta,strlen(beta)+1);
    }
    //[*]printf("\n\t--> Razonamiento 1\n");
    //[*]printf("\t-> Nuevo Antecedente: %s\n",nvoAntecedente);

    nvoConsecuente = (char*)calloc(strlen(consecuente)+1,sizeof(char));
    strncat(nvoConsecuente,consecuente,strlen(consecuente)+1);
    //[*]printf("\t-> Nuevo Consecuente: %s\n",nvoConsecuente);

    //Copiamos al arreglo de cadenas
    ante_conse = (char**)calloc(1,sizeof(char));
    ante_conse[0] = (char*)calloc(strlen(nvoAntecedente)+1,sizeof(char));
    ante_conse[1] = (char*)calloc(strlen(nvoConsecuente)+1,sizeof(char));
    strncat(ante_conse[0],nvoAntecedente,strlen(nvoAntecedente)+1);
    strncat(ante_conse[1],nvoConsecuente,strlen(nvoConsecuente)+1);

    //Creamos la neva expresion 2
    //[*]printf("\n\t--> Razonamiento 2\n");
    //Obtenemos al nuevo antecedente y el consecuente:
    tamanio = strlen(alpha)+strlen(beta)+1;
    //printf("NUEVO TAMANIO PARA NVOANTECEDENTE: %d\n",tamanio);
    nvoAntecedente = (char*)calloc(tamanio+3,sizeof(char));
    if(strlen(alpha)!=0){
        strncat(nvoAntecedente,alpha,strlen(alpha)+1);
    }
    if(strlen(alpha)!=0 && strlen(beta)!=0 ){
        strncat(nvoAntecedente,",",1);
    }
    if(strlen(beta)!=0){
        strncat(nvoAntecedente,beta,strlen(beta)+1);
    }
    //[*]printf("\t-> Antecedente: %s\n",nvoAntecedente);

    tamanio = strlen(X)+strlen(gamma)+1;
    nvoConsecuente = (char*)calloc(tamanio,sizeof(char));
    strncat(nvoConsecuente,X,strlen(X)+1);
    strncat(nvoConsecuente,",",1);
    strncat(nvoConsecuente,consecuente,strlen(consecuente)+1);
    //[*]printf("\t-> Consecuente: %s\n",nvoConsecuente);

    //Copiamos a una nueva cadena:
    tamanio = strlen(nvoAntecedente)+strlen(nvoConsecuente)+2;
    char * razonamientoPila = (char*)calloc(tamanio,sizeof(char));
    strncat(razonamientoPila,nvoAntecedente,strlen(nvoAntecedente)+1);
    strncat(razonamientoPila,"=",1);
    strncat(razonamientoPila,nvoConsecuente,strlen(nvoConsecuente)+1);
    //[*]printf("\t-> ESTE! Razonamiento 2: %s => %s\n",nvoAntecedente,nvoConsecuente);
    add(primero,ultimo,razonamientoPila);
    return ante_conse;
}

//DOBLE IMPLICACION
char ** dobleImplicaA(char * antecedente, char * consecuente, pNode * primero, pNode * ultimo){
    char ** ante_conse; //Contendra el antecedente en la posicion 0 y el consecuente en la posicion 1
    //[*]printf("ANTECEDENTE: %s\nCONSECUENTE: %s\n\n",antecedente,consecuente); //Mostramos el antecedente y el consecuente actual

    //Variables para alfa, beta, gama, X, Y
    char * alpha, *beta, *gamma, *X, *Y , **strAux;
    char *simbolos, **XY;
    int MS,indice,tamanioArreglo=0,tamanio=0,comas=0;

    //Variables locales que almacenaran el nuevo antecedente y consecuente
    char * nvoAntecedente=NULL, *nvoConsecuente;

    //Creamos arreglo para gamma (es igual al consecuente)
    gamma = (char*)calloc(strlen(consecuente)+1,sizeof(char));
    //Copiamos a gamma el antecedente
    strncat(gamma,consecuente,strlen(consecuente)+1);

    //Hacemos una busqueda de donde se encuentre que el
    //operador v (MS), se guardara la primer coincidencia

    //Dividimos el antecedente en un arreglo (separado por comas)
    strAux = split(antecedente,",");
    tamanioArreglo = stringArraySize(strAux); //Calculamos el tamaño del arreglo
    simbolos = identificarSimbolosEnArreglo(antecedente); //Guardamos en un arreglo los simbolos
    MS = posSimbolo(simbolos,'&'); //Buscamos la posicion del Simbolo
    //printf("MS: %d\n",MS);
    //[*]printf("\t-> Gama: %s\n",gamma); //Mostramos gamma


    //Guardamos a alpha:
    //Calculamos el tamanio de la nueva cadena:
    for(indice=0;indice<MS;indice++){
        tamanio += strlen(strAux[indice]);
    }
    //printf("NUEVO TAMANIO PARA ALPHA: %d\n",tamanio+indice); //Se suma indice para las comas
    alpha = (char*)calloc(tamanio+indice+1,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a alpha las cadenas:
    for(indice=0;indice<MS;indice++){
        strncat(alpha,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=MS-1){
            strncat(alpha,",",1);
        }
    }
    //[*]printf("\t-> Alpha: %s\n",alpha);

    //Guardamos a beta:
    //Calculamos el tamanio de la nueva cadena:
    tamanio=0;
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        tamanio += strlen(strAux[indice]);
        comas++;
    }
    tamanio+=comas; //Se suma "comas" para las comas
    //printf("NUEVO TAMANIO PARA BETA: %d\n",tamanio);
    beta = (char*)calloc(tamanio,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a beta las cadenas:
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        strncat(beta,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=tamanioArreglo-1){
            strncat(beta,",",1);
        }
    }
    //[*]printf("\t-> Beta: %s\n",beta);


    //Obtener a "X" y a "Y"
    XY = buscarXY(strAux[MS]);
    //[*]printf("\t-> X: %s\n",XY[0]);
    //[*]printf("\t-> Y: %s\n",XY[1]);
    X = (char*)calloc(strlen(XY[0])+1,sizeof(char));
    Y = (char*)calloc(strlen(XY[1])+1,sizeof(char));
    X = strncat(X,XY[0],strlen(XY[0])+1);
    Y = strncat(Y,XY[1],strlen(XY[1])+1);

    //Obtenemos al nuevo antecedente y el consecuente:
    tamanio = strlen(X)+strlen(Y)+strlen(alpha)+strlen(beta)+1;
    //printf("NUEVO TAMANIO PARA NVOANTECEDENTE: %d\n",tamanio);
    nvoAntecedente = (char*)calloc(tamanio+3,sizeof(char));
    strncat(nvoAntecedente,X,strlen(X)+1);
    strncat(nvoAntecedente,",",1);
    strncat(nvoAntecedente,Y,strlen(Y)+1);
    if(strlen(alpha)!=0){
        strncat(nvoAntecedente,",",1);
        strncat(nvoAntecedente,alpha,strlen(alpha)+1);
    }
    if(strlen(beta)!=0){
        strncat(nvoAntecedente,",",1);
        strncat(nvoAntecedente,beta,strlen(beta)+1);
    }
    //[*]printf("\n\t--> Razonamiento 1\n");
    //[*]printf("\t-> Nuevo Antecedente: %s\n",nvoAntecedente);

    nvoConsecuente = (char*)calloc(strlen(consecuente)+1,sizeof(char));
    strncat(nvoConsecuente,consecuente,strlen(consecuente)+1);
    //[*]printf("\t-> Nuevo Consecuente: %s\n",nvoConsecuente);

    //Copiamos al arreglo de cadenas
    ante_conse = (char**)calloc(1,sizeof(char));
    ante_conse[0] = (char*)calloc(strlen(nvoAntecedente)+1,sizeof(char));
    ante_conse[1] = (char*)calloc(strlen(nvoConsecuente)+1,sizeof(char));
    strncat(ante_conse[0],nvoAntecedente,strlen(nvoAntecedente)+1);
    strncat(ante_conse[1],nvoConsecuente,strlen(nvoConsecuente)+1);

    //Creamos la neva expresion 2
    //[*]printf("\n\t--> Razonamiento 2\n");
    //Obtenemos al nuevo antecedente y el consecuente:
    tamanio = strlen(alpha)+strlen(beta)+1;
    //printf("NUEVO TAMANIO PARA NVOANTECEDENTE: %d\n",tamanio);
    nvoAntecedente = (char*)calloc(tamanio+3,sizeof(char));
    if(strlen(alpha)!=0){
        strncat(nvoAntecedente,alpha,strlen(alpha)+1);
    }
    if(strlen(alpha)!=0 && strlen(beta)!=0 ){
        strncat(nvoAntecedente,",",1);
    }
    if(strlen(beta)!=0){
        strncat(nvoAntecedente,beta,strlen(beta)+1);
    }
    //[*]printf("\t-> Antecedente: %s\n",nvoAntecedente);

    tamanio = strlen(X)+strlen(Y)+strlen(gamma)+3;
    nvoConsecuente = (char*)calloc(tamanio,sizeof(char));
    strncat(nvoConsecuente,X,strlen(X)+1);
    strncat(nvoConsecuente,",",1);
    strncat(nvoConsecuente,Y,strlen(Y)+1);
    strncat(nvoConsecuente,",",1);
    strncat(nvoConsecuente,gamma,strlen(gamma)+1);
    //[*]printf("\t-> Consecuente: %s\n",nvoConsecuente);

    //Copiamos a una nueva cadena:
    tamanio = strlen(nvoAntecedente)+strlen(nvoConsecuente)+3;
    char * razonamientoPila = (char*)calloc(tamanio,sizeof(char));
    strncat(razonamientoPila,nvoAntecedente,strlen(nvoAntecedente)+1);
    strncat(razonamientoPila,"=",1);
    strncat(razonamientoPila,nvoConsecuente,strlen(nvoConsecuente)+1);
    //[*]printf("\t-> Razonamiento 2: %s => %s\n",nvoAntecedente,nvoConsecuente);
    add(primero,ultimo,razonamientoPila);
    return ante_conse;
}


/*Reglas del consecuente*/

//NEGADO
char ** negadoC(char * antecedente, char * consecuente){
    char ** ante_conse; //Contendra el antecedente en la posicion 0 y el consecuente en la posicion 1
    //[*]printf("ANTECEDENTE: %s\nCONSECUENTE: %s\n\n",antecedente,consecuente); //Mostramos el antecedente y el consecuente actual

    //Variables para alfa, beta, gama, X, Y
    char * alpha, *beta, *gamma, *X, *Y , **strAux;
    char *simbolos, **XY;
    int MS,indice,tamanioArreglo=0,tamanio=0,comas=0;

    //Variables locales que almacenaran el nuevo antecedente y consecuente
    char * nvoAntecedente=NULL, *nvoConsecuente;

    //Creamos arreglo para alpha (es igual al antecedente)
    alpha = (char*)calloc(strlen(antecedente)+1,sizeof(char));
    strncat(alpha,antecedente,strlen(antecedente)+1);

    //Hacemos una busqueda de donde se encuentre que el
    //operador ~ (MS), se guardara la primer coincidencia

    //Dividimos el consecuente en un arreglo (separado por comas)
    strAux = split(consecuente,",");
    tamanioArreglo = stringArraySize(strAux); //Calculamos el tamaño del arreglo
    simbolos = identificarSimbolosEnArreglo(consecuente); //Guardamos en un arreglo los simbolos
    MS = posSimbolo(simbolos,'~'); //Buscamos la posicion del Simbolo
    //printf("MS: %d\n",MS);
    //[*]printf("\t-> Alpha: %s\n",alpha); //Mostramos alpha

    //Guardamos a beta:
    //Calculamos el tamanio de la nueva cadena:
    for(indice=0;indice<MS;indice++){
        tamanio += strlen(strAux[indice]);
    }
    //printf("NUEVO TAMANIO PARA ALPHA: %d\n",tamanio+indice); //Se suma indice para las comas
    beta = (char*)calloc(tamanio+indice+1,sizeof(char)); //Asignamos tamaño para beta
    //Copiamos a alpha las cadenas:
    for(indice=0;indice<MS;indice++){
        strncat(beta,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=MS-1){
            strncat(beta,",",1);
        }
    }
    //[*]printf("\t-> Beta: %s\n",beta);

    //Guardamos a gamma:
    //Calculamos el tamanio de la nueva cadena:
    tamanio=0;
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        tamanio += strlen(strAux[indice]);
        comas++;
    }
    tamanio+=comas; //Se suma "comas" para las comas
    //printf("NUEVO TAMANIO PARA BETA: %d\n",tamanio);
    gamma = (char*)calloc(tamanio,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a beta las cadenas:
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        strncat(gamma,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=tamanioArreglo-1){
            strncat(gamma,",",1);
        }
    }
    //[*]printf("\t-> Gamma: %s\n",gamma);

    //Obtener a "X" y a "Y"

    if(contarNegados(strAux[MS])==1){
        strAux[MS]=limpiarParentesis(strAux[MS]);
        //printf("STR: %s\n",strAux[MS]);
        X =(char*)calloc(strlen(strAux[MS]),sizeof(char));
        strncat(X,strAux[MS]+1,strlen(strAux[MS]));
        //[*]printf("\t-> X: %s\n",X);
    }else{
        //Obtener a "X" y a "Y"
        XY = buscarXY(strAux[MS]);
        //[*]printf("\t-> X: %s\n",XY[0]);
        X = (char*)calloc(strlen(XY[0])+1,sizeof(char));
        X = strncat(X,XY[0],strlen(XY[0])+1);
    }

    /*XY = buscarXY(strAux[MS]);
    printf("\t-> X: %s\n",XY[0]);
    X = (char*)calloc(strlen(XY[0])+1,sizeof(char));
    X = strncat(X,XY[0],strlen(XY[0])+1);*/

    //Obtenemos al nuevo antecedente:
    tamanio = strlen(X)+strlen(alpha)+1;
    //printf("NUEVO TAMANIO PARA NVOANTECEDENTE: %d\n",tamanio);
    nvoAntecedente = (char*)calloc(tamanio+3,sizeof(char));
    strncat(nvoAntecedente,X,strlen(X)+1);
    if(strlen(alpha)!=0){
        strncat(nvoAntecedente,",",1);
        strncat(nvoAntecedente,alpha,strlen(alpha)+1);
    }
    //[*]printf("\t-> Nuevo Antecedente: %s\n",nvoAntecedente);

    //Nuevo consecuente:
    nvoConsecuente = (char*)calloc(strlen(beta)+strlen(gamma)+1,sizeof(char));
    if(strlen(beta)!=0){
        strncat(nvoConsecuente,beta,strlen(beta)+1);
    }
    if(strlen(beta)!=0 && strlen(gamma)!=0){
        strncat(nvoConsecuente,",",1);
    }
    if(strlen(gamma)!=0){
        strncat(nvoConsecuente,gamma,strlen(gamma)+1);
    }
    //[*]printf("\t-> Nuevo Consecuente: %s\n",nvoConsecuente);

    //Copiamos al arreglo de cadenas
    ante_conse = (char**)calloc(1,sizeof(char));
    ante_conse[0] = (char*)calloc(strlen(nvoAntecedente)+1,sizeof(char));
    ante_conse[1] = (char*)calloc(strlen(nvoConsecuente)+1,sizeof(char));
    strncat(ante_conse[0],nvoAntecedente,strlen(nvoAntecedente)+1);
    strncat(ante_conse[1],nvoConsecuente,strlen(nvoConsecuente)+1);

    return ante_conse;

}

//CONJUNCION
 char ** conjuncionC(char * antecedente, char * consecuente, pNode * primero, pNode * ultimo){
    char ** ante_conse; //Contendra el antecedente en la posicion 0 y el consecuente en la posicion 1
    //[*]printf("ANTECEDENTE: %s\nCONSECUENTE: %s\n\n",antecedente,consecuente); //Mostramos el antecedente y el consecuente actual

    //Variables para alfa, beta, gama, X, Y
    char * alpha, *beta, *gamma, *X, *Y , **strAux;
    char *simbolos, **XY;
    int MS,indice,tamanioArreglo=0,tamanio=0,comas=0;

    //Variables locales que almacenaran el nuevo antecedente y consecuente
    char * nvoAntecedente=NULL, *nvoConsecuente;

    //Creamos arreglo para alpha (es igual al consecuente)
    alpha = (char*)calloc(strlen(antecedente)+1,sizeof(char));
    //Copiamos a gamma el antecedente
    strncat(alpha,antecedente,strlen(antecedente)+1);

    //Hacemos una busqueda de donde se encuentre que el
    //operador ^ (MS), se guardara la primer coincidencia

    //Dividimos el consecuente en un arreglo (separado por comas)
    strAux = split(consecuente,",");
    tamanioArreglo = stringArraySize(strAux); //Calculamos el tamaño del arreglo
    simbolos = identificarSimbolosEnArreglo(consecuente); //Guardamos en un arreglo los simbolos
    MS = posSimbolo(simbolos,'^'); //Buscamos la posicion del Simbolo
    //printf("MS: %d\n",MS);
    //[*]printf("\t-> Alpha: %s\n",alpha); //Mostramos alpha


    //Guardamos a Beta:
    //Calculamos el tamanio de la nueva cadena:
    for(indice=0;indice<MS;indice++){
        tamanio += strlen(strAux[indice]);
    }
    //printf("NUEVO TAMANIO PARA BETA: %d\n",tamanio+indice); //Se suma indice para las comas
    beta = (char*)calloc(tamanio+indice+1,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a beta las cadenas:
    for(indice=0;indice<MS;indice++){
        strncat(beta,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=MS-1){
            strncat(beta,",",1);
        }
    }
    //[*]printf("\t-> Beta: %s\n",beta);

    //Guardamos a gamma:
    //Calculamos el tamanio de la nueva cadena:
    tamanio=0;
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        tamanio += strlen(strAux[indice]);
        comas++;
    }
    tamanio+=comas; //Se suma "comas" para las comas
    //printf("NUEVO TAMANIO PARA BETA: %d\n",tamanio);
    gamma = (char*)calloc(tamanio,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a beta las cadenas:
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        strncat(gamma,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=tamanioArreglo-1){
            strncat(gamma,",",1);
        }
    }
    //[*]printf("\t-> Gamma: %s\n",gamma);


    //Obtener a "X" y a "Y"
    XY = buscarXY(strAux[MS]);
    //[*]printf("\t-> X: %s\n",XY[0]);
    //[*]printf("\t-> Y: %s\n",XY[1]);
    X = (char*)calloc(strlen(XY[0])+1,sizeof(char));
    Y = (char*)calloc(strlen(XY[1])+1,sizeof(char));
    X = strncat(X,XY[0],strlen(XY[0])+1);
    Y = strncat(Y,XY[1],strlen(XY[1])+1);

    //Obtenemos al nuevo antecedente y el consecuente:
    tamanio = strlen(alpha)+1;
    //printf("NUEVO TAMANIO PARA NVOANTECEDENTE: %d\n",tamanio);
    nvoAntecedente = (char*)calloc(tamanio+3,sizeof(char));

    strncat(nvoAntecedente,alpha,strlen(alpha)+1);
    //[*]printf("\n\t--> Razonamiento 1\n");
    //[*]printf("\t-> Nuevo Antecedente: %s\n",nvoAntecedente);

    tamanio = strlen(X)+strlen(beta)+strlen(gamma)+3;
    nvoConsecuente = (char*)calloc(tamanio,sizeof(char));
    strncat(nvoConsecuente,X,strlen(X)+1);
    if(strlen(beta)!=0){
        strncat(nvoConsecuente,",",1);
        strncat(nvoConsecuente,beta,strlen(beta)+1);
    }
    if(strlen(gamma)!=0){
        strncat(nvoConsecuente,",",1);
        strncat(nvoConsecuente,gamma,strlen(gamma)+1);
    }
    //[*]printf("\t-> Nuevo Consecuente: %s\n",nvoConsecuente);

    //Copiamos al arreglo de cadenas
    ante_conse = (char**)calloc(1,sizeof(char));
    ante_conse[0] = (char*)calloc(strlen(nvoAntecedente)+1,sizeof(char));
    ante_conse[1] = (char*)calloc(strlen(nvoConsecuente)+1,sizeof(char));
    strncat(ante_conse[0],nvoAntecedente,strlen(nvoAntecedente)+1);
    strncat(ante_conse[1],nvoConsecuente,strlen(nvoConsecuente)+1);

    //Creamos la neva expresion 2
    //[*]printf("\n\t--> Razonamiento 2\n");
    //Obtenemos al nuevo antecedente y el consecuente:
    nvoAntecedente = (char*)calloc(strlen(alpha)+1,sizeof(char));
    strncat(nvoAntecedente,alpha,strlen(alpha)+1);
    //[*]printf("\t-> Antecedente: %s\n",nvoAntecedente);

    tamanio = strlen(Y)+strlen(beta)+strlen(gamma)+3;
    nvoConsecuente = (char*)calloc(tamanio,sizeof(char));
    strncat(nvoConsecuente,Y,strlen(Y)+1);
    if(strlen(beta)!=0){
        strncat(nvoConsecuente,",",1);
        strncat(nvoConsecuente,beta,strlen(beta)+1);
    }
    if(strlen(gamma)!=0){
        strncat(nvoConsecuente,",",1);
        strncat(nvoConsecuente,gamma,strlen(gamma)+1);
    }
    //[*]printf("\t-> Consecuente: %s\n",nvoConsecuente);

    //Copiamos a una nueva cadena:
    tamanio = strlen(nvoAntecedente)+strlen(nvoConsecuente)+2;
    char * razonamientoPila = (char*)calloc(tamanio,sizeof(char));
    strncat(razonamientoPila,nvoAntecedente,strlen(nvoAntecedente)+1);
    strncat(razonamientoPila,"=",1);
    strncat(razonamientoPila,nvoConsecuente,strlen(nvoConsecuente)+1);
    //[*]printf("\t-> Razonamiento 2: %s => %s\n",nvoAntecedente,nvoConsecuente);
    add(primero,ultimo,razonamientoPila);
    return ante_conse;
 }

//DISYUNCION
 char ** disyuncionC(char * antecedente, char * consecuente){
    char ** ante_conse; //Contendra el antecedente en la posicion 0 y el consecuente en la posicion 1
    //[*]printf("ANTECEDENTE: %s\nCONSECUENTE: %s\n\n",antecedente,consecuente); //Mostramos el antecedente y el consecuente actual

    //Variables para alfa, beta, gama, X, Y
    char * alpha, *beta, *gamma, *X, *Y , **strAux;
    char *simbolos, **XY;
    int MS,indice,tamanioArreglo=0,tamanio=0,comas=0;

    //Variables locales que almacenaran el nuevo antecedente y consecuente
    char * nvoAntecedente=NULL, *nvoConsecuente;

    //Creamos arreglo para alpha (es igual al antecedente)
    alpha = (char*)calloc(strlen(antecedente)+1,sizeof(char));
    //Copiamos a gamma el antecedente
    strncat(alpha,antecedente,strlen(antecedente)+1);

    //Hacemos una busqueda de donde se encuentre que el
    //operador v (MS), se guardara la primer coincidencia

    //Dividimos el consecuente en un arreglo (separado por comas)
    strAux = split(consecuente,",");
    tamanioArreglo = stringArraySize(strAux); //Calculamos el tamaño del arreglo
    simbolos = identificarSimbolosEnArreglo(consecuente); //Guardamos en un arreglo los simbolos
    MS = posSimbolo(simbolos,'v'); //Buscamos la posicion del Simbolo
    //printf("MS: %d\n",MS);
    //[*]printf("\t-> Alpha: %s\n",alpha); //Mostramos alpha


    //Guardamos a Beta:
    //Calculamos el tamanio de la nueva cadena:
    for(indice=0;indice<MS;indice++){
        tamanio += strlen(strAux[indice]);
    }
    //printf("NUEVO TAMANIO PARA BETA: %d\n",tamanio+indice); //Se suma indice para las comas
    beta = (char*)calloc(tamanio+indice+1,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a beta las cadenas:
    for(indice=0;indice<MS;indice++){
        strncat(beta,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=MS-1){
            strncat(beta,",",1);
        }
    }
    //[*]printf("\t-> Beta: %s\n",beta);

    //Guardamos a gamma:
    //Calculamos el tamanio de la nueva cadena:
    tamanio=0;
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        tamanio += strlen(strAux[indice]);
        comas++;
    }
    tamanio+=comas; //Se suma "comas" para las comas
    //printf("NUEVO TAMANIO PARA BETA: %d\n",tamanio);
    gamma = (char*)calloc(tamanio,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a beta las cadenas:
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        strncat(gamma,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=tamanioArreglo-1){
            strncat(gamma,",",1);
        }
    }
    //[*]printf("\t-> Gamma: %s\n",gamma);


    //Obtener a "X" y a "Y"
    XY = buscarXY(strAux[MS]);
    //[*]printf("\t-> X: %s\n",XY[0]);
    //[*]printf("\t-> Y: %s\n",XY[1]);
    X = (char*)calloc(strlen(XY[0])+1,sizeof(char));
    Y = (char*)calloc(strlen(XY[1])+1,sizeof(char));
    X = strncat(X,XY[0],strlen(XY[0])+1);
    Y = strncat(Y,XY[1],strlen(XY[1])+1);

    //Obtenemos al nuevo antecedente y el consecuente:
    tamanio = strlen(alpha)+1;
    //printf("NUEVO TAMANIO PARA NVOANTECEDENTE: %d\n",tamanio);
    nvoAntecedente = (char*)calloc(tamanio,sizeof(char));

    strncat(nvoAntecedente,alpha,strlen(alpha)+1);
    //[*]printf("\n\t--> Razonamiento 1\n");
    //[*]printf("\t-> Nuevo Antecedente: %s\n",nvoAntecedente);

    tamanio = strlen(beta)+strlen(X)+strlen(Y)+strlen(gamma)+4;
    nvoConsecuente = (char*)calloc(tamanio,sizeof(char));
    strncat(nvoConsecuente,X,strlen(X)+1);
    strncat(nvoConsecuente,",",1);
    strncat(nvoConsecuente,Y,strlen(Y)+1);
    if(strlen(beta)!=0){
        strncat(nvoConsecuente,",",1);
        strncat(nvoConsecuente,beta,strlen(beta)+1);
    }
    if(strlen(gamma)!=0){
        strncat(nvoConsecuente,",",1);
        strncat(nvoConsecuente,gamma,strlen(gamma)+1);
    }
    //[*]printf("\t-> Nuevo Consecuente: %s\n",nvoConsecuente);

    //Copiamos al arreglo de cadenas
    ante_conse = (char**)calloc(1,sizeof(char));
    ante_conse[0] = (char*)calloc(strlen(nvoAntecedente)+1,sizeof(char));
    ante_conse[1] = (char*)calloc(strlen(nvoConsecuente)+1,sizeof(char));
    strncat(ante_conse[0],nvoAntecedente,strlen(nvoAntecedente)+1);
    strncat(ante_conse[1],nvoConsecuente,strlen(nvoConsecuente)+1);
    return ante_conse;
 }

//DISYUNCION
 char ** implicacionC(char * antecedente, char * consecuente){
    char ** ante_conse; //Contendra el antecedente en la posicion 0 y el consecuente en la posicion 1
    //[*]printf("ANTECEDENTE: %s\nCONSECUENTE: %s\n\n",antecedente,consecuente); //Mostramos el antecedente y el consecuente actual

    //Variables para alfa, beta, gama, X, Y
    char * alpha, *beta, *gamma, *X, *Y , **strAux;
    char *simbolos, **XY;
    int MS,indice,tamanioArreglo=0,tamanio=0,comas=0;

    //Variables locales que almacenaran el nuevo antecedente y consecuente
    char * nvoAntecedente=NULL, *nvoConsecuente;

    //Creamos arreglo para alpha (es igual al antecedente)
    alpha = (char*)calloc(strlen(antecedente)+1,sizeof(char));
    //Copiamos a gamma el antecedente
    strncat(alpha,antecedente,strlen(antecedente)+1);

    //Hacemos una busqueda de donde se encuentre que el
    //operador v (MS), se guardara la primer coincidencia

    //Dividimos el consecuente en un arreglo (separado por comas)
    strAux = split(consecuente,",");
    tamanioArreglo = stringArraySize(strAux); //Calculamos el tamaño del arreglo
    simbolos = identificarSimbolosEnArreglo(consecuente); //Guardamos en un arreglo los simbolos
    MS = posSimbolo(simbolos,'>'); //Buscamos la posicion del Simbolo
    //printf("MS: %d\n",MS);
    //[*]printf("\t-> Alpha: %s\n",alpha); //Mostramos alpha


    //Guardamos a Beta:
    //Calculamos el tamanio de la nueva cadena:
    for(indice=0;indice<MS;indice++){
        tamanio += strlen(strAux[indice]);
    }
    //printf("NUEVO TAMANIO PARA BETA: %d\n",tamanio+indice); //Se suma indice para las comas
    beta = (char*)calloc(tamanio+indice+1,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a beta las cadenas:
    for(indice=0;indice<MS;indice++){
        strncat(beta,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=MS-1){
            strncat(beta,",",1);
        }
    }
    //[*]printf("\t-> Beta: %s\n",beta);

    //Guardamos a gamma:
    //Calculamos el tamanio de la nueva cadena:
    tamanio=0;
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        tamanio += strlen(strAux[indice]);
        comas++;
    }
    tamanio+=comas; //Se suma "comas" para las comas
    //printf("NUEVO TAMANIO PARA BETA: %d\n",tamanio);
    gamma = (char*)calloc(tamanio,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a beta las cadenas:
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        strncat(gamma,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=tamanioArreglo-1){
            strncat(gamma,",",1);
        }
    }
    //[*]printf("\t-> Gamma: %s\n",gamma);


    //Obtener a "X" y a "Y"
    XY = buscarXY(strAux[MS]);
    //[*]printf("\t-> X: %s\n",XY[0]);
    //[*]printf("\t-> Y: %s\n",XY[1]);
    X = (char*)calloc(strlen(XY[0])+1,sizeof(char));
    Y = (char*)calloc(strlen(XY[1])+1,sizeof(char));
    X = strncat(X,XY[0],strlen(XY[0])+1);
    Y = strncat(Y,XY[1],strlen(XY[1])+1);

    //Obtenemos al nuevo antecedente y el consecuente:
    tamanio = strlen(X)+strlen(alpha)+3;
    //printf("NUEVO TAMANIO PARA NVOANTECEDENTE: %d\n",tamanio);
    nvoAntecedente = (char*)calloc(tamanio,sizeof(char));
    strncat(nvoAntecedente,X,strlen(X)+1);
    strncat(nvoAntecedente,",",1);
    strncat(nvoAntecedente,alpha,strlen(alpha)+1);
    //[*]printf("\n\t--> Razonamiento 1\n");
    //[*]printf("\t-> Nuevo Antecedente: %s\n",nvoAntecedente);

    tamanio = strlen(Y)+strlen(beta)+strlen(gamma)+4;
    nvoConsecuente = (char*)calloc(tamanio,sizeof(char));
    strncat(nvoConsecuente,Y,strlen(Y)+1);
    if(strlen(beta)!=0){
        strncat(nvoConsecuente,",",1);
        strncat(nvoConsecuente,beta,strlen(beta)+1);
    }
    if(strlen(gamma)!=0){
        strncat(nvoConsecuente,",",1);
        strncat(nvoConsecuente,gamma,strlen(gamma)+1);
    }
    //[*]printf("\t-> Nuevo Consecuente: %s\n",nvoConsecuente);

    //Copiamos al arreglo de cadenas
    ante_conse = (char**)calloc(1,sizeof(char));
    ante_conse[0] = (char*)calloc(strlen(nvoAntecedente)+1,sizeof(char));
    ante_conse[1] = (char*)calloc(strlen(nvoConsecuente)+1,sizeof(char));
    strncat(ante_conse[0],nvoAntecedente,strlen(nvoAntecedente)+1);
    strncat(ante_conse[1],nvoConsecuente,strlen(nvoConsecuente)+1);
    return ante_conse;
 }

 //DOBLE IMPLICACION
 char ** dobleImplicaC(char * antecedente, char * consecuente, pNode * primero, pNode * ultimo){
    char ** ante_conse; //Contendra el antecedente en la posicion 0 y el consecuente en la posicion 1
    //[*]printf("ANTECEDENTE: %s\nCONSECUENTE: %s\n\n",antecedente,consecuente); //Mostramos el antecedente y el consecuente actual

    //Variables para alfa, beta, gama, X, Y
    char * alpha, *beta, *gamma, *X, *Y , **strAux;
    char *simbolos, **XY;
    int MS,indice,tamanioArreglo=0,tamanio=0,comas=0;

    //Variables locales que almacenaran el nuevo antecedente y consecuente
    char * nvoAntecedente=NULL, *nvoConsecuente;

    //Creamos arreglo para alpha (es igual al antecedente)
    alpha = (char*)calloc(strlen(antecedente)+1,sizeof(char));
    //Copiamos a gamma el antecedente
    strncat(alpha,antecedente,strlen(antecedente)+1);

    //Hacemos una busqueda de donde se encuentre que el
    //operador ^ (MS), se guardara la primer coincidencia

    //Dividimos el consecuente en un arreglo (separado por comas)
    strAux = split(consecuente,",");
    tamanioArreglo = stringArraySize(strAux); //Calculamos el tamaño del arreglo
    simbolos = identificarSimbolosEnArreglo(consecuente); //Guardamos en un arreglo los simbolos
    MS = posSimbolo(simbolos,'&'); //Buscamos la posicion del Simbolo
    //printf("MS: %d\n",MS);
    //[*]printf("\t-> Alpha: %s\n",alpha); //Mostramos alpha


    //Guardamos a Beta:
    //Calculamos el tamanio de la nueva cadena:
    for(indice=0;indice<MS;indice++){
        tamanio += strlen(strAux[indice]);
    }
    //printf("NUEVO TAMANIO PARA BETA: %d\n",tamanio+indice); //Se suma indice para las comas
    beta = (char*)calloc(tamanio+indice+1,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a beta las cadenas:
    for(indice=0;indice<MS;indice++){
        strncat(beta,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=MS-1){
            strncat(beta,",",1);
        }
    }
    //[*]printf("\t-> Beta: %s\n",beta);

    //Guardamos a gamma:
    //Calculamos el tamanio de la nueva cadena:
    tamanio=0;
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        tamanio += strlen(strAux[indice]);
        comas++;
    }
    tamanio+=comas; //Se suma "comas" para las comas
    //printf("NUEVO TAMANIO PARA BETA: %d\n",tamanio);
    gamma = (char*)calloc(tamanio,sizeof(char)); //Asignamos tamaño para alpha
    //Copiamos a beta las cadenas:
    for(indice=MS+1;indice<tamanioArreglo;indice++){
        strncat(gamma,strAux[indice],strlen(strAux[indice])+1);
        if(indice!=tamanioArreglo-1){
            strncat(gamma,",",1);
        }
    }
    //[*]printf("\t-> Gamma: %s\n",gamma);


    //Obtener a "X" y a "Y"
    XY = buscarXY(strAux[MS]);
    //[*]printf("\t-> X: %s\n",XY[0]);
    //[*]printf("\t-> Y: %s\n",XY[1]);
    X = (char*)calloc(strlen(XY[0])+1,sizeof(char));
    Y = (char*)calloc(strlen(XY[1])+1,sizeof(char));
    X = strncat(X,XY[0],strlen(XY[0])+1);
    Y = strncat(Y,XY[1],strlen(XY[1])+1);

    //Obtenemos al nuevo antecedente y el consecuente:
    tamanio = strlen(X)+strlen(alpha)+1;
    //printf("NUEVO TAMANIO PARA NVOANTECEDENTE: %d\n",tamanio);
    nvoAntecedente = (char*)calloc(tamanio+2,sizeof(char));
    strncat(nvoAntecedente,X,strlen(X)+1);
    strncat(nvoAntecedente,",",1);
    strncat(nvoAntecedente,alpha,strlen(alpha)+1);
    //[*]printf("\n\t--> Razonamiento 1\n");
    //[*]printf("\t-> Nuevo Antecedente: %s\n",nvoAntecedente);

    tamanio = strlen(Y)+strlen(beta)+2;
    nvoConsecuente = (char*)calloc(tamanio,sizeof(char));
    strncat(nvoConsecuente,Y,strlen(Y)+1);
    if(strlen(beta)!=0){
        strncat(nvoConsecuente,",",1);
        strncat(nvoConsecuente,beta,strlen(beta)+1);
    }
    //[*]printf("\t-> Nuevo Consecuente: %s\n",nvoConsecuente);

    //Copiamos al arreglo de cadenas
    ante_conse = (char**)calloc(1,sizeof(char));
    ante_conse[0] = (char*)calloc(strlen(nvoAntecedente)+1,sizeof(char));
    ante_conse[1] = (char*)calloc(strlen(nvoConsecuente)+1,sizeof(char));
    strncat(ante_conse[0],nvoAntecedente,strlen(nvoAntecedente)+1);
    strncat(ante_conse[1],nvoConsecuente,strlen(nvoConsecuente)+1);

    //Creamos la neva expresion 2
    //[*]printf("\n\t--> Razonamiento 2\n");
    //Obtenemos al nuevo antecedente y el consecuente:
    tamanio = strlen(Y)+strlen(alpha)+1;
    //printf("NUEVO TAMANIO PARA NVOANTECEDENTE: %d\n",tamanio);
    nvoAntecedente = (char*)calloc(tamanio+2,sizeof(char));
    strncat(nvoAntecedente,Y,strlen(Y)+1);
    strncat(nvoAntecedente,",",1);
    strncat(nvoAntecedente,alpha,strlen(alpha)+1);
    //[*]printf("\t-> Antecedente: %s\n",nvoAntecedente);

    tamanio = strlen(X)+strlen(beta)+2;
    nvoConsecuente = (char*)calloc(tamanio,sizeof(char));
    strncat(nvoConsecuente,X,strlen(X)+1);
    if(strlen(beta)!=0){
        strncat(nvoConsecuente,",",1);
        strncat(nvoConsecuente,beta,strlen(beta)+1);
    }
    //[*]printf("\t-> Consecuente: %s\n",nvoConsecuente);

    //Copiamos a una nueva cadena:
    tamanio = strlen(nvoAntecedente)+strlen(nvoConsecuente)+2;
    char * razonamientoPila = (char*)calloc(tamanio,sizeof(char));
    strncat(razonamientoPila,nvoAntecedente,strlen(nvoAntecedente)+1);
    strncat(razonamientoPila,"=",1);
    strncat(razonamientoPila,nvoConsecuente,strlen(nvoConsecuente)+1);
    //[*]printf("\t-> Razonamiento 2: %s => %s\n",nvoAntecedente,nvoConsecuente);
    add(primero,ultimo,razonamientoPila);
    return ante_conse;
 }

//Funcion para aplicar la regla en base al operador y al la bandera (A o C)
char ** aplicarRegla(char regla,char flag, char * antecedente, char * consecuente, pNode *primero, pNode *ultimo){
    //Regresa un arreglo con el antecedente y el consecuente
    //Recibe:
    // regla -> Regla que se va a aplicar (caracter)
    // flag -> Bandera con quien se ba a trabajar (Antecedente o Consecuente)
    // antecedente y consecuente -> Cadenas a manipular
    // primero y ultimo -> Nodos de la cola (en caso de tener que agregar nuevos razonamientos)
    char ** ante_conse=NULL;
	/*Si es el antecedente, se aplica una regla del antecedente*/
	if(flag == 'A'){
		if(regla=='~'){
			//[*]printf("\tAplicando regla del Negado en el Antecedente\n\n");
			ante_conse = negadoA(antecedente,consecuente);
		}
		else if(regla=='^'){
			//[*]printf("\tAplicando regla de Conjuncion en el Antecedente\n\n");
			ante_conse = conjuncionA(antecedente,consecuente);
		}
		else if(regla=='v'){
			//[*]printf("\tAplicando regla de Disyuncion en el Antecedente\n\n");
			ante_conse = disyuncionA(antecedente,consecuente,primero,ultimo);
		}
		else if(regla=='>'){
			//[*]printf("\tAplicando regla de Implicacion en el Antecedente\n\n");
            ante_conse = implicacionA(antecedente,consecuente,primero,ultimo);
		}
		else if(regla=='&'){
			//[*]printf("\tAplicando regla de <=> en el Antecedente\n\n");
			ante_conse = dobleImplicaA(antecedente,consecuente,primero,ultimo);
		}
		else{
			printf("\tNo se aplicara ninguna regla\n");
		}
	}
	/*En caso contrario se aplica la regla del consecuente*/
	else{

		if(regla=='~'){
			//[*]printf("\tAplicando regla del Negado en el Consecuente\n\n");
			ante_conse = negadoC(antecedente,consecuente);
		}
		else if(regla=='^'){
			//[*]printf("\tAplicando regla de Conjuncion en el Consecuente\n\n");
			ante_conse = conjuncionC(antecedente,consecuente,primero,ultimo);
		}
		else if(regla=='v'){
			//[*]printf("\tAplicando regla de Disyuncion en el Consecuente\n\n");
			ante_conse = disyuncionC(antecedente,consecuente);
		}
		else if(regla=='>'){
			//[*]printf("\tAplicando regla de Implicacion en el Consecuente\n\n");
			ante_conse = implicacionC(antecedente,consecuente);
		}
		else if(regla=='&'){
			//[*]printf("\tAplicando regla de <=> en el Consecuente\n\n");
			ante_conse = dobleImplicaC(antecedente,consecuente,primero,ultimo);
		}
		else{
			printf("\tNo se aplicara ninguna regla\n");
		}
	}
	return ante_conse;
}




//The_End[?]
