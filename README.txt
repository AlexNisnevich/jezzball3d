Author: Erik Gui and Alex Nisnevich
Login: cs184-cx and cs184-dp
SID: 21178740 and 21323554
Email: erik.gui@berkeley.edu and alex.nisnevich@berkeley.edu

Compiled on Windows, also tested on OSX 10.6
See doc/as13.pdf for final report

Controls:

Left-click to place a wall
Middle-click or spacebar to change wall orientation
Right-click and drag to rotate (or zoom, in zoom mode)

P to toggle Pause
S to toggle Sound
Z to toggle Zoom Mode

Goal: Partition the playfield so that 80% of the volume is unreachable by the balls to complete each level.

Compilation
===========
Linux: Install freeglut (http://www.cs.uregina.ca/Links/class-info/315/WWW/Lab1/GLUT/linux.html), then run:

g++ -DOSX=1 -Iinclude/ -Isrc/UCB/ -o jezzball -v src/* -lGL -lGLU -lglut

Windows: Use Visual Studio.

