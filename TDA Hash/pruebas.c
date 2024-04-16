#include "src/hash.h"
#include "pa2m.h"
#include "string.h"
#include <stdlib.h>

void pruebas_de_creacion()
{
	pa2m_nuevo_grupo("Pruebas de creación de hash");

	hash_t *hash = hash_crear(1);
	pa2m_afirmar(hash != NULL, "Puedo crear un hash con capacidad menor a la mínima.");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash está vacío.");
	hash_destruir(hash);

	hash = hash_crear(100);
	pa2m_afirmar(hash != NULL, "Puedo crear un hash con capacidad 100.");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash está vacío.");
	hash_destruir(hash);

	hash = hash_crear(1000);
	pa2m_afirmar(hash != NULL, "Puedo crear un hash con capacidad 1000.");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash está vacío.");
	hash_destruir(hash);
}

void pruebas_de_insercion_NULL()
{
	pa2m_nuevo_grupo("Pruebas de inserción NULL en hash");

	int elementos[] = {0};
	void *anterior = NULL;

	hash_t *hash = hash_crear(100);

	pa2m_afirmar(hash_insertar(NULL, "A", &elementos[0], &anterior) == NULL, "No puedo insertar un par en un hash inexistente.");
	pa2m_afirmar(!hash_contiene(NULL, "A"), "No se puede buscar un elemento en un hash inexistente.");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash está vacío.");
	pa2m_afirmar(hash_insertar(hash, NULL, &elementos[0], &anterior) == NULL, "No puedo insertar un par con clave NULL en un hash.");
	pa2m_afirmar(hash_insertar(hash, NULL, NULL, &anterior) == NULL, "No puedo insertar un par con clave y valor NULL en un hash válido.");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash sigue vacío.");
	pa2m_afirmar(hash_insertar(hash, "A", NULL, &anterior) == hash, "Se puede insertar un par con valor NULL en un hash.");
	pa2m_afirmar(hash_cantidad(hash) == 1, "El hash no está vacío.");

	hash_destruir(hash);
}

void pruebas_de_insercion()
{
	pa2m_nuevo_grupo("Pruebas de inserción en hash");

	int elementos[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	void *anterior = NULL;

	hash_t *hash = hash_crear(100);

	pa2m_afirmar(hash_insertar(hash, "A", &elementos[0], &anterior) == hash, "Inserto el par <A,1> en un hash vacío.");
	pa2m_afirmar(hash_contiene(hash, "A"), "El hash guardó la clave <A,1>.");
	pa2m_afirmar(*(int *)hash_obtener(hash, "A") == elementos[0], "Cuando se busca la clave A se encuentra el valor 1.");
	pa2m_afirmar(hash_cantidad(hash) == 1, "El hash tiene cantidad 1.");
	printf("\n");
	pa2m_afirmar(hash_insertar(hash, "B", &elementos[1], &anterior) == hash, "Inserto el par <B,2> en un hash no vacío.");
	pa2m_afirmar(hash_contiene(hash, "B"), "El hash guardó la clave B.");
	pa2m_afirmar(*(int *)hash_obtener(hash, "B") == elementos[1], "Cuando se busca la clave B se encuentra el valor 2.");
	pa2m_afirmar(hash_cantidad(hash) == 2, "El hash tiene cantidad 2.");
	printf("\n");
	pa2m_afirmar(hash_insertar(hash, "C", &elementos[2], &anterior) == hash, "Inserto el par <C,3> en un hash no vacío.");
	pa2m_afirmar(hash_contiene(hash, "C"), "El hash guardó la clave C.");
	pa2m_afirmar(*(int *)hash_obtener(hash, "C") == elementos[2], "Cuando se busca la clave C se encuentra el valor 3.");
	pa2m_afirmar(hash_cantidad(hash) == 3, "El hash tiene cantidad 3.");
	printf("\n");
	pa2m_afirmar(hash_insertar(hash, "D", &elementos[3], &anterior) == hash, "Inserto el par <D,4> en un hash no vacío.");
	pa2m_afirmar(hash_contiene(hash, "D"), "El hash guardó la clave D.");
	pa2m_afirmar(*(int *)hash_obtener(hash, "D") == elementos[3], "Cuando se busca la clave D se encuentra el valor 4.");
	pa2m_afirmar(hash_cantidad(hash) == 4, "El hash tiene cantidad 4.");
	printf("\n");
	pa2m_afirmar(hash_insertar(hash, "E", &elementos[4], &anterior) == hash, "Inserto el par <E,5> en un hash no vacío.");
	pa2m_afirmar(hash_contiene(hash, "E"), "El hash guardó la clave E.");
	pa2m_afirmar(*(int *)hash_obtener(hash, "E") == elementos[4], "Cuando se busca la clave E se encuentra el valor 5.");
	pa2m_afirmar(hash_cantidad(hash) == 5, "El hash tiene cantidad 5.");
	printf("\n");
	pa2m_afirmar(hash_insertar(hash, "F", &elementos[5], &anterior) == hash, "Inserto el par <F,6> en un hash no vacío.");
	pa2m_afirmar(hash_contiene(hash, "F"), "El hash guardó la clave F.");
	pa2m_afirmar(*(int *)hash_obtener(hash, "F") == elementos[5], "Cuando se busca la clave F se encuentra el valor 6.");
	pa2m_afirmar(hash_cantidad(hash) == 6, "El hash tiene cantidad 6.");
	printf("\n");
	pa2m_afirmar(hash_insertar(hash, "G", &elementos[6], &anterior) == hash, "Inserto el par <G,7> en un hash no vacío.");
	pa2m_afirmar(hash_contiene(hash, "G"), "El hash guardó la clave G.");
	pa2m_afirmar(*(int *)hash_obtener(hash, "G") == elementos[6], "Cuando se busca la clave G se encuentra el valor 7.");
	pa2m_afirmar(hash_cantidad(hash) == 7, "El hash tiene cantidad 7.");
	printf("\n");
	pa2m_afirmar(hash_insertar(hash, "H", &elementos[7], &anterior) == hash, "Inserto el par <H,8> en un hash no vacío.");
	pa2m_afirmar(hash_contiene(hash, "H"), "El hash guardó la clave H.");
	pa2m_afirmar(*(int *)hash_obtener(hash, "H") == elementos[7], "Cuando se busca la clave H se encuentra el valor 8.");
	pa2m_afirmar(hash_cantidad(hash) == 8, "El hash tiene cantidad 8.");
	printf("\n");
	pa2m_afirmar(hash_insertar(hash, "I", &elementos[8], &anterior) == hash, "Inserto el par <I,9> en un hash no vacío.");
	pa2m_afirmar(hash_contiene(hash, "I"), "El hash guardó la clave I.");
	pa2m_afirmar(*(int *)hash_obtener(hash, "I") == elementos[8], "Cuando se busca la clave I se encuentra el valor 9.");
	pa2m_afirmar(hash_cantidad(hash) == 9, "El hash tiene cantidad 9.");
	printf("\n");
	pa2m_afirmar(hash_insertar(hash, "J", &elementos[9], &anterior) == hash, "Inserto el par <J,10> en un hash no vacío.");
	pa2m_afirmar(hash_contiene(hash, "J"), "El hash guardó la clave J.");
	pa2m_afirmar(*(int *)hash_obtener(hash, "J") == elementos[9], "Cuando se busca la clave J se encuentra el valor 10.");
	pa2m_afirmar(hash_cantidad(hash) == 10, "El hash tiene cantidad 10.");

	hash_destruir(hash);
}

void pruebas_de_eliminacion()
{
	pa2m_nuevo_grupo("Pruebas de eliminación de hash");

	int elementos[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	void *anterior = NULL;

	hash_t *hash = hash_crear(100);

	hash_insertar(hash, "A", &elementos[0], &anterior);

	pa2m_afirmar(hash_quitar(NULL, "A") == NULL, "No puedo quitar una clave de un hash inexistente.");
	pa2m_afirmar(hash_quitar(hash, NULL) == NULL, "No puedo quitar de un hash una clave NULL.");
	hash_quitar(hash, "A");
	printf("\n");
	pa2m_afirmar(hash_insertar(hash, "A", &elementos[0], &anterior) == hash, "Inserto el par <A,1>.");
	pa2m_afirmar(*(int *)hash_quitar(hash, "A") == elementos[0], "Elimino la clave A y devuelve el valor 1.");
	pa2m_afirmar(!hash_contiene(hash, "A"), "La clave eliminada no se encuentra en el hash.");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash está vacío.");
	printf("\n");
	pa2m_afirmar(hash_insertar(hash, "A", &elementos[1], &anterior) == hash, "Inserto el par <A,2>.");
	pa2m_afirmar(*(int *)hash_quitar(hash, "A") == elementos[1], "Elimino la clave A y devuelve el valor 2.");
	pa2m_afirmar(!hash_contiene(hash, "A"), "La clave eliminada no se encuentra en el hash.");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash sigue vacío.");
	printf("\n");
	pa2m_afirmar(hash_insertar(hash, "A", &elementos[0], &anterior) == hash, "Inserto el par <A,1>.");
	pa2m_afirmar(hash_insertar(hash, "A", &elementos[1], &anterior) == hash, "Inserto el par <A,2>.");
	pa2m_afirmar(hash_cantidad(hash) == 1, "El hash tiene un elemento.");
	pa2m_afirmar(*(int *)hash_quitar(hash, "A") == elementos[1], "Elimino la clave A y devuelve el valor 2.");
	pa2m_afirmar(!hash_contiene(hash, "A"), "La clave eliminada no se encuentra en el hash.");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash vuelve a estar vacío.");
	printf("\n");
	pa2m_afirmar(hash_insertar(hash, "A", &elementos[0], &anterior) == hash, "Inserto el par <A,1>.");
	pa2m_afirmar(hash_insertar(hash, "B", &elementos[1], &anterior) == hash, "Inserto el par <B,2>.");
	pa2m_afirmar(hash_cantidad(hash) == 2, "El hash tiene dos elementos.");
	pa2m_afirmar(*(int *)hash_quitar(hash, "A") == elementos[0], "Elimino la clave A y devuelve el valor 1.");
	pa2m_afirmar(!hash_contiene(hash, "A"), "La clave eliminada no se encuentra en el hash.");
	pa2m_afirmar(hash_cantidad(hash) == 1, "El hash tiene un elemento.");
	pa2m_afirmar(*(int *)hash_quitar(hash, "B") == elementos[1], "Elimino la clave B y devuelve el valor 2.");
	pa2m_afirmar(!hash_contiene(hash, "B"), "La clave eliminada no se encuentra en el hash.");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash vuelve a estar vacío.");

	hash_destruir(hash);
}

void pruebas_de_claves_repetidas()
{
	pa2m_nuevo_grupo("Pruebas de claves repetidas en hash");

	int elementos[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	void *anterior = NULL;

	hash_t *hash = hash_crear(100);

	pa2m_afirmar(hash_insertar(hash, "A", &elementos[0], &anterior) == hash, "Inserto el par <A,1> en un hash vacío.");
	pa2m_afirmar(anterior == NULL, "El valor anterior al insertar <A,1> es NULL.");
	pa2m_afirmar(*(int *)hash_obtener(hash, "A") == elementos[0], "Cuando se busca la clave A se encuentra el valor 1.");
	pa2m_afirmar(hash_cantidad(hash) == 1, "El hash tiene cantidad 1.");
	pa2m_afirmar(hash_insertar(hash, "A", &elementos[1], &anterior) == hash, "Inserto el par <A,2>.");
	pa2m_afirmar(*(int *)anterior == elementos[0], "El valor anterior al insertar <A,2> es 1.");
	pa2m_afirmar(hash_cantidad(hash) == 1, "El hash tiene cantidad 1.");
	pa2m_afirmar(*(int *)hash_obtener(hash, "A") == elementos[1], "Cuando se busca la clave A se encuentra el valor 2.");
	pa2m_afirmar(*(int *)hash_quitar(hash, "A") == elementos[1], "Quitar la clave A del hash devuelve el valor 2.");
	pa2m_afirmar(hash_insertar(hash, "A", &elementos[2], &anterior) == hash, "Inserto el par <A,3>.");
	pa2m_afirmar(anterior == NULL, "El valor anterior al insertar <A,3> es NULL.");
	pa2m_afirmar(hash_cantidad(hash) == 1, "El hash tiene cantidad 1.");
	pa2m_afirmar(*(int *)hash_obtener(hash, "A") == elementos[2], "Cuando se busca la clave A se encuentra el valor 3.");
	pa2m_afirmar(hash_insertar(hash, "A", &elementos[3], &anterior) == hash, "Inserto el par <A,4>.");
	pa2m_afirmar(*(int *)anterior == elementos[2], "El valor anterior al insertar <A,4> es 3.");
	pa2m_afirmar(hash_cantidad(hash) == 1, "El hash tiene cantidad 1.");
	pa2m_afirmar(*(int *)hash_obtener(hash, "A") == elementos[3], "Cuando se busca la clave A se encuentra el valor 4.");
	pa2m_afirmar(hash_insertar(hash, "A", &elementos[4], &anterior) == hash, "Inserto el par <A,5>.");
	pa2m_afirmar(*(int *)anterior == elementos[3], "El valor anterior al insertar <A,5> es 4.");
	pa2m_afirmar(hash_cantidad(hash) == 1, "El hash tiene cantidad 1.");
	pa2m_afirmar(*(int *)hash_obtener(hash, "A") == elementos[4], "Cuando se busca la clave A se encuentra el valor 4.");

	hash_destruir(hash);
}

void pruebas_de_rehash()
{
	pa2m_nuevo_grupo("Pruebas de muchas inserciones en hash");

	const char* claves[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
	void *anterior = NULL;

	bool fallo_insercion = false;

	hash_t *hash = hash_crear(2);

	pa2m_afirmar(hash != NULL, "Creo un hash con capacidad mínima.");
	
	for (int i = 0; i < 26; i++){
		if ((hash_insertar(hash, claves[i], &i, &anterior) == NULL))
			fallo_insercion = true;
	}

	pa2m_afirmar(fallo_insercion == false, "Inserto 26 elementos en el hash de capacidad mínima exitosamente.");
	pa2m_afirmar(hash_cantidad(hash) == 26, "El hash contiene 26 elementos.");

	for (int i = 0; i < 26; i++){
		if (!hash_contiene(hash, claves[i]))
			fallo_insercion = true;
	}

	pa2m_afirmar(fallo_insercion == false, "Encuentro los 26 elementos insertados en el hash.");

	hash_destruir(hash);
}

bool seguir_iterando(const char *clave, void *valor, void *aux)
{
	return true;
}

bool no_seguir_iterando(const char *clave, void *valor, void *aux)
{
	return false;
}

void pruebas_de_iterador()
{
	pa2m_nuevo_grupo("Pruebas de iterador interno de hash");

	const char* claves[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
	void *anterior = NULL;

	hash_t *hash = hash_crear(100);

	for (int i = 0; i < 10; i++) 
		hash_insertar(hash, claves[i], &i, &anterior);

	pa2m_afirmar(hash_cantidad(hash) == 10, "Se insertaron 10 pares y ahora el hash tiene cantidad 10.");

	size_t iteraciones = 0;

	iteraciones = hash_con_cada_clave(NULL, seguir_iterando, NULL);

	pa2m_afirmar(iteraciones == 0, "Iterar en un hash inexistente itera 0 veces.");

	iteraciones = hash_con_cada_clave(hash, NULL, NULL);

	pa2m_afirmar(iteraciones == 0, "Iterar sin una función itera 0 veces.");

	iteraciones = hash_con_cada_clave(hash, no_seguir_iterando, NULL);

	pa2m_afirmar(iteraciones == 1, "Iterar con una función que nunca devuelve true devuelve cantidad de iteraciones 1.");

	iteraciones = hash_con_cada_clave(hash, seguir_iterando, NULL);

	pa2m_afirmar(iteraciones != 0, "El iterador recorre todas las claves.");

	pa2m_afirmar(iteraciones == 10, "El iterador cuenta 10 pares correctamente.");

	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de Hash");

	pruebas_de_creacion();
	pruebas_de_insercion_NULL();
	pruebas_de_insercion();
	pruebas_de_eliminacion();
	pruebas_de_claves_repetidas();
	pruebas_de_iterador();
	pruebas_de_rehash();
	
	return pa2m_mostrar_reporte();
}