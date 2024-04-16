#include "objeto.h"
#include "estructuras.h"
#include <stdlib.h>
#include "string.h"
#include <stdio.h>

#define LECTURA     "%[^;];%[^;];%[^\n]"
#define MAX_FLAG    6
#define SON_IGUALES 0


/*
* Devuelve true si el string recibido coincide con el string "true" o "false", 
* devuelve false si esto no ocurre.
*/
bool string_valido(const char *string)
{
	return((strcmp(string, "true") == SON_IGUALES) || (strcmp(string, "false") == SON_IGUALES));
}

struct objeto *objeto_crear_desde_string(const char *string)
{
	if (string == NULL) 
		return NULL;
	
	char flag[MAX_FLAG]; 

	struct objeto *objeto_aux = malloc(sizeof(struct objeto));

	if (objeto_aux == NULL) {
		free(objeto_aux); 
		return NULL;
	}

	int leidos = sscanf(string, LECTURA, objeto_aux->nombre, objeto_aux->descripcion, flag);

	if ((leidos != 3) || !(string_valido(flag))) {
		free(objeto_aux);
		return NULL;
	}

	if ((strcmp(flag, "false") == SON_IGUALES))
		objeto_aux->es_asible = false;
	else if ((strcmp(flag, "true") == SON_IGUALES))
		objeto_aux->es_asible = true;

	return objeto_aux;
}