#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

#define TAM_INICIAL 50
#define FACTOR_REDIMENSION 2
#define MULTIPLICADOR 4

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

bool redimensionar(pila_t* pila, size_t nuevo_tam){
	void* datos_nuevos;
	if(nuevo_tam < TAM_INICIAL)	nuevo_tam = TAM_INICIAL;
	datos_nuevos = realloc(pila->datos, nuevo_tam * sizeof(pila_t));
	if(!datos_nuevos) return false;
	pila->datos = datos_nuevos;
	pila->capacidad = nuevo_tam; 
	return true;
}
pila_t* pila_crear(void){
	pila_t* pila = malloc(sizeof(pila_t));
	if(!pila) return NULL;
	pila->cantidad = 0;
	pila->capacidad = TAM_INICIAL;
	pila->datos = malloc(TAM_INICIAL * sizeof(void*));
	if(!pila->datos){
		free(pila);
		return NULL;
	}
	return pila;
}

void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
	return (pila->cantidad == 0);
}

bool pila_apilar(pila_t *pila, void* valor){
	if(pila->cantidad == pila->capacidad){
		if(!redimensionar(pila, pila->capacidad * FACTOR_REDIMENSION)) return false;
	}
	pila->datos[pila->cantidad] = valor;
	pila->cantidad ++;
	return true;
}
void* pila_ver_tope(const pila_t *pila){
	if(pila_esta_vacia(pila)) return NULL;
	return pila->datos[pila->cantidad-1];
}
void* pila_desapilar(pila_t *pila){
	if(pila_esta_vacia(pila)) return NULL;
	pila->cantidad --;
	if((pila->cantidad*MULTIPLICADOR <= pila->capacidad) && (pila->capacidad > TAM_INICIAL)){
		redimensionar(pila, pila->capacidad / FACTOR_REDIMENSION);
	}
	return pila->datos[pila->cantidad];
}