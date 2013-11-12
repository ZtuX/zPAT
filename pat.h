/*
---> pat.h
Prueba automatica de teoremas

[Descripcion]: Regresa el valor de 1 si el razonamiento es valido,
en caso contrario regresa un 0.
*/
#include "functions.h"
#include "depurar.h"
//#include "funciones_pat.h"
#include "reglas.h"

char ** ANTE_CONSE = NULL;  //Variable que contendra el antecedente y consecuente
                            //que se pueden modificar durante todo el proceso

int PAT(char * razonamiento,pNode * primero, pNode * ultimo){
    //Recibe el razonamiento con el que se va a trabajar (razonaiento)
    //y recible los nodos de la cola

    int valido=0;
    int i=0; //Variable que sirve como indice en los arreglos
    //IDENTIFICAR ANTECEDENTE Y CONSECUENTE
    //Eliminar espacios en blanco de la expresión
    quitarEspaciosBlanco(razonamiento);
    //Pasamos a minusculas el razonamiento
    strlwr(razonamiento);

    //Falta agregar si es valida la sintaxis o no

    //Separar en antecedente y consecuente
    char ** Array=NULL;
    Array = split(razonamiento,"=\r\n"); //SE SEPARARAN POR =
    if (stringArraySize(Array)>2){
        printf("[Error] El operador '=>' encontrado mas de una vez\n");
        return -1;
    }

    //CREAMOS LA ESTRUCTIRA DE UN NUEVO RAZONAMIENTO
    RAZONAMIENTO R = NULL;
    R = (RAZONAMIENTO)calloc(1,sizeof(RAZONAMIENTO));
    R->Antecedente = (char*)calloc(strlen(Array[0])+1,sizeof(char)+1);
    R->Consecuente = (char*)calloc(strlen(Array[1])+1,sizeof(char)+1);
    R->trabajando = NULL;
    R->Antecedente = Array[0]; //strcpy(R->Antecedente,Array[0]);
    R->Consecuente = Array[1]; //strcpy(R->Consecuente,Array[1]);
    //mostrarInfoRazonamiento(R);
    printf("\n");
    mostrarRazonamiento(R->Antecedente,R->Consecuente);

    //CONTAR OPERADORES EN EL ANTECEDENTE Y CONSECUENTE */
    R->A = contarSimbolos(R->Antecedente);
    R->C = contarSimbolos(R->Consecuente);
    //mostrarInfoRazonamiento(R);

    //3.A Quien tiene menos operadores[?]
    int value = identificarMasOperadores(R->A,R->C);


    /*3.b Si tienen el mismo numero de operadores, entonces value = 0*/
    if(value==0){
        /*3.b.i. BUSCAR EN EL ANTECEDENTE Y CONSECUENTE EL DE MAYOR JERARQUIA*/
        //printf("Antecedente: %s\n",R->Antecedente);
        //printf("Consecuente: %s\n",R->Consecuente);
        R->AntecedenteOp = identificarSimbolos(R->Antecedente);
        R->ConsecuenteOp = identificarSimbolos(R->Consecuente);
         /* 3.b.ii.  COMPARAR EL OPERADOR DE MAYOR JERARQUIA DEL ANTECEDENTE CON EL DEL CONSECUENTE*/
         /* 3.b.iii. TRABAJAR CON EL QUE TIENE MAYOR JERARQUIA */
        if(symbcmp(R->AntecedenteOp,R->ConsecuenteOp)==0){
            /*Si son de la misma jerarquia, trabajaremos con el antecedente*/
            R->flag='A';
            R->nFlag=0;
            R->trabajando = (char*)calloc(strlen(R->Antecedente)+1,sizeof(char)+1);
            strncpy(R->trabajando,R->Antecedente,strlen(R->Antecedente)+1);
        }else if(symbcmp(R->AntecedenteOp,R->ConsecuenteOp)==1){
            /*Si el antecedente tiene mayor jerarquía se trabaja con el*/
            R->flag='A';
            R->nFlag=0;
            R->trabajando = (char*)calloc(strlen(R->Antecedente)+1,sizeof(char)+1);
            strncpy(R->trabajando,R->Antecedente,strlen(R->Antecedente)+1);
        }else{
            /*Si el consecuente tiene mayor jerarquía se trabaja con el*/
            R->flag='C';
            R->nFlag=1;
            R->trabajando = (char*)calloc(strlen(R->Consecuente)+1,sizeof(char)+1);
            strncpy(R->trabajando,R->Consecuente,strlen(R->Consecuente)+1);
        }
    /*3.a.	IDENTIFICAR QUIEN ES EL QUE TIENE MENOS OPERADORES (A o C)*/
    }else if(value==1){
        /*SI A > C, se trabaja con el consecuente*/
        R->flag='C';
        R->nFlag=1;
        R->trabajando = (char*)calloc(strlen(R->Consecuente)+1,sizeof(char)+1);
        strncpy(R->trabajando,R->Consecuente,strlen(R->Consecuente)+1);
    }else{
        /*SI A < C, se trabaja con el antecedente*/
        R->flag='A';
        R->nFlag=0;
        R->trabajando = (char*)calloc(strlen(R->Antecedente)+1,sizeof(char)+1);
        strncpy(R->trabajando,R->Antecedente,strlen(R->Antecedente)+1);
    }
    //mostrarInfoRazonamiento(R);


    //AQUI ES DONDE SE APLICAN LAS REGLAS
    //4. TRABAJAR CON EL QUE TENGA MENOS OPERADORES (A o C) O EL DE MAYOR JERARQUIA. CONTADOR=0
    int contador = 0;
    while(contador!=2){
		//printf("TRABAJANDO INICIANDO EL WHILE: %s\n",R->trabajando);
        Array = split(R->trabajando,","); //Se separan por coma
        //Si existe una hipotesis con quien trabajar...
        if (Array[i]!=NULL){
            /*SI hay operador*/
            //printf("[3] Trabajando con %s\n",R->trabajando);
            //printf("ARRAY[i]: %s\n",Array[i]);
            if((R->opTrabajando=getOperadorTrabajar(Array[i]))!='-'){
                printf("\n\n[REGLA] Se aplicara la regla %c del %s en \"%s\"\n\n",R->opTrabajando,flag[R->nFlag],R->trabajando);
                ANTE_CONSE = aplicarRegla(R->opTrabajando,R->flag,R->Antecedente,R->Consecuente,primero,ultimo);
                printf("\n[*] SE APLICO LA REGLA CORRECTAMENTE\n");
                //i++; //Eliminar esta operacion
                /*Cambiar a la cadena con quien se trabaja*/
                //return 0;
                //memset(R->trabajando,'\0',strlen(R->trabajando));
                //COPIAR EL NUEVO ANTECEDENTE Y CONSECUENTE EN LAS CADENAS CORRESPONDIENTES
                R->Antecedente = (char*)calloc(strlen(ANTE_CONSE[0])+1,sizeof(char));
                R->Consecuente = (char*)calloc(strlen(ANTE_CONSE[1])+1,sizeof(char));
                strncat(R->Antecedente,ANTE_CONSE[0],strlen(ANTE_CONSE[0])+1);
                strncat(R->Consecuente,ANTE_CONSE[1],strlen(ANTE_CONSE[1])+1);

                if(R->flag=='A'){
                    R->trabajando = (char*)calloc(strlen(ANTE_CONSE[0])+1,sizeof(char));
                    strncat(R->trabajando,ANTE_CONSE[0],strlen(ANTE_CONSE[0])+1);
                }else{
                    R->trabajando = (char*)calloc(strlen(ANTE_CONSE[1])+1,sizeof(char));
                    strncat(R->trabajando,ANTE_CONSE[1],strlen(ANTE_CONSE[1])+1);
                }
                contador=0;
                i=0;
                //Mostramos el razonaiento modificado
                mostrarRazonamiento(R->Antecedente,R->Consecuente);
            }
            /*Si NO HAY OPERADOR*/
            else{
                i++;
                //printf("VALOR DE i: %d\n",i);
            }
        }else{
            /*Si no hay hipotesis con quien trabajar*/
            contador++;
            /*Cambiar a bandera contraria*/
            if(R->nFlag==0){
                //printf("[!] SE ANALIZARA CONSECUENTE\n");
                R->nFlag=1;
                R->flag='C';
                R->trabajando = (char*)calloc(strlen(R->Consecuente)+1,sizeof(char));
                strncat(R->trabajando,R->Consecuente,strlen(R->Consecuente)+1);
            }else{
                //printf("[!] SE ANALIZARA ANTECEDENTE\n");
                R->nFlag=0;
                R->flag='A';
                R->trabajando = (char*)calloc(strlen(R->Antecedente)+1,sizeof(char));
                strncat(R->trabajando,R->Antecedente,strlen(R->Antecedente)+1);
            }
            i=0;
        }
	}

	/*PASO 5: verificar que exista por lo menos una vez un _____ en ambos lados de la expresion*/
    if(contador==2){
        /*Verificar que exista un operando repetido...*/
        printf("[*] Verificando la validez del razonamiento...\n");
        valido = esValido(R->Antecedente,R->Consecuente);
        if(valido==1){
            printf("[VALIDO] El razonamiento es valido\n\n");
            mostrarRazonamiento(R->Antecedente,R->Consecuente);
            return 1;
        }else{
            printf("[INVALIDO] El razonamiento es invalido\n\n");
            mostrarRazonamiento(R->Antecedente,R->Consecuente);
            return 0;
        }
    }
    return valido;
}
