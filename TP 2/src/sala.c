#include "estructuras.h"
#include "interaccion.h"
#include "objeto.h"
#include "sala.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "hash.h"
#include "lista.h"

#define MAX_CARACTERES 1024
#define MAX_NOMBRE 20
#define SON_IGUALES 0
#define CAPACIDAD_INICIAL 4
#define ERROR -1
#define EXITO 0

struct sala {
	hash_t *objetos;
	hash_t *objetos_conocidos;
	hash_t *objetos_poseidos;
	lista_t *lista_de_objetos;
	lista_t *interacciones;
	bool escape_exitoso;
};

typedef struct array {
	void **vector;
	int tamanio;
	int contador;
} array_t;

size_t cantidad_de_objetos(sala_t *sala)
{
	return hash_cantidad(sala->objetos);
}

size_t cantidad_de_objetos_poseidos(sala_t *sala)
{
	return hash_cantidad(sala->objetos_poseidos);
}

size_t cantidad_de_objetos_conocidos(sala_t *sala)
{
	return hash_cantidad(sala->objetos_conocidos);
}

size_t cantidad_de_interacciones(sala_t *sala)
{
	return lista_tamanio(sala->interacciones);
}

bool strings_coinciden(const char* string1, const char* string2)
{
	return strcmp(string1, string2) == SON_IGUALES;
}

void *inicializar_sala(sala_t *sala)
{
	sala->escape_exitoso = false;
	sala->objetos = hash_crear(CAPACIDAD_INICIAL);
	sala->objetos_conocidos = hash_crear(CAPACIDAD_INICIAL);
	sala->objetos_poseidos = hash_crear(CAPACIDAD_INICIAL);
	sala->lista_de_objetos = lista_crear();
	sala->interacciones = lista_crear();

	if (!sala->objetos
		|| !sala->interacciones
		|| !sala->objetos_poseidos
		|| !sala->objetos_conocidos 
		|| !sala->lista_de_objetos) {
		sala_destruir(sala);
		return NULL;
	}
	return sala;
}

void agregar_objetos(sala_t *sala, FILE *arch_objetos)
{
	char linea[MAX_CARACTERES];
	bool es_primer_elemento = true;

	int leidos = fscanf(arch_objetos, "%[^\n]\n", linea);
	while(leidos == 1) {
		struct objeto *objeto = objeto_crear_desde_string(linea);
		if (objeto) {
			hash_insertar(sala->objetos, objeto->nombre, objeto, NULL);
			lista_insertar(sala->lista_de_objetos, objeto);
			if (es_primer_elemento) {
				hash_insertar(sala->objetos_conocidos, objeto->nombre, objeto, NULL);
				es_primer_elemento = false;
			}
		}
		leidos = fscanf(arch_objetos, "%[^\n]\n", linea);
	}
	fclose(arch_objetos);
}

void agregar_interacciones(sala_t *sala, FILE *arch_interacciones)
{
	char linea[MAX_CARACTERES];

	int leidos = fscanf(arch_interacciones, "%[^\n]\n", linea);
	while(leidos == 1) {
		struct interaccion *interaccion = interaccion_crear_desde_string(linea);
		if (interaccion) 
			lista_insertar(sala->interacciones, interaccion);
		leidos = fscanf(arch_interacciones, "%[^\n]\n", linea);
	}
	fclose(arch_interacciones);
}

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
    sala_t *sala = malloc(sizeof(sala_t));

	if (!sala || !objetos || !interacciones)
		return NULL;

	if (!inicializar_sala(sala))
		return NULL;
		
   	FILE *arch_objetos = fopen(objetos, "r");
	if (!arch_objetos) {
		sala_destruir(sala);
		return NULL;
	}

	FILE *arch_interacciones = fopen(interacciones, "r");
	if (!arch_interacciones) {
		sala_destruir(sala);
		fclose(arch_objetos);
		return NULL;
	}

	agregar_objetos(sala, arch_objetos);
	if (cantidad_de_objetos(sala) == 0) {
		sala_destruir(sala);
		fclose(arch_interacciones);
		return NULL;
	}

	agregar_interacciones(sala, arch_interacciones);
	if (cantidad_de_interacciones(sala) == 0) {
		sala_destruir(sala);
		return NULL;
	}

	return sala;
}

bool agregar_al_vector_de_nombres(const char *clave, void *valor, void *aux)
{
	array_t *array = aux;
	array->vector[array->contador] = (char *)clave;
	array->contador++;

	return true;
}

char **sala_obtener_nombre(int *cantidad, hash_t *hash, int cantidad_objetos)
{
	char **vector_nombres = malloc((unsigned)cantidad_objetos * sizeof(char *));
	if (!vector_nombres) {
		if (cantidad)
			(*cantidad) = -1; 
		return NULL;
	}

	array_t array;
	array.vector = (void *)vector_nombres;
	array.tamanio = cantidad_objetos;
	array.contador = 0;

	hash_con_cada_clave(hash, agregar_al_vector_de_nombres, &array);

	if (cantidad) 
		(*cantidad) = cantidad_objetos;

	return vector_nombres;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if (!sala) {
		if (cantidad)
			(*cantidad) = -1; 
		return NULL;
	}

	int cantidad_objetos = (int)cantidad_de_objetos(sala);

	return sala_obtener_nombre(cantidad, sala->objetos, cantidad_objetos);
}

char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{
	if (!sala) {
		if (cantidad)
			(*cantidad) = -1; 
		return NULL;
	}

	int cantidad_objetos_conocidos = (int)cantidad_de_objetos_conocidos(sala);

	return sala_obtener_nombre(cantidad, sala->objetos_conocidos, cantidad_objetos_conocidos);
}

char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{
	if (!sala) {
		if (cantidad)
			(*cantidad) = -1; 
		return NULL;
	}

	int cantidad_objetos_poseidos = (int)cantidad_de_objetos_poseidos(sala);

	return sala_obtener_nombre(cantidad, sala->objetos_poseidos, cantidad_objetos_poseidos);
}

bool objeto_visible(sala_t *sala, const char *nombre_objeto)
{
	return hash_contiene(sala->objetos_conocidos, nombre_objeto)
	|| hash_contiene(sala->objetos_poseidos, nombre_objeto)
	|| strings_coinciden(nombre_objeto, "");
}

bool posee_objeto(sala_t *sala, const char *nombre_objeto)
{
	return !hash_contiene(sala->objetos_conocidos, nombre_objeto)
	|| hash_contiene(sala->objetos_poseidos, nombre_objeto);
}

bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
{
	if (!sala || !nombre_objeto)
		return false;

	if (posee_objeto(sala, nombre_objeto))
		return false;

	struct objeto *objeto = (struct objeto *)hash_obtener(sala->objetos, nombre_objeto);
	if (objeto) {
		if (objeto->es_asible) {
			hash_quitar(sala->objetos_conocidos, nombre_objeto);
			hash_insertar(sala->objetos_poseidos, nombre_objeto, objeto, NULL);
			return true;
		}
	}
	return false;
}

char* sala_describir_objeto(sala_t* sala, const char *nombre_objeto)
{
	if (!sala || !nombre_objeto)
		return NULL;

	if (!objeto_visible(sala, nombre_objeto))
		return NULL;

	struct objeto *objeto = (struct objeto *)hash_obtener(sala->objetos, nombre_objeto);
	if (!objeto)
		return NULL;

	return objeto->descripcion;
}

bool verificar_interaccion(struct interaccion *interaccion, const char *verbo, const char *objeto1,
				const char *objeto2)
{
	return (strings_coinciden(interaccion->objeto, objeto1)
		&& strings_coinciden(interaccion->objeto_parametro, objeto2)
		&& strings_coinciden(interaccion->verbo, verbo));
}

int eliminar_objeto(sala_t *sala, struct interaccion *interaccion)
{
	if(posee_objeto(sala, interaccion->objeto)){
		hash_quitar(sala->objetos, interaccion->objeto);
		hash_quitar(sala->objetos_poseidos, interaccion->objeto);
		return 1;
	}
	else {
		hash_quitar(sala->objetos, interaccion->objeto);
		hash_quitar(sala->objetos_conocidos, interaccion->objeto);
		return 1;
	}
				
	return 0;
}

int descubrir_objeto(sala_t *sala, struct interaccion *interaccion)
{
	if (objeto_visible(sala, interaccion->objeto)
		&& objeto_visible(sala, interaccion->objeto_parametro)) {
		struct objeto *objeto = hash_obtener(sala->objetos, interaccion->accion.objeto);
		if (objeto && !objeto_visible(sala, interaccion->accion.objeto)) {
			hash_insertar(sala->objetos_conocidos, interaccion->accion.objeto, objeto, NULL);
			return 1;
		}
	}
	return 0;
}

int escapar(sala_t *sala, struct interaccion *interaccion)
{
	if (hash_contiene(sala->objetos_conocidos, interaccion->objeto)) {
		sala->escape_exitoso = true;
		return 1;
	}
	return 0;
}

int reemplazar_objeto(sala_t *sala, struct interaccion *interaccion)
{
	if (objeto_visible(sala, interaccion->objeto_parametro)) {
		hash_quitar(sala->objetos, interaccion->objeto_parametro);
		hash_quitar(sala->objetos_poseidos, interaccion->objeto_parametro);
		hash_quitar(sala->objetos_conocidos, interaccion->objeto_parametro);
		struct objeto *objeto = hash_obtener(sala->objetos, interaccion->accion.objeto);
		if (objeto) {
			hash_insertar(sala->objetos_conocidos, interaccion->accion.objeto, objeto, NULL);
			return 1;
		}
	}
	return 0;
}

int ejecutar_interaccion(sala_t *sala, struct interaccion *interaccion,
			      void (*mostrar_mensaje)(const char *mensaje,
						      enum tipo_accion accion,
						      void *aux),
			      void *aux)
{
	if (interaccion->accion.tipo == ACCION_INVALIDA)
		return 0;
	else if (interaccion->accion.tipo == MOSTRAR_MENSAJE) {
		if(objeto_visible(sala, interaccion->objeto) && mostrar_mensaje)
			return 1;
	}
	else if (interaccion->accion.tipo == ELIMINAR_OBJETO)
		return eliminar_objeto(sala, interaccion);
	else if (interaccion->accion.tipo == DESCUBRIR_OBJETO)
		return descubrir_objeto(sala, interaccion);
	else if (interaccion->accion.tipo == ESCAPAR)
		return escapar(sala, interaccion);
	else if (interaccion->accion.tipo == REEMPLAZAR_OBJETO)
		return reemplazar_objeto(sala, interaccion);
	return 0;
}

int sala_ejecutar_interaccion(sala_t *sala, const char *verbo,
			      const char *objeto1, const char *objeto2,
			      void (*mostrar_mensaje)(const char *mensaje,
						      enum tipo_accion accion,
						      void *aux),
			      void *aux)
{
	if (!sala || !verbo || !objeto1 || !objeto2)
		return ERROR;

	int ejecuciones = 0;
	int se_ejecuto = 0;

	lista_iterador_t *iterador = lista_iterador_crear(sala->interacciones);
	while (lista_iterador_tiene_siguiente(iterador)) {
		struct interaccion *interaccion = lista_iterador_elemento_actual(iterador);

		if (verificar_interaccion(interaccion, verbo, objeto1, objeto2)) {
			se_ejecuto = ejecutar_interaccion(sala, interaccion, mostrar_mensaje, aux);

			if (se_ejecuto == 1 && mostrar_mensaje)
				mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);

			ejecuciones += se_ejecuto;
		}
		lista_iterador_avanzar(iterador);
	}
	lista_iterador_destruir(iterador);

	return ejecuciones;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,
				const char *objeto2)
{
	bool es_valida = false;

	if (!sala || !verbo || !objeto1 || !objeto2)
		return es_valida;

	lista_iterador_t *iterador = lista_iterador_crear(sala->interacciones);
	if (!iterador)
		return NULL;

	while (lista_iterador_tiene_siguiente(iterador) && !es_valida) {
		struct interaccion *interaccion = 
		(struct interaccion *)lista_iterador_elemento_actual(iterador);

		if (verificar_interaccion(interaccion, verbo, objeto1, objeto2)) 
			es_valida = true;

		lista_iterador_avanzar(iterador);
	}
	lista_iterador_destruir(iterador);
	return es_valida;
}

bool sala_escape_exitoso(sala_t *sala)
{
	if (!sala)
		return false;
	return sala->escape_exitoso;
}

void sala_destruir(sala_t *sala)
{
	if (!sala)
		return;

	hash_destruir(sala->objetos);
	hash_destruir(sala->objetos_poseidos);
	hash_destruir(sala->objetos_conocidos);
	lista_destruir_todo(sala->lista_de_objetos, free);
	lista_destruir_todo(sala->interacciones, free);

	free(sala);
}