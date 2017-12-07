unset log
unset label
set encoding utf8
set title "Last S"
set xlabel "x, {/Symbol m}m"
set ylabel "S, mmol m^{-3}"
#set yr [0.06:]
plot "out/S.dat" u ($1*1e6):2 title 'S' with lines