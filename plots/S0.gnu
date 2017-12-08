unset log
unset label
set encoding utf8
set title "S0"
set xlabel "x, {/Symbol m}m"
set ylabel "S, mmol m^{-3}"
#set xr [18.9:]
#set yr [0.06:]
plot "out/S1.dat" u ($1*1e6):2 title 'S' with lines