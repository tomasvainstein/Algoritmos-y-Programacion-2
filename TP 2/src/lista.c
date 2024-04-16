#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

#define ERROR 0

lista_t *lista_crear()
{
	return calloc(1, sizeof(lista_t));
}

bool lista_vacia(lista_t *lista)
{
	return (lista->cantidad == 0);
}

/*
*	Se reserva memoria para un struct de tipo nodo_t y se inicializan sus campos en NULL o 0 
* correspondientemente. 
* Luego se le asigna un puntero al elemento recibido por parámetro en caso de que este exista.
* Devuelve el nodo en caso de que el nodo haya sido creado exitosamente, o NULL en caso de error.
*
*/

nodo_t *nuevo_nodo(void *elemento)
{
	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));

	if (!nuevo_nodo)
		return NULL;

	nuevo_nodo->elemento = elemento;

	return nuevo_nodo;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista)
		return NULL;

	nodo_t *nodo_a_insertar = nuevo_nodo(elemento);

	if (!nodo_a_insertar)
		return NULL;

	if (lista_vacia(lista))
		lista->nodo_inicio = nodo_a_insertar;
		
	else
		lista->nodo_fin->siguiente = nodo_a_insertar;
	
	lista->nodo_fin = nodo_a_insertar;
	lista->cantidad++;

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (!lista)
		return NULL;

	if (lista->cantidad <= posicion)
		return lista_insertar(lista, elemento);

	nodo_t *nodo_a_insertar = nuevo_nodo(elemento);

	if (!nodo_a_insertar)
			return NULL;

	if (posicion == 0) {
		nodo_a_insertar->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo_a_insertar;

	} else {
		nodo_t *nodo_aux = lista->nodo_inicio;

		for (int i = 0; i < posicion-1; i++)
			nodo_aux = nodo_aux->siguiente;

		nodo_a_insertar->siguiente = nodo_aux->siguiente;
		nodo_aux->siguiente = nodo_a_insertar;
	}
	lista->cantidad++;
	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (lista_vacia(lista) || !lista->nodo_inicio)
		return NULL;

	nodo_t *nodo_a_quitar = lista->nodo_fin;
	void *elemento = lista->nodo_fin->elemento;

	if (lista->cantidad == 1) {
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;

		free(nodo_a_quitar);
	} else {
		nodo_t* nuevo_fin = lista->nodo_inicio;
		int i = 1; 

		while(i < lista->cantidad-1){
			nuevo_fin = nuevo_fin->siguiente;
			i++;
		}
		elemento = nuevo_fin->siguiente->elemento;

		free(nuevo_fin->siguiente);

		nuevo_fin->siguiente = NULL;
		lista->nodo_fin = nuevo_fin;
	}
	lista->cantidad--;
	
	return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista_vacia(lista))
		return NULL;

	if (lista->cantidad <= posicion)
		return lista_quitar(lista);	 
	
	nodo_t *nodo_aux = lista->nodo_inicio;
	void *elemento = lista->nodo_inicio->elemento;
	
	if (posicion == 0) {
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		free(nodo_aux);
	} else {
		for (int i = 0; i < posicion-1; i++)
			nodo_aux = nodo_aux->siguiente;

		nodo_t *nodo_a_quitar = nodo_aux->siguiente;
		nodo_aux->siguiente = nodo_aux->siguiente->siguiente;
		elemento = nodo_a_quitar->elemento;

		free(nodo_a_quitar);
	}
	lista->cantidad--;
	
	return elemento;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista->cantidad <= posicion || lista_vacia(lista)) 
		return NULL;

	nodo_t *nodo_aux = lista->nodo_inicio;

	for (int i = 0; i < posicion; i++)
		nodo_aux = nodo_aux->siguiente;

	return nodo_aux->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (lista_vacia(lista) || !comparador) 
		return NULL;

	nodo_t *nodo_aux = lista->nodo_inicio;

	while(nodo_aux != NULL) {
		if (comparador(nodo_aux->elemento, contexto) == 0)
			return nodo_aux->elemento;
		nodo_aux = nodo_aux->siguiente;		
	}
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if (lista_vacia(lista))
		return NULL;

	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if (lista_vacia(lista))
		return NULL;
	
	return lista->nodo_fin->elemento;
}

size_t lista_tamanio(lista_t *lista)
{
	if (lista)
		return lista->cantidad;
	return 0;
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (!lista)
		return;
	while(lista->nodo_inicio) {
		nodo_t *nodo_aux = lista->nodo_inicio->siguiente;
		if (funcion)
			funcion(lista->nodo_inicio->elemento);
		free(lista->nodo_inicio);
		lista->nodo_inicio = nodo_aux;
	}
	free(lista);
}	

void lista_destruir(lista_t *lista)
{
	lista_destruir_todo(lista, NULL);
}	

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista)
		return NULL;

	lista_iterador_t *resultado = malloc(sizeof(lista_iterador_t));

	if (!resultado)
		return NULL;

	resultado->corriente = lista->nodo_inicio;
	resultado->lista = lista;

	return resultado;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if (!iterador || !iterador->corriente)
		return false;

	return iterador->corriente;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (!iterador || !iterador->corriente)
		return false;

	iterador->corriente = iterador->corriente->siguiente;
	return iterador->corriente;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if(!iterador || !iterador->corriente)
		return NULL;

	return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (!lista || !contexto || !funcion)
		return ERROR;

	nodo_t *nodo_a_iterar = lista->nodo_inicio;
	size_t elementos_iterados = 0;

	do {
		elementos_iterados++;
		if(funcion(nodo_a_iterar->elemento, contexto))
			return elementos_iterados;
		nodo_a_iterar = nodo_a_iterar->siguiente;
	
	}while(elementos_iterados < lista_tamanio(lista));

	return elementos_iterados;
}
