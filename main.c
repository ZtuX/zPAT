#include "functions.h" //FUNCIONES PARA LECTURA DE CADENAS
#include "queue.h"     //COlA
#include "pat.h"

void menu(){
    printf("\n");
    printf("\tPrueba Automatica de Teoremas (PAT)\n\n");
    printf("Simbologia:\n");
    printf("\t = \t Implicacion Tautologica\t => \n");
    printf("\t > \t Implicacion\t -> \n");
    printf("\t ^ \t Conjuncion\t ^ \n");
    printf("\t v \t Disyuncion\t v \n");
    printf("\t ~ \t Negado\t \n");
    printf("\t & \t Bicondicional\t <=> \n");
    printf("\n\nIntrduce el razonamiento a verificar\n> ");
}

int main(){
    char * razonamiento = NULL;
    //PILA DONDE SE ALMACENARÁN LAS OPERACIONES A RESOLVER
    pNode primero = NULL, ultimo=NULL;

    int validez, invalidos=0, validos=0, total=0;
    char * razonamientoEnCola; //Variable que saca un razonamiento de la cola
    char ** rCola; //Mostrara el razonamiento que esta en la cola
    //MENU
    menu();

    //INGRESAR LA CADENA
    razonamiento = readString();

    //SEPARAMOS EN ANTECEDENTE Y CONSECUENTE EL RAZONAMIENTO AUXILIAR PARA
    //MOSTRARLO EN PANTALLA AL FINAL
    char ** rAux = split(razonamiento,"=");

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
    return 0;
}
