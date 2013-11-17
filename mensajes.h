#define nComandos 6

char * comandos [] = {"ayuda","a","salir","s","invalido","i"};

int esComando(char * comando){
    //regresa un 1 si es un comando, en caso comtrario 0
    int i;
    for(i=0;i<nComandos;i++){
        if(strncmp(comandos[i],comando,strlen(comando))==0){
            return 1;
        }
    }
    return 0;
}

void simbologia(){
    printf("\n");
    printf("Simbologia:\n");
    printf("| = \t| Implicacion T\t| =>\t|\n");
    printf("| > \t| Implicacion\t| ->\t| \n");
    printf("| ^ \t| Conjuncion\t| ^\t| \n");
    printf("| v \t| Disyuncion\t| v\t| \n");
    printf("| ~ \t| Negado\t| 7\t|\n");
    printf("| & \t| Bicondicional\t| <=>\t| \n");
}

void consola(int cuenta){
    printf("($%d PAT) ",cuenta);
}

void mostrarAyuda(){
    printf("- - - - - - - - - - - - -\n");
    printf("\n[AYUDA] Prueba automatica de Teoremas (PAT)\n");
    printf("Para ingresar un razonamiento es necesario hacer uso de la simbología\n");
    printf("establecida:\n");
    simbologia();
    printf("\nPor ejemplo si se quiere ingresar la siguiente expresion:\n");
    printf("\ta^b->c => 7(a^b),c <-> f\n");
    printf("Se tendria que hacer de la siguiente manera:\n");
    printf("\ta^b>c = ~(a^b),c&f\n");
    printf("- - - - - - - - - - - - -\n");
    printf("[COMANDOS] Comandos del PAT\n");
    printf("* \"salir\" o \"s\" -> Salir del programa\n");
    printf("* \"ayuda\" o \"a\" -> Muestra la ayuda\n");
    printf("* \"invalido\" o \"i\" -> Muestra el ultimo razonamiento invalido\n");
}
