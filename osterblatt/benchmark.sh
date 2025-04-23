#!/bin/bash

echo "Starte 10 Läufe à 10^8 normalverteilte Zufallszahlen..."
echo

total_time=0

for i in {1..10}; do
    echo "Lauf $i:"
    start=$(date +%s.%N)

    ./rnorm_test > /dev/null

    end=$(date +%s.%N)
    elapsed=$(echo "$end - $start" | bc)
    echo "  Dauer: $elapsed Sekunden"
    total_time=$(echo "$total_time + $elapsed" | bc)
done

average=$(echo "$total_time / 10" | bc -l)
echo
echo "Durchschnittliche Laufzeit über 10 Läufe: $average Sekunden"



