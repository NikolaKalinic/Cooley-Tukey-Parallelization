#!/bin/bash

# Broj ponavljanja
num_repeats=10
# Pokreni program 10 puta
total_time=0
for ((i=1; i<=$num_repeats; i++)); do
    #start_time=$(mpiexec -n $i ./mpi)
    start_time=$($1)
    echo $start_time >> mpi.txt
    total_time=$(echo "$total_time + $start_time" | bc)
done
# Izračunaj prosečno vreme izvršavanja
average_time=$(echo "scale=4; $total_time / $num_repeats" | bc)
echo "Prosečno vreme izvrsavanja: 0$average_time sekundi"
