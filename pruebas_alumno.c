#include "testing.h"
#include "lista.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "pila.h"

#define VALOR_PRUEBA_1 3
#define VALOR_PRUEBA_2 5
#define VALOR_PRUEBA_3 6
#define VALOR_PRUEBA_4 8
#define VALOR_PRUEBA_5 11
#define VALOR_PRUEBA_6 1
#define VALOR_PRUEBA_7 2
#define VALOR_PRUEBA_8 3
#define VALOR_INICIAL_DE_PRUEBA_VOLUMEN 10
#define VALOR_INSERTO_MUCHO_1 5000
#define VALOR_INSERTO_MUCHO_2 5000
#define VALOR_BORRO_MUCHO 10000
#define VALOR_DE_PRUEBA_INTERNO 1
#define FACTOR_NEUTRO_PRODUCTO 1
#define VALOR_VOLUMEN 5000

void destruir_lista_wrapper(void* pila){
	pila_destruir((pila_t*)pila);
}

int* crear_valor_prueba(int valor){
	int* dato = malloc(sizeof(int));
	*dato = valor;
	return dato;
}
void pruebas_lista_vacia(){
	printf("PRUEBAS LISTA VACIA\n");
	//creo una lista
	lista_t* lista = lista_crear();
	print_test("puntero valido", lista != NULL);
	print_test("El primero de la lista vacia es NULL", lista_ver_primero(lista) == NULL);
	print_test("El ultimo de la lista vacia es NULL", lista_ver_ultimo(lista) == NULL);
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	print_test("El largo es 0", lista_largo(lista) == 0);
	lista_destruir(lista, NULL);
}

void pruebas_lista_con_un_elemento(){
	printf("PRUEBAS LISTA CON 1 ELEMENTO\n");
	bool inserto;
	void* borrado;
	int valor_a_probar = VALOR_PRUEBA_1;
	int* valor = crear_valor_prueba(valor_a_probar);
	lista_t* lista = lista_crear();
	print_test("puntero valido", lista != NULL);
	inserto = lista_insertar_primero(lista, valor);
	print_test("inserto bien", inserto);
	print_test("El largo es 1", lista_largo(lista) == 1);
	print_test("lista no esta vacia", !lista_esta_vacia(lista));
	print_test("El primero de la lista es el valor que inserte", lista_ver_primero(lista) == valor);
	print_test("El ultimo de la lista es el valor que inserte", lista_ver_ultimo(lista) == valor);
	borrado = lista_borrar_primero(lista);
	free(valor);
	print_test("lista_esta_vacia", lista_esta_vacia(lista));
	print_test("Borro al principio correctamente", borrado == valor);
	lista_destruir(lista, free);
}
void pruebas_lista_con_dos_elementos(){
	printf("PRUEBAS LISTA CON 2 ELEMENTOS\n");
	//con 2 elementos, borro solo 1 y destruyo
	bool inserto;
	void* borrado;
	int valor_a_probar_1 = VALOR_PRUEBA_2;
	int valor_a_probar_2 = VALOR_PRUEBA_3;
	int* valor_1 = crear_valor_prueba(valor_a_probar_1);
	int* valor_2 = crear_valor_prueba(valor_a_probar_2);
	lista_t* lista = lista_crear();
	inserto = lista_insertar_primero(lista, valor_1);
	inserto = lista_insertar_ultimo(lista, valor_2);
	print_test("inserto bien", inserto);
	print_test("El largo es 2", lista_largo(lista) == 2);
	print_test("lista no esta vacia", !lista_esta_vacia(lista));
	print_test("El primero de la lista es el valor que inserte", lista_ver_primero(lista) == valor_1);
	print_test("El ultimo de la lista es el valor que inserte", lista_ver_ultimo(lista) == valor_2);
	borrado = lista_borrar_primero(lista);
	free(valor_1);
	print_test("lista no esta vacia", !lista_esta_vacia(lista));
	print_test("Borro al principio correctamente", borrado == valor_1);
	lista_destruir(lista, free);
}
void pruebas_insertando_null(){
	printf("PRUEBAS INSERTANDO NULL\n");
	void* valor = NULL;
	lista_t* lista = lista_crear();
	print_test("puntero valido", lista != NULL);
	print_test("El primero de la lista vacia es NULL", lista_ver_primero(lista) == NULL);
	print_test("El ultimo de la lista vacia es NULL", lista_ver_ultimo(lista) == NULL);
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	print_test("El largo es 0", lista_largo(lista) == 0);
	
	for(int i = 0; i < 15; i++) lista_insertar_ultimo(lista, valor);
	print_test("El primero de la lista es NULL", lista_ver_primero(lista) == NULL);
	print_test("El ultimo de la lista es NULL", lista_ver_ultimo(lista) == NULL);
	print_test("La lista tiene elementos", !lista_esta_vacia(lista));
	print_test("El largo de la lista es la cantidad de veces que inserte", lista_largo(lista) == 15);

	for(int i = 0; i < 15; i++) lista_insertar_primero(lista, valor);
	print_test("La lista tiene elementos", !lista_esta_vacia(lista));
	print_test("El primero de la lista es NULL", lista_ver_primero(lista) == NULL);
	print_test("El ultimo de la lista es NULL", lista_ver_ultimo(lista) == NULL);
	print_test("El largo de la lista es la cantidad de veces que inserte mas el largo anterior", lista_largo(lista) == 30);

	for(int i = 0; i < 20; i ++) lista_borrar_primero(lista);
	print_test("La lista tiene elementos", !lista_esta_vacia(lista));
	print_test("El largo de la lista es la cantidad de veces que inserte menos las que borre", lista_largo(lista) == 10);
	for(int i = 0; i < 10; i ++){
		void* borrado = lista_borrar_primero(lista);
		if(borrado != valor){
			print_test("se borro lo que se inserto", borrado == valor);
		}
	}
	print_test("La lista no tiene elementos", lista_esta_vacia(lista));
	print_test("El largo de la lista es 0", lista_largo(lista) == 0);
	lista_destruir(lista, free);
}


void pruebas_destruccion_insertando_colas(){
	//Pruebo insertar ultimo y destruir(sin borrar) 
	int valor_a_probar = VALOR_PRUEBA_1;
	int* valor = crear_valor_prueba(valor_a_probar);
	lista_t* lista = lista_crear();
	pila_t* pila_1 = pila_crear();
	pila_t* pila_2 = pila_crear();
	pila_apilar(pila_1, valor);
	lista_insertar_ultimo(lista, pila_1);
	lista_insertar_ultimo(lista, pila_2);
	lista_destruir(lista, destruir_lista_wrapper);
	print_test("Lista destruida correctamente", lista);
	free(valor);
}

void pruebas_volumen_lista(){
	printf("PRUEBAS VOLUMEN\n");
	lista_t* lista = lista_crear();

	bool ok = true;
	int a_insertar_ultimo[VALOR_VOLUMEN];
	for (int i = 0; i< VALOR_VOLUMEN; i++) a_insertar_ultimo[i] = i;
	for (int i = 0; i< VALOR_VOLUMEN; i++){
		ok = ok && lista_insertar_ultimo(lista, &a_insertar_ultimo[i]);
	}
	int* primero_lista = lista_ver_primero(lista);
	int* ultimo_lista = lista_ver_ultimo(lista);
	ok = ok && (*primero_lista == 0);
	ok = ok && (*ultimo_lista == VALOR_VOLUMEN-1);
	print_test("Se inserta correctamente al principio", ok);
	print_test("La lista no esta vacia", !lista_esta_vacia(lista));
	print_test("El largo es la cantidad de veces que inserte", lista_largo(lista) == VALOR_VOLUMEN);

	ok = true;
	int a_insertar_primero[VALOR_VOLUMEN];
	printf("LLEGO\n");
	int j = VALOR_VOLUMEN;
	for (int i = 0; i< VALOR_VOLUMEN; i++,j++) a_insertar_primero[i] = j;
	j = VALOR_VOLUMEN;
	for (int i = 0; i< VALOR_VOLUMEN; i++){
		ok = ok && lista_insertar_primero(lista, &a_insertar_primero[i]);
	}
	primero_lista = lista_ver_primero(lista);
	int* ultimo_lista_pos_insertar = lista_ver_ultimo(lista);
	ok = ok && (*primero_lista == (VALOR_VOLUMEN*2)-1);
	ok = ok && (*ultimo_lista == *ultimo_lista_pos_insertar);
	print_test("Se inserta correctamente al principio y al final", ok);
	print_test("La lista no esta vacia", !lista_esta_vacia(lista));
	print_test("El largo es la cantidad de veces que inserte", lista_largo(lista) == VALOR_VOLUMEN*2);

	for (int i = 0; i< VALOR_VOLUMEN*2; i++){
		ok = ok && (lista_ver_primero(lista) == lista_borrar_primero(lista));  
	}
	print_test("Se cumple la invariante de la lista", ok);
	print_test("No se puede borrar más", !lista_borrar_primero(lista));
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	print_test("La lista no tiene elementos", lista_largo(lista) == 0);
	print_test("El primero de la lista es NULL", (!lista_ver_primero(lista)));
	print_test("El ultimo de la lista es NULL", (!lista_ver_ultimo(lista)));

	if(lista_esta_vacia(lista))	lista_destruir(lista, NULL);
	else lista_destruir(lista, free);
}

void pruebas_borrar_iter_ext(lista_t* lista, lista_iter_t* iter_A, lista_iter_t* iter_B){
	printf("-------------Pruebas borrar ext----------");
	//borro y destruyo la lista con iter ext
	lista_iter_t* iter_C = lista_iter_crear(lista);
	if(lista_esta_vacia(lista)) lista_destruir(lista, NULL);
	else{
		while(!lista_esta_vacia(lista)){
			if(lista_iter_al_final(iter_A) && (lista_iter_al_final(iter_B))){
				void* actual_C = lista_iter_ver_actual(iter_C);
				void* dato_a_destruir_C = lista_iter_borrar(iter_C);
				if(lista_ver_primero(lista) != lista_iter_ver_actual(iter_C))
					print_test("el primero es el actual", lista_ver_primero(lista) == lista_iter_ver_actual(iter_C));
				free(dato_a_destruir_C);
				if(actual_C != dato_a_destruir_C) print_test("borro el apuntado", actual_C == dato_a_destruir_C);
			}
			else if((!lista_iter_al_final(iter_A)) && (!lista_iter_al_final(iter_B))){
				lista_iter_avanzar(iter_A);
				lista_iter_avanzar(iter_B);
			}
			else{
				if(!lista_iter_al_final(iter_A)) lista_iter_avanzar(iter_B);
				if(!lista_iter_al_final(iter_B)) lista_iter_avanzar(iter_A);
			}
		}
		lista_iter_destruir(iter_A);
		lista_iter_destruir(iter_B);
		lista_iter_destruir(iter_C);
		print_test("La lista esta vacia", lista_esta_vacia(lista));
		lista_destruir(lista, free);
	}
}
void pruebas_iterador_ext(){
	printf("PRUEBAS ITERADOR EXTERNO\n");

	lista_t* lista_1 = lista_crear();
	print_test("puntero valido lista", lista_1 != NULL);
	lista_iter_t* iter_A = lista_iter_crear(lista_1);
	print_test("puntero valido iterador ext", iter_A != NULL);
	print_test("La lista esta vacia", lista_esta_vacia(lista_1));
	print_test("el iterador ext no apunta a ninguna posicion de la lista", lista_iter_ver_actual(iter_A) == NULL);
	print_test("el iterador no pudo avanzar, apunta a null", !lista_iter_avanzar(iter_A));

	int valor_1 = VALOR_PRUEBA_4;
	int* dato_a_insertar_1 = crear_valor_prueba(valor_1);
	print_test("pudo insertar", lista_iter_insertar(iter_A, dato_a_insertar_1));
	print_test("El primero de la lista es el que inserte", (lista_ver_primero(lista_1) == dato_a_insertar_1));
	print_test("El actual NO apunta a null, sino al unico dato que inserte\n", (dato_a_insertar_1 == lista_iter_ver_actual(iter_A)));
	print_test("La lista no esta vacia", !lista_esta_vacia(lista_1));

	int valor_2 = VALOR_PRUEBA_5;
	int* dato_a_insertar_2 = crear_valor_prueba(valor_2);
	print_test("pudo insertar", lista_iter_insertar(iter_A, dato_a_insertar_2));
	print_test("El primero de la lista es el que inserte recien", lista_ver_primero(lista_1) == dato_a_insertar_2);
	print_test("El ultimo de la lista es el que inserte al principio", lista_ver_ultimo(lista_1) == dato_a_insertar_1);
	print_test("El actual NO apunta a null, sino al primero de la lista\n", (dato_a_insertar_2 == lista_iter_ver_actual(iter_A)));

	lista_iter_t* iter_B = lista_iter_crear(lista_1);
	print_test("puntero valido iterador ext auxiliar", iter_B != NULL);
	pruebas_borrar_iter_ext(lista_1, iter_A, iter_B);

	lista_t* lista_2 = lista_crear();
	int dato_1 = VALOR_PRUEBA_6;
	int* dato_a_insertar_A = crear_valor_prueba(dato_1);
	print_test("pudo insertar", lista_insertar_ultimo(lista_2, dato_a_insertar_A));
	printf("el ultimo es %d", dato_1);
	int dato_2 = VALOR_PRUEBA_7;
	int* dato_a_insertar_B = crear_valor_prueba(dato_2);
	print_test("pudo insertar", lista_insertar_ultimo(lista_2, dato_a_insertar_B));
	printf("el ultimo es %d", dato_2);
	int dato_3 = VALOR_PRUEBA_8;
	int* dato_a_insertar_C = crear_valor_prueba(dato_3);
	print_test("pudo insertar", lista_insertar_ultimo(lista_2, dato_a_insertar_C));
	printf("el ultimo es %d", dato_3);
	
	lista_iter_t* iter_C = lista_iter_crear(lista_2);
	print_test("iter actual es dato_1", lista_iter_ver_actual(iter_C) == dato_a_insertar_A);
	print_test("avanzar es true", lista_iter_avanzar(iter_C));
	print_test("iter actual es dato_2", lista_iter_ver_actual(iter_C) == dato_a_insertar_B);
	print_test("el borrado es dato_2", lista_iter_borrar(iter_C) == dato_a_insertar_B);
	free(dato_a_insertar_B);
	print_test("iter actual es dato_3", lista_iter_ver_actual(iter_C) == dato_a_insertar_C);
	print_test("el borrado es dato_3", lista_iter_borrar(iter_C) == dato_a_insertar_C);
	free(dato_a_insertar_C);
	print_test("el largo es 1", lista_largo(lista_2) == 1);
	print_test("avanzar es false", !lista_iter_avanzar(iter_C));
	print_test("borrar es null", !lista_iter_borrar(iter_C));
	print_test("iter actual es null", !lista_iter_ver_actual(iter_C));
	
	lista_iter_t* iter_D = lista_iter_crear(lista_2);
	print_test("iter actual es dato 1", lista_iter_ver_actual(iter_D) == dato_a_insertar_A);
	print_test("avanzar es true", lista_iter_avanzar(iter_D));
	print_test("iter actual es null", !lista_iter_ver_actual(iter_D));
	pruebas_borrar_iter_ext(lista_2, iter_C, iter_D);
}

void pruebas_volumen_iter_ext(){
	printf("PRUEBAS VOLUMEN ITERADOR EXTERNO\n");
	lista_t* lista_1 = lista_crear();
	print_test("puntero valido lista", lista_1 != NULL);
	lista_iter_t* iter_A = lista_iter_crear(lista_1);
	print_test("puntero valido iterador ext", iter_A != NULL);

	printf("------------PRUEBAS INSERTAR---------------\n");
	int valor = VALOR_INICIAL_DE_PRUEBA_VOLUMEN;
	bool inserto;
	int elementos = 0;
	for(int i=0; i < VALOR_INSERTO_MUCHO_1 + VALOR_INSERTO_MUCHO_2; i++){
		int* dato_a_insertar = crear_valor_prueba(valor);
		inserto = lista_iter_insertar(iter_A, dato_a_insertar);
		if(!inserto) print_test("pudo insertar", inserto);
		valor ++;
		elementos ++;
	}
	print_test("El primero de la lista es el ultimo valor que inserte", (*(int*)lista_ver_primero(lista_1) == valor-1));
	print_test("El ultimo de la lista es el que inserte inicialmente", (*(int*)lista_ver_ultimo(lista_1) == VALOR_INICIAL_DE_PRUEBA_VOLUMEN));
	print_test("El largo es la cantidad de veces que inserte", lista_largo(lista_1) == elementos);
	print_test("El actual NO esta en null, es lo ultimo que inserte\n",(lista_ver_primero(lista_1) == lista_iter_ver_actual(iter_A)));

	lista_iter_t* iter_B = lista_iter_crear(lista_1);
	print_test("puntero valido iterador ext auxiliar", iter_B != NULL);
	print_test("El actual esta en el primero\n", (lista_ver_primero(lista_1) == lista_iter_ver_actual(iter_A)));
	print_test("El actual esta en el primero\n", (lista_ver_primero(lista_1) == lista_iter_ver_actual(iter_B)));

	pruebas_borrar_iter_ext(lista_1, iter_A, iter_B);
}

bool multpilicacion (void* dato, void* extra){
	int aux = *(int*)dato;
	*(int*)extra *= aux;
	return (*(int*)extra < 300);
}

void pruebas_iterador_int(){                                    
	lista_t* lista = lista_crear();
	int valor = VALOR_DE_PRUEBA_INTERNO;
	int producto = FACTOR_NEUTRO_PRODUCTO;
	for (int i = 0; i < 5; i++){
		int* dato_a_insertar = crear_valor_prueba(valor);
		lista_insertar_ultimo(lista, dato_a_insertar);
		if(*dato_a_insertar == 0)	producto = 0;
		valor ++;
	}
	lista_iterar(lista, multpilicacion, &producto);
	print_test("se pudo multiplicar correctamente",  producto == 120);
	lista_destruir(lista, free);
}

void pruebas_lista_alumno(){
	pruebas_lista_vacia();
	pruebas_lista_con_un_elemento();
	pruebas_lista_con_dos_elementos();
	pruebas_insertando_null();
	pruebas_destruccion_insertando_colas();
	pruebas_volumen_lista();
	pruebas_iterador_ext();
	pruebas_volumen_iter_ext();
	pruebas_iterador_int();
}