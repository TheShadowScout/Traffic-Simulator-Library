set datafile separator ';'

set key autotitle columnhead
set ylabel 'Road capacity [amount of cars until T]'
set xlabel 'Vehicle density [%]'

set style line 100 lt 1 lc rgb "grey" lw 0.5
set grid ls 100
set ytics 50
set xtics 5

set style line 101 lw 2 lt rgb "#00dd00"
set style line 102 lw 2 lt rgb "#aa00ff"
set style line 103 lw 2 lt rgb "#ff1223"
set style line 104 lw 2 lt rgb "#ffaa00"
set style line 105 lw 2 lt rgb "#1323fd"
set style line 106 lw 2 lt rgb "#000000"

set xtics rotate
set key outside right bottom

set term png
set output "./StatisticsHistory/DensityPlot.png"
plot './StatisticsHistory/data.csv' using 1:2 with lines ls 101, '' using 1:3 with lines ls 102, '' using 1:4 with lines ls 103, '' using 1:5 with lines ls 104, '' using 1:6 with lines ls 105, '' using 1:7 with lines ls 106

