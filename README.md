Before anything else...

Blessings, Honor, Power, and Glory to our Lord and Saviour...

# Jesus of Nazareth

The Son of God, risen from the grave by his own power, alive forever. the
Mighty God, the King Eternal, whose mercies endure forever.

Give thanks and praise to him, for he is worthy.

Amen.

# Get FREE Blessings from the CREATOR OF HEAVEN AND EARTH!

Bless Abraham - Get blessed - Genesis 12:3. Jesus Christ is God, but he
came in the flesh after the seed of Abraham. Bless him

"If I have the power to bless, I Bless the Lord Jesus Christ, who is Worthy."

I don't know exactly what the blessing you get for blessing him is,
but God's attitude about his promises seems to be "Prove me now herewith" 
(Malachi 3:10 KJV)

I do not deserve the wonderful things he has given me.

He can give you eternal life too. God raised him from the dead. Believe
the report and confess him with your mouth and he'll save you.


# THE SEABASS METAPROGRAMMING LANGUAGE

Welcome! This repository contains the code for the Seabass metaprogramming
tool along with some libraries and example code.

All of it is public domain.

# What is this?

A programming language... sort of. A tool for programming which can help you write code
better/faster.

The rough concept is that it's a programming language that you can extend using itself,
mutable and extensible both syntactically and in structure.

# How do I use it?

make and install the `cbas` tool. `make q` on a typical Linux machine using sudo/doas or as root
should do the trick. I use a program I wrote called "admin". You should just be able to compile all
the .c files in the top level directory together `gcc -O3 *.c -o cbas` and that _should_ give you
a working cbas tool. Make sure to delete any `auto_out.c` files in the top level (should any
be left).

# What can it do right now?

You can write code in the seabass metaprogramming language and the tool will compile to C, which
can then be compiled by GCC into target code. It should be possible to retarget Seabass easily-
this is part of how it was designed.

The tool itself does syntax error checking although due to the nature of metaprogramming
it is very easy for errors to crop up which are difficult to track down. No line/column
numbers are given for internally generated code.

There is a metaprogramming library- you should be able to use the tools contained therein
to rapidly lay down code equivalent to C. 

OpenGL 1.1 and OpenAL 1.1 have both been ported (notwithstanding mistakes/errors). There is
a graphics library based on SDL2.

# What is the potential of the project?

To be blunt- I do not know. My hope is that it can be made to maximally extend and take
advantage of man's God-given talents.

I believe this tool and this language can be useful for programming and help people
write better code more quickly.

# Why would you want to write Seabass? Why not just write C?

In short- custom abstractions, custom syntax sugars, and compiler extension.

Your source code can extend and manipulate the compilation process, from parsing
to code generation.

In standard C, I do not believe Seabass's practical capabilities are matched in this regard.


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

https://conquerors_of_mystery.codeberg.page/seabass/



