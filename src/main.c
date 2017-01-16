/*
 * Copyright (c) 2016 Zoltan Gyarmati (http://zgyarmati.de)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdarg.h>

#include "minIni.h"
#include "../config.h"


#define sizearray(a)  (sizeof(a) / sizeof((a)[0]))

int verbosity = 0;

typedef enum {
    NOP,
    GET,
    SET
} opcode_t;

void print_help(){
    fputs("HELP!\n", stderr);
}

/* prints the got message to the stderr, but only if the verbosity level
 * lets us
 */
void print_msg(const int level, const char *fmt, ...){
    if(verbosity < level){
        return;
    }
    fputs("manini: ", stderr);
    va_list args;
    va_start (args, fmt);
    vfprintf(stderr,fmt, args);
}

void print_version(){
    fputs(PACKAGE_STRING"\n", stderr);
}

/* prints the given error message, and exits the application
 * with the given error code
 */
void exit_error(const int code, const char* fmt, ...){
    va_list args;
    va_start (args, fmt);
    print_msg(0, fmt, args);
    exit(code);
}

int main(int argc, char *argv[]) {
    int ret; //used for checking return values
    char str[INI_BUFFERSIZE];
    char *inifilename = NULL;
    int opt;
    opcode_t opcode = NOP;

    struct option longopts[] = {
        {"help", 0, NULL, 'h'},
        {"verbose", 0, NULL, 'v'},
        {"file", 1, NULL, 'f'},
        {"set", 0, NULL, 's'},
        {"get", 0, NULL, 'g'},
        {0,0,0,0}
    };

    //first getting the filename value from the env, if there is a
    //file cmd line argument, it will overwrite the env value
    inifilename = getenv("MANINI_INIFILEPATH");

    while((opt = getopt_long(argc, argv, "Vhvf:sgck", longopts, NULL)) != -1) {
        switch(opt) {
            case 'V':
                print_version();
                break;
            case 'h':
                print_help();
                break;
            case 'v':
                verbosity++;
                break;
            case 'f':
                print_msg(2,"Got filename from command line: %s\n", inifilename);
                inifilename = optarg;
                break;
            case 's':
                if (opcode) exit_error(-1, "Multiple operation argument, exiting\n");
                opcode = SET;
                break;
            case 'g':
                if (opcode) exit_error(-1, "Multiple operation argument, exiting\n");
                opcode = GET;
                break;
            case ':':
                exit_error(-1,"option needs a value\n");
                break;
            case '?':
                exit_error(-1,"unknown option: %c\n", optopt);
                break;
        }
    }
    print_msg(1, "Verbosity: %d\n", verbosity);
    if (!inifilename){
        exit_error(-1, "No ini file specified, you need to set the "
                       "MANINI_INIFILEPATH envvar or use -f </path/to/file>\n");
    }
    print_msg(1, "Ini filename: %s\n", inifilename);
    int i;
    print_msg(1,"ARGC: %d, ARGC-OPTIND: %d\n", argc, argc -optind);
    for (i = optind; i < argc; i++){
            print_msg(2, "<<<<  POS argument <%d> %s\n", i, argv[i]);
    }

    // so we have this number of positional args after getopt is ready
    int positional_argc = argc - optind;
    print_msg(1, "SECTION: %s\n", argv[optind]);
    print_msg(1, "KEY: %s\n", argv[optind+1]);
    switch(opcode){
        case GET:
            if (positional_argc != 2 && positional_argc !=3 ){
                print_msg(0,"Incorrect invocation, for getting a value, call:\n");
                print_msg(0,"%s --get [--configfile test.ini] section key [default val]\n", argv[0]);
                exit_error(-1, "Incorrect section/key arguments, exiting\n");
            }
            print_msg(1, "DEFVAL: %s\n", argv[optind+2]);
            ret = ini_gets(argv[optind], argv[optind+1], argv[optind+2], str, sizearray(str), inifilename);
            if(!ret){
                exit_error(-2,"minIni error when trying to set value\n");
            }
            puts(str);
            break;
        case SET:
            if (positional_argc !=3 ){
                print_msg(0,"Incorrect invocation, for setting a value, call:\n");
                print_msg(0,"%s --get [--configfile test.ini] section key value\n", argv[0]);
                exit_error(-1, "Incorrect section/key arguments, exiting\n");
            }
            print_msg(1, "VALUE: %s\n", argv[optind+2]);
            ret = ini_puts(argv[optind], argv[optind+1], argv[optind+2], inifilename);
            puts(str);
            break;
    }

    return 0;
}
