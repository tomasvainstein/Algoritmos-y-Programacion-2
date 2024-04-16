#include "estructuras.h"
#include "interaccion.h"
#include "objeto.h"
#include "sala.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define MAX_CARACTERES 1024
#define MAX_NOMBRE     20
#define SON_IGUALES    0

void *agregar_objeto(struct objeto ***objeto, int *cantidad_objetos, struct objeto *elemento_a_agregar, FILE* arch_objetos)
{
	struct objeto **objeto_aux = realloc(*objeto, (unsigned)((*cantidad_objetos)+1) * sizeof(struct objeto*));

	if (objeto_aux == NULL) {
		fclose(arch_objetos);
		return NULL;
	}
	objeto_aux[*cantidad_objetos] = elemento_a_agregar;
	(*cantidad_objetos)++;
	*objeto = objeto_aux;

	return objeto_aux;		
}

void *agregar_interaccion(struct interaccion ***interaccion, int *cantidad_interacciones, struct interaccion *elemento_a_agregar, FILE* arch_interacciones)
{
	struct interaccion **interaccion_aux = realloc(*interaccion, (unsigned)((*cantidad_interacciones)+1) * sizeof(struct interaccion));

	if (interaccion_aux == NULL) {
		fclose(arch_interacciones);
		return NULL;
	}
	interaccion_aux[*cantidad_interacciones] = elemento_a_agregar;
	(*cantidad_interacciones)++;
	*interaccion = interaccion_aux;

	return interaccion_aux;
}

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	FILE *arch_objetos = fopen(objetos, "r");
	if (!arch_objetos) {
		printf("No se pudo abrir el archivo de objetos.\n");
		return NULL;
	}

	FILE *arch_interacciones = fopen(interacciones, "r");
	if (!arch_interacciones) {
		fclose(arch_objetos);
		printf("No se pudo abrir el archivo de interacciones.\n");
		return NULL;
	}

	sala_t *sala = malloc(sizeof(sala_t));

	if (sala == NULL)
		return NULL;
	
	char linea[MAX_CARACTERES];

	sala->objetos = NULL;
	sala->cantidad_objetos = 0;

	int leidos = fscanf(arch_objetos, "%[^\n]\n", linea);
	while(leidos == 1) {
		struct objeto *objeto = objeto_crear_desde_string(linea);
		if (objeto != NULL) 
			agregar_objeto(&sala->objetos, &sala->cantidad_objetos, objeto, arch_objetos);
		leidos = fscanf(arch_objetos, "%[^\n]\n", linea);
	}

	fclose(arch_objetos);

	if (sala->cantidad_objetos == 0) {
		free(sala);
		return NULL;
	}

	sala->interacciones = NULL;
	sala->cantidad_interacciones = 0;

	leidos = fscanf(arch_interacciones, "%[^\n]\n", linea);
	while(leidos == 1) {
		struct interaccion *interaccion = interaccion_crear_desde_string(linea);
		if (interaccion != NULL)
			agregar_interaccion(&sala->interacciones, &sala->cantidad_interacciones, interaccion, arch_interacciones);
		leidos = fscanf(arch_interacciones, "%[^\n]\n", linea);
	}

	fclose(arch_interacciones);

	if (sala->cantidad_interacciones == 0) {
		for (int i = 0; i < sala->cantidad_objetos; i++) 
			free(sala->objetos[i]);
		free(sala->objetos);
		free(sala);
		return NULL;
	}
	return sala;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if (sala == NULL) {
		(*cantidad) = -1; 
		return NULL;
	}

	char **vector_nombres = malloc((unsigned) (sala->cantidad_objetos) * sizeof(char*));

	if (vector_nombres == NULL) {
		(*cantidad) = -1; 
		return NULL;
	}

	if (cantidad == NULL) 
		return vector_nombres;
	else
		(*cantidad) = sala->cantidad_objetos;

	for (int i = 0; i < (*cantidad); i++) {
		vector_nombres[i] = sala->objetos[i]->nombre;
	}
	return vector_nombres;
}

bool strings_coinciden(const char* string1, const char* string2)
{
	return(strcmp(string1, string2) == SON_IGUALES);
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,
				const char *objeto2)
{
	bool es_valida = false;

	if (sala == NULL || verbo == NULL || objeto1 == NULL || objeto2 == NULL)
		return es_valida;

	for (int i = 0; i < sala->cantidad_interacciones; i++) {
		if (strings_coinciden(sala->interacciones[i]->objeto, objeto1) && strings_coinciden(sala->interacciones[i]->objeto_parametro, objeto2)
			&& strings_coinciden(sala->interacciones[i]->verbo, verbo)) {
			es_valida = true;
		}
	}
	return es_valida;
}

void sala_destruir(sala_t *sala)
{
	for (int i = 0; i < sala->cantidad_objetos; i++) 
		free(sala->objetos[i]);

	for (int i = 0; i < sala->cantidad_interacciones; i++) 
		free(sala->interacciones[i]);

	free(sala->objetos);
	free(sala->interacciones);
	free(sala);
}
