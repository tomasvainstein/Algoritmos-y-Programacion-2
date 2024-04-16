#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define MAX_CARACTERES 1024
#define LECTURA "%s %s %s"
#define SON_IGUALES 0
#define MAX_TEXTO 200
#define ERROR -1
#define KRED "\x1B[31m"

bool coinciden(const char* string1, const char* string2)
{
	return strcmp(string1, string2) == SON_IGUALES;
}

void mostrar_mensaje(const char *mensaje, enum tipo_accion accion, void *aux)
{
	printf("%s\n\n", mensaje);
}

void imprimir_objetos_conocidos(sala_t *sala)
{
	int cantidad = 0;

	char **vector_nombres = sala_obtener_nombre_objetos_conocidos(sala, &cantidad);
	printf("Objetos conocidos:\n");
	for (int i = 0; i < cantidad; i++)
		printf("%i: %s\n", i, vector_nombres[i]);
	printf("\n");

	free(vector_nombres);
}

void imprimir_objetos_poseidos(sala_t *sala)
{
	int cantidad = 0;

	char **vector_nombres = sala_obtener_nombre_objetos_poseidos(sala, &cantidad);
	printf("Objetos poseídos:\n");
	for (int i = 0; i < cantidad; i++)
		printf("%i: %s\n", i, vector_nombres[i]);
	printf("\n");

	free(vector_nombres);
}

char *leer_linea(char *memoria, size_t tamanio_memoria, FILE *archivo)
{
	char *linea_leida = NULL;

	linea_leida = fgets(memoria, (int)tamanio_memoria, archivo);
	if (!linea_leida)
		return NULL;

	size_t posicion_cero = strlen(memoria);

	if (posicion_cero == 0 || memoria[posicion_cero-1] != '\n') {
		char descartar[MAX_CARACTERES];
		leer_linea(descartar, MAX_CARACTERES, archivo);
	}
	memoria[posicion_cero-1] = 0;

	return memoria;
}

int main(int argc, char *argv[])
{
	if (argc != 3) 
		return -1;

	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);
	if (!sala) {
		printf("Error al crear la sala de escape\n");
		return -1;
	}

	char linea[MAX_CARACTERES] = "";
	char comando[MAX_CARACTERES] = "";
	char objeto1[MAX_CARACTERES] = "";
	char objeto2[MAX_CARACTERES] = "";
	bool termino_juego = false;
	char *descripcion = "";

	while (!termino_juego) {
		printf("%sJUGANDO ESCAPE POKÉMON: Utilice lo nesario para escapar de la sala\n\n", KRED);

		imprimir_objetos_conocidos(sala);
		imprimir_objetos_poseidos(sala);

		char *lectura = leer_linea(linea, MAX_CARACTERES, stdin);
		if (!lectura)
			return -1;

		if (system("clear") == ERROR)
			return ERROR;

		int leidos = sscanf(linea, LECTURA, comando, objeto1, objeto2);

		if (leidos == 1) {
			if (coinciden(comando, "ayuda")) {
				printf("Los comandos disponibles son:\n\
					- ayuda: ver los comandos disponibles.\n\
					- agarrar <objeto>: agarrar algún objeto conocido.\n\
					- describir <objeto>: describe algún objeto conocido.\n\
					- salir: finaliza el juego.\n\n");
			}
			else if (coinciden(comando, "salir"))
				break;
			else printf("No se puede hacer eso...\n");
		}
		else if (leidos == 2) {
			if (coinciden(comando, "agarrar"))
				sala_agarrar_objeto(sala, objeto1);
			else if (coinciden(comando, "describir")) {
				descripcion = sala_describir_objeto(sala, objeto1);
				if (!descripcion)
					printf("No tenés ese objeto.");
				else printf("%s\n", descripcion);
			}
		}
		else printf("No se puede hacer eso...\n");

		if (leidos >= 2 && !coinciden(comando, "") && !coinciden(objeto1, "")) {
			if (sala_ejecutar_interaccion(sala, comando, objeto1, objeto2, mostrar_mensaje, NULL) == 0)
				printf("No se puede hacer eso...\n");
		}
		termino_juego = sala_escape_exitoso(sala);
	}
	if (sala_escape_exitoso(sala) == true)
		printf("GANASTE\n");
	else printf("PERDISTE\n");

	sala_destruir(sala);
	
	return 0;
}