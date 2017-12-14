unset log
unset label
set encoding utf8
set title "I derivative"
set xlabel "t, s"
#set ylabel "i', {/Symbol m}A m^{-2}"
set ylabel "i', A m^{-2}s^{-1}"
plot "out/It.dat" title 'i' with lines
