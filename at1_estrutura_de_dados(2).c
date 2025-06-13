#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SENSORS 16
#define MAX_ID 32
#define MAX_TYPE 16
#define MAX_LINE 128

typedef enum { T_INT, T_BOOL, T_FLOAT, T_STRING } SensorType;

SensorType parse_type(const char *type) {
    if (strcmp(type, "int") == 0) return T_INT;
    if (strcmp(type, "bool") == 0) return T_BOOL;
    if (strcmp(type, "float") == 0) return T_FLOAT;
    if (strcmp(type, "string") == 0) return T_STRING;
    return T_INT; 
}

void random_string(char *out, int len) {
    static const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; ++i)
        out[i] = charset[rand() % (sizeof(charset) - 1)];
    out[len] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc < 5 || (argc - 3) % 2 != 0) {
        printf("Uso: %s <inicio_epoch> <fim_epoch> <sensor1> <tipo1> [<sensor2> <tipo2> ...]\n", argv[0]);
        return 1;
    }

    long start = atol(argv[1]);
    long end = atol(argv[2]);
    int nsensors = (argc - 3) / 2;

    char sensor_ids[MAX_SENSORS][MAX_ID];
    SensorType sensor_types[MAX_SENSORS];

    for (int i = 0; i < nsensors; ++i) {
        strncpy(sensor_ids[i], argv[3 + i * 2], MAX_ID - 1);
        sensor_ids[i][MAX_ID - 1] = '\0';
        sensor_types[i] = parse_type(argv[4 + i * 2]);
    }

    FILE *f = fopen("amostras_teste.txt", "w");
    if (!f) {
        perror("Erro ao criar arquivo de teste");
        return 1;
    }

    srand((unsigned)time(NULL));

    for (int i = 0; i < nsensors; ++i) {
        for (int j = 0; j < 2000; ++j) {
            long timestamp = start + rand() % (end - start + 1);
            char value[32];
            switch (sensor_types[i]) {
                case T_INT:
                    snprintf(value, sizeof(value), "%d", rand() % 10000 - 5000);
                    break;
                case T_BOOL:
                    snprintf(value, sizeof(value), "%s", rand() % 2 ? "true" : "false");
                    break;
                case T_FLOAT:
                    snprintf(value, sizeof(value), "%.3f", ((float)rand() / RAND_MAX) * 200.0f - 100.0f);
                    break;
                case T_STRING: {
                    int len = 4 + rand() % 13; 
                    random_string(value, len);
                    break;
                }
                default:
                    strcpy(value, "0");
            }
            fprintf(f, "%ld %s %s\n", timestamp, sensor_ids[i], value);
        }
    }

    fclose(f);
    printf("Arquivo 'amostras_teste.txt' gerado com sucesso.\n");
    return 0;
}