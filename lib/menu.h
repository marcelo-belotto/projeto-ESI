#ifndef MENU_H
#define MENU_H

#include "usuario.h"
#include "utils.h"
#include "reservas.h"
#include "salas.h"

void iniciarSistema();

void logarMenu();

void exibirMenuPadrao();

void exibirMenuADM();

int obterOpcao();

void liberarMemoria();

#endif // MENU_H