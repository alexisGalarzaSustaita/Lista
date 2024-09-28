#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Definición de la estructura y typedef
typedef struct nodo {
    char cadena[100];
    struct nodo *liga;
} *LISTA;

// Prototipos de funciones
void iniLista(LISTA *cab);
int creaNodo(LISTA *nuevo, char cadena[]);
void capLista(LISTA *cab);
int insIni(LISTA *cab, char cadena[]);
void muestraLstIt(LISTA cab);
int elimIni(LISTA *cab);
int elimFinalIt(LISTA *cab);
void repetir(LISTA *cab);

int main(int argc, char** argv) {
    LISTA lista;

    iniLista(&lista);
    capLista(&lista);
    muestraLstIt(lista);

    return 0;
}

/* Inicializa la cabecera */
void iniLista(LISTA *cab){
    *cab = NULL;
}

/* Crea nodo */
int creaNodo(LISTA *nuevo, char cadena[]){
    int res = 0;

    *nuevo = (LISTA) malloc(sizeof(struct nodo));
    if(*nuevo){
        strcpy((*nuevo)->cadena, cadena); // Copiar cadena al nodo
        (*nuevo)->liga = NULL;
        res = 1;
    }

    return res;
}

/* Captura lista */
void capLista(LISTA *cab){
    char cadena[100];
    char resp = 's';
    int res;

    do {
        printf("Cadena: ");
        gets(cadena);  // Uso de gets (no recomendado, pero solicitado)
        res = insIni(cab, cadena);

        if(res){
            printf("¿Deseas ingresar otra cadena? (s/n): ");
            resp = getchar(); // Leer la respuesta
            while (getchar() != '\n' && !feof(stdin)); // Limpiar el búfer de entrada
        } else {
            printf("Error al insertar la cadena.\n");
            resp = 'n';
        }
    } while(tolower(resp) == 's');
}

/* Inserta al inicio */
int insIni(LISTA *cab, char cadena[]){
    int res;
    LISTA nuevo;
    res = creaNodo(&nuevo, cadena);

    if(res){
        nuevo->liga = *cab;
        *cab = nuevo;
    }

    return res;
}

/* Muestra la lista */
void muestraLstIt(LISTA cab){

    printf("Contenido de la lista:\n");
    while(cab){
        printf("%s, ", cab->cadena);
        cab = cab->liga;
    }
}

/* Elimina dato del inicio */
int elimIni(LISTA *cab){
    int res = 0;
    LISTA aux;

    if(*cab){
        aux = *cab;
        *cab = aux->liga; // Asignar el siguiente nodo
        free(aux);
        res = 1;
    }

    return res;
}

/* Elimina el final de la lista */
int elimFinalIt(LISTA *cab){
    int res = 0;
    LISTA aux, ant;

    if(*cab){
        aux = *cab;
        if(aux->liga == NULL){
            *cab = NULL;  // Solo un nodo
        } else {
            while(aux->liga){
                ant = aux;
                aux = aux->liga;
            }
            ant->liga = NULL;
        }
        free(aux);
        res = 1;
    }

    return res;
}

/* Función para repetir la captura de lista */
void repetir(LISTA *cab){
    char resp = 's';

    do {
        printf("Cadena: ");
        gets((*cab)->cadena);
        printf("¿Otro? (s/n): ");
        resp = getchar();
        while (getchar() != '\n' && !feof(stdin)); // Limpiar el búfer de entrada
    } while(tolower(resp) == 's');
}
