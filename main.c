#include "functions.h" //FUNCIONES PARA LECTURA DE CADENAS
#include "queue.h"     //COlA
#include "pat.h"
#include "mensajes.h"

int main(){
    char * razonamiento = NULL;
    //PILA DONDE SE ALMACENARÁN LAS OPERACIONES A RESOLVER
    pNode primero = NULL, ultimo=NULL;

    int validez, invalidos=0, validos=0, total=0, Bool=1;
    char * razonamientoEnCola; //Variable que saca un razonamiento de la cola
    char ** rCola; //Mostrara el razonamiento que esta en la cola
    //VARIABLE QUE SEPARAMOS EN ANTECEDENTE Y CONSECUENTE EL RAZONAMIENTO AUXILIAR PARA
    //MOSTRARLO EN PANTALLA AL FINAL
    char ** rAux;
    printf("==================================================\n");
    printf("\tPrueba Automatica de Teoremas (PAT)\n");
    printf("==================================================\n");
    simbologia();
    printf("\n\nIntrduce el razonamiento a verificar:\n");

    while(Bool==1){
        //MENU
        consola();
        //INGRESAR LA CADENA
        razonamiento = readString();
        rAux = split(razonamiento,"=");
        //Comando para salir del programa
        if(strncmp("s",razonamiento,strlen(razonamiento))==0 || strncmp("salir",razonamiento,5)==0){
                printf("[-] Saliendo del programa\n");
                Bool = 0;
        }
        else if(strncmp("h",razonamiento,strlen(razonamiento))==0 || strncmp("ayuda",razonamiento,5)==0){
                mostrarAyuda();
        }
        else if(stringArraySize(rAux)<2){
                printf("[Error] Falta el operador '=>'\n");
        }
        else{
            //AGREGAMOS A LA COLA EL RAZONAIENTO INGRESADO
            add(&primero,&ultimo,razonamiento);
            //LEEMOS EL RAZONAMIENTO INGRESADO DE LA COLA
            razonamientoEnCola = read(&primero,&ultimo);

            //MIENTRAS QUE EXISTAN RAZONAMIENTOS:
            do{
                validez = PAT(razonamientoEnCola,&primero,&ultimo);
                if(validez==0){
                    invalidos++;
                }else if(validez==1){
                    validos++;
                }else{
                    return 0;
                }
                //showQueue(primero,ultimo); //Mostramos la cola
                razonamientoEnCola = read(&primero,&ultimo);
                if(razonamientoEnCola!=NULL){
                    rCola = split(razonamientoEnCola,"=");
                    printf("\n= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
                    printf("[+] Analizando el siguiente razonamiento en espera: %s => %s \n",rCola[0],rCola[1]);
                    printf("= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
                }
            }while(razonamientoEnCola!=NULL);

            total = validos+invalidos;
            if(invalidos==0){
                if (total==1) printf("\n[*] El Razonamiento : %s => %s es valido\n\n",rAux[0],rAux[1]);
                else printf("Todos los razonamientos fueron validos (%d de %d), el razonamiento %s => %s es valido\n",validos,total,rAux[0],rAux[1]);
            }else{
                if(total==1) printf("\n[[*] El Razonamiento : %s => %s es invalido\n\n",rAux[0],rAux[1]);
                else printf("%d de %d razonamientos fueron invalidos, el razonamiento %s => %s es invalido\n",invalidos,total,rAux[0],rAux[1]);
            }
        }
    }
    return 0;
}
