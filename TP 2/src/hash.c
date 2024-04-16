#include "hash.h"
#include "lista.h"
#include "string.h"
#include <stddef.h>
#include <stdlib.h>

#define CAPACIDAD_MINIMA 3
#define VALOR_SOBRECARGA 0.75
#define SON_IGUALES 0
#define SON_DISTINTOS 1

struct hash {
	lista_t **tabla_hash;
	size_t cantidad;
	size_t capacidad;
};

typedef struct par_hash {
        const char *clave;
        void *valor;
} par_hash_t;

/*
 * Procedimiento que se encarga de destruir cada lista
 * del vector del vector de listas recibidos y luego
 * liberar la memoria del mismo.
 */

void destruir_tabla_hash(lista_t **tabla_hash, size_t capacidad) 
{
	if (!tabla_hash || !capacidad)
		return;

	size_t i = 0;

	while (i < capacidad) {
		lista_destruir(tabla_hash[i]);
		i++;
	}
	free(tabla_hash);
}

/*
 * Función que reserva memoria para un vector
 * con cantidad de listas igual a la capacidad recibida,
 * lo inicializa y lo devuelve al final de la función.
 * En caso de no poder reservar memoria para una lista,
 * se liberan las creadas exitosamente, el vector y
 * se devuelve NULL.
 */

lista_t **crear_tabla_hash(size_t capacidad) 
{
	lista_t **tabla_hash = calloc(capacidad, sizeof(lista_t *));
	if (!tabla_hash)
		return NULL;

	size_t i = 0;

	while (i < capacidad) {
		tabla_hash[i] = lista_crear();

		if (!tabla_hash[i]) {
			destruir_tabla_hash(tabla_hash, capacidad);
			return NULL;
		}
		i++;
	}
	return tabla_hash;
}

hash_t *hash_crear(size_t capacidad) 
{
	hash_t *hash = malloc(sizeof(hash_t));
	if (!hash)
		return NULL;

	if (capacidad < CAPACIDAD_MINIMA)
		capacidad = CAPACIDAD_MINIMA;

	lista_t **tabla_hash = crear_tabla_hash(capacidad);
	if (!tabla_hash) {
		free(hash);
		return NULL;
	}

	hash->tabla_hash = tabla_hash;
	hash->capacidad = capacidad;
	hash->cantidad = 0;

	return hash;
}

/*
 * Función que devuelve el resultado determinado por
 * la multiplicación del valor de la tabla ASCII de
 * cada char del string recibido y el valor de la variable i,
 * y el módulo entre ese resultado y la capacidad recibida.
 */

size_t funcion_hash(const char *clave, size_t capacidad_tabla) 
{
	size_t valor = 0;
	size_t i = 15;

	while (*clave) {
		valor += i * (size_t)*clave++;
		i += 25;
	}
	return valor % capacidad_tabla;
}

/*
 * Función que reserva memoria para copiar el string
 * recibido y lo devuelve.
 */

char *duplicar_clave(const char *clave) 
{
	if (!clave)
		return NULL;

	char *clave_copia = malloc(strlen(clave) + 1);
	if (!clave_copia)
		return NULL;

	strcpy(clave_copia, clave);

	return clave_copia;
}

/*
 * Función que reserva memoria para una variable de
 * tipo par_hash_t y le asigna la clave duplicada y
 * el valor recibido. Se devuelve el par creado o NULL
 * si falla.
 */

par_hash_t *nuevo_par(const char *clave, void *valor) 
{
	par_hash_t *par_creado = malloc(sizeof(par_hash_t));
	if (!par_creado)
		return NULL;

	par_creado->clave = duplicar_clave(clave);
	par_creado->valor = valor;

	return par_creado;
}

/*
 * Función que compara el string del par y la
 * clave recibidos. Devuelve SON_IGUALES si
 * strcmp devuelve 0 o SON_DISTINTOS si
 * devuelve distinto de 0.
 */

int comparador(void *par, void *clave) 
{
	par_hash_t *par_a_comparar = (par_hash_t *)par;

	if (strcmp(par_a_comparar->clave, clave) == SON_IGUALES)
		return SON_IGUALES;

	return SON_DISTINTOS;
}

/*
 * Función que devuelve true si el valor de la división
 * entre la cantidad y la capacidad del hash es mayor o igual
 * al valor de sobrecarga. Sino, devuelve false.
 */

bool hay_sobrecarga(hash_t *hash) 
{
	float valor = (float)(hash->cantidad / hash->capacidad);

	return valor >= VALOR_SOBRECARGA;
}

/*
 * Función que aumenta la capacidad de la tabla de  hash y reinserta todos los
 * elementos de la misma en una nueva, liberando la memoria de todas las listas
 * previas y su vector.
 * Se devuelve la nueva tabla de hash en caso de éxito, o NULL en caso de error.
 */

hash_t *funcion_rehash(hash_t *hash) 
{
	size_t capacidad_actualizada = hash->capacidad * 2;

	lista_t **tabla_rehash = crear_tabla_hash(capacidad_actualizada);
	if (!tabla_rehash)
		return NULL;

	size_t i = 0;

	while (i < hash->capacidad) {
		while (hash->tabla_hash[i] && !lista_vacia(hash->tabla_hash[i])) {
			par_hash_t *par_a_insertar =
			(par_hash_t *)lista_quitar_de_posicion(hash->tabla_hash[i], 0);
			if (!par_a_insertar)
				return NULL;

			size_t nueva_posicion =
			funcion_hash(par_a_insertar->clave, capacidad_actualizada);

			lista_insertar(tabla_rehash[nueva_posicion], par_a_insertar);
		}
		lista_destruir(hash->tabla_hash[i]);
		i++;
	}
	hash->capacidad = capacidad_actualizada;

	free(hash->tabla_hash);
	hash->tabla_hash = tabla_rehash;

	return hash;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
	void **anterior) 
{
	if (!hash || !clave)
		return NULL;

	size_t posicion = funcion_hash(clave, hash->capacidad);

	if (!hash->tabla_hash[posicion])
		return NULL;

	par_hash_t *par_a_insertar = (par_hash_t *)lista_buscar_elemento(
		hash->tabla_hash[posicion], comparador, (void *)clave);

	if (par_a_insertar) {
		if (anterior)
			*anterior = par_a_insertar->valor;
		par_a_insertar->valor = elemento;

		return hash;
	}

	par_a_insertar = nuevo_par(clave, elemento);
	if (!par_a_insertar)
		return NULL;

	if (!lista_insertar(hash->tabla_hash[posicion], par_a_insertar))
		return NULL;

	hash->cantidad++;
	if (anterior)
		*anterior = NULL;

	if (hay_sobrecarga(hash))
		return funcion_rehash(hash);

	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	size_t posicion = funcion_hash(clave, hash->capacidad);
	size_t posicion_clave = 0;
	int estado_funcion = SON_DISTINTOS;
	void *valor_par_a_quitar = NULL;

	lista_iterador_t *iterador = lista_iterador_crear(hash->tabla_hash[posicion]);

	if (!iterador)
		return NULL;

	while (lista_iterador_tiene_siguiente(iterador) && estado_funcion) {
		par_hash_t *par_a_quitar = lista_iterador_elemento_actual(iterador);

		estado_funcion = comparador(par_a_quitar, (void *)clave);

		if (estado_funcion == SON_IGUALES) {
			if (!lista_quitar_de_posicion(
				hash->tabla_hash[posicion], posicion_clave))
				return NULL;

			hash->cantidad--;

			valor_par_a_quitar = par_a_quitar->valor;
			free((void *)par_a_quitar->clave);
			free(par_a_quitar);
		} else {
			posicion_clave++;
			lista_iterador_avanzar(iterador);
		}
	}
	lista_iterador_destruir(iterador);
	return valor_par_a_quitar;
}

void *hash_obtener(hash_t *hash, const char *clave) 
{
	if (!hash || !clave)
		return NULL;

	size_t posicion = funcion_hash(clave, hash->capacidad);

	par_hash_t *par_a_buscar = (par_hash_t *)lista_buscar_elemento(
		hash->tabla_hash[posicion], comparador, (void *)clave);
	if (!par_a_buscar)
		return NULL;

	return par_a_buscar->valor;
}

bool hash_contiene(hash_t *hash, const char *clave) 
{
	if (!hash || !clave)
		return NULL;

	size_t posicion = funcion_hash(clave, hash->capacidad);

	par_hash_t *par_a_buscar = (par_hash_t *)lista_buscar_elemento(
		hash->tabla_hash[posicion], comparador, (void *)clave);
	if (!par_a_buscar)
		return NULL;

	return par_a_buscar->valor;
}

size_t hash_cantidad(hash_t *hash) 
{
	if (!hash)
		return 0;

	return hash->cantidad;
}

void hash_destruir(hash_t *hash) 
{ 
	hash_destruir_todo(hash, NULL); 
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *)) {
	if (!hash)
		return;

	size_t i = 0;

	while (i < hash->capacidad) {
		while (hash->tabla_hash[i] && !lista_vacia(hash->tabla_hash[i])) {
			par_hash_t *par_a_destruir =
			(par_hash_t *)lista_quitar_de_posicion(hash->tabla_hash[i], 0);
			if (!par_a_destruir)
				return;

			if (destructor)
				destructor(par_a_destruir->valor);

			free((void *)par_a_destruir->clave);
			free(par_a_destruir);
		}
		lista_destruir(hash->tabla_hash[i]);
		i++;
	}
	free(hash->tabla_hash);
	free(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
	bool (*f)(const char *clave, void *valor, void *aux),
	void *aux) 
{
	if (!hash || !f)
		return 0;

	size_t claves_iteradas = 0;
	bool estado_funcion = true;

	size_t i = 0;

	while (i < hash->capacidad) {
		if (hash->tabla_hash[i]) {
			lista_iterador_t *iterador = 
			lista_iterador_crear(hash->tabla_hash[i]);
			if (!iterador)
				return claves_iteradas;

			while (lista_iterador_tiene_siguiente(iterador) && estado_funcion) {
				par_hash_t *par_actual = 
				(par_hash_t *)lista_iterador_elemento_actual(iterador);

				claves_iteradas++;

				estado_funcion = f(par_actual->clave, par_actual->valor, aux);

				if (estado_funcion)
					lista_iterador_avanzar(iterador);
			}
			lista_iterador_destruir(iterador);
		}
		i++;
	}
	return claves_iteradas;
}