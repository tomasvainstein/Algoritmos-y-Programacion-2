#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "lista.h"

struct sala {
	hash_t *objetos;
	hash_t *objetos_conocidos;
	hash_t *objetos_poseidos;
	lista_t *lista_de_objetos;
	lista_t *interacciones;
	bool escape_exitoso;
};