#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

typedef struct cosa {
	int clave;
	char contenido[10];
} cosa;

void destruir_cosa(cosa *c)
{
	free(c);
}

int comparador(void *c1, void *c2)
{
	cosa *cosa1 = c1;
	cosa *cosa2 = c2;
	return cosa1->clave - cosa2->clave;
}

bool seguir_iterando(void *elemento, void *extra)
{
	if (elemento && extra)
		return true;
	return false;
}

void creo_un_abb_con_nodo_raiz_nulo_y_tamanio_0()
{
	abb_t *arbol = abb_crear(comparador);

	pa2m_afirmar(arbol != NULL, "El árbol creado es válido.");
  	pa2m_afirmar(arbol->nodo_raiz == NULL, "El nodo raíz tiene valor NULL.");
 	pa2m_afirmar(abb_tamanio(arbol) == 0, "El árbol tiene cantidad 0.");

  	abb_destruir(arbol);
}

void no_puedo_crear_un_abb_con_comparador_nulo()
{
	abb_t *arbol = abb_crear(NULL);

	pa2m_afirmar(arbol == NULL, "No puedo crear el árbol sin comparador.");
}

void no_se_puede_insertar_nada_en_un_arbol_inexistente()
{
	int elemento1 = 1;

	pa2m_afirmar(abb_insertar(NULL, &elemento1) == NULL, "No puedo insertar en un árbol que no existe.");
}

void inserto_elementos_en_un_arbol_vacio()
{
	abb_t *arbol = abb_crear(comparador);

	int elemento1 = 50, elemento2 = 70, elemento3 = 40, elemento4 = 20, elemento5 = 45, elemento6 = 60, elemento7 = 80;

	void *nada = NULL;

  	pa2m_afirmar(abb_insertar(arbol, &elemento1) == arbol, "Inserto un elemento en un árbol vacío.");
 	pa2m_afirmar(abb_tamanio(arbol) == 1, "El árbol deja de estar vacío y tiene cantidad 1.");
 	pa2m_afirmar(*(int *)arbol->nodo_raiz->elemento == elemento1, "El elemento agregado se encuentra en el nodo raíz.");

 	pa2m_afirmar(abb_insertar(arbol, &elemento2) == arbol, "Inserto un elemento más grande que la raíz del árbol.");
 	pa2m_afirmar(abb_tamanio(arbol) == 2, "El árbol ahora tiene dos elementos.");
 	pa2m_afirmar(*(int *)arbol->nodo_raiz->derecha->elemento == elemento2, "El segundo elemento se encuentra en el hijo derecho de la raíz.");

 	pa2m_afirmar(abb_insertar(arbol, &elemento3) == arbol, "Inserto un elemento más chico que la raíz del árbol.");
 	pa2m_afirmar(abb_tamanio(arbol) == 3, "El árbol ahora tiene tres elementos.");
 	pa2m_afirmar(*(int *)arbol->nodo_raiz->izquierda->elemento == elemento3, "El tercer elemento se encuentra en el hijo izquierdo de la raíz.");

 	pa2m_afirmar(abb_insertar(arbol, &elemento4) == arbol, "Inserto un elemento más chico que el hijo izquierdo de la raíz del árbol.");
 	pa2m_afirmar(abb_tamanio(arbol) == 4, "El árbol ahora tiene cuatro elementos.");
 	pa2m_afirmar(*(int *)arbol->nodo_raiz->izquierda->izquierda->elemento == elemento4, "El cuarto elemento se encuentra en el hijo izquierdo del hijo izquierdo de la raíz.");

 	pa2m_afirmar(abb_insertar(arbol, &elemento5) == arbol, "Inserto un elemento más grande que el hijo izquierdo de la raíz del árbol.");
 	pa2m_afirmar(abb_tamanio(arbol) == 5, "El árbol ahora tiene cinco elementos.");
 	pa2m_afirmar(*(int *)arbol->nodo_raiz->izquierda->derecha->elemento == elemento5, "El quinto elemento se encuentra en el hijo derecho del hijo izquierdo de la raíz.");

 	pa2m_afirmar(abb_insertar(arbol, &elemento6) == arbol, "Inserto un elemento más chico que el hijo derecho de la raíz del árbol.");
 	pa2m_afirmar(abb_tamanio(arbol) == 6, "El árbol ahora tiene seis elementos.");
 	pa2m_afirmar(*(int *)arbol->nodo_raiz->derecha->izquierda->elemento == elemento6, "El sexto elemento se encuentra en el hijo izquierdo del hijo derecho de la raíz.");

 	pa2m_afirmar(abb_insertar(arbol, &elemento7) == arbol, "Inserto un elemento más grande que el hijo derecho de la raíz del árbol.");
 	pa2m_afirmar(abb_tamanio(arbol) == 7, "El árbol ahora tiene siete elementos.");
 	pa2m_afirmar(*(int *)arbol->nodo_raiz->derecha->derecha->elemento == elemento7, "El sexto elemento se encuentra en el hijo derecho del hijo derecho de la raíz.");

 	pa2m_afirmar(abb_insertar(arbol, &nada) == arbol, "Puedo insertar un elemento nulo en el árbol.");

  	abb_destruir(arbol);
}

void pruebas_de_creacion()
{
	pa2m_nuevo_grupo("Pruebas de creación de árbol:");

	creo_un_abb_con_nodo_raiz_nulo_y_tamanio_0();
	no_puedo_crear_un_abb_con_comparador_nulo();
}

void pruebas_de_insercion()
{
	pa2m_nuevo_grupo("Pruebas de inserción en árbol:");

	no_se_puede_insertar_nada_en_un_arbol_inexistente();
	inserto_elementos_en_un_arbol_vacio();
}

void pruebas_de_borrado()
{
	pa2m_nuevo_grupo("Pruebas de borrado en árbol:");

	abb_t *arbol = abb_crear(comparador);

	int elemento1 = 50, elemento2 = 70, elemento3 = 40, elemento4 = 20, elemento5 = 45, elemento6 = 60, elemento7 = 80, elemento8 = 75, elemento9 = 10, elemento10 = 30, elemento = 99;

	void *nada = NULL;

	pa2m_afirmar(abb_quitar(arbol, &elemento1) == NULL, "No puedo buscar un elemento en un árbol sin elementos.");

	abb_insertar(arbol, &elemento1);
	abb_insertar(arbol, &elemento2);
	abb_insertar(arbol, &elemento3);
	abb_insertar(arbol, &elemento4);
	abb_insertar(arbol, &elemento5);
	abb_insertar(arbol, &elemento6);
	abb_insertar(arbol, &elemento7);
	abb_insertar(arbol, &elemento8);
	abb_insertar(arbol, &elemento9);
	abb_insertar(arbol, &elemento10);
	abb_insertar(arbol, &nada);

	pa2m_afirmar(abb_quitar(arbol, &nada) == &nada, "Puedo quitar un elemento nulo en el árbol.");

	size_t cantidad = abb_tamanio(arbol);

	pa2m_afirmar(abb_quitar(NULL, &elemento1) == NULL, "No puedo quitar un elemento en un árbol nulo.");
	pa2m_afirmar(abb_quitar(arbol, &elemento) == NULL, "No puedo quitar un elemento que no se encuentra en el árbol.");
	pa2m_afirmar(abb_tamanio(arbol) == cantidad, "El árbol tiene la misma cantidad de elementos que antes.");

  	pa2m_afirmar(*(int *)abb_quitar(arbol, &elemento8) == elemento8, "Puedo quitar un nodo hoja en el árbol.");
  	pa2m_afirmar(abb_tamanio(arbol) == cantidad-1, "El árbol tiene un elemento menos.");

  	pa2m_afirmar(*(int *)abb_quitar(arbol, &elemento2) == elemento2, "Puedo quitar un nodo con dos hijos.");
  	pa2m_afirmar(*(int *)arbol->nodo_raiz->derecha->elemento == elemento6, "El predecesor inorden ocupa su lugar.");
  	pa2m_afirmar(abb_tamanio(arbol) == cantidad-2, "El árbol tiene un elemento menos.");

  	pa2m_afirmar(*(int *)abb_quitar(arbol, &elemento3) == elemento3, "Puedo quitar un nodo con dos hijos.");
  	pa2m_afirmar(*(int *)arbol->nodo_raiz->izquierda->elemento == elemento10, "El predecesor inorden ocupa su lugar.");
  	pa2m_afirmar(abb_tamanio(arbol) == cantidad-3, "El árbol tiene un elemento menos.");

  	pa2m_afirmar(*(int *)abb_quitar(arbol, &elemento1) == elemento1, "Puedo quitar la raíz del árbol.");
  	pa2m_afirmar(*(int *)arbol->nodo_raiz->elemento == elemento5, "El predecesor inorden ocupa su lugar.");
  	pa2m_afirmar(abb_tamanio(arbol) == cantidad-4, "El árbol tiene un elemento menos.");

  	pa2m_afirmar(*(int *)abb_quitar(arbol, &elemento10) == elemento10, "Puedo quitar un nodo con un hijo.");
  	pa2m_afirmar(*(int *)arbol->nodo_raiz->izquierda->elemento == elemento4, "El hijo del eliminado ocupa su lugar.");
  	pa2m_afirmar(abb_tamanio(arbol) == cantidad-5, "El árbol tiene un elemento menos.");

  	pa2m_afirmar(*(int *)abb_quitar(arbol, &elemento6) == elemento6, "Puedo quitar un nodo con un hijo.");
  	pa2m_afirmar(*(int *)arbol->nodo_raiz->derecha->elemento == elemento7, "El hijo del eliminado ocupa su lugar.");
  	pa2m_afirmar(abb_tamanio(arbol) == cantidad-6, "El árbol tiene un elemento menos.");

  	pa2m_afirmar(*(int *)abb_quitar(arbol, &elemento4) == elemento4, "Puedo quitar un nodo con un hijo.");
  	pa2m_afirmar(*(int *)arbol->nodo_raiz->izquierda->elemento == elemento9, "El hijo del eliminado ocupa su lugar.");
  	pa2m_afirmar(abb_tamanio(arbol) == cantidad-7, "El árbol tiene un elemento menos.");

  	pa2m_afirmar(*(int *)abb_quitar(arbol, &elemento9) == elemento9, "Puedo quitar un nodo hoja en el árbol.");
  	pa2m_afirmar(abb_tamanio(arbol) == cantidad-8, "El árbol tiene un elemento menos.");

  	pa2m_afirmar(*(int *)abb_quitar(arbol, &elemento7) == elemento7, "Puedo quitar un nodo hoja en el árbol.");
  	pa2m_afirmar(abb_tamanio(arbol) == cantidad-9, "El árbol tiene un elemento menos.");

  	pa2m_afirmar(arbol->nodo_raiz->izquierda == NULL, "La raíz ahora tiene un hijo izquierdo apuntando a NULL");
  	pa2m_afirmar(arbol->nodo_raiz->derecha == NULL, "La raíz ahora tiene un hijo derecho apuntando a NULL");

  	pa2m_afirmar(*(int *)abb_quitar(arbol, &elemento5) == elemento5, "Borro el único nodo restante en el árbol.");
  	pa2m_afirmar(abb_tamanio(arbol) == 0, "El árbol ahora está vacío.");
  	pa2m_afirmar(arbol->nodo_raiz == NULL, "El nodo raíz apunta a NULL.");

  	abb_destruir(arbol);
}

void pruebas_de_busqueda()
{
	pa2m_nuevo_grupo("Pruebas de búsqueda en árbol:");

	abb_t *arbol = abb_crear(comparador);

	int elemento1 = 50, elemento2 = 70, elemento3 = 40, elemento4 = 20, elemento5 = 45, elemento6 = 60, elemento7 = 80;

	void *nada = NULL;

	pa2m_afirmar(abb_buscar(arbol, &elemento1) == NULL, "No puedo buscar un elemento en un árbol sin elementos.");

	abb_insertar(arbol, &elemento1);
	abb_insertar(arbol, &elemento2);
	abb_insertar(arbol, &elemento3);
	abb_insertar(arbol, &elemento4);
	abb_insertar(arbol, &elemento5);
	abb_insertar(arbol, &elemento6);
	abb_insertar(arbol, &elemento7);
	abb_insertar(arbol, &nada);

  	pa2m_afirmar(abb_buscar(NULL, &elemento1) == NULL, "No puedo buscar un elemento en un árbol nulo.");
  	pa2m_afirmar(abb_buscar(arbol, &nada) == &nada, "Puedo buscar un elemento nulo en el árbol.");
  	pa2m_afirmar(*(int *)abb_buscar(arbol, &elemento1) == elemento1, "Puedo buscar un elemento cualquiera en el árbol.");
  	pa2m_afirmar(*(int *)abb_buscar(arbol, &elemento2) == elemento2, "Puedo buscar un elemento cualquiera en el árbol.");
  	pa2m_afirmar(*(int *)abb_buscar(arbol, &elemento3) == elemento3, "Puedo buscar un elemento cualquiera en el árbol.");
  	pa2m_afirmar(*(int *)abb_buscar(arbol, &elemento4) == elemento4, "Puedo buscar un elemento cualquiera en el árbol.");
  	pa2m_afirmar(*(int *)abb_buscar(arbol, &elemento5) == elemento5, "Puedo buscar un elemento cualquiera en el árbol.");
  	pa2m_afirmar(*(int *)abb_buscar(arbol, &elemento6) == elemento6, "Puedo buscar un elemento cualquiera en el árbol.");
  	pa2m_afirmar(*(int *)abb_buscar(arbol, &elemento7) == elemento7, "Puedo buscar un elemento cualquiera en el árbol.");

  	abb_destruir(arbol);
}

void pruebas_de_iterador()
{
	pa2m_nuevo_grupo("Pruebas de iterador:");

	abb_t *arbol = abb_crear(comparador);

	int elemento1 = 50, elemento2 = 70, elemento3 = 40, elemento4 = 20, elemento5 = 45, elemento6 = 60, elemento7 = 80, elemento8 = 75, elemento9 = 10, elemento10 = 30;

	abb_insertar(arbol, &elemento1);
	abb_insertar(arbol, &elemento2);
	abb_insertar(arbol, &elemento3);
	abb_insertar(arbol, &elemento4);
	abb_insertar(arbol, &elemento5);
	abb_insertar(arbol, &elemento6);
	abb_insertar(arbol, &elemento7);
	abb_insertar(arbol, &elemento8);
	abb_insertar(arbol, &elemento9);
	abb_insertar(arbol, &elemento10);

	int aux = 0;

	pa2m_afirmar(abb_con_cada_elemento(NULL, INORDEN, seguir_iterando, NULL) == 0, "No puedo iterar un árbol inexistente.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, NULL, NULL) == 0, "No puedo iterar el árbol sin una función.");

	pa2m_nuevo_grupo("Pruebas de iterador inorden:");

	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, seguir_iterando, NULL) != 0, "Puedo iterar el árbol con recorrido INORDEN y puntero auxiliar NULL.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, seguir_iterando, &aux) == 10, "Iterar el árbol con recorrido INORDEN me devuelve correcta cantidad de iteraciones.");

	pa2m_nuevo_grupo("Pruebas de iterador preorden:");

	pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, seguir_iterando, NULL) != 0, "Puedo iterar el árbol con recorrido PREORDEN y puntero auxiliar NULL.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, seguir_iterando, &aux) == 10, "Iterar el árbol con recorrido PREORDEN me devuelve correcta cantidad de iteraciones.");

	pa2m_nuevo_grupo("Pruebas de iterador postorden:");

	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, seguir_iterando, NULL) != 0, "Puedo iterar el árbol con recorrido POSTORDEN y puntero auxiliar NULL.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, seguir_iterando, &aux) == 10, "Iterar el árbol con recorrido POSTORDEN me devuelve correcta cantidad de iteraciones.");

	abb_destruir(arbol);
}

void pruebas_de_recorrido()
{
	pa2m_nuevo_grupo("Pruebas de recorrido:");

	abb_t *arbol = abb_crear(comparador);

	cosa *array[9];
	cosa *array1[9];
	cosa *array2[9];

	size_t tamanio_array = 9;

	int elemento1 = 50, elemento2 = 70, elemento3 = 40, elemento4 = 20, elemento5 = 45, elemento6 = 60, elemento7 = 80, elemento8 = 75, elemento9 = 30;

	abb_insertar(arbol, &elemento1);
	abb_insertar(arbol, &elemento2);
	abb_insertar(arbol, &elemento3);
	abb_insertar(arbol, &elemento4);
	abb_insertar(arbol, &elemento5);
	abb_insertar(arbol, &elemento6);
	abb_insertar(arbol, &elemento7);
	abb_insertar(arbol, &elemento8);
	abb_insertar(arbol, &elemento9);

	pa2m_afirmar(abb_recorrer(NULL, INORDEN, (void **)array, tamanio_array) == 0, "No puedo recorrer un árbol inexistente.");
	pa2m_afirmar(abb_recorrer(arbol, INORDEN, (void **)array, tamanio_array) == 9, "Recorrer el árbol de cualquier forma me devuelve la cantidad de elementos del array."); 

	pa2m_nuevo_grupo("Pruebas de recorrido inorden:");

	pa2m_afirmar(abb_recorrer(arbol, INORDEN, (void **)array, tamanio_array) == 9, "Iterar el árbol con recorrido INORDEN me devuelve correcta cantidad de iteraciones.");

	pa2m_afirmar(*(int *)array[0] == elemento4, "El primer elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array[1] == elemento9, "El segundo elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array[2] == elemento3, "El tercer elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array[3] == elemento5, "El cuarto elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array[4] == elemento1, "El quinto elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array[5] == elemento6, "El sexto elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array[6] == elemento2, "El séptimo elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array[7] == elemento8, "El octavo elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array[8] == elemento7, "El noveno elemento está en la posición correcta del array.");

	pa2m_nuevo_grupo("Pruebas de recorrido preorden:");

	pa2m_afirmar(abb_recorrer(arbol, PREORDEN, (void **)array1, tamanio_array) == 9, "Iterar el árbol con recorrido PREORDEN me devuelve correcta cantidad de iteraciones.");

	pa2m_afirmar(*(int *)array1[0] == elemento1, "El primer elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array1[1] == elemento3, "El segundo elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array1[2] == elemento4, "El tercer elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array1[3] == elemento9, "El cuarto elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array1[4] == elemento5, "El quinto elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array1[5] == elemento2, "El sexto elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array1[6] == elemento6, "El séptimo elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array1[7] == elemento7, "El octavo elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array1[8] == elemento8, "El noveno elemento está en la posición correcta del array.");

	pa2m_nuevo_grupo("Pruebas de recorrido postorden:");

	pa2m_afirmar(abb_recorrer(arbol, POSTORDEN, (void **)array2, tamanio_array) == 9, "Iterar el árbol con recorrido POSTORDEN me devuelve correcta cantidad de iteraciones.");

	pa2m_afirmar(*(int *)array2[0] == elemento9, "El primer elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array2[1] == elemento4, "El segundo elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array2[2] == elemento5, "El tercer elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array2[3] == elemento3, "El cuarto elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array2[4] == elemento6, "El quinto elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array2[5] == elemento8, "El sexto elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array2[6] == elemento7, "El séptimo elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array2[7] == elemento2, "El octavo elemento está en la posición correcta del array.");
	pa2m_afirmar(*(int *)array2[8] == elemento1, "El noveno elemento está en la posición correcta del array.");

	abb_destruir(arbol);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de ABB");

	pruebas_de_creacion();

	pruebas_de_insercion();

	pruebas_de_borrado();

	pruebas_de_busqueda();

	pruebas_de_iterador();

	pruebas_de_recorrido();

	return pa2m_mostrar_reporte();
}