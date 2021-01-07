set -e
FREEGLUT="./a__/libglut.a"
GLUT="/System/Library/Frameworks/GLUT.framework/GLUT"
Cocoa="/System/Library/Frameworks/Cocoa.framework/Cocoa"
X11="-L/opt/X11/lib -lGL -lGLU -lX11"
IOKit="/System/Library/Frameworks/IOKit.framework/IOKit"
S="-Wno-deprecated-declarations -Wno-#warnings"
#D="-fsanitize=address -g"
D="-g -fno-pie"
F="$Cocoa $GLUT $X11 $FREEGLUT $IOKit"
I="-I h__"
gcc $D $I $S $F $L main.c -o exec__/main
