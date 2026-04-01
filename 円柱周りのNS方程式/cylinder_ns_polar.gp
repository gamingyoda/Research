set terminal pngcairo size 980,1460 enhanced font 'Times New Roman,18'
set output 'cylinder_ns_overview.png'
unset key
set multiplot layout 2,1 margins 0.08,0.96,0.05,0.97 spacing 0.05,0.07
set size ratio -1
unset colorbox
unset xlabel
unset ylabel
unset xtics
unset ytics
unset border
set xrange [-1.2000000000e-01:1.2000000000e-01]
set yrange [-1.2000000000e-01:1.2000000000e-01]
set title ''
set object 1 circle at 0,0 size 5.0000000000e-03 fc rgb 'black' fill solid 1.0 border lc rgb 'black'
plot 'cylinder_ns_grid.dat' using 1:2 with lines lc rgb '#4a61ff' lw 0.55, \
     'cylinder_ns_grid_wake.dat' using 1:2 with lines lc rgb '#ff4b4b' lw 0.70
unset object 1
set border 15
set xtics out
set ytics out
set xlabel 'x [m]'
set ylabel 'y [m]'
set size ratio -1
set xrange [-1.5000000000e-02:1.6500000000e-01]
set yrange [-4.5000000000e-02:4.5000000000e-02]
set cbrange [0.0:4.0000000000e+01]
set cbtics 0,10,4.0000000000e+01
set colorbox horizontal user origin 0.36,0.095 size 0.28,0.018
set cblabel 'Absolute Velocity m/s'
set palette defined (0 '#0018ff', 0.20 '#00b8ff', 0.45 '#00ff8a', 0.65 '#fff200', 0.85 '#ff8c00', 1 '#ff0000')
unset surface
set object 2 circle at 0,0 size 5.0000000000e-03 fc rgb '#2b2b2b' fill solid 1.0 border lc rgb 'black'
plot 'cylinder_ns_wake_map.dat' using 1:2:3 with image
unset multiplot
