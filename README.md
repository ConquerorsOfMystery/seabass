![CBAS_logo](CBAS_logo.png)

***The First Hammer of the Silicon Sages***

# CODER'S BASILISK - THE ULTIMATE PROGRAMMING TOOL

Coder's Basilisk (CBAS) is the first of the last programming languages.

At its base level, CBAS is little more than a C clone. We have all your favorite
C features- structs, functions, unions, pointers, malloc and free, with a little
bit of syntax sugar here and there to make things easier (methods, constructors
and destructors, et cetera).

The "secret sauce" of CBAS is metaprogramming. The compiler itself is both
extensible and programmable from within the compilation unit (i.e. the code
you write). If CBAS does not have a feature that you want, you can add the
feature. **This has already been used to add several major features to the 
language without additions to the actual compiler's source code.**

CBAS is meant to completely supersede all existing programming language
infrastructure and replace it with a clean, sleek, simple and reasonably efficient system.



## BEFORE YOU READ: if you like the project?

CBAS is my gift to humanity. The fruit of my brain and my effort which I have put out there
for anyone to have.

I could horde it for myself, but I have good reasons not to.

My reasons are as follows:

1. Prestige. I feel like I can get more earned respect if I write public domain code. 
I don't believe people deserve to have any honor unless they've really done some 
measurable good in the world to help others. Putting CBAS into the public domain is
essentially a "maximum good" I can achieve, and I think if I make it a real fully fleshed
out project that is really useful, I will deserve honor and hopefully get it from the right
people (the smart ones, the people with good hearts and minds who are actually worth receiving 
honor from and not socialites and half-wits).

2. Investment. I believe that in forty years I may be able to reap the benefits of society
having access to this technology. Keeping it out of the hands of the common man may be to
my direct detriment, even if I became fabulously wealthy now, just because CBAS may drastically
increase intellectual output that much.

3. Love. I care about the creators, My fellow sages, the brilliant and creative people out there 
trying to make stuff, who are hindered by the weak and pathetic tools that hold them back. CBAS should
be a substantial improvement, although I believe I can create far more powerful tools (which I hope
to make in CBAS).

You might find it disappointing that I put "love" as the last reason- indeed, if it were only
about my love for humanity, I would have already closed the source code of the project and made
it my private project just for myself and perhaps a small number of people that I choose to
bestow it upon.

Enough people have insulted, berrated, and disrespected me over this project that my pure good
will towards humanity is no longer strong enough for that to be my reason. I am a misanthrope.

If you are truly grateful and find what I made useful for you, these are my requests, in order:

1. I want you to acknowledge that I have been your benefactor. I (David MHS Webster) made something
that you use. Go out of your way to make sure I get credit and honor for what I have made and your use of it. 

If you should ever meet me, give me honor. 

My rank and title is "Grand Sage of the Silicon Tongues" (GSotST), and if you ever 
make a video game  or something, if you could put an easter egg or reference to me with that, that
would be awesome. Even if it was just in a credits screen or something.

2. If you ever become fabulously rich and powerful? share some of your spoil with me. Find me and
dump treasure into my lap. I like big crystals and shiny jewels. I like pure gold. I like
rare and unusual things. I like wizards and sorcerers and stuff.

3. If you were to find I am ever in need, if I am ever without common rest, welcome me. Supply me.

The TLDR is "REMEMBER ME, HONOR ME, GIVE BACK".

I have been called a crank, scum, a schizo, I've had my work called garbage, I've listened to
people spew ignorant crap about my work without any understanding of it or my ideas...

I'm tired of it.

I know that there are good people out there. there've been a few people who have made nice comments about my work-
but scars tend to be easier to remember than kisses.

Is this petty? Absolutely. I don't care.

My full self-proclaimed title is Grand Sage of the Silicon Tongues, Keggek, Creator of Coder's Basilisk.

You can call me "Grand Sage" or "The Grand Sage" in the third person. I'm not "sir" or "mister".

I want it to be honest though, so if you don't find joy in calling me "Sage" or speaking about me
like I'm gandalf but cooler (can anyone be cooler than gandalf?), don't bother. Honorifics are if you love me.

"Hey, David, Thank you for creating cool, good stuff for me"

is sufficient to make me feel like I'm not only writing code for ungrateful jerks.

## What makes Coder's BASILISK good?

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

## What is the state of the project?

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

## Are you planning on self-hosting the compiler?

It would be fairly trivial to port the compiler into its own language, however I do not find this necessary
at the current time. The C99 implementation works wonderfully.

It is a TODO.

## If I used CBAS right now using only what is already here, what would I get?

An extremely portable, easily automated C-like language with much better macros. 
FFI with C is fairly trivial to set up too, so you could
forward your favorite libraries and use them without too much hassle.

Metaprogramming in CBAS is extremely advanced compared to other languages, but not quite "breathing fire and firing
lightning out of your finger tips".

In order to use this, though, you'd have to have documentation... which this project also lacks.

That's a TODO.

## How do I use it?

make and install the `cbas` tool. `make q` on a typical Linux machine using sudo/doas or as root
should do the trick. You should just be able to compile all the .c files in the top level 
directory together `gcc -O3 *.c -o cbas` and that _should_ give you a working cbas tool. Make sure 
to delete any `auto_out.c` files in the top level (should any be left).

You'll want to install the standard libraries (everything under library/) into /usr/include/cbas/
or something. 

after that's done, try building some of the test programs. Look at the Makefile.

the `cbas` tool itself should be build-able on most systems with a C compiler (Windows and Linux are of course
fully capable). The metaprogramming library should also be a no brainer on those platforms as well as the `toc` 
converter however the standard library stuff in `toc` may have to be tweaked per-platform. This is mostly 
because C itself differs from platform to platform, and cbas currently only has a C backend written (toc).

## How do I write cbas code?

At time-of-writing (June 2024) the codebase goes largely without proper documentation.

Getting proper documentation is a TODO, I think I want to write an automated tool which allows
me to write some sort of markup inside of comments or something.

Look at the example programs written. Mess around with it. I tried to make some tutorials
but they were garbage. The base-level language feels like Lua, Rust, and C had a baby,
and the metaprogramming makes you feel like a god.

If you are competent enough to write a mandelbrot renderer in C, you can learn cbas's base-level syntax pretty quick. 
Most of it is the same, just with tweaked or trimmed-down syntax.

The metaprogramming capabilities of cbas are a whole other animal, though. As far as I know, there is nothing quite
like it in all the world- It is currently a pretty good question what can be done with them. Not even one iota of 
the capabilities of this language have been tapped.

## What fantastic capabilities does CBAS actually have right now?

You can implement your own programming language (compiling to CBAS) and then use it in
the very same file you implemented it in. Your languages can be just as powerful as CBAS
and FFI with CBAS (and consequently with C) should be pretty much seamless.

You can automate the authoring of custom or templated code very easily using pre-made metaprogramming
tools available in `stdmeta`.

If you write your code right, it should be extremely trivial to port any software you write in CBAS
to any platform with the same word size (i.e. if you wrote for 64 bit, any 64 bit platform).

All (well-formed) code written in CBAS is 100% cross platform from the start. You need only implement
something that takes all elements of the CBAS AST and turn them into the target language.

## Can CBAS do multithreading?

Yes. There is a very simple pthreads-based multithreading system implemented in the standard library.

It's untested, but it basically just leverages how C would do it.

If pthreads isn't your cup of tea, it should be fairly easy to FFI your favorite multithreading
library into CBAS using a wrapper.

## Can I use language feature X in CBAS?

Is there a way to do X (even if it is rather obtuse and difficult to read) in C?

Example: coroutines. They're not a C feature, but you can do what a coroutine does
by writing your own state machines.

Then the answer is "almost certainly yes" and you can make it look pretty and easy to
use to- that's what CBAS is all about.

## What memory model does CBAS use?

Compiletime CBAS hooks into the system's C library implementations of malloc, realloc, and free
which are exposed to compiletime code through "__builtin_" functions.

Runtime CBAS usually (see comment) behaves the same way.

COMMENT:

Runtime CBAS behaves the way that the code generator says it should. 

The "toc" code generator makes low-level CBAS code behave like C.

Theoretically you could make a backend for CBAS that generates code that is garbage collected.

## Are there any demonstrations of CBAS's true power?

There are some rather beautiful pieces of work in the standard metaprogramming library stdmeta,
but apart from that, no.

CBAS is a sapphire in the rough. Get your chisel.

## I looked through the code- isn't this just macros?

The majority of CBAS metaprogramming usage in the codebase is to implement macros, and indeed
CBAS does have one of the most intricate and flexible macro systems I know of, however CBAS's
metaprogramming facilities are not "just macros".

You can procedurally generate code at compiletime, manipulate the AST of the language, you name it.

CBAS's metaprogramming facilities have not been properly demonstrated, nor fully fleshed out yet.

You are forgiven if you "don't get it". **I** know that the theory is correct and ***I*** know
that CBAS is infinitely more powerful than "just macros".

I, the sole author, David MHS Webster, am still working on the "theory" of metaprogramming as it
pertains to the project.

## Do you accept contributions?

Ideas, yes, but absolutely no code submissions. Fork the project.

## What "real programming" can I do in CBAS immediately?

You can write code in the cbas metaprogramming language and the tool can compile to C, which
can then be compiled by GCC, TinyCC, or clang into target code. 

With a little bit of effort it should be trivial to compile cbas code to any target and not just C.

The cbas programming tool (cbas) is not the only thing in-box. This puppy comes with
batteries included, we have OpenAL 1.1, OpenGL 1.1, BSD sockets, a simple threading implementation 
and parts of SDL2 already available for programming.

While this does make cbas a capable programming language in its own right, it ultimately serves
as little more than a demo. I expect that any real development in the language will require FFI-ing
more libraries.

REPEAT: For "real" development, you should FFI your favorite C libraries into cbas.

OpenGL 1.1, OpenAL 1.1, usermode_stdlib, and funbas provide examples of how you do this.

## What is the potential of the project?

In the right hands, cbas could supersede every existing programming language.

Call me arrogant? Fuck you! I know I'm right!

I genuinely believe this technology could change the whole world.

## Why would you want to write cbas? Why not just write C++, Rust, Etc?

Other languages do not enable, or do not flexibly allow, the programmer to automate
their own work effectively. I've heard *idiots* brag at CPPcon about how C++ will
"never have mutable syntax". 

***Backwards cretins, that's what they are.***

cbas isn't just another programming language. It is a dynamo for letting clever people
make the language suit their needs. You can make the language bend to your will.

## What if I don't like how cbas looks/works?

You can write your own "skin" for it. Make your own custom language in cbas which
compiles to cbas during the execution of the `cbas` tool. You can even give it its own
file extension and everything, write your own lexer, you name it.

## Documentation?

Needs work, but the best we have is this:

`cbas -m help`

It's hardly sufficient, but it's better than nothing, right?

This is new technology hot from the press of my mind, still being developed. 

You're on your own, kid.

## The Grand Vision of CBAS

"Maximize the utilization of Man's intellectual capabilities"

CBAS allows programmers to make the language itself seamlessly meld with
your mind. You can make the structure of the language better reflect
the problem being solved, and even make problems easier to think about. 
You can then take this super language you've molded for your own purposes
and use it ANYWHERE YOU CAN IMAGINE. Write a code generator.

Taken to its extreme, I imagine this concept makes each programmer a 
"10x" version of himself, or more properly, a "1000x"
version. The end result should be that all intellectual output is boosted
drastically, to such a point that even a single gifted person using this tech 
can outperform a billion dollar company packed with geniuses.

Alright, maybe I'm exaggerating just a little, but this should seriously boost
productivity in software development (and then... the world!).

The natural progression of this ideology will eventually outgrow this tool,
as multimedia programming will eventually take over, but for now this is the
best I can really do. *Then we take over the world...*

CBAS represents my best attempt to advance humanity out of its delusional and
emotionally driven infancy into a utopian future.

## How close is CBAS to the accomplishment of this vision?

It has barely started. CBAS's raw immediate capabilities do not yet replace Rust or
C++, let alone revolutionize the industry.

If I just ported a bunch of libraries, it could definitely be a competitor, but not
a displacer as I envision.

If I can keep working on CBAS, and keep having good ideas, this should change soon.

## Do you have a time-estimate for how long this would take?

If I had 8 months of concentrated development time I could probably do it.

If you know any helpful spirits, wandering gods, fairies or gremlins that can offer their
assistance in my finishing this project... prayers, sacrificial offerings, and intercessions
are welcome.

## TECHNOLOGY DEVELOPMENT ROADMAP

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

## DOCUMENTATION AND PACKAGING ROADMAP

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

## Do you believe Coder's Basilisk has more potential for revolutionizing the world than neural network AIs?

It depends on how quickly we reach A.S.I. and what the state of the world is when that happens.

If ASI is <5 years away and we have a utopian future where it's all free software that anyone can use,
then I don't see how CBAS could be useful to anyone except as a curiosity when that happens.

If ASI is <5 years away and it's owned by a few small companies who get governments to lock it down
and prevent anyone else from having them, then CBAS may represent the best tech that us "normal folks"
can access.

If ASI is 40 years away, then CBAS and technology which is like it will likely define the period of
time until ASI comes around, and would probably what would be used to build ASI quicker than if it
had not come around.


