/* -----------------------------------------------------------------------------

FILE NAME:         driver.CPP

DESCRIPTION:       This is the driver program for the Polynomial class

PURPOSE:           This program tests the member functions and other operations
                   for the Polynomial Class. It demonstrates Object assignment, 
                   Object addition, Object subtraction, Object multiplication, Object 
                   equality testing, Object output, Object output, and Object 
                   evalutaion.

USAGE:             In the linux command line, type ./polynomial

EXAMPLES:          To run the program, type ./polynomial in the linux command line

PARAMETERS:        N/A

EXIT CODES:        0 = Success
                   Otherwise = Error

COMPILATION:       Linux GNU

NOTES:             - added function headers to all new test functions.
                   - removed old test code
                   - removed debugging code

MODIFICATION HISTORY:

Author          Date           Modification(s)
-------------   -----------    ---------------
Adam Landis     04-14-2016     Version 0001
Adam Landis     04-15-2016     Version 0002
Adam Landis     04-15-2016     Version 0003
Adam Landis     04-15-2016     Version 0004
Adam Landis     04-15-2016     Version 0005
Adam Landis     04-16-2016     Version 0006
Adam Landis     04-21-2016     Version 0007
Adam Landis     04-21-2016     Version 0008
Adam Landis     04-21-2016     Version 0009
Adam Landis     04-22-2016     Version 0010
Adam Landis     04-23-2016     Version 0011
Adam Landis     04-27-2016     Version 0012
Adam Landis     04-27-2016     Version 0013
Adam Landis     04-27-2016     Version 0014
Adam Landis     04-27-2016     Version 0015
Adam Landis     04-27-2016     Version 0016

----------------------------------------------------------------------------- */

#include "Polynomial.hpp"
#include "general.hpp"
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

int genRandNum(int, int);
Polynomial genRandPoly();

// Function prototypes for testing the member function of the Polynomial class
void displayPolyDetails(const Polynomial &);
void testDefaultConstructor();
void testOverloadedConstructor();
void testOverloadedConstructor();
void testCopyConstructor();
void testObjectAssignment();
void testObjectAddition();
void testObjectSubtraction();
void testObjectMultiplication();
void testObjectEquality();
void testObjectOutput();
void testEvaluateX();
void testObjectInput();

int main()
{   
    srand((unsigned)time(0)); // seed the random number generator
     
    CLEAR_SCREEN;
	
    testDefaultConstructor();
    testOverloadedConstructor();
    testCopyConstructor();
    testObjectAssignment();
    testObjectAddition();
    testObjectSubtraction();
    testObjectMultiplication();
    testObjectEquality();
    testObjectOutput();
    testEvaluateX();
    testObjectInput();
    
    cout << endl;
    
    return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     genRandNum(int floor, int ceiling)
PURPOSE:           Generates a random number between given floor and ceiling
RETURNS:           An integer representing the random number
NOTES:             
----------------------------------------------------------------------------- */
int genRandNum(int floor, int ceiling)
{    
    int range = ceiling - floor;
    int rand_num = (rand() % (range + 1)) + floor; 
    
    return rand_num;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     genRandPoly()
PURPOSE:           Generates a random polynomial
RETURNS:           returns a random Polynomial object
NOTES:             
----------------------------------------------------------------------------- */
Polynomial genRandPoly()
{
    int size = genRandNum(1,5);
    int degree = size - 1;
    int * array = new int [size];
    for (int index = 0; index < size; index++)
        *(array + index) = genRandNum(-20,20);
        
   Polynomial temp(degree, array);
   delete [] array;
   
   return temp;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     displayPolyDetails(const Polynomial &poly)
PURPOSE:           Displays details about a Polynomial object
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void displayPolyDetails(const Polynomial &poly)
{
    int degree = poly.getDegree();
    
    cout << "Here are the results: " << endl << endl;
    cout << "f(x)   = " << poly << endl;
    cout << "Degree = " << poly.getDegree() << endl;
    cout << "Size   = " << poly.getArraySize() << endl;
    
    cout << "Coefficients of each term..." << endl;
    for (int idx = degree; idx >= 0; idx--)
        cout << "x^" << idx << ": " << poly.getTerm(idx) << endl;
    
    cout << endl;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     testDefaultConstructor()
PURPOSE:           Tests the Default Constructor
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void testDefaultConstructor()
{
    cout << "Testing the Default Construtor" << endl << endl;
    cout << "Defining an instance of the Polynomial class ";
    cout << "with no parameters..." << endl;
    Polynomial temp;
    cout << "Instance 'temp' created." << endl << endl;
    
    displayPolyDetails(temp);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     testOverloadedConstructor()
PURPOSE:           Tests the Overloaded Constructor
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void testOverloadedConstructor()
{   
    Polynomial * objPtr;
    
    cout << "Testing the Overloaded Construtor" << endl << endl;
    cout << "Defining an instance of the Polynomial class ";
    cout << "with two parameters." << endl << endl;
    
    cout << "Overloading the constructor with degree of 0 and array of {0}..." << endl;
    int * array = new int [1]();
    objPtr = new Polynomial(0,array);
    displayPolyDetails(*objPtr);
    delete [] array;
    array = nullptr;
    delete objPtr;
    objPtr = nullptr;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    
    cout << "Overloading the constructor with degree of 1 and array of {1,0}" << endl;
    cout << "(to test initialization with an array that contains leading zeros)...";
    int array2[2] = {1, 0};
    objPtr = new Polynomial(1,array2);
    displayPolyDetails(*objPtr);
    delete [] array;
    array = nullptr;
    delete objPtr;
    objPtr = nullptr;  
    
    int num_rand_polys = 5;
    cout << "Generating " << num_rand_polys << " random polynomials..." << endl;
    cout << "======================================" << endl << endl;
    for (int count = 0; count < num_rand_polys; count++)
    {
        cout << "Generating random polynomial #" << count + 1;
        cout << " ..." << endl << endl;
        int degree = genRandNum(0,5);
        int size = degree + 1;
        array = new int [size];
        for (int index = 0; index < size; index++)
            *(array + index) = genRandNum(-20,20);
        
        cout << "Parameter 1 ... int degree  = " << degree << endl;
        cout << "Parameter 2 ... int * array = {";
        int idx;
        for (idx = 0; idx < size - 1; idx++)
            cout << *(array + idx) << ", ";
        cout << *(array + idx) << "}" << endl << endl;
        
        objPtr = new Polynomial(degree, array);
        cout << "Instance 'temp' created." << endl << endl;
        
        displayPolyDetails(*objPtr);
        
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        
        delete [] array;
        array = nullptr;
        delete objPtr;
        objPtr = nullptr;
    }
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     testCopyConstructor()
PURPOSE:           Tests the Copy Constructor
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void testCopyConstructor()
{
    cout << "Testing the Copy Construtor" << endl << endl;
    
    cout << "Defining first polynomial..." << endl;
    Polynomial temp1 = genRandPoly();
    cout << "First polynomial generated." << endl << endl;
    displayPolyDetails(temp1);
    
    cout << "Defining second polynomial and initializing it with";
    cout << " the first polynomial..." << endl;
    Polynomial temp2 = temp1;
    cout << "Second polynomial generated." << endl << endl;
    displayPolyDetails(temp2);    
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     testObjectAssignment()
PURPOSE:           Tests the Object Assignment function
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void testObjectAssignment()
{
    cout << "Testing the Object assignment function (overloading the = operator)" << endl << endl;
    
    cout << "Defining first polynomial..." << endl;
    Polynomial temp1 = genRandPoly();
    cout << "First polynomial generated." << endl << endl;
    displayPolyDetails(temp1);
    
    cout << "Defining second polynomial..." << endl;
    Polynomial temp2 = genRandPoly();
    cout << "Second polynomial generated." << endl << endl;
    displayPolyDetails(temp2);
    
    cout << "Assigning the first polynomial to the second..." << endl;
    temp2 = temp1;
    cout << "Object assignment complete." << endl << endl;
    displayPolyDetails(temp2);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     testObjectAddition()
PURPOSE:           Tests the Object Addition function
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void testObjectAddition()
{
    cout << "Testing the Object addition function (overloading the + operator)"; 
    cout << endl << endl;
    
    cout << "Defining first polynomial..." << endl;
    Polynomial temp1 = genRandPoly();
    cout << "First polynomial generated." << endl << endl;
    displayPolyDetails(temp1);
    
    cout << "Defining second polynomial..." << endl;
    Polynomial temp2 = genRandPoly();
    cout << "Second polynomial generated." << endl << endl;
    displayPolyDetails(temp2);
    
    cout << "Defining the third polynomial and setting it equal" << endl;
    cout << "to the sum of the first two polynomials..." << endl; 
    Polynomial temp3 = temp1 + temp2;
    cout << "Object addition complete." << endl << endl;
    displayPolyDetails(temp3);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     testObjectSubtraction()
PURPOSE:           Tests the Object Subtraction function
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void testObjectSubtraction()
{
    cout << "Testing the Object subtraction function (overloading the - operator)"; 
    cout << endl << endl;
    
    cout << "Defining first polynomial..." << endl;
    Polynomial temp1 = genRandPoly();
    cout << "First polynomial generated." << endl << endl;
    displayPolyDetails(temp1);
    
    cout << "Defining second polynomial..." << endl;
    Polynomial temp2 = genRandPoly();
    cout << "Second polynomial generated." << endl << endl;
    displayPolyDetails(temp2);
    
    cout << "Defining the third polynomial and setting it equal" << endl;
    cout << "to the difference of the first two polynomials..." << endl; 
    Polynomial temp3 = temp1 - temp2;
    cout << "Object subtraction complete." << endl << endl;
    displayPolyDetails(temp3);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     testObjectMultiplication()
PURPOSE:           Tests the Object Multiplication function
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void testObjectMultiplication()
{
    cout << "Testing the Object Multiplication function (overloading the * operator)"; 
    cout << endl << endl;
    
    cout << "Defining first polynomial..." << endl;
    Polynomial temp1 = genRandPoly();
    cout << "First polynomial generated." << endl << endl;
    displayPolyDetails(temp1);
    
    cout << "Defining second polynomial..." << endl;
    Polynomial temp2 = genRandPoly();
    cout << "Second polynomial generated." << endl << endl;
    displayPolyDetails(temp2);
    
    cout << "Defining the third polynomial and setting it equal" << endl;
    cout << "to the product of the first two polynomials..." << endl; 
    Polynomial temp3 = temp1 * temp2;
    cout << "Object Multiplication complete." << endl << endl;
    displayPolyDetails(temp3);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     testObjectEquality()
PURPOSE:           Tests the Object Equality function
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void testObjectEquality()
{
    cout << "Testing the Object Equality function (overloading the == operator)"; 
    cout << endl << endl;
    
    cout << "Defining first polynomial..." << endl;
    Polynomial temp1 = genRandPoly();
    cout << "First polynomial generated." << endl << endl;
    displayPolyDetails(temp1);
    
    cout << "Defining second polynomial..." << endl;
    Polynomial temp2 = genRandPoly();
    cout << "Second polynomial generated." << endl << endl;
    displayPolyDetails(temp2);
    
    cout << "(BEFORE) The two polynomials are ";
    cout << ((temp1) == (temp2) ? "Equal" : "NOT Equal");
    cout << ".";
    cout << endl << endl;
    
    cout << "Now assigning the first polynomial to the second..." << endl;
    temp2 = temp1;
    cout << "Assignment complete." << endl << endl;
    displayPolyDetails(temp2);
    
    cout << "(AFTER) The two polynomials are ";
    cout << ((temp1) == (temp2) ? "Equal" : "NOT Equal");
    cout << ".";
    cout << endl << endl;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     testObjectOutput()
PURPOSE:           Tests the Object Output function
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void testObjectOutput()
{
    cout << "Testing the Object Output function (overloading the << operator)"; 
    cout << endl << endl;
    
    cout << "Defining a polynomial..." << endl;
    Polynomial temp = genRandPoly();
    cout << "Polynomial generated." << endl << endl;
    displayPolyDetails(temp);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     testEvaluateX()
PURPOSE:           Tests the Object Evaluation function
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void testEvaluateX()
{
    cout << "Testing the Object Evaluation function: evaluateX()"; 
    cout << endl << endl;
    
    cout << "Defining a polynomial..." << endl;
    Polynomial temp = genRandPoly();
    cout << "Polynomial generated." << endl << endl;
    displayPolyDetails(temp);
    
    int num_xvals = 5;
    double * x_vals = new double [num_xvals] {0, 1, -1, 2, -2};
    double * solutions = new double [num_xvals]();
    
    cout << "EVALUATE FOR X" << endl;
    cout << "f(x)\t= " << temp << endl;
    
    for (int x_sub = 0; x_sub < num_xvals; x_sub++)
    {
        double x_val = *(x_vals + x_sub);
        double solution = temp.evaluateX(x_val);
        
        *(solutions + x_sub) = solution;
        cout << "f(" << x_val << ")\t= " << solution << endl;
    }
    
    delete [] x_vals;
    delete [] solutions;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     testObjectInput()
PURPOSE:           Tests the Object Input function
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void testObjectInput()
{
    cout << "Testing the Object Input function (overloading the >> operator)"; 
    cout << endl << endl;
    
    cout << "Defining a polynomial..." << endl;
    Polynomial temp = genRandPoly();
    cout << "Polynomial generated." << endl << endl;
    displayPolyDetails(temp);
    
    cin >> temp;
}