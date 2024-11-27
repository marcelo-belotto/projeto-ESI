#ifndef MENU_H
#define MENU_H

#include "utils.h"
#include "usuario.h"
#include "salas.h"
#include "reservas.h"
#include "reservaDB.h"

typedef struct Usuario usuario;
typedef usuario *pUsuario;

void logarMenu();

void exibirMenuPadrao();

void exibirMenuADM();

#endif // MENU_H