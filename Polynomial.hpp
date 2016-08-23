/* -----------------------------------------------------------------------------

FILE NAME:         Polynomial.HPP

DESCRIPTION:       This is the specification file for the Polynomial class

PURPOSE:           The purpose of this file is to specify the Polynomial class
                   and to provide prototypes for its member functions.

USAGE:             In the linux command line, type ./polynomial

EXAMPLES:          To run the program, type ./polynomial in the linux command line

PARAMETERS:        N/A

EXIT CODES:        0 = Success
                   1 = Error: INDEX_OUT_OF_RANGE

COMPILATION:       Linux GNU

NOTES:             - 
                     
MODIFICATION HISTORY:

Author          Date           Modification(s)
-------------   -----------    ---------------
Adam Landis     04-14-2016     Version 0001
Adam Landis     04-14-2016     Version 0002
Adam Landis     04-15-2016     Version 0003
Adam Landis     04-16-2016     Version 0004
Adam Landis     04-21-2016     Version 0005
Adam Landis     04-21-2016     Version 0006
Adam Landis     04-21-2016     Version 0007
Adam Landis     04-22-2016     Version 0008
Adam Landis     04-22-2016     Version 0009
Adam Landis     04-27-2016     Version 0010
Adam Landis     04-27-2016     Version 0011

----------------------------------------------------------------------------- */

#ifndef __Polynomial_HPP__
#define __Polynomial_HPP__

#include <iostream>
#include <math.h>       /* for using pow (in evaluateX() function)*/
#include <vector>
#include <string>

using std::ostream;
using std::istream;
using std::vector;
using std::string;
using std::to_string;

enum errors_t {INDEX_OUT_OF_RANGE = 1};

/* Some compilers require the >> and << operator functions to be prototyped outside 
the class. The following three lines of code are needed to avoid any compilation problems. */
class Polynomial;   // Forward Declaration

// Function prototypes for Overloaded Stream Operators
ostream &operator << (ostream &, const Polynomial &);
istream &operator >> (istream &, Polynomial &);

class Polynomial
{
    private: // Everything following this is invisible from the outside
        int _degree;
        int _array_size;
        int * _terms_array;
        errors_t _ERROR_CODES;
    
    public: // Everything following this is visible from the outside
        
        /***** Constructor(s) *****/
        // Default Constructor
		Polynomial();
        
        // Overloaded Constructor
        Polynomial(const int, const int *);
        
        // Copy Constructor
		Polynomial(const Polynomial &);
        
		/***** Destructor *****/
		~Polynomial();
        
	    /***** Accessor functions *****/
        int getTerm(int) const;
        int getArraySize() const;
        int getDegree() const;
        
        /***** Setter (Mutator) functions *****/
        void setTerm(int, int);
		
        /***** Work functions *****/
        Polynomial polyMax(const Polynomial &);
        int arrayMin(const Polynomial &);   
        double evaluateX(double) const;
        bool allZeros(int, const int, const int *) const;
        
        /***** Error Handling function *****/
        void errorHandler(const int);
        
        /***** Operator functions *****/
        // Object assignment, overloading the = operator
        Polynomial operator = (const Polynomial &);
        
        // Object addition, overloading the + operator
        Polynomial operator + (const Polynomial &);
        
        // Object subtraction, overloading the - operator
        Polynomial operator - (const Polynomial &);
        
        // Object multiplication, overloading the * operator
        Polynomial operator * (const Polynomial &);
        Polynomial operator * (const int) const;
        
        // Object equality testing, overloading the == operator
        bool operator == (const Polynomial &);
        
        /***** Friends *****/
        // Object output, overloading the << operator
        friend ostream &operator << (ostream &, const Polynomial &);
        
        // Object input, overloading the >> operator
        friend istream &operator >> (istream &, Polynomial &);
    
};

#endif /* __Polynomial_HPP__ */