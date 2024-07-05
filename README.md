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

"codegen code" (also called compiletime code) is code which runs at compiletime. codegen code is different
from "normal" CBAS code in that it does not get compiled into the final binary- it only "lives" during
the execution of the compiler itself.

codegen code is turing complete and it gives CBAS near-complete compiletime execution.

"codegen_main" is the name of a function which the compilation unit must define whose purpose is to generate
"target code" - i.e. assembly, C, or a final binary. Because CBAS places the requirement of defining how code
is compiled on the code itself, it is self-retargeting. All code in CBAS is portable.

"parsehooks" are the ultimate secret sauce of CBAS. The parser regularly checks for the presence of the at sign
`@` at various points in your code. If it sees the @ sign followed by an identifier, say, `@serpent`, it will
look for a codegen function named `parsehook_serpent` and execute it. 

Parsehooks give CBAS the ability to define custom syntax, even entirely new programming languages right within
the confines of a single compilation unit, even a single file. They can manipulate the state of the compiler,
read and write files, and even generate or manipulate source code (which can then be parsed by the main parser).

# What is the state of the project?

TLDR? Feature-complete, but not fully realized.

The language is more-or-less finished, and the CBAS tool implementation is considered "complete and ready for use".

the `toc` translator is mostly finished and ready for production.

`stdmeta`, the standard metaprogramming library, is woefully underdeveloped and incomplete, which is sad because it is
the "main point" of this language. This is where 90% of the work has to happen, and a significant fraction of that is
"theory work", much of which involves trial-and-error in implementation design.

There is an enormous amount of theory work and new metaprogramming code that has to be written to make CBAS into even ten
percent of what it is capable of being. 

All work on metaprogramming in CBAS has exponential gains in productivity due to the nature of metaprogramming,
so as more work happens, the work itself should get quicker (the core concept of metaprogramming).

# If I used CBAS right now using only what is already here, what would I get?

An extremely portable C-like language with much better macros. FFI with C is fairly trivial to set up too, so you could
forward your favorite libraries and use them without too much hassle.

Metaprogramming in CBAS is extremely advanced compared to other languages, but not quite "breathing fire and firing
lightning out of your finger tips".

In order to use this, though, you'd have to have documentation... which this project also lacks.

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

# Are there any demonstrations of CBAS's true power?

Truly? No, but there are minor examples- we have a compiletime recursive descent parser generator
DSL implemented (`@cgrdparser`), which was used to implement a custom pretty-printer syntax, `@pprint`.

Some language features from C++ have been mirrored in CBAS using metaprogramming code- notably templates.

Most CBAS code is unfortunately mostly just a spruced-up C or a dumbed-down C++.

# I looked through the code- isn't this just macros?

The majority of CBAS metaprogramming usage in the codebase is to implement macros, and indeed
CBAS does have one of the most intricate and flexible macro systems I know of, however CBAS's
metaprogramming facilities are not "just macros".

CBAS's metaprogramming facilities have not been properly demonstrated, nor fully fleshed out yet.

I, the sole author, David MHS Webster, am still working on the "theory" of metaprogramming as it
pertains to the project.

# Do you accept contributions?

Ideas, yes, but absolutely no code submissions.

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

Needs work, but the best we have is this:

`cbas -m help`

This is new technology still being developed. You're on your own, kid.

# The Grand Vision of CBAS

"Maximize the utilization of Man's intellectual capabilities"

CBAS allows programmers to make the language itself seamlessly meld with
your mind. You can make the structure of the language better reflect
the problem being solved, and even make problems easier to think about. 

Taken to its extreme, I imagine this concept makes each programmer a 
"10x" version of himself, or more properly, a "1000x"
version. The end result should be that all intellectual output is boosted
drastically, to such a point that even a single gifted person can outperform
a billion dollar company packed with geniuses.

The natural progression of this ideology will eventually outgrow this tool,
as multimedia programming will eventually take over, but for now this is the
best I can really do.

CBAS represents my best attempt to advance humanity out of its delusional and
emotionally driven infancy into a utopian future.

# How close is CBAS to the accomplishment of this vision?

It has barely started. CBAS's raw immediate capabilities do not yet replace Rust or
C++, let alone revolutionize the industry.

If I can keep working on it, and keep having good ideas this should change soon.

# Do you have a time-estimate for how long this would take?

If I had 8 months of concentrated development time I could probably do it.

I know my own capabilities, I believe I understand where this project has to go, and thus I am confident in that figure.

# TECHNOLOGY DEVELOPMENT ROADMAP

What code needs to be written for the CBAS project to make it a real success?

Primarily for me, but perhaps to the intrigue of any curious reader...

(These are mostly in-order, but I may be in multiple phases at once)

1. The Language Designer toolkit. I've already written `@cgrdparser`, but this is not
sufficient for designing and implementing a programming language. Designing an AST and
dictating how the AST is semantically analyzed and traversed are also extremely important.

2. Write DSLs and custom helpers for various common programming problems. CBAS's whole shtick
is writing your own languages... but I really haven't done that very much. Most of these
DSL things I write to begin with are probably just going to be things that help me design and
implement programming language features faster, since that's going to be my first line of work here.

3. Write libraries. I need commonly used libraries from C available to me in CBAS, everything from
modern OpenGL to cryptography libraries to audio processing to gui toolkits. I may also choose to 
write full replacements in CBAS.

This also includes code generators- I want to be able to generate more than just C code. Particularly,
I would like to have at least one interpreter or JIT or something.

4. Make an IDE. Now, I usually hate IDEs, but I believe that I can probably wrap CBAS in a way to make
it into a graphical programming language, or rather make a graphical programming language which is, at
its core, CBAS.

5. Write real-world software. Big stuff. I want a web browser, file system utilities, you name it. I want
stuff that really grabs peoples' attention. Development tools.

# DOCUMENTATION AND PACKAGING ROADMAP

How do I take what I have written or will write in CBAS and package it into useful (?marketable?) tools?

1. Write example programs in CBAS. Basic stuff. Stuff which reads and writes files and maybe draws some pretty
pictures in the terminal, answers math problems or whatever. 

2. Write reference material. I want the whole language documented including the metaprogramming library. I want
all the reference material in nice pretty HTML, hopefully with diagrams.

3. Write tutorials in CBAS. I want a full "introduction to metaprogramming with CBAS" series which starts
with teaching people how to write simple stuff like they had never written C in their life all the way to
writing their custom DSLs.

4. Make videos about CBAS. What is this language, what does it do, why would you want to use it instead of
Rust or C++.

5. Showcase stuff written in CBAS. When I get around to writing "cool stuff" in CBAS, I want to show it off
so that people will actually use my stuff.

6. Write books about CBAS. I figure once the tech is out there, there will be a market for books written on
the language. The first and most obvious book I want to write is a K&R style book about the language (i'll
have to make it much thicker...).

7. Make an SDK. A complete toolchain you can download. For Linux, it's pretty easy, but for Windows it's not
easy.

# Do you believe Coder's Basilisk has more potential for revolutionizing the industry than AI?

Both yes and no. The primary gain of Coder's Basilisk is the ability to more efficiently utilize an intelligent
mind to generate code. Whether that intelligent mind is an AI or a human is not particularly important.

Existing programming languages leverage the human mind extremely poorly and expressing your programming ideas
to the computer is often awkward.

You can talk to online chatbots and ask them to write code for you, and I am impressed with what they have done,
but it's not a replacement for real programming.

If AI were to become "advanced enough" I believe it could internally develop something like CBAS in order to write
code. As it stands, it's fucking bad at it.

I used to believe neural network based AIs were never going to get anywhere, but GPT-4o and Claude 3.5 have made me
reneg on that- I am skeptical (I was rather unimpressed with ChatGPT).

So I'll be conservative and say "maybe yes".


