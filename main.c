#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include "lib/menu.h"
#include "lib/reservas.h"
#include "lib/salas.h"
#include "lib/usuario.h"
#include "lib/bancoDados.h"
#include "lib/utils.h"

int main(void) {
    setlocale(LC_ALL, "Portuguese_Brazil");

    inicializarReservas();
    carregarReservas();  // Load reservations from file before displaying menu
    inicializarSalas();  // Make sure this function exists in salas.c
    inicializarUsuario();  // Make sure this function exists in usuario.c

    iniciarSistema();

    salvarReservas();  // Save reservations before exiting

    atexit(liberarMemoria);

    return 0;
}