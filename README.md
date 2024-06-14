Before anything else...

# THE SEABASS METAPROGRAMMING LANGUAGE

Welcome! This repository contains the code for the Seabass metaprogramming
tool along with some libraries and example code.

All of it is public domain.

# What is this?

The most powerful programming tool ever created. Seabass is the first of the last 
programming languages.

Seabass is a self-modifying, self-extending, self-retargeting programming language.

That means you can extend the language to have new features, create new syntaxes (even
whole new languages), and then compile it for almost any target in existence.

Your intellectual capabilities are the limit.

# How do I use it?

make and install the `cbas` tool. `make q` on a typical Linux machine using sudo/doas or as root
should do the trick. I use a program I wrote called "admin". You should just be able to compile all
the .c files in the top level directory together `gcc -O3 *.c -o cbas` and that _should_ give you
a working cbas tool. Make sure to delete any `auto_out.c` files in the top level (should any
be left).

You'll want to install the standard libraries (everything under library/) into /usr/include/cbas/
or something. 

after that's done, try building some of the test programs. Look at the Makefile.

the `cbas` tool itself should be build-able on most systems with a C compiler (Windows and Linux are of course
fully capable). The metaprogramming library should also be a no brainer on those platforms as well as the `toc` 
converter however the standard library stuff in `toc` may have to be tweaked per-platform. This is mostly 
because C itself differs from platform
to platform, and Seabass currently only has a C backend written (toc).

Some `cstring` functions (`string.h`) may not be available on some platforms, but they are
easily replaced.

# How do I write Seabass code?

Look at the example programs written. Mess around with it. I tried to make some tutorials
but they were garbage. The base-level language feels like Lua, Rust, and C had a baby,
and the metaprogramming makes you feel like a god.

If you can write a mandelbrot renderer in C, you can learn Seabass pretty quick. Most of it is the same,
just with tweaked or trimmed-down syntax.

The metaprogramming capabilities of seabass are a whole other animal, though. It is currently a pretty
good question what can be done with them. Not even one iota of the capabilities of this language have been
tapped.

Do you like money? Here's an entrepeneurial idea for you: Take what I've written here and figure out how
to package it into the most powerful programming devkit ever made, and sell it to the US Government.

You'll be a multi-millionaire in less than a year.

# What can it do right now?

You can write code in the seabass metaprogramming language and the tool can compile to C, which
can then be compiled by GCC into target code. 


With a little bit of effort it should be trivial to compile seabass code to any target.

The seabass programming tool (cbas) is not the only thing in-box. This puppy comes with
batteries included, we have OpenAL 1.1, OpenGL 1.1, BSD sockets, and parts of SDL2 already available
for programming.

While this does make Seabass a capable programming language in its own right, it ultimately serves
as little more than a demo. You really want to FFI existing C libraries into Seabass (or whatever
language you choose to have Seabass compile into).


# What is the potential of the project?

In the right hands, Seabass could supersede every existing programming language.

The primary "new development" with Seabass is the discovery of the "parsehook",
a language element which enables the programmer to extend the parser with new
functionality, enabling new syntaxes. It also, of course, has full compiletime execution.

# Why would you want to write Seabass? Why not just write C++, Rust, Etc?

Other languages do not enable, or do not flexibly allow, the programmer to alter the
compiler itself.

Seabass 
# Why Seabass?

Three big things-

0. Codegen code. You can write code which extends the cbas tool itself inside your programs...

1. parsehooks. You can write code which extends the `cbas` tool and runs at parse time.

2. codegen_main. You write your own code generator. You get to tell the compiler what to turn
your code into. Currently, a code generator exists for compiling to C- `toc`, with special
support for 64 bit platforms, `toc_native_user` but seabass has compiled for 32 bit as well.

little things-

0. Maybe you like how seabass looks/feels?

1. CC0/Public Domain

2. FFI with the C language.



# What if I don't like how Seabass looks/works?

You can write your own "skin" for it. Make your own custom language within Seabass which
compiles to seabass during the execution of the `cbas` tool. You can even give it its own
file extension and everything.

# Documentation?

I have some old documentation I wrote which I believe has errors in it (much lacking in Godliness) 
but it may be useful regardless:




