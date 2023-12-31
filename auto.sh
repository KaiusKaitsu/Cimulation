#bin/bash
gcc simulation.c -o simOut -lm `pkg-config --cflags --libs gtk+-3.0`
wait 1
./simOut
