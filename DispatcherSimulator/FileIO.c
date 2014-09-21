/*************************************************************************/
/*                                                                       */
/* Copyright (c) 2011 Abelardo Lopez Lagunas                             */
/*                                                                       */
/* File name: FileIO.h                                                   */
/*                                                                       */
/* Author:                                                               */
/*          Abelardo Lopez Lagunas                                       */
/*                                                                       */
/* Edited by:                                                            */
/*          Mario García Navarro                                         */
/*                                                                       */
/* Purpose:                                                              */
/*          Support routines that handle reading ASCII files             */
/*                                                                       */
/* References:                                                           */
/*          Based on my own code, but won't be surprised if it is        */
/*          similar to other code out there                              */
/*                                                                       */
/* Restrictions:                                                         */
/*          All functions return EXIT_FAILURE in case something went     */
/*          wrong                                                        */
/*                                                                       */
/* Revision history:                                                     */
/*          Feb  4 15:15 2011 -- File created                            */
/*                                                                       */
/*          May 22 09:13 2012 -- Added recognition of negative numbers   */
/*                                                                       */
/* Error handling:                                                       */
/*          None                                                         */
/*                                                                       */
/* Notes:                                                                */
/*          Support routine that reads an ASCII file and returns an      */
/*          integer value skiping over non-numeric data                  */
/*                                                                       */
/*************************************************************************/

#include <stdlib.h>              /* Used for getc() and feof() functions */
#include <ctype.h>                    /* Used for the isdigit() function */
#include <stdio.h>                       /* Used to handle the FILE type */
#include "FileIO.h"                                   /* Function header */

/*************************************************************************/
/*                                                                       */
/*  Function: GetInt                                                     */
/*                                                                       */
/*  Purpose: The function will read the input file and return an integer */
/*           representing the ASCII characters that form a number. It    */
/*           skips over comments, which begin a line with a #, and other */
/*           ASCI characters that do not represent numbers               */
/*                                                                       */
/*  Parameters:                                                          */
/*            Input :   Pointer to the text file to parse                */
/*                                                                       */
/*            Output:   Integer representing value, only positive values */
/*                      are possible. If the end of file is reached, a   */
/*                      -1 is returned                                   */
/*                                                                       */
/*************************************************************************/

int GetInt (FILE *fp){
    int	c, i;         /* Character read and integer representation of it */
    int sign = 1;
    
     /* Skip the comment */
    do {
        c = getc (fp);                          /* Get next character */
        if ( c == '#' )
            do {
                c = getc (fp);
            } while ( c != '\n');
         /* This is for take account the negative sign, in case the number has */
        if ( c == '-')
            sign = -1;
    } while (!isdigit(c) && !feof(fp));
    
    if (feof(fp))
        return (EXIT_FAILURE);
    else {
        
    /* Found 1st digit, begin conversion until a non-digit is found */
        i = 0;
        while (isdigit (c) && !feof(fp)){
            i = (i * 10) + (c - '0');         /* ASCII conversion */
            c = getc (fp);
        }
        
        return (i * sign);
    }
}

/************************************************************************/
/*                                                                      */
/*  Function: ErrorMsg                                                  */
/*                                                                      */
/*  Purpose: Prints an error message and then gracefully terminate the  */
/*           program. This is the release version of assert.            */
/*                                                                      */
/*  Parameters:                                                         */
/*            Input :  String with the error message                    */
/*                                                                      */
/*            Output:  Prints the error in standard output and exit     */
/*                                                                      */
/************************************************************************/

void ErrorMsg (char * function, char *message){
    
    printf ("\nError in function %s\n", function);
    printf ("\t %s\n", message);
    printf ("The program will terminate.\n\n");
    
}
