#ifndef EXT_H
#define EXT_H

#include <fcntl.h>      
#include <unistd.h>     
#include <sys/stat.h> 
#include <dirent.h>     
#include <sys/types.h>  
#include <errno.h>      
#include <string.h>     
#include <stdlib.h>     
#include <stdio.h>      

#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <netdb.h>     

#include <curl/curl.h>

#include <limits.h>     
#include <unistd.h>     

#include <time.h>
#include <sys/time.h>
void traverse_folder(const char *path, void (*file_callback)(const char *file_path));
int upload_file(const char *filepath);

#endif