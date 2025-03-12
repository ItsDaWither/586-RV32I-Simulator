#include <stdint.h>

uint32_t add(uint32_t a, uint32_t b);

int main() {
    uint32_t x = 10;
    uint32_t y = 20;
    uint32_t sum = add(x, y);
    return 0;
}

uint32_t add(uint32_t a, uint32_t b) {
    return a + b;
}
