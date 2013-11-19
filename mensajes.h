#define nComandos 10

char * comandos [] = {"ayuda","a","salir","s","invalido","i","limpiar","l","v","version"};

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
    printf("[COMANDOS] Comandos del PAT\n\n");
    printf("|Comando|\t|Tecla rapida|\t|Descripcion|\n");
    printf("salir\t\ts\t\tSalir del programa\n");
    printf("ayuda\t\ta\t\tMuestra la ayuda\n");
    printf("invalido\ti\t\tMuestra el ultimo razonamiento invalido\n");
    printf("limpiar\t\tl\t\tLimpia la pantalla\n");
    printf("version\t\tv\t\tMuestra la version del programa\n");
    printf("- - - - - - - - - - - - -\n");
}

void version(){
    printf("		 ____   _  _____\n"); 
    printf("		|  _ \\ / \\|_   _|\n");
    printf("		| |_) / _ \\ | |\n");
    printf("		|  __/ ___ \\| |\n");  
    printf("		|_| /_/   \\_\\_|\n"); 
    printf("\n");             
    printf("	--=[P]rueba [A]utomatica de [T]eoremas [PAT]\n");
    printf("+---**---==[Version : 1.0.0\n");
    printf("+---**---==[Codename : Genesis\n");
    printf("+---**---==[Desarrollador : Hernandez Alarcon Jesus Alfredo\n");
    printf("	--=[Update Date : [19.11.2013]\n");
    printf("\n");
}
