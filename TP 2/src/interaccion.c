#include "estructuras.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

#define MAX_ACCION 1020
#define LECTURA "%[^;];%[^;];%[^;];%[^\n]"
#define LECTURA_ACCION "%c:%[^:]:%[^\n]"
#define SON_IGUALES 0

void asignar_accion(struct interaccion *interaccion, char tipo_accion)
{
	if (tipo_accion == 'd') 
		interaccion->accion.tipo = DESCUBRIR_OBJETO;
	else if (tipo_accion == 'e') 
		interaccion->accion.tipo = ELIMINAR_OBJETO;
	else if (tipo_accion == 'r') 
		interaccion->accion.tipo = REEMPLAZAR_OBJETO;
	else if (tipo_accion == 'm') 
		interaccion->accion.tipo = MOSTRAR_MENSAJE;
	else if (tipo_accion == 'g')
		interaccion->accion.tipo = ESCAPAR;
	else 
		interaccion->accion.tipo = ACCION_INVALIDA;
}

struct interaccion *interaccion_crear_desde_string(const char *string)
{
	if (!string) 
		return NULL;

	char accion[MAX_ACCION];
	char tipo_accion;

	struct interaccion *interaccion = malloc(sizeof(struct interaccion));

	if (!interaccion)
		return NULL;

	int leidos = sscanf(string, LECTURA, interaccion->objeto, interaccion->verbo, interaccion->objeto_parametro, accion);

	
	if (leidos != 4) {
		free(interaccion);
		return NULL;
	}

	if (strcmp(interaccion->objeto_parametro, "_") == SON_IGUALES) 
		strcpy(interaccion->objeto_parametro, "");

	leidos = sscanf(accion, LECTURA_ACCION, &tipo_accion, interaccion->accion.objeto, interaccion->accion.mensaje);

	if (leidos != 3) {
		free(interaccion);
		return NULL;
	}

	if (strcmp(interaccion->accion.objeto, "_") == SON_IGUALES) 
		strcpy(interaccion->accion.objeto, "");

	asignar_accion(interaccion, tipo_accion);

	return interaccion;
}