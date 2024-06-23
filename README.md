Before anything else...

# CODER'S BASILISK - THE ULTIMATE PROGRAMMING TOOL

Coder's Basilisk (CBAS) is the first of the last programming languages.

It is a self-extending, self-retargeting programming language designed
to completely supersede C and C++. 

The core idea of CBAS is that the program being compiled specifies how 
it should be compiled- the syntax of CBAS is totally mutable and extensible.

Programs written in CBAS can extend the compiler itself to give it new
and useful capabilities.

The tool itself is considered "finished" at this time, however it is not
yet packaged properly for widespread use.

# What makes Coder's Basilisk special?

Using Coder's Basilisk, it is possible to tailor a vast array of DSLs as well as custom
general-purpose abstractions, all perfectly melded with a capable high-performance low-level
C-like language.

# What is the state of the project?

The language is more-or-less finalized, and the tool implementation is considered "complete and ready for use".

You may find implementation bugs, but they should be rare. Error messages are pretty good, but they could
use some work.

A small but powerful array of metaprogramming tools are provided in `stdmeta`. It is planned to be extended
in the future.

The "toc" code generator is useful and effective.

There are some libraries written for the `toc` backend- notably FFIs for OpenGL 1.1 and OpenAL 1.1.

The codebase is largely undocumented. Tutorials, references, guides, and expository material need to be written to make
the language a success.

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
because C itself differs from platform to platform, and cbas currently only has a C backend written (toc).

Some `cstring` functions (`string.h`) may not be available on some platforms, but they are
easily replaced.

# How do I write cbas code?

At time-of-writing (June 2024) the codebase goes largely without proper documentation.

This is one of the biggest hurdles of making the project a success.

Look at the example programs written. Mess around with it. I tried to make some tutorials
but they were garbage. The base-level language feels like Lua, Rust, and C had a baby,
and the metaprogramming makes you feel like a god.

If you can write a mandelbrot renderer in C, you can learn cbas pretty quick. Most of it is the same,
just with tweaked or trimmed-down syntax.

The metaprogramming capabilities of cbas are a whole other animal, though. It is currently a pretty
good question what can be done with them. Not even one iota of the capabilities of this language have been
tapped.

Do you like money? Here's an entrepeneurial idea for you: Take what I've written here and figure out how
to package it into the most powerful programming devkit ever made, and sell it to the US Government.

You'll be a multi-millionaire in less than a year.

# What can it do right now?

You can write code in the cbas metaprogramming language and the tool can compile to C, which
can then be compiled by GCC, TinyCC, or clang into target code. 

With a little bit of effort it should be trivial to compile cbas code to any target and not just C.

The cbas programming tool (cbas) is not the only thing in-box. This puppy comes with
batteries included, we have OpenAL 1.1, OpenGL 1.1, BSD sockets, and (wrapped) parts of SDL2 already available
for programming.

While this does make cbas a capable programming language in its own right, it ultimately serves
as little more than a demo. 

For "real" development, you should FFI your favorite C libraries into cbas.

OpenGL 1.1 and OpenAL 1.1 provide examples of how you do this.


# What is the potential of the project?

In the right hands, cbas could supersede every existing programming language.

I genuinely believe this technology could change the whole world.

# Why would you want to write cbas? Why not just write C++, Rust, Etc?

Other languages do not enable, or do not flexibly allow, the programmer to alter the
compiler itself.

cbas isn't just another programming language. It is a dynamo for letting clever people
make the language suit their needs.

In the right hands, CBAS should be more powerful than C++ or Rust.

# What if I don't like how cbas looks/works?

You can write your own "skin" for it. Make your own custom language within cbas which
compiles to cbas during the execution of the `cbas` tool. You can even give it its own
file extension and everything.

# Documentation?

`cbas -m help`

# Didn't this project have another name?

it is also called "Seabass". However, I discovered this name was taken by multiple other projects.

I wanted to keep the "cbas" name (if for no other reason than the enormous trouble of going through
all my code and removing it) but not have it mean "Seabass".

While in the shower, I had the idea of calling it "Coder's Basilisk".

There is a thought experiment known as "Roko's Basilisk" in which a sentient AI creates simulations
of those who did not assist in its creation (but were aware of it) to torture forever.

the CBAS project's ultimate goal is to hyper-stimulate human intellectual output, which will hopefully
contribute to the advancement of our race. While there's no torture, it's not too dissimilar a concept.

So this project is "Coder's Basilisk".

# I am interested in your theory. What's the theory behind CBAS?

"Maximize the utilization of Man's intellectual capabilities"

CBAS allows programmers to make the language itself seamlessly meld with
your mind. You can make the structure of the language better reflect
the problem being solved.


