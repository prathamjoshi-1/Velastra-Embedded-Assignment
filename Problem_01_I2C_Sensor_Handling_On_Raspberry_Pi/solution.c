#include <stdio.h> // printing logs
#include <stdlib.h> // rand() and srand()
#include <time.h> // for timestamp
#include <stdint.h> // Fixed size types like for data register should be of 16 bit uint16_t

// Here we are using windows thats why we are using sleep() otherwise if we use linux we use usleep()
#ifdef _WIN32
#include <windows.h>
#define sleep_ms(x) Sleep(x)
#else
#include <unistd.h>
#define sleep_ms(x) usleep((x) * 1000)
#endif

typedef enum {
    STATE_OPERATIONAL,
    STATE_RECOVERING
} SystemState;

typedef enum {
    SENSOR_OK = 0,
    I2C_TIMEOUT,
    INVALID_DATA,
    SENSOR_DISCONNECTED
} SensorStatus;

typedef struct {
    uint8_t config_reg;
    uint16_t data_reg;
    uint8_t status_reg;
    int is_connected;
} MockSensor;

// Timestamp function
void get_timestamp(char *buf) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buf, 20, "%H:%M:%S", t);
}

SensorStatus sensor_read(MockSensor *s) {
    if (!s->is_connected)
        return SENSOR_DISCONNECTED;

    int r = rand() % 20;

    if (r == 0)
        return I2C_TIMEOUT;

    if (r == 1) {
        s->is_connected = 0;
        return SENSOR_DISCONNECTED;
    }

    // Simulate reading 16-bit register
    s->data_reg = rand() % 0xFFFF;

    if (s->data_reg == 0xFFFF)
        return INVALID_DATA;

    return SENSOR_OK;
}

int main() {
    MockSensor sensor;
    SystemState state = STATE_OPERATIONAL;
    char ts[20];

    // Proper initialization
    sensor.is_connected = 1;
    sensor.config_reg = 0;
    sensor.data_reg = 0;
    sensor.status_reg = 0;

    srand((unsigned)time(NULL));

    printf("Starting Sensor Controller...\n");

    while (1) {
        get_timestamp(ts);

        if (state == STATE_OPERATIONAL) {
            SensorStatus status = sensor_read(&sensor);

            if (status == SENSOR_OK) {
                printf("[%s] DATA: %u\n", ts, sensor.data_reg);
            }
            else if (status == SENSOR_DISCONNECTED) {
                printf("[%s] ALARM: Sensor Lost! Entering Recovery...\n", ts);
                state = STATE_RECOVERING;
            }
            else {
                printf("[%s] ERROR: Code %d\n", ts, status);
            }
        }
        else if (state == STATE_RECOVERING) {
            if (rand() % 5 == 0) {
                sensor.is_connected = 1;
                state = STATE_OPERATIONAL;
                printf("[%s] RECOVERY: Sensor Re-initialized.\n", ts);
            }
            else {
                printf("[%s] RECOVERY: Still waiting for sensor...\n", ts);
            }
        }

        sleep_ms(500); // 500 ms delay
    }

    return 0;
}
