set datafile commentschars "#"
set terminal pngcairo enhanced font "Times New Roman,18"
unset key

grid_radius = 3
cylinder_radius = 0.25
wake_xmin = -0.8
wake_xmax = 4
wake_ymin = -1.2
wake_ymax = 1.2

stats "cylinder_wake_map.dat" using 3 nooutput
max_speed = STATS_max
if (max_speed < 1.0) max_speed = 1.0

stats "cylinder_wake_map.dat" using 4 nooutput
omega_abs = (abs(STATS_min) > abs(STATS_max) ? abs(STATS_min) : abs(STATS_max))
if (omega_abs < 6.0) omega_abs = 6.0
omega_cap = 180.0
if (omega_abs < omega_cap) omega_cap = omega_abs
omega_step = omega_cap / 6.0

unset surface
set contour base
set cntrparam levels incremental -omega_cap, omega_step, omega_cap
set table "cylinder_wake_contours.dat"
splot "cylinder_wake_map.dat" using 1:2:(($4 > omega_cap) ? omega_cap : (($4 < -omega_cap) ? -omega_cap : $4))
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
set xtics 0.5
set ytics 0.3
set palette defined (0 "#0626a8", 0.18 "#0090ff", 0.36 "#00d8c3", 0.55 "#b9f300", 0.72 "#ffd100", 0.88 "#ff7b00", 1 "#cc1800")
set cbrange [0.0:max_speed]
set colorbox vertical user origin 0.92,0.18 size 0.018,0.56
set cblabel "speed [m/s]" offset 1.4,0
set object 2 circle at 0,0 size cylinder_radius fc rgb "#202020" fill solid 1.0 border lc rgb "black"
plot "cylinder_wake_map.dat" using 1:2:3 with image, \
     "cylinder_wake_contours.dat" using 1:2 with lines lc rgb "#111111" lw 0.8
unset object 2
