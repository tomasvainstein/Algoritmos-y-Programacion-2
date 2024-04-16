#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if(!comparador)
		return NULL;

	abb_t *arbol = calloc(1, sizeof(abb_t));

	if (!arbol)
		return NULL;

	arbol->comparador = comparador;

	return arbol;
}

/*
*	Se reserva memoria para un struct de tipo nodo_t y se inicializan sus campos 
* en NULL o 0 correspondientemente. 
* Luego se le asigna un puntero al elemento recibido por parámetro en caso de que este exista.
* Devuelve el nodo en caso de que el nodo haya sido creado exitosamente, o NULL en caso de error.
*
*/
nodo_abb_t *nuevo_nodo_arbol(void *elemento)
{
	nodo_abb_t *nuevo_nodo_abb = calloc(1, sizeof(nodo_abb_t));

	if (!nuevo_nodo_abb)
		return NULL;

	nuevo_nodo_abb->elemento = elemento;

	return nuevo_nodo_abb;
}

nodo_abb_t *abb_insertar_nodo(nodo_abb_t *nodo, void *elemento, int (*comparador)(void *, void *))
{
	if (nodo == NULL) {
		nodo_abb_t *nuevo_nodo_abb = nuevo_nodo_arbol(elemento);
		return nuevo_nodo_abb;
	}

	int comparacion = comparador(elemento, nodo->elemento);

	if (comparacion <= 0) 
		nodo->izquierda = abb_insertar_nodo(nodo->izquierda, elemento, comparador);
	else
		nodo->derecha = abb_insertar_nodo(nodo->derecha, elemento, comparador);

	return nodo;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (!arbol)
		return NULL;
	
	arbol->nodo_raiz = abb_insertar_nodo(arbol->nodo_raiz, elemento, arbol->comparador);

	if (arbol->nodo_raiz != NULL)
		arbol->tamanio++;

	return arbol;
}

nodo_abb_t *extraer_mas_derecho(size_t *tamanio_abb, nodo_abb_t *nodo, void **extraido)
{
	if (!nodo->derecha) {
		*extraido = nodo->elemento;
		nodo_abb_t *nodo_aux = nodo->izquierda;

		(*tamanio_abb)--;
		free(nodo);

		return nodo_aux;
	}
	nodo->derecha = extraer_mas_derecho(tamanio_abb, nodo->derecha, extraido);
	return nodo;
}

nodo_abb_t *abb_quitar_nodo(size_t *tamanio_abb, nodo_abb_t *nodo, void *a_quitar, int (*comparador)(void *, void *), void **elemento_quitado)
{
	if (nodo == NULL){
		return NULL;
	}

	int comparacion = comparador(a_quitar, nodo->elemento);

	if (comparacion == 0) {
		*elemento_quitado = nodo->elemento;
		nodo_abb_t *derecha = nodo->derecha;
		nodo_abb_t *izquierda = nodo->izquierda;

		if (izquierda && derecha) {
			void *extraido = NULL;
			nodo->izquierda = extraer_mas_derecho(tamanio_abb, nodo->izquierda, &extraido);
			nodo->elemento = extraido;
			return nodo;
		}
		if (derecha) {
			free(nodo);
			(*tamanio_abb)--;
			return derecha;
		}
		free(nodo);
		(*tamanio_abb)--;
		return izquierda;
	}
	if (comparacion < 0)
		nodo->izquierda = abb_quitar_nodo(tamanio_abb, nodo->izquierda, a_quitar, comparador, elemento_quitado);
	nodo->derecha = abb_quitar_nodo(tamanio_abb, nodo->derecha, a_quitar, comparador, elemento_quitado);

	return nodo;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{	
	if (arbol == NULL)
		return NULL;

	void *elemento_quitado = NULL;

	arbol->nodo_raiz = abb_quitar_nodo(&arbol->tamanio, arbol->nodo_raiz, elemento, arbol->comparador, &elemento_quitado);

	if (elemento_quitado != NULL)
		return elemento_quitado;

	return NULL;
}

void *abb_buscar_nodo(nodo_abb_t *nodo, void *elemento_buscado, int (*comparador)(void *, void *))
{
	if (!nodo)
		return NULL;

	int comparacion = comparador(elemento_buscado, nodo->elemento);

	if (comparacion == 0)
		return nodo->elemento;

	if (comparacion < 0)
		return abb_buscar_nodo(nodo->izquierda, elemento_buscado, comparador);
	return abb_buscar_nodo(nodo->derecha, elemento_buscado, comparador);
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (!arbol || abb_vacio(arbol))
		return NULL;

	return abb_buscar_nodo(arbol->nodo_raiz, elemento, arbol->comparador);
}

bool abb_vacio(abb_t *arbol)
{
	return (arbol == NULL || arbol->tamanio == 0);
}

size_t abb_tamanio(abb_t *arbol)
{
	if (arbol == NULL)
		return 0;

	return arbol->tamanio;
}

void abb_destruir(abb_t *arbol)
{
	abb_destruir_todo(arbol, NULL);
}

void abb_destruir_todo_nodo(nodo_abb_t *nodo, void (*destructor)(void *))
{
	if (!nodo)
		return;

	abb_destruir_todo_nodo(nodo->izquierda, destructor);
	abb_destruir_todo_nodo(nodo->derecha, destructor);

	if (destructor)
		destructor(nodo->elemento);

	free(nodo);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (!arbol)
		return;

	abb_destruir_todo_nodo(arbol->nodo_raiz, destructor);

	free(arbol);
}

/*
* 	Iteración inorden.
*
*/
void abb_con_cada_elemento_inorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, bool *seguir_iterando, size_t *iteraciones)
{
	if (!nodo || !(*seguir_iterando))
		return;
	
	abb_con_cada_elemento_inorden(nodo->izquierda, funcion, aux, seguir_iterando, iteraciones);

	if (!(*seguir_iterando))
		return;
	(*iteraciones)++;	

	*seguir_iterando = funcion(nodo->elemento, aux);

	abb_con_cada_elemento_inorden(nodo->derecha, funcion, aux, seguir_iterando, iteraciones);
}

/*
* 	Iteración preorden.
*
*/
void abb_con_cada_elemento_preorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, bool *seguir_iterando, size_t *iteraciones)
{
	if (!nodo || !(*seguir_iterando))
		return;
	
	if (!(*seguir_iterando))
		return;
	(*iteraciones)++;	

	*seguir_iterando = funcion(nodo->elemento, aux);

	abb_con_cada_elemento_preorden(nodo->izquierda, funcion, aux, seguir_iterando, iteraciones);

	abb_con_cada_elemento_preorden(nodo->derecha, funcion, aux, seguir_iterando, iteraciones);
}

/*
* 	Iteración postorden.
*
*/
void abb_con_cada_elemento_postorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, bool *seguir_iterando, size_t *iteraciones)
{
	if (!nodo || !(*seguir_iterando))	
		return;

	abb_con_cada_elemento_postorden(nodo->izquierda, funcion, aux, seguir_iterando, iteraciones);

	abb_con_cada_elemento_postorden(nodo->derecha, funcion, aux, seguir_iterando, iteraciones);

	if (!(*seguir_iterando))
		return;
	(*iteraciones)++;	

	*seguir_iterando = funcion(nodo->elemento, aux);
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (!funcion || !arbol)
		return 0;

	bool seguir_iterando = true;
	size_t iteraciones = 0;

	switch (recorrido) {
		case INORDEN:
			abb_con_cada_elemento_inorden(arbol->nodo_raiz, funcion, aux, &seguir_iterando, &iteraciones);
			break;
		case PREORDEN:
			abb_con_cada_elemento_preorden(arbol->nodo_raiz, funcion, aux, &seguir_iterando, &iteraciones);
			break;
		case POSTORDEN:
			abb_con_cada_elemento_postorden(arbol->nodo_raiz, funcion, aux, &seguir_iterando, &iteraciones);
			break;
	}
	return iteraciones;
}

/*
* 	Función que se encarga de insertar el elemento recibido en la posición determinada
* por la variable *elementos_almacenados. Cuando se almacena un elemento, se aumenta un número
* en la misma variable.
* Devuelve true siempre y cuando tamanio_array sea mayor a *elementos_almacenados. Sino, 
* devuelve false.
*
*/
bool insertado_en_array(void **array, size_t tamanio_array, size_t *elementos_almacenados, void *elemento)
{
	if (tamanio_array > *elementos_almacenados){
		array[*elementos_almacenados] = elemento;
		(*elementos_almacenados)++;
		return true;
	}
	return false;
}

/*
* 	Recorrido inorden.
*
*/
void abb_recorrer_inorden(nodo_abb_t *nodo_raiz, bool *seguir_iterando, size_t *iteraciones, void **array, size_t tamanio_array)
{
	if (!nodo_raiz || !(*seguir_iterando))
		return;

	abb_recorrer_inorden(nodo_raiz->izquierda, seguir_iterando, iteraciones, array, tamanio_array);

	*seguir_iterando = insertado_en_array(array, tamanio_array, iteraciones, nodo_raiz->elemento);

	abb_recorrer_inorden(nodo_raiz->derecha, seguir_iterando, iteraciones, array, tamanio_array);
}

/*
* 	Recorrido preorden.
*
*/
void abb_recorrer_preorden(nodo_abb_t *nodo_raiz, bool *seguir_iterando, size_t *iteraciones, void **array, size_t tamanio_array)
{
	if (!nodo_raiz || !(*seguir_iterando))
		return;

	*seguir_iterando = insertado_en_array(array, tamanio_array, iteraciones, nodo_raiz->elemento);

	abb_recorrer_preorden(nodo_raiz->izquierda, seguir_iterando, iteraciones, array, tamanio_array);

	abb_recorrer_preorden(nodo_raiz->derecha, seguir_iterando, iteraciones, array, tamanio_array);
}

/*
* 	Recorrido postorden.
*
*/
void abb_recorrer_postorden(nodo_abb_t *nodo_raiz, bool *seguir_iterando, size_t *iteraciones, void **array, size_t tamanio_array)
{
	if (!nodo_raiz || !(*seguir_iterando))
		return;

	abb_recorrer_postorden(nodo_raiz->izquierda, seguir_iterando, iteraciones, array, tamanio_array);

	abb_recorrer_postorden(nodo_raiz->derecha, seguir_iterando, iteraciones, array, tamanio_array);

	*seguir_iterando = insertado_en_array(array, tamanio_array, iteraciones, nodo_raiz->elemento);
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (!arbol)
		return 0;

	size_t elementos_almacenados = 0;

	bool seguir_iterando = true;

	switch (recorrido) {
		case INORDEN:
			abb_recorrer_inorden(arbol->nodo_raiz, &seguir_iterando, &elementos_almacenados, array, tamanio_array);
			break;
		case PREORDEN:
			abb_recorrer_preorden(arbol->nodo_raiz, &seguir_iterando, &elementos_almacenados, array, tamanio_array);
			break;
		case POSTORDEN:
			abb_recorrer_postorden(arbol->nodo_raiz, &seguir_iterando, &elementos_almacenados, array, tamanio_array);
			break;
	}
	return elementos_almacenados;
}