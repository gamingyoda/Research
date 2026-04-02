set datafile commentschars "#"
set terminal pngcairo enhanced font "Times New Roman,18"
unset key

grid_radius = 3
cylinder_radius = 0.25
wake_xmin = -0.8
wake_xmax = 4
wake_ymin = -1.2
wake_ymax = 1.2

speed_cap = 2.0
contour_step = 0.05

unset surface
set contour base
set cntrparam levels incremental contour_step, contour_step, speed_cap
set table "cylinder_speed_contours.dat"
splot "cylinder_wake_map.dat" using 1:2:(($3 > speed_cap) ? speed_cap : $3)
unset table
unset contour

set output "cylinder_grid.png"
set terminal pngcairo size 1100,1100 enhanced font "Times New Roman,18"
set size ratio -1
set border lw 1.1
set xrange [-grid_radius:grid_radius]
set yrange [-grid_radius:grid_radius]
set xlabel "x [m]"
set ylabel "y [m]"
set xtics 1.0
set ytics 1.0
unset colorbox
set object 1 circle at 0,0 size cylinder_radius fc rgb "#202020" fill solid 1.0 border lc rgb "black"
plot "cylinder_grid.dat" using 1:2 with lines lc rgb "#4567ff" lw 0.45, \
     "cylinder_grid_wake.dat" using 1:2 with lines lc rgb "#ff5b3a" lw 0.85
unset object 1

set output "cylinder_karman_wake.png"
set terminal pngcairo size 1380,760 enhanced font "Times New Roman,18"
set size ratio -1
set border lw 1.1
set xrange [wake_xmin:wake_xmax]
set yrange [wake_ymin:wake_ymax]
set xlabel "x [m]"
set ylabel "y [m]"
set bmargin 4.5
set xtics 0.5
set ytics 0.3
set palette defined (0 "#1734ff", 0.18 "#00d7ff", 0.50 "#00ff00", 0.75 "#fff000", 0.92 "#ff8a00", 1 "#ff2800")
set cbrange [0.0:speed_cap]
set colorbox horizontal user origin 0.34,0.06 size 0.32,0.028
set cbtics ("0" 0.0, "1" 1.0, "2" 2.0) scale 0
set cblabel "|u| / U_inf" offset 0,1.0
set object 2 circle at 0,0 size cylinder_radius fc rgb "#202020" fill solid 1.0 border lc rgb "black"
plot "cylinder_wake_map.dat" using 1:2:(($3 > speed_cap) ? speed_cap : $3) with image, \
     "cylinder_speed_contours.dat" using 1:2 with lines lc rgb "#1a1a1a" lw 0.9
unset object 2
