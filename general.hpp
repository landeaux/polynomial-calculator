/* -----------------------------------------------------------------------------

FILE NAME:         general_ver3.HPP

DESCRIPTION:       General stuff for all files

PURPOSE:           The purpose of this file is to provide useful macros for the
                   rest of the program to utilize.

USAGE:             In the linux command line, type ./polynomial

EXAMPLES:          To run the program, type ./polynomial in the linux command line

PARAMETERS:        N/A

EXIT CODES:        0 = Success
                   Otherwise = Error

COMPILATION:       Linux GNU

NOTES:             - removed GLOBAL_SHOW_LOCATION macro. only needed for 
                     debugging

MODIFICATION HISTORY:

Author          Date           Modification(s)
-------------   -----------    ---------------
Adam Landis     04-14-2016     Version 0001
Adam Landis     04-16-2016     Version 0002
Adam Landis     04-21-2016     Version 0003
Adam Landis     04-27-2016     Version 0004

----------------------------------------------------------------------------- */

#ifndef __GENERAL_HPP__
#define __GENERAL_HPP__

#include <iostream>
#include <cstring> // Brings in the C-string handling functions

// URL:  http://stackoverflow.com/questions/4062045/clearing-terminal-in-linux-with-c-code
#define CLEAR_SCREEN \
    std::cout << "\033[2J\033[1;1H"

#define PRINT_LOCATION(x) \
    std::cout << "We are here: " << x << std::endl

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

#define MAX(x,y) ((x) > (y) ? (x) : (y))

#define MIN(x,y) ((x) < (y) ? (x) : (y))

#endif /* __GENERAL_HPP__ */