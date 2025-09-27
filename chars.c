#include <stdio.h>

#define ASCII_PALETTE_SIZE 256

char ascii_palette[ASCII_PALETTE_SIZE + 1] = "   ...',;:clodxkO0KXNWM"; // this is 23 characters


int main() {

    for (int i=0; i<23; i++) {
        printf("%c", ascii_palette[i]);
    }
    printf("michaelgirafortniteskin\n");
    return 0;
}
