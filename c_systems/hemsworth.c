/* thor.c */

#include "hammer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Functions */

void usage(const char *progname, int status) {
    fprintf(stderr, "Usage: %s [options] URL\n", progname);
    fprintf(stderr, "    -n HAMMERS How many times to hammer the URL\n");
    exit(status);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* TODO: Parse command line arguments */

    if(argc == 1) usage(argv[0], EXIT_FAILURE);

    int hammers = 1;
    int argind = 1;
    char *url = NULL;

    while(argind < argc){
        char *argument = argv[argind++];
        // printf("check: %d %s\n", argind, argv[argind]);
        if(argument[0] == '-'){
            switch(argument[1]){
                case 'h':
                    usage(argv[0], EXIT_SUCCESS);
                    break;
                case 'n':
                    hammers = atoi(argv[argind++]);
                    // printf("argind: %d %s\n", argind, argv[argind]);
                    break;
                default:
                    usage(argv[0], EXIT_FAILURE);
            }
        }else{
            url = argument;
        }
    }

    // printf("Hammers: %d\n", hammers);
    /* TODO: Throw Hammers */
    return(!(throw(url, hammers, stdout)));

    return EXIT_FAILURE;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
