#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "persona.h"

typedef struct nodo{
    stPersona dato;
    struct nodo * siguiente;
} nodo;

nodo * inicLista();
nodo * crearNodo(stPersona dato);
nodo * agregarAlPrincipio(nodo * lista, nodo * nuevo);
nodo * archivoToLista(nodo * lista, char archivo[]);
void mostrarLista(nodo * lista);
nodo * agregarEnOrdenApellido(nodo * lista, nodo * nuevo);
nodo * archivoToListaOrdenadoXApellido(nodo * lista, char archivo[]);
nodo * agregarEnOrdenEdad(nodo * lista, nodo * nuevo);
nodo * archivoToListaOrdenadoXEdad(nodo * lista, char archivo[]);
nodo * agregarEnOrdenDni(nodo * lista, nodo * nuevo);
nodo * archivoToListaOrdenadoXDni(nodo * lista, char archivo[]);
int buscarLetraEnLista(nodo * lista, char letra);
void archivotoListaParcial(char archivo[], nodo ** lista );
void  agregarEnOrdenApellido2(nodo ** lista, nodo * nuevo );
int sumaEdadesRecursiva(nodo * lista, int dato);
 int buscaMenorRecursuvo(nodo * lista);
 stPersona buscaPersonaMenorRecursivo(nodo * lista);
 void listaToArchivoApellido(nodo * lista, char archivo[], char letra);
 void mostrarArchivo(char archivo[]);
 int cantidadPersonasRecursivo(nodo * lista, int edad);
 float calcularPorcentajeDePersonas(nodo * lista, int edad);


int main()
{
    /*nodo * lista = inicLista();
    lista = archivoToLista(lista, "personas.dat");
    mostrarLista(lista);
    lista = archivoToListaOrdenadoXDni(lista, "personas.dat");
    mostrarLista(lista);
    char letra;
    printf("\n Ingrese una letra para buscarla en la lista: ");
    fflush(stdin);
    scanf("%c",&letra);
    int flag = 0;
    flag =  buscarLetraEnLista(lista,letra);
    printf("\n%i",flag);*/

    nodo * lista = inicLista();
    int edad = 0;
    int suma = 0;
    int menor = 0;
    int cantidad = 0;
    float porcentaje = 0;
    stPersona p;
    archivotoListaParcial("personas.dat", &lista);
    mostrarLista(lista);
    /*printf("\n Ingrese una edad para buscar los mayores: ");
    scanf("%i", &edad);
    suma = sumaEdadesRecursiva(lista, edad);
    printf("El resultado es  : %i",suma);
    menor = buscaMenorRecursuvo(lista);
    printf("\nEl menor de la lista tiene: %i", menor);
    printf("\n El menor es: ");
    p = buscaPersonaMenorRecursivo(lista);
    muestraUnaPersona(p);
    listaToArchivoApellido(lista, "personasA.dat", 'A');
    printf("\n Los que arrancan con a: \n");
    mostrarArchivo("personasA.dat");*/
    cantidad = cantidadPersonasRecursivo(lista, 50);
    printf("\ncantidad:  %i", cantidad);
    porcentaje = calcularPorcentajeDePersonas(lista,50 );
    printf("\n El porcentaje es: %.2f", porcentaje);

    return 0;
}
/*
void mostrarLista(nodo * lista){

    nodo * auxLista = lista;
    while(auxLista != NULL){
        mostrarPersona(auxLista->dato);
        auxLista = auxLista ->siguiente;
    }
}

nodo * agregarAlFinal(nodo * lista, nodo * nuevo){

    if(lista == NULL){

        lista = nuevo;
    }
    else{
        nodo * auxLista = buscarUltimo(lista);
        auxLista->siguiente = nuevo;
    }

    return lista;
}

nodo * buscarUltimo(nodo * lista){

    while(lista->siguiente !=NULL){

        lista = lista->siguiente;
    }

    return lista;
}*/

nodo * inicLista(){
    return NULL;
}

nodo * crearNodo(stPersona dato){
    nodo * nuevo = (nodo * ) malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->siguiente = NULL;
    return nuevo;
}

nodo * agregarAlPrincipio(nodo * lista, nodo * nuevo){
    nuevo->siguiente = lista;
    return nuevo;
}

void mostrarLista(nodo * lista){
    nodo *  aux = lista;
    while(aux != NULL){
        muestraUnaPersona(aux->dato);
        aux = aux->siguiente;
    }
}

nodo * agregarEnOrdenApellido(nodo * lista, nodo * nuevo){
    if(lista ==NULL){
        lista = nuevo;
    }
    else{
        if(strcmp(nuevo->dato.apellido, lista->dato.apellido) < 0){
            lista = agregarAlPrincipio(lista, nuevo);
        }
        else{
            nodo * anterior = lista;
            nodo * sig = lista->siguiente;
            while( sig && strcmp(nuevo->dato.apellido, sig->dato.apellido) > 0){
                anterior = sig;
                sig = sig->siguiente;
            }
            anterior->siguiente = nuevo;
            nuevo->siguiente = sig;
        }
    }
    return lista;
}

nodo * agregarEnOrdenEdad(nodo * lista, nodo * nuevo){
    if(lista == NULL){
        lista = nuevo;
    }
    else{
        if(nuevo->dato.edad <= lista->dato.edad){
            lista = agregarAlPrincipio(lista,nuevo);
        }
        else{
            nodo * anterior = lista;
            nodo * sig = lista->siguiente;
            while(sig && (nuevo->dato.edad > sig->dato.edad)){
                anterior = sig;
                sig = sig->siguiente;
            }
            anterior->siguiente = nuevo;
            nuevo->siguiente = sig;
        }
    }
    return lista;
}

nodo * agregarEnOrdenDni(nodo * lista, nodo * nuevo){
    if(lista == NULL){
        lista = nuevo;
    }
    else{
        if(strcmp(nuevo->dato.dni, lista->dato.dni) < 0){
            lista = agregarAlPrincipio(lista, nuevo);
        }
        else{
            nodo * anterior = lista;
            nodo * sig = lista->siguiente;
            while(sig && strcmp(nuevo->dato.dni,sig->dato.dni) > 0){
                anterior = sig;
                sig = sig->siguiente;
            }
            anterior->siguiente = nuevo;
            nuevo->siguiente = sig;
        }
    }
    return lista;
}

/// 1. Hacer un programa que lea de un archivo datos y los inserte en una lista.

nodo * archivoToLista(nodo * lista, char archivo[]){
    stPersona p;
    FILE * archi = fopen(archivo,"rb");
    if(archi){
        while(fread(&p,sizeof(stPersona), 1, archi) > 0){
            lista = agregarAlPrincipio(lista, crearNodo(p));
        }
        fclose(archi);
    }
    return lista;
}

/// 2. Hacer un programa que lea de un archivo datos y los inserte en una lista en forma ordenada.

nodo * archivoToListaOrdenadoXApellido(nodo * lista, char archivo[]){
    stPersona p;
    FILE * archi = fopen(archivo, "rb");
    if(archi){
        while(fread(&p, sizeof(stPersona), 1, archi) > 0){
            lista = agregarEnOrdenApellido(lista,crearNodo(p));
        }
    fclose(archi);
    }
    return lista;
}

nodo * archivoToListaOrdenadoXEdad(nodo * lista, char archivo[]){
    stPersona p;
    FILE * archi = fopen(archivo,"rb");
    if(archi){
        while(fread(&p,sizeof(stPersona), 1, archi) > 0){
            lista = agregarEnOrdenEdad(lista, crearNodo(p));
        }
    fclose(archi);
    }
    return lista;
}

nodo * archivoToListaOrdenadoXDni(nodo * lista, char archivo[]){
    stPersona p;
    FILE * archi = fopen(archivo, "rb");
    if(archi){
        while(fread(&p,sizeof(stPersona), 1, archi) > 0){
            lista = agregarEnOrdenDni(lista, crearNodo(p));
        }
        fclose(archi);
    }
    return lista;
}

/* 3. Hacer una función que retorne un 1 (uno) o 0 (cero) si existe un determinado elemento en una lista dada.
(considerar caso ordenada y caso desordenada)*/

int buscarLetraEnLista(nodo * lista, char letra){
    int flag = 0;
    if(lista){
        nodo * aux = lista;
        while(flag == 0 && aux->siguiente != NULL){
            if(aux->dato.apellido[0] == letra){
                flag = 1;
            }
            else{
                aux = aux->siguiente;
            }
        }
    }
    else{
        flag = 0;
    }
    return flag;
}

/* 4. Hacer una función que intercale en orden los elementos de dos listas ordenadas generando una nueva lista.
Se deben redireccionar los punteros, no se deben crear nuevos nodos. */

                                                                                                                   /*Parcial*/
/* 1- Copiar los datos de las personas del archivo en una lista simplemente enlazada, insertando sus datos en orden por apellido.
(para realizar este punto deberá hacer la función agregarEnOrdenPorApellido() utilizando puntero doble)*/

void archivotoListaParcial(char archivo[], nodo ** lista ){
    stPersona p;
    FILE * archi = fopen(archivo, "rb");
    if(archi){
        while(fread(&p, sizeof(stPersona), 1, archi) > 0) {
            agregarEnOrdenApellido2(lista, crearNodo(p));
        }
        fclose(archi);
    }
}

void  agregarEnOrdenApellido2(nodo ** lista, nodo * nuevo ){
    if(!(*lista)){
        (*lista) = nuevo;
    }
    else{
        if(strcmp(nuevo->dato.apellido, (*lista)->dato.apellido) < 0){
            (*lista) = agregarAlPrincipio((*lista), nuevo);
        }
        else{
            nodo * anterior = (*lista);
            nodo * sig = (*lista)->siguiente;
            while(sig && strcmp(nuevo->dato.apellido, sig->dato.apellido) > 0){
                anterior = sig;
                sig = sig->siguiente;
            }
            anterior ->siguiente = nuevo;
            nuevo->siguiente = sig;
        }
    }
}

/*2 - Hacer una función recursiva que sume las edades de las personas de la lista que tengan DNI par y sean mayores de edad.
 (Recuerde que el dato DNI es de tipo char[]).*/

 int sumaEdadesRecursiva(nodo * lista, int dato){
    int suma = 0;

    if(lista){
        if(lista->dato.edad > dato && atoi(lista->dato.dni)%2 == 0 ){
            suma = lista->dato.edad + sumaEdadesRecursiva(lista->siguiente, dato);
        }
        else{
            suma = sumaEdadesRecursiva(lista->siguiente, dato);
        }
    }
    return suma;
 }

 /* 3- Hacer una función recursiva que busque la persona de menor edad en la lista y la retorne.*/

 int buscaMenorRecursuvo(nodo * lista){
   int menor;
    printf("\n menor = %i", menor);
    if(lista){

        menor = buscaMenorRecursuvo(lista->siguiente);
        printf("\n menor = %i", menor);
        if(menor > lista->dato.edad ){
            menor = lista->dato.edad;
        }
    }
    return menor;
}


 /* 3- Hacer una función recursiva que busque la persona de menor edad en la lista y la retorne.*/

 stPersona buscaPersonaMenorRecursivo(nodo * lista){
    stPersona p;
    if(lista){
        p = buscaPersonaMenorRecursivo(lista->siguiente);
        if(p.edad > lista->dato.edad){
            p = lista->dato;
        }
    }
    return p;
 }


/* 4- Hacer una función que recorra la lista y copie las personas cuyo apellido comience con una letra recibida por parámetro
a un archivo nuevo. (Recuerde que un string es un arreglo de caracteres).*/

void listaToArchivoApellido(nodo * lista, char archivo[], char letra){
    stPersona p;
    FILE * archi = fopen( archivo ,"ab");
    nodo * aux = lista;
    if(archi){
        while(aux){
            if(aux->dato.apellido[0] == letra){
                    p = aux->dato;
                fwrite(&p, sizeof(stPersona), 1, archi);
                aux = aux->siguiente;
            }
            else{
                aux = aux->siguiente;
            }
        }
        fclose(archi);
    }

}
void mostrarArchivo(char archivo[]){
    stPersona p;
    FILE * archi = fopen(archivo, "rb");
    if(archi){
        while(fread(&p, sizeof(stPersona), 1, archi) > 0){
            muestraUnaPersona(p);
        }
    }
}


/* 5- Hacer una función recursiva que cuente las personas de la lista, mayores a una edad recibida por parámetro.*/

int cantidadPersonasRecursivo(nodo * lista, int edad){
    int cantidad = 0;
    if(lista){
        if(lista->dato.edad > edad){
            cantidad = 1 + cantidadPersonasRecursivo(lista->siguiente, edad);
        }
        else{
            cantidad = cantidadPersonasRecursivo(lista->siguiente, edad);
        }
    }
    return cantidad;
}

/* 6- Hacer una función que calcule el porcentaje de personas mayores a cierta edad con respecto al total de personas de la lista.
 (Para éste cálculo deberá utilizar la función anterior (dos veces enviando distintos parámetros?), piense!!!).*/

 float calcularPorcentajeDePersonas(nodo * lista, int edad){
    int mayores = cantidadPersonasRecursivo(lista, edad);
    int total = cantidadPersonasRecursivo(lista, 0);
    float porcentaje = (mayores *100) / total;

    return porcentaje;
 }






