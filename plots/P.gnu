unset log
unset label
set encoding utf8
set title "Last P"
set xlabel "x, {/Symbol m}m"
set ylabel "P, mmol m^{-3}"
plot "out/P.dat" u ($1*1e6):2 title 'P' with lines
