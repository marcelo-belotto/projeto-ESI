#include "./tests/tests-src/unity.h""
#include "../src/reservaDB.c"
#include <stdio.h>
#include <string.h>

void setUp(void) {
    // Set up any necessary test fixtures
}

void tearDown(void) {
    // Clean up after each test
}

void test_carregarIndiceReservas(void) {
    // Test case 1: Empty file
    FILE *emptyFile = fopen("empty_test.csv", "w");
    fclose(emptyFile);
    TEST_ASSERT_EQUAL_INT(0, carregarIndiceReservas("empty_test.csv"));

    // Test case 2: File with header only
    FILE *headerFile = fopen("header_test.csv", "w");
    fprintf(headerFile, "id,idUsuario,numeroSala,dataInicio,horaInicio,dataFinal,horaFinal,status\n");
    fclose(headerFile);
    TEST_ASSERT_EQUAL_INT(0, carregarIndiceReservas("header_test.csv"));

    // Test case 3: File with one valid entry
    FILE *oneEntryFile = fopen("one_entry_test.csv", "w");
    fprintf(oneEntryFile, "id,idUsuario,numeroSala,dataInicio,horaInicio,dataFinal,horaFinal,status\n");
    fprintf(oneEntryFile, "1,100,201,2023-05-20,14:00,2023-05-20,15:00,1\n");
    fclose(oneEntryFile);
    TEST_ASSERT_EQUAL_INT(1, carregarIndiceReservas("one_entry_test.csv"));

    // Clean up test files
    remove("empty_test.csv");
    remove("header_test.csv");
    remove("one_entry_test.csv");
}

void test_salvarNovaReserva(void) {
    reserva novaReserva = {
        .id = 1,
        .idUsuario = 100,
        .numeroSala = 201,
        .dataInicio = "2023-05-20",
        .horaInicio = "14:00",
        .dataFinal = "2023-05-20",
        .horaFinal = "15:00",
        .status = 1
    };

    // Test case 1: Successful save
    TEST_ASSERT_EQUAL_INT(1, salvarNovaReserva(&novaReserva));

    // Test case 2: Failed save (id = 0)
    novaReserva.id = 0;
    TEST_ASSERT_EQUAL_INT(0, salvarNovaReserva(&novaReserva));

    // Clean up test file
    remove(PATH_RESERVA);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_carregarIndiceReservas);
    RUN_TEST(test_salvarNovaReserva);
    return UNITY_END();
}