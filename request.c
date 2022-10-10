/* request.c: Make HTTP Requests */

#include "request.h"

#include "macros.h"
#include "socket.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

/* Constants */

#define HOST_DELIMITER  "://"
#define PATH_DELIMITER  '/'
#define PORT_DELIMITER  ':'

/* Functions */

/**
 * Construct Request structure by parsing URL string into separate host, port,
 * and path components.
 *
 * @param   url         URL string to parse.
 *
 * @return  Request structure.
 **/
Request *   request_create(const char *url) {
    /* TODO: Copy data to local buffer */
    char buff[BUFSIZ];
    strcpy(buff, url);
    char *host, *port, *path;
    /* TODO: Skip scheme to host */
    if((host = strstr(buff, HOST_DELIMITER)) != 0){
        host += 3; // accounts for 3 chars of '://'
    }else{
        host = buff; // if there is no protocol, the host just begins at the whole url
    }
    /* TODO: Split host:port from path */
    path = strchr(host, PATH_DELIMITER);
    if(!path) path = "";
    else{
        *path = 0;
        path++;
    }
    /* TODO: Split host and port */
    port = strchr(host, PORT_DELIMITER);
    if (!port) port = "80";
    else{
        *port = 0;
        port++;
    }
    /* TODO: Allocate Request structure */
    Request *req = malloc(sizeof(Request));
    if (!req){ // Check to ensure req is allocated
        fprintf(stderr, "malloc: %s\n", strerror(errno));
        return NULL;
    }
    /* TODO: Copy components to URL structure */
    req->host = strdup(host);
    req->port = strdup(port);
    req->path = strdup(path);
    
    return req;
}

/**
 * Deallocate Request structure.
 *
 * @param   request     Request structure to deallocate.
 **/
void	    request_delete(Request *request) {
    free(request->path);
    free(request->port);
    free(request->host);
    free(request);
}

/**
 * Make a HTTP request and write the contents of the response to the specified
 * stream.
 *
 * @param   url         Make a HTTP request to this URL.
 * @param   stream      Write the contents of response to this stream.
 *
 * @return  -1 on error, otherwise the number of bytes written.
 **/
ssize_t     request_stream(Request *request, FILE *stream) {
    if(!request) return -1;
    if(!stream) return -1;
    ssize_t content_length = 0;
    ssize_t numread = 0;
    ssize_t temp = 0;
    /* TODO: Connect to remote host and port */
    FILE *client_file = socket_dial(request->host, request->port);
    if(!client_file) return -1;
    /* TODO: Send request to server */
    fprintf(client_file, "GET /%s HTTP/1.0\r\n", request->path);
    fprintf(client_file, "Host: %s\r\n", request->host);
    fprintf(client_file, "\r\n");
    /* TODO: Read response status from server */
    char buffer[BUFSIZ];
    if(!fgets(buffer, BUFSIZ, client_file)) return -1;
    if(!strstr(buffer, "200 OK")) return -1;
    /* TODO: Read response headers from server */
    while(fgets(buffer, BUFSIZ, client_file) && strlen(buffer) > 2){
        sscanf(buffer, "Content-Length: %lu", &content_length);
    }
    /* TODO: Read response body from server */
    while ((temp = fread(buffer, 1, BUFSIZ, client_file))){
    numread += fwrite(buffer, 1, temp, stream);
    }
    
    /* TODO: Close connection */
    fclose(client_file);
    /* TODO: Return number of bytes written and check if it matches Content-Length */
    if(content_length == 0 || content_length == numread) return numread;
    return -1;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
