#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

void crear_una_lista_me_devuelve_una_lista_con_cantidad_0()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista != NULL, "La lista creada es válida.");
	pa2m_afirmar(lista_tamanio(lista) == 0, "La lista creada tiene cantidad 0.");

	lista_destruir(lista);
}

void crear_una_lista_me_devuelve_un_nodo_inicio_y_nodo_fin_con_elementos_nulos()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_primero(lista) == NULL, "El primer elemento de la lista está vacío.");
	pa2m_afirmar(lista_ultimo(lista) == NULL, "El último elemento de la lista está vacío.");

	lista_destruir(lista);
}

void insertar_elementos_en_lisa_vacia_devuelve_una_lista_con_la_cantidad_de_elementos_insertados()
{
	lista_t *lista = lista_crear();

	int valor1 = 1;
	int valor2 = 2;

	pa2m_afirmar(lista_insertar(NULL, &valor1) == NULL, "No se inserta un elemento en una lista inexistente.");
	pa2m_afirmar(lista_insertar(lista, &valor1) != NULL, "Se inserta un elemento en una lista vacía.");
	pa2m_afirmar(lista_tamanio(lista) == 1, "Se inserta un elemento entonces ahora lista tiene tamaño 1.");
	pa2m_afirmar(lista_insertar(lista, &valor2) != NULL, "Se inserta el segundo elemento.");
	pa2m_afirmar(lista_tamanio(lista) == 2, "Se inserta un segundo elemento entonces ahora lista tiene tama 2.");

	lista_destruir(lista);
}

void se_inserta_un_elemento_en_una_lista_vacia_entonces_nodo_inicio_y_nodo_fin_apuntan_al_nodo_con_ese_elemento()
{
	lista_t *lista = lista_crear();

	lista_insertar(lista, 0);
	pa2m_afirmar(lista->nodo_inicio != NULL, "El primer nodo ya no está vacío luego de agregar un elemento.");
	pa2m_afirmar(lista->nodo_fin != NULL, "El último nodo ya no está vacío luego de agregar un elemento.");
	pa2m_afirmar(lista->nodo_inicio == lista->nodo_fin, "El primer y último nodo apuntan al mismo elemento.");

	lista_destruir(lista);
}

void se_insertan_elementos_en_posiciones_inexistentes_de_la_lista_y_cada_uno_pertence_al_final_de_esta()
{
	lista_t *lista = lista_crear();

	int valor1 = 1;
	int valor2 = 2;
	int valor3 = 3;

	pa2m_afirmar(lista_insertar_en_posicion(lista, &valor1, 28) == lista, "Se inserta elemento en posición inexistente.");
	pa2m_afirmar(lista->nodo_fin->elemento == &valor1, "El elemento del nodo final es el elemento que se acaba de agregar.");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &valor2, 7) == lista, "Se inserta elemento en posición inexistente.");
	pa2m_afirmar(lista->nodo_fin->elemento == &valor2, "El elemento del nodo final es ahora el segundo elemento agregado.");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &valor3, 4) == lista, "Se inserta elemento en posición inexistente.");
	pa2m_afirmar(lista->nodo_fin->elemento == &valor3, "El elemento del nodo final es ahora el tercer elemento agregado.");

	lista_destruir(lista);
}

void se_insertan_elementos_en_el_medio_de_la_lista_y_este_no_se_encuentra_ni_al_principio_ni_al_final()
{
	lista_t *lista = lista_crear();

	size_t posicion = 0;
	int valor = 0;
	int valor1 = 1;
	int valor2 = 2;

	while(posicion < 10) {
		lista_insertar_en_posicion(lista, &valor, posicion);
		valor++;
		posicion++;
	}

	pa2m_afirmar(lista_insertar_en_posicion(lista, &valor1, 3) == lista, "Se inserta un elemento en una posición del medio de la lista.");
	pa2m_afirmar(lista->nodo_inicio->elemento != &valor1, "El elemento no se encuentra al principio de la lista.");
	pa2m_afirmar(lista->nodo_fin->elemento != &valor1, "El elemento no se encuentra al final de la lista.");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &valor2, 6) == lista, "Se inserta otro elemento en una posición del medio de la lista.");
	pa2m_afirmar(lista->nodo_inicio->elemento != &valor2, "El elemento no se encuentra al principio de la lista.");
	pa2m_afirmar(lista->nodo_fin->elemento != &valor2, "El elemento no se encuentra al final de la lista.");

	lista_destruir(lista);
}

void se_insertan_elementos_en_la_primer_posicion_de_la_lista_y_estos_se_encuentran_al_principio()
{
	lista_t *lista = lista_crear();

	size_t posicion = 0;
	int valor = 0;
	int valor1 = 1;
	int valor2 = 2;

	while(posicion < 10) {
		lista_insertar_en_posicion(lista, &valor, posicion);
		valor++;
		posicion++;
	}

	pa2m_afirmar(lista_insertar_en_posicion(lista, &valor1, 0) == lista, "Se inserta un elemento en la primera posición de la lista.");
	pa2m_afirmar(lista->nodo_inicio->elemento == &valor1, "El elemento se encuentra al principio de la lista.");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &valor2, 0) == lista, "Se inserta otro elemento en la primera posición de la lista.");
	pa2m_afirmar(lista->nodo_inicio->elemento == &valor2, "El elemento se encuentra al principio de la lista.");

	lista_destruir(lista);
}

void borrar_elementos_de_una_lista_vacia_o_inexistente_devuelve_NULL()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_quitar(NULL) == NULL, "No se puede borrar elementos de una lista inexistente.");
	pa2m_afirmar(lista_quitar(lista) == NULL, "No se puede borrar elementos de una lista vacía.");

	lista_destruir(lista);
}

void si_se_quita_el_unico_elemento_de_una_lista_nodo_inicio_y_nodo_fin_apuntan_a_NULL_y_el_tamanio_de_la_lista_es_0()
{
	lista_t *lista = lista_crear();

	int valor = 0;

	lista_insertar(lista, &valor);

	pa2m_afirmar(lista_quitar(lista) == &valor, "Se quitó el único elemento de la lista.");
	pa2m_afirmar(lista->nodo_inicio == NULL, "El primer nodo de la lista está vacío.");
	pa2m_afirmar(lista->nodo_fin == NULL, "El último nodo de la lista está vacío.");
	pa2m_afirmar(lista_tamanio(lista) == 0, "La lista no tiene más elementos.");

	lista_destruir(lista);
}


void si_se_quita_el_ultimo_elemento_de_la_lista_este_deja_de_estar_en_el_final()
{
	lista_t *lista = lista_crear();

	int valor1 = 1;
	int valor2 = 2;
	int valor3 = 3;

	lista_insertar_en_posicion(lista, &valor1, 0);
	lista_insertar_en_posicion(lista, &valor2, 1);
	lista_insertar_en_posicion(lista, &valor3, 2);

	size_t tamanio = lista_tamanio(lista);

	pa2m_afirmar(lista_quitar(lista) == &valor3, "Se quitó el elemento en la última posición de la lista.");
	pa2m_afirmar(lista->nodo_fin->elemento != &valor3, "El elemento borrado ya no se encuentra en la lista.");
	pa2m_afirmar(lista->nodo_fin->elemento == &valor2, "El elemento que estaba en la posición anterior al borrado ahora está al final de la lista.");
	pa2m_afirmar(lista_tamanio(lista) == tamanio-1, "El tamaño de la lista es un elemento menos al tamaño previo a quitar el elemento.");

	lista_destruir(lista);
}
/**/
void se_quita_el_primer_elemento_de_la_lista_y_este_deja_de_estar_al_principio()
{
	lista_t *lista = lista_crear();

	int valor1 = 1;
	int valor2 = 2;
	int valor3 = 3;

	lista_insertar_en_posicion(lista, &valor1, 0);
	lista_insertar_en_posicion(lista, &valor2, 1);
	lista_insertar_en_posicion(lista, &valor3, 2);

	size_t tamanio = lista_tamanio(lista);

	pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == &valor1, "Se quitó el elemento en la primera posicion de la lista.");
	pa2m_afirmar(lista->nodo_inicio->elemento != &valor1, "El elemento borrado ya no se encuentra en la lista.");
	pa2m_afirmar(lista->nodo_inicio->elemento == &valor2, "El elemento que estaba en la posición siguiente al borrado ahora está al inicio de la lista.");
	pa2m_afirmar(lista_tamanio(lista) == tamanio-1, "El tamaño de la lista es un elemento menos al tamaño previo a quitar el elemento.");

	lista_destruir(lista);
}

void se_quitan_elementos_en_el_medio_de_la_lista_y_estos_no_se_encuentran_ni_al_principio_ni_al_final()
{
	lista_t *lista = lista_crear();

	int valor1 = 1;
	int valor2 = 2;
	int valor3 = 3;

	lista_insertar_en_posicion(lista, &valor1, 0);
	lista_insertar_en_posicion(lista, &valor2, 1);
	lista_insertar_en_posicion(lista, &valor3, 2);

	size_t tamanio = lista_tamanio(lista);

	pa2m_afirmar(lista_quitar_de_posicion(lista, 1) == &valor2, "Se quitó el elemento de la segunda posición.");
	pa2m_afirmar(lista->nodo_inicio->siguiente->elemento == &valor3, "El elemento que estaba en la tercera posición ahora está en la segunda.");
	pa2m_afirmar(lista_tamanio(lista) == tamanio-1, "La lista tiene un elemento menos de cantidad.");

	lista_destruir(lista);
}

void apilo_y_desapilo_una_pila_correctamente()
{
	lista_t *pila = lista_crear();
	pa2m_afirmar(pila != NULL, "Se puede crear una lista.");

	size_t valor = 0;
	size_t tamanio = 0;

	while(valor < 5) {
		pa2m_afirmar(lista_insertar(pila, &valor) != NULL, "Puedo apilar un elemento.");
		pa2m_afirmar(lista_tamanio(pila) == tamanio+1, "El tamaño de la pila es un elemento mayor.");
		tamanio++;
		valor++;
	}

	while(valor != 0) {
		pa2m_afirmar(lista_quitar(pila) == &valor, "Puedo desapilar un elemento.");
		pa2m_afirmar(lista_tamanio(pila) == tamanio-1, "El tamaño de la pila es un elemento menor.");
		tamanio--;
		valor--;
	}

	lista_destruir(pila);
}

void encolo_y_desencolo_una_cola_correctamente()
{
	lista_t *cola = lista_crear();
	pa2m_afirmar(cola != NULL, "Se puede crear una cola.");

	size_t valor = 0;
	size_t tamanio = 0;

	while(valor < 5) {
		pa2m_afirmar(lista_insertar(cola, &valor) != NULL, "Puedo encolar un elemento.");
		pa2m_afirmar(lista_tamanio(cola) == tamanio+1, "El tamaño de la cola es un elemento mayor.");
		tamanio++;
		valor++;
	}

	while(valor != 0) {
		pa2m_afirmar(lista_quitar_de_posicion(cola, 0) == &valor, "Puedo desencolar un elemento.");
		pa2m_afirmar(lista_tamanio(cola) == tamanio-1, "El tamaño de la cola es un elemento menor.");
		tamanio--;
		valor--;
	}

	lista_destruir(cola);
}

int main() {
	pa2m_nuevo_grupo("Pruebas de creación de lista");

	crear_una_lista_me_devuelve_una_lista_con_cantidad_0();
	crear_una_lista_me_devuelve_un_nodo_inicio_y_nodo_fin_con_elementos_nulos();

	pa2m_nuevo_grupo("Pruebas de inserción en lista");

	insertar_elementos_en_lisa_vacia_devuelve_una_lista_con_la_cantidad_de_elementos_insertados();
	se_inserta_un_elemento_en_una_lista_vacia_entonces_nodo_inicio_y_nodo_fin_apuntan_al_nodo_con_ese_elemento();

	pa2m_nuevo_grupo("Pruebas de inserción en posicion de lista");
	
	se_insertan_elementos_en_el_medio_de_la_lista_y_este_no_se_encuentra_ni_al_principio_ni_al_final();

	pa2m_nuevo_grupo("Pruebas de inserción al final de lista");

	se_insertan_elementos_en_posiciones_inexistentes_de_la_lista_y_cada_uno_pertence_al_final_de_esta();

	pa2m_nuevo_grupo("Pruebas de inserción al principio de lista");

	se_insertan_elementos_en_la_primer_posicion_de_la_lista_y_estos_se_encuentran_al_principio();

	pa2m_nuevo_grupo("Pruebas de borrado en lista");

	borrar_elementos_de_una_lista_vacia_o_inexistente_devuelve_NULL();
	si_se_quita_el_unico_elemento_de_una_lista_nodo_inicio_y_nodo_fin_apuntan_a_NULL_y_el_tamanio_de_la_lista_es_0();

	pa2m_nuevo_grupo("Pruebas de borrado al final de lista");

	si_se_quita_el_ultimo_elemento_de_la_lista_este_deja_de_estar_en_el_final();

	pa2m_nuevo_grupo("Pruebas de borrado al principio de lista");

	se_quita_el_primer_elemento_de_la_lista_y_este_deja_de_estar_al_principio();

	pa2m_nuevo_grupo("Pruebas de borrado en posicion de lista");

	se_quitan_elementos_en_el_medio_de_la_lista_y_estos_no_se_encuentran_ni_al_principio_ni_al_final();

	pa2m_nuevo_grupo("Pruebas de pila");

	apilo_y_desapilo_una_pila_correctamente();

	pa2m_nuevo_grupo("Pruebas de cola");

	encolo_y_desencolo_una_cola_correctamente();

	return pa2m_mostrar_reporte();
}
