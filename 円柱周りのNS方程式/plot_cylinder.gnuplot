set datafile commentschars "#"
set terminal pngcairo size 980,1460 enhanced font "Times New Roman,18"
set output "cylinder_overview.png"
unset key
set multiplot layout 2,1 margins 0.08,0.96,0.05,0.97 spacing 0.05,0.07

set size ratio -1
unset colorbox
unset xlabel
unset ylabel
unset xtics
unset ytics
unset border
set xrange [-1.2e-1:1.2e-1]
set yrange [-1.2e-1:1.2e-1]
set object 1 circle at 0,0 size 5.0e-3 fc rgb "black" fill solid 1.0 border lc rgb "black"
plot "cylinder_grid.dat" using 1:2 with lines lc rgb "#4a61ff" lw 0.55, \
     "cylinder_grid_wake.dat" using 1:2 with lines lc rgb "#ff4b4b" lw 0.70
unset object 1

unset surface
set contour base
set cntrparam levels incremental -1.2e6,2.0e5,1.2e6
set table "cylinder_wake_contours.dat"
splot "cylinder_wake_map.dat" using 1:2:4
unset table
unset contour

set size ratio -1
unset border
unset xtics
unset ytics
unset xlabel
unset ylabel
set xrange [-1.5e-2:1.65e-1]
set yrange [-4.5e-2:4.5e-2]
set cbrange [0.0:4.0e1]
set palette defined (0 "#0018ff", 0.20 "#00b8ff", 0.45 "#00ff8a", 0.65 "#fff200", 0.85 "#ff8c00", 1 "#ff0000")
set colorbox horizontal user origin 0.37,0.07 size 0.26,0.016
set cbtics ("0" 0, "2U_{inf}" 40) scale 0
set label 1 "Absolute Velocity m/s" at screen 0.50,0.105 center
set object 2 circle at 0,0 size 5.0e-3 fc rgb "#222222" fill solid 1.0 border lc rgb "black"
plot "cylinder_wake_map.dat" using 1:2:3 with image, \
     "cylinder_wake_contours.dat" using 1:2 with lines lc rgb "#202020" lw 0.7
unset object 2
unset label 1

unset multiplot
