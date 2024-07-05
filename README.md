# CODER'S BASILISK - THE ULTIMATE PROGRAMMING TOOL

Coder's Basilisk (CBAS) is the first of the last programming languages.

At its base level, CBAS is little more than a C clone. We have all your favorite
C features- structs, functions, unions, pointers, malloc and free, with a little
bit of syntax sugar here and there to make things easier (methods, constructors
and destructors).

The "secret sauce" of CBAS is metaprogramming. The compiler itself is both
extensible and programmable from within the compilation unit (i.e. the code
you write). If CBAS does not have a feature that you want, you can add the
feature.

CBAS is meant to completely supersede all existing programming language
infrastructure and replace it with a clean, sleek, simple system written
in C99.

# What makes Coder's BASILISK good?

In layman's terms: you can program the computer to write code for you instead of you writing
it yourself. Offload work from the programmer onto the computer.

This means the programmer can focus their effort away from the minutae of implementation detail
and more on core infrastructure.

In technical terms, CBAS contains three key components which make it the best thing since K&R:

1. codegen code

2. codegen_main

3. parsehooks



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

# What fantastic capabilities does CBAS actually have right now?

You can implement your own programming language (compiling to CBAS) and then use it in
the very same file you implemented it in. Your languages can be just as powerful as CBAS
and FFI is pretty much seamless.

You can write procedurally generated code generators using the builder (@mkbldr, @mkbldrn) 
and worksheet (@wksht) interfaces, so that the computer can write code for you instead of you
doing it.

You can take your code and retarget to any platform you can fathom, or just use the
already-written C backend, "toc".

All (well-formed) code written in CBAS is 100% cross platform from the start. You need only implement
something that takes all elements of the CBAS AST and turn them into the target language.

# Can CBAS do multithreading?

Yes. There is a very simple pthreads-based multithreading system implemented in the standard library.

You should be able to write your own for any potential target.

# Can I use language feature X in CBAS?

Is there a way to do X (even if it is rather obtuse and difficult to read) in C?

Example: coroutines. They're not a C feature, but you can do what a coroutine does
by writing your own state machines.

Then the answer is "almost certainly yes" and you can make it look pretty and easy to
use to- that's what CBAS is all about.

# What memory model does CBAS use?

Compiletime CBAS hooks into the system's C library implementations of malloc, realloc, and free
which are exposed to compiletime code through "__builtin_" functions.

Runtime CBAS behaves the same way (see comment below).

COMMENT:

Runtime CBAS behaves the way that the code generator says it should The "toc" code generator
makes low-level CBAS code behave like C.



# What "real programming" can I do in CBAS immediately?

You can write code in the cbas metaprogramming language and the tool can compile to C, which
can then be compiled by GCC, TinyCC, or clang into target code. 

With a little bit of effort it should be trivial to compile cbas code to any target and not just C.

The cbas programming tool (cbas) is not the only thing in-box. This puppy comes with
batteries included, we have OpenAL 1.1, OpenGL 1.1, BSD sockets, and (wrapped) parts of SDL2 already available
for programming. We also have a very simple threading implementation written in pthreads.

While this does make cbas a capable programming language in its own right, it ultimately serves
as little more than a demo. 

For "real" development, you should FFI your favorite C libraries into cbas.

OpenGL 1.1, OpenAL 1.1, usermode_stdlib, and funbas provide examples of how you do this.


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

# What is the theory or idea behind this language?

"Maximize the utilization of Man's intellectual capabilities"

CBAS allows programmers to make the language itself seamlessly meld with
your mind. You can make the structure of the language better reflect
the problem being solved.



