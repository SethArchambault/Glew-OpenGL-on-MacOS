# My Journey using Glew and then FreeGLUT on MacOS

**TLDR**

- Don't use Glew on macOS unless you can cope with old 1.2 version shaders.
- Don't use FreeGlut on macOS unless you love X11 for some reason.

# Background

- I want to draw a triangle on the screen 
- I'd like to have full control over the low level details, so no graphics
  framework (SDL, SFML, Raylib, etc)

Options:
- GLFW
- GLEW

I've used GLFW and it works great, but I was curious about the GLUT / GLEW
option. I came across a post from someone who said it was trivial to add glew
to a project, and I saw a lot of people saying "Just use GLFW." Sometimes
people complain about stuff simply because it is older, or outside their
comfort zone, so I decided to give it a shot. 

# Just GLEW

I got the initial version working really easily and was pleased to find I could
just include glew.c, and that would be enough. Great! I love less dependencies! 

But then I ran up against the problem. GLUT on MacOS only supports shader
version 1.2. This isn't the worst thing in the world, but most shader tutorials
are written in higher versions. I'd like to write in version 3.2, so the
default GLUT on MacOS is a no-go. 

Enter FreeGlut.

# FreeGlut 

FreeGlut brings modern shaders to my simple Glew / Glut setup on MacOS, but
it's a more intensive process to install. 

First you've got to install X11, which was a big red warning flag. We'll come
back to that.

You've got to build FreeGlut using cmake, and it produces build versions out of
the box. At least with freeglut-3.2.1.  [After solving those errors](https://github.com/dcnieho/FreeGLUT/issues/70), 
and linking X11 properly, I finally got it running.

Dissapointingly, there is just a white screen inside of an X11 box. I hate that
X11 box. I want to be working natively, not in some bulky cross platform
emulated window. This is a deal breaker for me. 

# Epilogue

So given then I want to use modern OpenGL shaders, and I don't want to be stuck
in an X11 box, it's back to GLFW for me. There may be other solutions here, but
I'm looking forward to making more progress on the project at hand, rather than
thrashing around in the dirt in these initial setup phases.


