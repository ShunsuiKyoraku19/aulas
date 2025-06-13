#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SENSORS 100
#define MAX_ID 32
#define MAX_LINE 128
#define MAX_VALUE 32
#define MAX_TYPE 16
#define MAX_SENSOR_FILE 64

typedef enum { T_INT, T_BOOL, T_FLOAT, T_STRING, T_UNKNOWN } SensorType;

typedef struct {
    long timestamp;
    char value[MAX_VALUE];
} Reading;

typedef struct {
    char id[MAX_ID];
    SensorType type;
    Reading *readings;
    size_t count;
    size_t capacity;
} SensorData;

SensorType detect_type(const char *value) {
    if (strcmp(value, "true") == 0 || strcmp(value, "false") == 0)
        return T_BOOL;
    char *endptr;
    strtol(value, &endptr, 10);
    if (*endptr == '\0') return T_INT;
    strtod(value, &endptr);
    if (*endptr == '\0') return T_FLOAT;
    if (strlen(value) <= 16) return T_STRING;
    return T_UNKNOWN;
}

int compare_readings(const void *a, const void *b) {
    const Reading *ra = (const Reading *)a;
    const Reading *rb = (const Reading *)b;
    return (ra->timestamp > rb->timestamp) - (ra->timestamp < rb->timestamp);
}

int find_sensor(SensorData sensors[], int nsensors, const char *id) {
    for (int i = 0; i < nsensors; ++i)
        if (strcmp(sensors[i].id, id) == 0)
            return i;
    return -1;
}

void add_reading(SensorData *sensor, long timestamp, const char *value) {
    if (sensor->count == sensor->capacity) {
        sensor->capacity = sensor->capacity ? sensor->capacity * 2 : 16;
        sensor->readings = realloc(sensor->readings, sensor->capacity * sizeof(Reading));
    }
    sensor->readings[sensor->count].timestamp = timestamp;
    strncpy(sensor->readings[sensor->count].value, value, MAX_VALUE-1);
    sensor->readings[sensor->count].value[MAX_VALUE-1] = '\0';
    sensor->count++;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }
    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    SensorData sensors[MAX_SENSORS] = {0};
    int nsensors = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fin)) {
        long timestamp;
        char id[MAX_ID], value[MAX_VALUE];
        if (sscanf(line, "%ld %31s %31s", &timestamp, id, value) != 3)
            continue;

        int idx = find_sensor(sensors, nsensors, id);
        if (idx == -1) {
            idx = nsensors++;
            strncpy(sensors[idx].id, id, MAX_ID-1);
            sensors[idx].id[MAX_ID-1] = '\0';
            sensors[idx].type = detect_type(value);
            sensors[idx].readings = NULL;
            sensors[idx].count = 0;
            sensors[idx].capacity = 0;
        }
        add_reading(&sensors[idx], timestamp, value);
    }
    fclose(fin);

    // Ordena e salva cada sensor em arquivo separado
    for (int i = 0; i < nsensors; ++i) {
        qsort(sensors[i].readings, sensors[i].count, sizeof(Reading), compare_readings);
        char fname[MAX_SENSOR_FILE];
        snprintf(fname, sizeof(fname), "%s.txt", sensors[i].id);
        FILE *fout = fopen(fname, "w");
        if (!fout) continue;
        for (size_t j = 0; j < sensors[i].count; ++j)
            fprintf(fout, "%ld %s %s\n", sensors[i].readings[j].timestamp, sensors[i].id, sensors[i].readings[j].value);
        fclose(fout);
        free(sensors[i].readings);
    }
    return 0;
}