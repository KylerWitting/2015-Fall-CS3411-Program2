/*
*  Author:    Kyler Witting
*  Date:    10/29/15
*  Class:    CS3411
*  Semester:    Fall 2015
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
int main( int argc, char **argv ){

    //arguments
    int i, status, finish = 1;
    pid_t *childPID;
    char buffer[256];
    
    //checks to make sure there is arguments 
    if ( argc < 2 ) {
        sprintf( buffer, "No arguments were given.\n" );
        write( 2, buffer, strlen( buffer ) );
        return (-1);
    }
    
    //uses mkdir to check if directory is there
    //if it is not, makes it with 0777 permissions 
    //if it exists, it prints out error message saying that
    //any other error happens, it uses perror to print out the error
    if(mkdir( "./SORTED", S_IRWXU ) == 0) {
        sprintf( buffer, "Creating SORTED folder with 0700 Permissions.\n" );
        write( 1, buffer, strlen( buffer ) );    
    }
    else if (errno == EEXIST) {
        sprintf( buffer, "SORTED folder already exists.\n" );
        write( 2, buffer, strlen( buffer ) );
    }
        else
            perror( "mkdir" );
    
    
    childPID = (pid_t*)malloc(sizeof(pid_t)*(argc));
    //for each argument, forks a new child from parent
    //calls execve, prints error if there is one
    //and then sleeps for 20 seconds before exiting
    for ( i = 1; i < argc; i++ ) {
        char output[256];
        sprintf( output, "SORTED/%s", argv[i] );
        char *newARGV[] = { "sort", "-o", output, argv[i], NULL };
        if ( childPID[i] = fork() == 0 ) {
            execve( "/usr/bin/sort", newARGV);
            perror( "execve" );
            exit( 0 );
        }    
    }
    
    //Goes through each argument, waits on the child PID
    //Prints if the sort was successful, and if not, prints error code
    for ( i = 1; i < argc; i++ ) {
        waitpid( childPID[i], &status, 0 );
        if ( status == 0 )
           sprintf( buffer, "%s : success (%d)\n", argv[i], status );
        else {
            finish = 0;
            sprintf( buffer, "%s : fail (%d)\n", argv[i], status );
            
        }
        write( 1, buffer, strlen( buffer ) );
    }

    //Prints the all done if there was no errors
    //informs you if there were errors
    if ( finish == 1 ) 
        sprintf( buffer, "All Done.\n" );
    else
        sprintf( buffer, "All Done. Error was encountered.\n" );
    write( 1, buffer, strlen( buffer ) );

    free(childPID);
    return 0;   
}

