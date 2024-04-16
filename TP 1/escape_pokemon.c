#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>

/*
* Procedimiento que se encarga de imprimir la validez de las interacción
* recibida.
*/
void validar_interacciones(sala_t* sala, const char *verbo, const char *objeto1,
				const char *objeto2, const char *string_interaccion)
{
	if (sala_es_interaccion_valida(sala, verbo, objeto1, objeto2))
		printf("%s: Válido\n", string_interaccion);
	else 
		printf("%s: Inválido\n", string_interaccion);
}

int main(int argc, char *argv[])
{
	if (argc == 3) {
		//Los archivos deben venir como parámetros del main
		sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);
	
		if (sala == NULL) {
			printf("Error al crear la sala de escape\n");
			return -1;
		}
	
		//Mostrar todos los objetos en la sala
	
		printf("Objetos...\n");

		int cantidad = 0;

		char **vector_nombres = sala_obtener_nombre_objetos(sala, &cantidad);
		for (int i = 0; i < cantidad; i++){
			printf("%i: %s\n", i, vector_nombres[i]);
		}

		free(vector_nombres);
	
		//Mostrar si son válidas las siguientes interacciones
		//1. examinar habitacion
		//2. abrir pokebola
		//3. usar llave cajon
		//4. quemar mesa
	
		printf("\nInteracciones...\n");

		validar_interacciones(sala, "examinar", "habitacion", "", "Examinar la habitación");
		validar_interacciones(sala, "abrir", "pokebola", "", "Abrir pokebola");
		validar_interacciones(sala, "usar", "llave", "cajon", "Usar la llave en el cajón");
		validar_interacciones(sala, "quemar", "mesa", "", "Quemar la mesa");

		sala_destruir(sala);
	
		return 0;
	}
	return -1;
}