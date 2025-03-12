#include <stdint.h>

int main() {
    uint32_t a = 10;
    uint32_t b = 20;
    uint32_t result = 0;

    if (a < b) {
        result = 1;
    } else {
        result = 2;
    }

    return 0;
}
