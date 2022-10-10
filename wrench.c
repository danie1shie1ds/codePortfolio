/* hammer.c: Make HTTP request and measure bandwidth */

#include "hammer.h"
#include "macros.h"
#include "request.h"
#include "timestamp.h"

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Constants */

#define MEGABYTE    (double)(1<<20)

/* Functions */

/**
 * Perform a hammer through by making a HTTP request to the specified URL and
 * printing the contents of the response to the given stream.
 * Function prints the bandwidth of the HTTP transaction if it is successful to
 * stderr.
 *
 * @param   url         Make HTTP request to this URL.
 * @param   stream      Write the contents of each response to this stream.
 *
 * @return  Whether or not the HTTP request was successful.
 **/
bool	hammer(const char *url, FILE *stream) {
    if(!url) return false; // Check for null pointers
    if(!stream) return false;
    
    double before;
    before = timestamp();
    if(!before) return false;
    double after;
    /* TODO: Perform HTTP request */
    Request *req = request_create(url);
    if (req == NULL) return false; // checks if request_create fails

    ssize_t bytes_written = request_stream(req, stream);
    if(bytes_written < 1){
        request_delete(req);
        return false;
    }
    after = timestamp();
    if(!after){
        request_delete(req);
        return false;
    }
    /* TODO: Compute and display bandwith to stderr if HTTP request was
     * successful */
    if(req != NULL){
        double bandwidth = (double)bytes_written / 1048576.0 / (after - before);
        fprintf(stderr, "Bandwidth: %0.2lf MB/s\n", bandwidth);
        request_delete(req);
        bytes_written = -1;
        return true;
    }
    
    request_delete(req);
    return false;
}

/**
 * Make hammers HTTP requests to the specified url, while writing the contents
 * of the request to the specified stream.
 *
 * Each HTTP request must be performed by a separate child process.
 *
 * Function prints the total elapsed time for all throws to stderr at the end.
 *
 * @param   url         Make HTTP requests to this URL.
 * @param   hammers     The number of HTTP requests to make.
 * @param   stream      Write the contents of each response to this stream.
 *
 * @return  Whether or not all hammer throws were successful.
 **/
bool	throw(const char *url, size_t hammers, FILE *stream) {
    int status = 0;
    double before = timestamp();
    /* TODO: Throw all hammers by spawning child processes that call hammer and
     * exit success if the hammer throw was successful. */
    for(size_t i = 0; i < hammers; i++){
        pid_t pid = fork();
        if(pid == 0){
            if(hammer(url, stream)) exit(false);
            else exit(true);
        }else if (pid < 0){
            return false;
        }
    }
    /* TODO: Collect results of throws by waiting for all children */
    

    pid_t kid;
    for(size_t i = 0; i < hammers; i++){
        while((wait(&kid)) < 0);
        status += kid;
    }
    double after = timestamp();

    /* TODO: Print elapsed time to stderr */
    fprintf(stderr, "Elapsed Time: %0.2lf seconds\n", (double)(after-before));

    return (status == 0);
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
