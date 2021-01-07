set -e
GLUT="/System/Library/Frameworks/GLUT.framework/GLUT"
OpenGL="/System/Library/Frameworks/OpenGL.framework/OpenGL"
Cocoa="/System/Library/Frameworks/Cocoa.framework/Cocoa"
IOKit="/System/Library/Frameworks/IOKit.framework/IOKit"
S="-Wno-deprecated-declarations -Wno-#warnings"
#D="-fsanitize=address -g"
D="-g -fno-pie"
F="$Cocoa $OpenGL $GLUT $IOKit"
I="-I h__"
gcc $D $I $S $F $L main.c -o exec__/main
