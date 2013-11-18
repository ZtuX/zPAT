#include "functions.h" //FUNCIONES PARA LECTURA DE CADENAS
#include "queue.h"     //COlA
#include "pat.h"
#include "mensajes.h"

int main(){
    char * razonamiento = NULL;
    //PILA DONDE SE ALMACENARÁN LAS OPERACIONES A RESOLVER
    pNode primero = NULL, ultimo=NULL;
    int vFlag = 1; //Bandera que verifica si un razonamiento es valido o no
    int validez, invalidos=0, validos=0, total=0, Bool=1;
    int cuenta=0; //
    char * razonamientoEnCola; //Variable que saca un razonamiento de la cola
    char ** rCola; //Mostrara el razonamiento que esta en la cola
    char * rInvalido = NULL, **rInvalidoAux=NULL; //Para mostrar el ultimo razonamiento invalido

    //VARIABLE QUE SEPARAMOS EN ANTECEDENTE Y CONSECUENTE EL RAZONAMIENTO AUXILIAR PARA
    //MOSTRARLO EN PANTALLA AL FINAL
    char ** rAux;

    //Variables para la verificacion de la cadena:
    char * aParentesis=NULL;
    int parentesisValidos=0, variablesValidas=0;

    printf("==================================================\n");
    printf("\tPrueba Automatica de Teoremas (PAT)\n");
    printf("==================================================\n");
    simbologia();
    printf("Para mostrar la ayuda escriba el comando \"a\" o \"ayuda\"\n");
    printf("\nIntroduce el razonamiento a verificar:\n");

    while(Bool==1){
        //MENU
        consola(cuenta);
        //INGRESAR LA CADENA
        razonamiento = readString();
        rAux = split(razonamiento,"=");
        //Si es un comando
        if(esComando(razonamiento)==1){
            if(strncmp("s",razonamiento,1)==0 || strncmp("salir",razonamiento,5)==0){
                //printf("[-] Saliendo del programa\n");
                Bool = 0;
            }
            else if(strncmp("a",razonamiento,1)==0 || strncmp("ayuda",razonamiento,5)==0){
                mostrarAyuda();
            }
            else if(strncmp("i",razonamiento,1)==0 || strncmp("invalido",razonamiento,8)==0){
                if(rInvalido!=NULL){
                    rInvalidoAux = split(rInvalido,"=");
                    printf("[+] Ultimo razonamiento invalido\n");
                    mostrarRazonamiento(rInvalidoAux[0],rInvalidoAux[1]);
                }else{
                    printf("[!] No existe algun razonamiento invalido\n");
                }
            }
            else if(strncmp("l",razonamiento,1)==0 || strncmp("limpiar",razonamiento,7)==0){
                system("clear");
            }
        }
        else if(stringArraySize(rAux)<2){
                printf("[Error] Falta el operador '=>'\n");
        }else if (stringArraySize(rAux)>2){
            printf("[Error] El operador '=>' encontrado mas de una vez\n");
        }
        else{
            //Verificamos la cadena (Parentesis)
            aParentesis = obtenerParentesis(razonamiento);
            parentesisValidos = verificaParentesis(aParentesis);
            if(parentesisValidos==0){
                printf("[Error] Razonamiento no valido: Parentesis no validos\n");
            }
            variablesValidas = verificaVariables(razonamiento);
            if(variablesValidas==0){
                printf("[Error] Razonamiento no valido: Falta algun operador\n");
            }
            //Si no hay errores entonces hace el procedimiento
            if(parentesisValidos==1 && variablesValidas==1){
                //AGREGAMOS A LA COLA EL RAZONAIENTO INGRESADO
                add(&primero,&ultimo,razonamiento);
                //LEEMOS EL RAZONAMIENTO INGRESADO DE LA COLA
                razonamientoEnCola = read(&primero,&ultimo);

                //MIENTRAS QUE EXISTAN RAZONAMIENTOS:
                do{
                    validez = PAT(razonamientoEnCola,&primero,&ultimo);
                    if(validez!=0){
                        //Mientras sea valido el razonamiento
                        razonamientoEnCola = read(&primero,&ultimo);
                        if(razonamientoEnCola!=NULL){
                            rCola = split(razonamientoEnCola,"=");
                            printf("\n[+] Analizando el siguiente razonamiento en espera: %s => %s \n",rCola[0],rCola[1]);
                        }
                        vFlag = 1;
                    }else{
                        //Si existe algun razonamiento invalido lo copiamos a rInvalido
                        rInvalido = (char*)calloc(strlen(razonamientoEnCola)+1,sizeof(char));
                        strncpy(rInvalido,razonamientoEnCola,strlen(razonamientoEnCola)+1);
                        vFlag = 0;
                        break;
                    }
                }while(razonamientoEnCola!=NULL);
                if (vFlag == 1){
                    printf("\n[VALIDO] El Razonamiento : %s => %s es valido\n\n",rAux[0],rAux[1]);
                }else{
                    printf("\n[INVALIDO] El Razonamiento : %s => %s es invalido\n\n",rAux[0],rAux[1]);
                }
                //VACIAMOS LA COLA
                primero=ultimo=NULL;
            }
        }
        cuenta++;
    }
    return 0;
}
