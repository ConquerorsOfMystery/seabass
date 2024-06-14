
//ctok_main is the way to invoke the Seabass metaprogramming compiler itself.
//ctok_main is in ctok.c
//main has been moved out with the intention that it might be useful to 

int ctok_main(int argc, char** argv);

int main(int argc, char** argv){
    ctok_main(argc, argv);
}
