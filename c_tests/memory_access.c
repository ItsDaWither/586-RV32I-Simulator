#include <stdint.h>

uint32_t data[10];

int main() {
    data[0] = 10;
    data[1] = 20;
    uint32_t sum = data[0] + data[1];
    return 0;
}
