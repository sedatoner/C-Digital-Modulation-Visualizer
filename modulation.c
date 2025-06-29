#include <stdio.h>
#include <stdlib.h>

// I’m working with 8 bits of data in this example
#define BITS 8

// These are the amplitude values I’ll use for ASK modulation
#define AMPLITUDE_HIGH 5
#define AMPLITUDE_LOW 0

// Frequency values for FSK (these are just symbolic for now)
#define FREQ_HIGH 10
#define FREQ_LOW 5

// Phase values for BPSK – 0 and 180 degrees (represented as integers)
#define PHASE_0 0
#define PHASE_180 180

// I had to define 'i' globally because I'm writing in a C89-compatible way
int i;

// ASK Modulation: I assign a high amplitude for 1, and a low amplitude for 0
void modulate_ask(const int* input, int* modulated) {
    for (i = 0; i < BITS; i++)
        modulated[i] = input[i] ? AMPLITUDE_HIGH : AMPLITUDE_LOW;
}

// ASK Demodulation: If the signal's amplitude is above halfway, I treat it as a 1
void demodulate_ask(const int* modulated, int* output) {
    for (i = 0; i < BITS; i++)
        output[i] = modulated[i] > (AMPLITUDE_HIGH / 2) ? 1 : 0;
}

// FSK Modulation: I encode bits by choosing between two frequencies
void modulate_fsk(const int* input, int* modulated) {
    for (i = 0; i < BITS; i++)
        modulated[i] = input[i] ? FREQ_HIGH : FREQ_LOW;
}

// FSK Demodulation: I reverse the process by checking if the frequency is high or low
void demodulate_fsk(const int* modulated, int* output) {
    for (i = 0; i < BITS; i++)
        output[i] = modulated[i] > ((FREQ_HIGH + FREQ_LOW) / 2) ? 1 : 0;
}

// BPSK Modulation: For 1 I assign phase 0, and for 0 I assign phase 180
void modulate_bpsk(const int* input, int* modulated) {
    for (i = 0; i < BITS; i++)
        modulated[i] = input[i] ? PHASE_0 : PHASE_180;
}

// BPSK Demodulation: If the phase is 0, it’s a 1; if it's 180, it’s a 0
void demodulate_bpsk(const int* modulated, int* output) {
    for (i = 0; i < BITS; i++)
        output[i] = modulated[i] == PHASE_0 ? 1 : 0;
}

// I use this function to write all the data (input, modulated, demodulated) into a text file
void write_data(const char* name, const int* input, const int* modulated, const int* demodulated) {
    FILE* f = fopen(name, "w");
    for (i = 0; i < BITS; i++) fprintf(f, "%d ", input[i]);
    fprintf(f, "\n");
    for (i = 0; i < BITS; i++) fprintf(f, "%d ", modulated[i]);
    fprintf(f, "\n");
    for (i = 0; i < BITS; i++) fprintf(f, "%d ", demodulated[i]);
    fprintf(f, "\n");
    fclose(f);
}

int main() {
    // Here’s my example input – just a fixed 8-bit array for now
    int input[BITS] = {1, 0, 1, 1, 0, 0, 1, 0};
    int modulated[BITS], demodulated[BITS];

    // ASK: I modulate and then demodulate, then save the results
    modulate_ask(input, modulated);
    demodulate_ask(modulated, demodulated);
    write_data("ask.txt", input, modulated, demodulated);

    // FSK: Same process
    modulate_fsk(input, modulated);
    demodulate_fsk(modulated, demodulated);
    write_data("fsk.txt", input, modulated, demodulated);

    // BPSK: And again
    modulate_bpsk(input, modulated);
    demodulate_bpsk(modulated, demodulated);
    write_data("bpsk.txt", input, modulated, demodulated);

    // Finally, I trigger the Python script that will plot all 3 modulation signals
    system("\"C:\\Users\\sdt\\anaconda3\\python.exe\" plot_signals.py");

    return 0;
}

