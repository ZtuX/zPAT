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

void consola(){
    printf("(PAT) ");
}

void mostrarAyuda(){
    printf("- - - - - - - - - - - - -\n");
    printf("\n[AYUDA] Prueba automatica de Teoremas (PAT)\n");
    printf("Para ingresar un razonamiento es necesario hacer uso de la simbología\n");
    printf("establecida:\n");
    simbologia();
    printf("\nPor ejemplo si se requiere ingresar la siguiente expresion:\n");
    printf("\ta^b->c => 7(a^b),c <-> f\n");
    printf("Se tendria que hacer de la siguiente manera:\n");
    printf("\ta^b>c = ~(a^b),c&f\n");
    printf("- - - - - - - - - - - - -\n");
    printf("[COMANDOS] Comandos del PAT\n");
    printf("* \"salir\" o \"s\"\t-> Salir del programa\n");
    printf("* \"ayuda\" o \"h\"\t-> Muestra la ayuda\n");
}
