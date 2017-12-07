unset log
unset label
set encoding utf8
set title "S at time 0.001"
set xlabel "x, {/Symbol m}m"
set ylabel "S, mmol m^{-3}"
plot "out/S1.dat" u ($1*1e6):2 title 'S' with lines