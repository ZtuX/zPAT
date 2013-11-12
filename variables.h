/*variables.h

[Descripcion]: Contiene diferentes tipos de variables para usar en
todo el programa

*/

//INICIO VARIABLES GLOBALES
struct Ante_Conse {
    char * Antecedente;
    char * Consecuente;
    char AntecedenteOp; /*Contiene el operador mas significativo*/
    char ConsecuenteOp; /*Contiene el operador mas significativo*/
    char flag;          /*Indica con quien se esta trabajando (A o C)*/
    int nFlag;          /*Indica el numero que representa con quien se trabaja (A=0 o C=1)*/
    int A;              /*Contador de operadores en el antecedente*/
    int C;              /*Contador de operadores en el consecuente*/
    char opTrabajando;  /*Indica el operador con quien se trabaja*/
    char * trabajando;  /*Contiene la cadena con la que se esta trabajando*/
};
typedef struct Ante_Conse *RAZONAMIENTO;

char operadores[7] = {'=','>','^','v','~',',','&'};
char operar[6] = {'>','^','v','~','&'};
char ops[6] = {'~','^','v','>','&','-'}; // EL operador - es una marca de operador invalido
int opsValor[6] = {4,3,2,1,0,-1};
const char * flag[2] = {"Antecedente","Consecuente"}; /*A=0 y C=1*/
//FIN VARIABLES GLOBALES
