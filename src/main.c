#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdarg.h>

#include "minIni.h"


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
    char *sectionname = NULL;
    char *keyname = NULL;
    int opt;
    opcode_t opcode = NOP;

    struct option longopts[] = {
        {"help", 0, NULL, 'h'},
        {"verbose", 0, NULL, 'v'},
        {"file", 1, NULL, 'f'},
        {"set", 0, NULL, 's'},
        {"get", 0, NULL, 'g'},
        {"section", 0, NULL, 'c'},
        {"key", 0, NULL, 'k'},
        {0,0,0,0}
    };

    //first getting the filename value from the env, if there is a
    //file cmd line argument, it will overwrite the env value
    inifilename = getenv("MANINI_INIFILEPATH");
    print_msg(2,"Read filename from environment: %s\n", inifilename);

    while((opt = getopt_long(argc, argv, "hvf:sgck", longopts, NULL)) != -1) {
        switch(opt) {
            case 'h':
                print_help();
                break;
            case 'v':
                verbosity++;
                break;
            case 's':
                if (opcode) exit_error(-1, "Multiple operation argument, exiting\n");
                opcode = SET;
                break;
            case 'g':
                if (opcode) exit_error(-1, "Multiple operation argument, exiting\n");
                opcode = GET;
                break;
            case 'f':
                print_msg(2,"Got filename from command line: %s\n", inifilename);
                inifilename = optarg;
                break;
            case 'c':
                print_msg(2,"Got sectionname from command line: %s\n", inifilename);
                sectionname = optarg;
                break;
            case 'k':
                print_msg(2,"Got keyname from command line: %s\n", inifilename);
                keyname = optarg;
                break;
            case ':':
                exit_error(-1,"option needs a value\n");
                break;
            case '?':
                exit_error(-1,"unknown option: %c\n", optopt);
                break;
        }
    }
    print_msg(1, "verbosity: %d\n", verbosity);
    print_msg(1, "Ini filename: %s\n", inifilename);
    print_msg(1, "Ini sectionname: %s\n", sectionname);
    print_msg(1, "Ini keyname: %s\n", keyname);
    switch(opcode){
        case GET:
            ret = ini_gets("first", "string", "", str, sizearray(str), inifilename);
            printf ("string value: %s\n", str);
            break;
        case SET:
            print_msg(0,"SET not implemented yet\n");
            //ret = ini_gets("first", "string", "", str, sizearray(str), inifilename);
            //printf ("string value: %s\n", str);
            break;
    }

    return 0;
}
