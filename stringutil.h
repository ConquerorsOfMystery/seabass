#ifndef STRUTIL_H
#define STRUTIL_H

/*
    Special brew of my string utility library especially for this project.
*/


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <stdint.h>

#ifndef STRUTIL_ALLOC
#define STRUTIL_ALLOC(s) malloc(s)
#endif

#ifndef STRUTIL_CALLOC
#define STRUTIL_CALLOC(n,s) calloc(n,s)
#endif

#ifndef STRUTIL_FREE
#define STRUTIL_FREE(s) free(s)
#endif

#ifndef STRUTIL_REALLOC
#define STRUTIL_REALLOC(s, t) realloc(s,t)
#endif

#ifndef STRUTIL_NO_SHORT_NAMES
#define strcata strcatalloc
#define strcataf1 strcatallocf1
#define strcataf2 strcatallocf2
#define strcatafb strcatallocfb
#endif





static inline char* strcatalloc(const char* s1, const char* s2){
    unsigned long ls1;
    unsigned long ls2;
    ls1 = strlen(s1);
    ls2 = strlen(s2);
    char* d = NULL; d = STRUTIL_ALLOC(ls1 + ls2 + 1);
    if(d){
        memcpy(d, s1, ls1);
        memcpy(d+ls1, s2, ls2+1);
    }
    return d;
}

static inline char* strcatallocf1(char* s1, const char* s2){
    unsigned long ls1;
    unsigned long ls2;
    ls1 = strlen(s1);
    ls2 = strlen(s2);
    char* d = STRUTIL_REALLOC(s1, ls1 + ls2 + 1);
    if(d){
        memcpy(d + ls1, s2, ls2+1);
    }
    return d;
}

static inline char* strcatallocf2(const char* s1, char* s2){
    unsigned long ls1;
    unsigned long ls2;
    ls1 = strlen(s1);
    ls2 = strlen(s2);
    char* d = NULL; d = STRUTIL_ALLOC(ls1 + ls2 + 1);
    if(d){
        memcpy(d, s1, ls1);
        memcpy(d + ls1, s2, ls2+1);
    }
    STRUTIL_FREE(s2);
    return d;
}

static inline char* strcatallocfb(char* s1, char* s2){
    unsigned long ls1;
    unsigned long ls2;
    ls1 = strlen(s1);
    ls2 = strlen(s2);
    char* d = NULL; d = STRUTIL_ALLOC(ls1 + ls2 + 1);
    if(d){
        memcpy(d, s1, ls1);
        memcpy(d+ls1, s2, ls2+1);
    }
    STRUTIL_FREE(s1);
    STRUTIL_FREE(s2);
    return d;
}


static inline char* str_null_terminated_alloc(const char* in, unsigned int len){
    char* d = NULL; d = malloc(len+1);
    if(d){
        memcpy(d,in,len);
        d[len] = '\0';
    }
    return d;
}



static inline unsigned int strprefix(const char *pre, const char *str)
{
        unsigned long lenpre = strlen(pre),
                     lenstr = strlen(str);
        return lenstr < lenpre ? 0 : memcmp(pre, str, lenpre) == 0;
}

static unsigned strpostfix(const char* str, const char* post)
{
        unsigned long lenpost = strlen(post),
                     lenstr = strlen(str);
        if(lenstr < lenpost) return 0;
        //we must check...
        str += lenstr-1;
        post += lenpost-1;
        for(;;){
            if(str[0] != post[0]) return 0;
            lenpost--;
            post--;
            str--;
            if(lenpost == 0) return 1;
        }
}

static inline unsigned int streq(const char *pre, const char *str)
{
        return strcmp(pre, str) == 0;
}

static long strfind(const char* text, const char* subtext){
    long ti = 0;
    long si = 0;
    long st = strlen(subtext);
    for(;text[ti] != '\0';ti++){
        if(text[ti] == subtext[si]) {
            si++;
            if(subtext[si] == '\0') return (ti - st)+1;
        }else{
            if(subtext[si] == '\0') return (ti - st)+1;
            ti-=si;si = 0;
        }
    }
    return -1;
}


static int str_inplace_repl_alloc(
    char** inbuf,
    char* replaceme,
    char* replacewith
){
    long loc;
    char* buf = *inbuf;
    if(!(buf)) return 0;
    loc = strfind(buf, replaceme);
    if(loc == -1) return 0;
    /*step 1- grab the before portion and make it into its own buffer.*/
    buf = str_null_terminated_alloc(*inbuf, loc);			if(!buf) goto error;
    /*step 2- add on the replacing text*/
    strcatallocf1(buf, replacewith); 						if(!buf) goto error;
    /*step 3- add on the after portion*/
    strcatallocf1(buf,(*inbuf) + loc + strlen(replaceme));	if(!buf) goto error;
    /*step 4- write the char* back*/
    inbuf[0] = buf;
    return 1;

    error:;
    *inbuf = NULL;
    return 0; /*error.*/
}

static unsigned long read_until_terminator(FILE* f, char* buf, const unsigned long buflen, char terminator){
    unsigned long i = 0;
    char c;
    for(i = 0; i < (buflen-1); i++)
    {
        if(feof(f))break;
        c = fgetc(f);
        if(c == terminator)break;
        buf[i] = c;
    }
    buf[buflen-1] = '\0';
    return i;
}





static char* read_until_terminator_alloced(FILE* f, unsigned long* lenout, char terminator, unsigned long initsize){
    char c;
    char* buf;
    unsigned long bcap = initsize;
    char* bufold;
    unsigned long blen = 0;
    buf = STRUTIL_ALLOC(initsize);
    if(!buf) return NULL;
    while(1){
        if(feof(f)){break;}
        c = fgetc(f);
        if(c == terminator) {break;}
        if(blen == (bcap-1))	/*Grow the buffer.*/
            {
                bcap<<=1;
                bufold = buf;
                buf = STRUTIL_REALLOC(buf, bcap);
                if(!buf){free(bufold); return NULL;}
            }
        buf[blen++] = c;
    }
    buf[blen] = '\0';
    *lenout = blen;
    return buf;
}


static void* read_file_into_alloced_buffer(FILE* f, unsigned long* len){
    void* buf = NULL;
    if(!f) return NULL;
    fseek(f, 0, SEEK_END);
    *len = ftell(f);
    fseek(f,0,SEEK_SET);
    buf = STRUTIL_ALLOC(*len + 1);
    if(!buf) return NULL;
    fread(buf, 1, *len, f);
    ((char*)buf)[*len] = '\0';
    return buf;
}



/*LIMITATIONS
GEK'S SIMPLE TEXT COMPRESSION SCHEMA
* Token names must be alphabetic (a-z, A-Z)
* The token mark must be escaped with a backslash.
* Token names which are substrings of other ones must be listed later
*/
static char* strencodealloc(const char* inbuf, const char** tokens, unsigned long ntokens, char esc, char tokmark){
    unsigned long lenin;
    unsigned long i = 0; unsigned long j;
    char c_str[512];
    char* out = NULL;

    lenin = strlen(inbuf);
    c_str[0] = esc;
    c_str[1] = tokmark;
    out = strcatalloc(c_str, "");
    c_str[0] = 0;
    c_str[1] = 0;
    c_str[511] = 0;

    for(j = 0; j < ntokens; j++){
        out = strcataf1(out, tokens[2*j]);

        sprintf(c_str, "%lu", (unsigned long)strlen(tokens[2*j+1]));
        out = strcataf1(out, c_str);
        c_str[0] = tokmark;
        c_str[1] = 0;
        out = strcataf1(out, c_str);
        out = strcataf1(out, tokens[2*j+1]);
    }
    c_str[0] = esc;
    c_str[1] = 0;
    out = strcataf1(out, c_str);

    for(i=0; i<lenin; i++){ unsigned long t;
        for(t = 0; t < ntokens; t++) /*t- the token we are processing.*/
            if(strprefix(tokens[t*2+1], inbuf+i)){ /*Matched at least one*/
                unsigned long h, curtoklen, howmany = 1;
                curtoklen = strlen(tokens[t*2+1]); /*Length of the current token we are counting*/
                for(h=1;i+h*curtoklen < lenin;h++){
                    if(strprefix(tokens[t*2+1], inbuf+i+h*curtoklen))
                        {howmany++;}
                    else
                        break; /*The number of these things is limited.*/
                }
                /*We know what token and how many, write it to out*/

                c_str[0] = tokmark;
                c_str[1] = 0;
                out = strcataf1(out, c_str);
                if(howmany > 1){
                    /*snprintf(c_str, 512, "%lu", (unsigned long)howmany);*/
                    sprintf(c_str, "%lu", (unsigned long)howmany);
                    out = strcataf1(out, c_str);
                }
                out = strcataf1(out, tokens[t*2]);
                i+=howmany*curtoklen;
                continue;
            }
        /*Test if we need to escape a sequence.*/
        if(inbuf[i] == esc || inbuf[i] == tokmark){
            c_str[0] = esc;
            c_str[1] = 0;
            out = strcataf1(out, c_str);
        }
        /*We were unable to find a match, just write the character out.*/
        c_str[0] = inbuf[i];
        c_str[1] = 0;
        out = strcataf1(out, c_str);
    }
    return out;
}

static char* strdecodealloc(char* inbuf){
    unsigned long lenin, ntokens;
    char* out;char** tokens = NULL; char esc; char tokmark; long doescape;
    char c; unsigned long vv,l,i = 2;
    char c_str[2] = {0,0};
    esc = inbuf[0];
    tokmark = inbuf[1];

    lenin = strlen(inbuf);


    out = strcatalloc("","");




    ntokens = 0;
        if(lenin < 3) {

        return NULL;
    }


    {if(i <= lenin) c = inbuf[i++]; else {goto end;}}; /*has to occur before the loop.*/
    while(c != esc){	ntokens++;
        tokens = STRUTIL_REALLOC(tokens, ntokens * 2 * sizeof(char*));


        tokens[(ntokens-1)*2] = strcatalloc("","");
        tokens[(ntokens-1)*2+1] = strcatalloc("","");


        if(!isalpha(c)) goto end;
        while(isalpha(c)){
            c_str[0] = c;
            tokens[(ntokens-1)*2] = strcatallocf1(tokens[(ntokens-1)*2], c_str);
            {if(i <= lenin) c = inbuf[i++]; else {goto end;}};
        }


        l = 0;
        if(!isdigit(c)) goto end;
        while(isdigit(c) && c!=tokmark){
            c_str[0] = c;
            l *= 10;
            l += atoi(c_str);
            {if(i <= lenin) c = inbuf[i++]; else {goto end;}};
        }



        for(vv = 0; vv < l; vv++){
            {if(i <= lenin) c = inbuf[i++]; else {goto end;}};
            c_str[0] = c;
            tokens[(ntokens-1)*2+1] = strcatallocf1(tokens[(ntokens-1)*2+1], c_str);
        }
        {if(i <= lenin) c = inbuf[i++]; else {goto end;}};

    }


    {if(i <= lenin) c = inbuf[i++]; else {goto end;}};
    doescape = 0;
    while(i<=lenin){
        if(!doescape && c==esc){
            doescape=1;{if(i <= lenin) c = inbuf[i++]; else {goto end;}};continue;
        }
        if(!doescape && c==tokmark){
            /*Handle digits prefixing a token.*/
            unsigned long t,l = 0;
            {if(i <= lenin) c = inbuf[i++]; else {goto end;}};
            if(isdigit(c))
                while(isdigit(c)){
                    c_str[0] = c;
                    l *= 10;
                    l += atoi(c_str);
                    {if(i <= lenin) c = inbuf[i++]; else {goto end;}};
                }
            else {l=1;}
            i--;

            for(t = 0; t < ntokens; t++)
                if(strprefix(tokens[t*2], inbuf+i)){ unsigned long q;
                    for(q = 0; q < l; q++)
                        out = strcatallocf1(out, tokens[t*2+1]);
                    i+=strlen(tokens[t*2]);
                    break; /*break out of the for.*/
                }

            if(i<=lenin) {if(i <= lenin) c = inbuf[i++]; else {goto end;}};
            continue;
        }else{
            c_str[0] = c;
            out = strcatallocf1(out, c_str);
            doescape = 0;
            {if(i <= lenin) c = inbuf[i++]; else {goto end;}};
        }
    }
    end:
    if(tokens){unsigned long j;
        for(j = 0; j < ntokens; j++)
            {STRUTIL_FREE(tokens[j*2]);STRUTIL_FREE(tokens[j*2+1]);}
        STRUTIL_FREE(tokens);
    }

    return out;
}



static char* str_repl_alloc(char* text, char* subtext, char* replacement){
    long bruh; char* result = NULL;
    bruh = strfind(text, subtext);
    if(bruh == -1) return (strcatalloc("", text)); /*This is already proper.*/
    result = str_null_terminated_alloc(text, bruh);
    result = strcatallocf1(result, replacement);
    result = strcatallocf1(result, text+bruh+strlen(subtext));
    return result;
}

static char* str_repl_allocf(char* text, char* subtext, char* replacement){
    char * result = str_repl_alloc(text, subtext, replacement);
    free(text);
    return result;
}

typedef struct strll{
    char* text;
    uint64_t linenum;
    uint64_t colnum;
    char* filename;
    void* data;
    struct strll* right;
}strll;

/*Make Child*/


static strll* consume_bytes(strll* current_node, unsigned long nbytes){
    strll* right_old; char* text_old;
    text_old = current_node->text;
    current_node->text = str_null_terminated_alloc(text_old, nbytes);
    right_old = current_node->right;
    current_node->right = STRUTIL_CALLOC(1, sizeof(strll));
    current_node->right->right = right_old;
    /*
        current_node->right->text = strcatalloc(text_old + nbytes, "");
        STRUTIL_FREE(text_old);
    */
    current_node->right->text = text_old;
    //perform a copy...
    char* dst = text_old;
    char* src = text_old + nbytes;
    size_t len_src = strlen(src);
    memmove(dst, src, len_src+1);
    return current_node->right;
}

//advance 
static inline strll* consume__bytes_with_bigstore(strll* current_node, unsigned long nbytes){
    strll* right_old; char* text_old;
    text_old = current_node->text;
    current_node->text = str_null_terminated_alloc(text_old, nbytes);
    right_old = current_node->right;
    current_node->right = STRUTIL_CALLOC(1, sizeof(strll));
    current_node->right->right = right_old;
    //We need to 
    current_node->right->text = text_old + nbytes;
    return current_node->right;
}

//used for whitespace....
static inline strll* skip__bytes_with_bigstore(strll* current_node, unsigned long nbytes){
    char* text_old;
    text_old = current_node->text;
    /*
    current_node->text = str_null_terminated_alloc(text_old, nbytes);
    right_old = current_node->right;
    current_node->right = STRUTIL_CALLOC(1, sizeof(strll));
    current_node->right->right = right_old;
    */
    //We need to 
    current_node->data = 0;
    current_node->text = text_old + nbytes;
    return current_node;
}





static strll* consume_until(strll* current_node, const char* find_me, const char delete_findable){
    long loc; strll* right_old; char* text_old;
    loc = strfind(current_node->text, find_me);
    if(loc < 0){ /*Nothing to do!*/
        return current_node;
    }
    /*loc was not -1.*/
    right_old = current_node->right;
    current_node->right = STRUTIL_CALLOC(1, sizeof(strll));
    current_node->right->right = right_old;
    text_old = current_node->text;
    current_node->text = str_null_terminated_alloc(text_old,loc + (delete_findable?strlen(find_me):0));
    current_node->right->text = strcatalloc(text_old + loc + strlen(find_me),"");
    STRUTIL_FREE(text_old);
    return current_node->right;
}

static strll tokenize(char* alloced_text, const char* token){
    strll result = {0}; strll* current;
    long current_token_location;
    long len_token;
    current = &result;
    len_token = strlen(token);
    current_token_location = strfind(alloced_text, token);
    while(current_token_location > -1){
        char* temp = strcatalloc(alloced_text+ current_token_location + len_token, "");
        current->text = str_null_terminated_alloc(alloced_text,current_token_location);
        STRUTIL_FREE(alloced_text);
        alloced_text = temp;
        current_token_location = strfind(alloced_text, token);
        current->right = STRUTIL_CALLOC(1, sizeof(strll));
        current = current->right;
    }
    STRUTIL_FREE(alloced_text);
    return result;
}


#endif
