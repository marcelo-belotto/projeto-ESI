#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/menu.h"
#include "../lib/usuario.h"
#include "../lib/salas.h"
#include "../lib/reservas.h"
#include "../lib/utils.h"

struct Usuario *usuarioTemp = NULL;

void iniciarSistema() {
    inicializarUsuario();
    logarMenu();
}

void logarMenu() {
    char password[50];
    int matricula;
    pUser usuarios[MAX_USUARIOS] = {NULL};
    int numUsuarios;

    printf("=== Sistema de Reserva de Sala de Reunião ===\n");
    printf("Digite sua matrícula: ");
    scanf("%d", &matricula);
    clearInputBuffer(); // Limpa o buffer do teclado
    printf("Digite sua senha: ");
    scanf("%49s", password);
    clearInputBuffer();

    // Carrega todos os usuários do arquivo
    numUsuarios = carregarTodosUsuarios(usuarios);

    // Procura o usuário com a matrícula fornecida
    pUser usuarioEncontrado = NULL;
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i]->matricula == matricula) {
            usuarioEncontrado = usuarios[i];
            break;
        }
    }

    // Verifica se o usuário foi encontrado e se a senha está correta
    if (usuarioEncontrado != NULL && strcmp(usuarioEncontrado->senha, password) == 0) {
        printf("Login bem-sucedido para o usuário: %s\n", usuarioEncontrado->nome);

        // Copia os dados do usuário encontrado para usuarioTemp
        usuarioTemp = (struct Usuario *)malloc(sizeof(struct Usuario));
        if (usuarioTemp == NULL) {
            printf("Erro ao alocar memória para usuarioTemp.\n");
            return;
        }
        *usuarioTemp = *usuarioEncontrado;

        // Verifica o perfil do usuário e exibe o menu apropriado
        if (strcmp(usuarioTemp->perfil, "ADM") == 0) {
            exibirMenuADM();
        } else {
            exibirMenuPadrao();
        }
    } else {
        printf("Falha na autenticação. Matrícula ou senha incorretos.\n");
    }

    // Libera a memória alocada para os usuários carregados
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i] != NULL) {
            free(usuarios[i]);
        }
    }
}

void exibirMenuPadrao() {
    int opcao;
    do {
        printf("\n=== Sistema de Reserva de Sala de Reunião ===\n");
        printf("1. Reservar sala\n");
        printf("2. Cancelar reserva\n");
        printf("3. Listar salas\n");
        printf("4. Sair\n");
        opcao = obterOpcao();
        switch(opcao) {
            case 1:
                listarSalas();
                fazerReserva(usuarioTemp);
                break;
            case 2:
                cancelarReserva();
                break;
            case 3:
                listarSalas();
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 4);
}

void exibirMenuADM() {
    int opcao;
    do {
        printf("\n=== Sistema de Reserva de Sala de Reunião (ADMIN) ===\n");
        printf("1. Reservar sala\n");
        printf("2. Cancelar reserva\n");
        printf("3. Listar reservas\n");
        printf("4. Excluir usuário\n");
        printf("5. Alterar usuário\n");
        printf("6. Gerenciar salas\n");
        printf("7. Sair\n");
        opcao = obterOpcao();
        switch(opcao) {
            case 1:
                fazerReserva(usuarioTemp);
                break;
            case 2:
                cancelarReserva();
                break;
            case 3:
                listarReservas();
                break;
            case 4:
                excluirUsuario();
                break;
            case 5:
                alterarUsuario();
                break;
            case 6:
                gerenciarSalas();
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 7);
}

int obterOpcao() {
    int opcao;
    char buffer[10];
    printf("Escolha uma opção: ");
    do {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erro na leitura da opção.\n");
            continue;
        }
        if (sscanf(buffer, "%d", &opcao) != 1) {
            printf("Valor inserido incorreto, digite novamente!\n");
        }
    } while (sscanf(buffer, "%d", &opcao) != 1);
    return opcao;
}

void liberarMemoria() {
    if (usuarioTemp != NULL) {
        free(usuarioTemp);
        usuarioTemp = NULL;
    }
}
