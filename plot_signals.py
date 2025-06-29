import matplotlib.pyplot as plt

# This function reads the data I saved in a text file earlier.
# Each file has 3 lines: input bits, modulated signal, and demodulated bits.
def read_data(filename):
    with open(filename) as f:
        lines = f.readlines()
        # I'm converting each line into a list of integers
        input_bits = list(map(int, lines[0].split()))
        modulated = list(map(int, lines[1].split()))
        demodulated = list(map(int, lines[2].split()))
    return input_bits, modulated, demodulated

# This function takes the input, modulated, and demodulated signals,
# and plots them together so I can visually compare what’s going on.
def plot_signal(title, input_bits, modulated, demodulated):
    plt.figure()  # Start a new figure
    plt.title(title)  # Title for the plot
    # I’m plotting the modulated signal with dots
    plt.plot(modulated, label="Modulated Signal", marker='o')
    # Input bits get a dashed line so I can tell them apart easily
    plt.plot(input_bits, label="Input Bits", linestyle="--", alpha=0.6)
    # Demodulated bits have a dotted line
    plt.plot(demodulated, label="Demodulated Bits", linestyle=":", alpha=0.6)
    plt.xlabel("Bit Index")
    plt.ylabel("Value")
    plt.legend()  # Show which line is which
    plt.grid(True)  # Makes it easier to read the graph

# Now I just read the data files I generated with the C program
ask = read_data("ask.txt")
fsk = read_data("fsk.txt")
bpsk = read_data("bpsk.txt")

# Then I plot each one in a separate figure
plot_signal("ASK Modulation", *ask)
plot_signal("FSK Modulation", *fsk)
plot_signal("BPSK Modulation", *bpsk)

plt.show()
