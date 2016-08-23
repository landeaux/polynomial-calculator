/* -----------------------------------------------------------------------------

FILE NAME:         Polynomial.CPP

DESCRIPTION:       This is the implementation program for the Polynomial class

PURPOSE:           The purpose of this file is to provide the Polynomial class
                   member function definitions.

USAGE:             In the linux command line, type ./polynomial

EXAMPLES:          To run the program, type ./polynomial in the linux command line

PARAMETERS:        N/A

EXIT CODES:        0 = Success
                   1 = Error: INDEX_OUT_OF_RANGE

COMPILATION:       Linux GNU

NOTES:             - removed debugging code.
                   
MODIFICATION HISTORY:

Author          Date           Modification(s)
-------------   -----------    ---------------
Adam Landis     04-14-2016     Version 0001
Adam Landis     04-14-2016     Version 0002
Adam Landis     04-15-2016     Version 0003
Adam Landis     04-15-2016     Version 0004
Adam Landis     04-15-2016     Version 0005
Adam Landis     04-15-2016     Version 0006
Adam Landis     04-16-2016     Version 0007
Adam Landis     04-21-2016     Version 0008
Adam Landis     04-21-2016     Version 0009
Adam Landis     04-21-2016     Version 0010
Adam Landis     04-22-2016     Version 0011
Adam Landis     04-23-2016     Version 0012
Adam Landis     04-27-2016     Version 0013
Adam Landis     04-27-2016     Version 0014
Adam Landis     04-27-2016     Version 0015

----------------------------------------------------------------------------- */

#include "Polynomial.hpp"
#include "general.hpp"

using std::cout;
using std::cin;
using std::endl;

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::Polynomial() 
PURPOSE:           This is the default constructor function for the Polynomial 
                   class.
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
Polynomial::Polynomial() 
{    
    _degree = 0;
    _array_size = 1;
    
    _terms_array = new int [_array_size]();
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::Polynomial() 
PURPOSE:           This is an overloaded constructor function for the Polynomial 
                   class
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
Polynomial::Polynomial(const int degree, const int * terms_array) 
{    
    _degree = degree;
    
    // This loop finds the last non-zero element of the input array and corrects
    // the polynomial degree with the associated index. This way the internal 
    // array can be initialized with no leading zeros (i.e. {0, 1, 0} => {0, 1})
    while (_degree > 0 && terms_array[_degree] == 0)
        _degree--;
    
    _array_size = _degree + 1;
    
    _terms_array = new int [_array_size];
    
    for (int count = 0; count < _array_size; count++)
        *(_terms_array + count) = *(terms_array + count);    
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::Polynomial() 
PURPOSE:           This is the copy constructor function for the Polynomial class
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
Polynomial::Polynomial(const Polynomial &obj) 
{    
    _degree = obj._degree;
    
    while (_degree > 0 && obj.getTerm(_degree) == 0)
        _degree--;
        
    _array_size = _degree + 1;
    
    _terms_array = new int [_array_size];
    
    for (int count = 0; count < _array_size; count++)
        *(_terms_array + count) = *(obj._terms_array + count);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::~Polynomial() 
PURPOSE:           This is the destructor function for the Polynomial class
RETURNS:           Nothing
NOTES:             
----------------------------------------------------------------------------- */
Polynomial::~Polynomial() 
{    
    delete [] _terms_array;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::operator=()
PURPOSE:           Object assignment (overloading = operator) member function 
                   for the Polynomial class
RETURNS:           Polynomial
NOTES:             
----------------------------------------------------------------------------- */
Polynomial Polynomial::operator = (const Polynomial &right)
{    
    _degree = right._degree;
    
    while (_degree > 0 && right.getTerm(_degree) == 0)
        _degree--;
    
    _array_size = _degree + 1;
    
    delete [] _terms_array;
    
    _terms_array = new int [_array_size];
    
    for (int count = 0; count < _array_size; count++)
        _terms_array[count] = right._terms_array[count];
    
    return *this;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::operator+()
PURPOSE:           Object addition (overloading + operator) member function 
                   for the Polynomial class
RETURNS:           Polynomial
NOTES:             
----------------------------------------------------------------------------- */
Polynomial Polynomial::operator + (const Polynomial &right)
{		
    int smaller_array_size = arrayMin(right);
    Polynomial temp = polyMax(right);
    
	for (int count = 0; count < smaller_array_size; count++)
	{
		int left_term = getTerm(count);
		int right_term = right.getTerm(count);

		temp.setTerm(count, left_term + right_term);
	}
		
    return temp;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::operator-()
PURPOSE:           Object subtraction (overloading - operator) member function 
                   for the Polynomial class
RETURNS:           Polynomial
NOTES:             
----------------------------------------------------------------------------- */
Polynomial Polynomial::operator - (const Polynomial &right)
{    
    Polynomial temp = right * -1;
    temp = *this + temp;
    
    return temp;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::operator*(const Polynomial &)
PURPOSE:           Object multiplication (overloading * operator) member function 
                   for the Polynomial class
RETURNS:           Polynomial that represents the product of two polynomials.
NOTES:             
----------------------------------------------------------------------------- */
Polynomial Polynomial::operator * (const Polynomial &right)
{
    int degree_left = getDegree();
    int degree_right = right.getDegree();
    int new_poly_degree = degree_left + degree_right;
    int new_poly_arr_size = new_poly_degree + 1;
    int * temp_array = new int[new_poly_arr_size]();
    
    for (int i = 0; i < getArraySize(); i++)
    {
        for (int j = 0; j < right.getArraySize(); j++)
        {
            int coefficient = _terms_array[i] * right._terms_array[j];
            int exponent = i + j;
            
            temp_array[exponent] += coefficient;
        }
    }
    
    Polynomial temp(new_poly_degree, temp_array);
    
    delete [] temp_array;
    
    return temp;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::operator*(const int)
PURPOSE:           Object multiplication (overloading * operator) member function 
                   for the Polynomial class
RETURNS:           Polynomial that represents the product of two polynomials.
NOTES:             
----------------------------------------------------------------------------- */
Polynomial Polynomial::operator * (const int val) const
{
    Polynomial temp = *this;
    
    for (int idx = 0; idx < temp.getArraySize(); idx++)
        temp._terms_array[idx] *= val;
        
    return temp;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::operator==()
PURPOSE:           Object equality testing (overloading == operator) member function 
                   for the Polynomial class
RETURNS:           Polynomial
NOTES:             
----------------------------------------------------------------------------- */
bool Polynomial::operator == (const Polynomial &right)
{    
    Polynomial bigger = polyMax(right);
    int bigger_array_size = bigger.getArraySize();    
    
    for (int idx = 0; idx < bigger_array_size; idx++)
    {
        if (_terms_array[idx] != right._terms_array[idx])
            return false;
    }
    
    return true;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::operator<<()
PURPOSE:           Object output (overloading << operator) member function 
                   for the Polynomial class
RETURNS:           Polynomial
NOTES:             
----------------------------------------------------------------------------- */
ostream &operator << (ostream &strm, const Polynomial &obj)
{    
    int _degree = obj.getDegree();
    int idx = _degree;
    
    if (_degree == 0 && obj.getTerm(0) == 0)
        return strm << "0";
    
    int * terms = new int [_degree + 1];
    for (int i = 0; i <= _degree; i++)
        terms[i] = obj.getTerm(i);
    
    for (; idx >= 0; idx--)
    {
        int coefficient  = terms[idx];
        string sign         = ""; 
        string coeff_as_str = "";
        char x_symbol       = '\0';
        string exponent     = ""; 
        char trailing_space = '\0'; 
         
        if (coefficient == 0)
            continue;
        
        // determining the value of sign
        if (idx != _degree)
        {
            if (coefficient > 0)
                sign = "+ ";
            else
                sign = "- "; 
        }
        else
        {
            if (coefficient == -1 && _degree != 0)
                sign = "-";
        }
        
        // determining the value of coeff_as_str
        if (abs(coefficient) != 1 || idx == 0)
        {
            if (idx == _degree)
                coeff_as_str = to_string(coefficient);
            else
                coeff_as_str = to_string(abs(coefficient));
        }
        
        // determining the value of x_symbol
        if (idx > 0)
            x_symbol = 'x';
        
        // determining the value of exponent
        if (idx > 1)
            exponent = "^" + to_string(idx);
        
        // determining the value of trailing_space
        if (idx > 0 && !obj.allZeros(0,idx,obj._terms_array))
            trailing_space = ' ';
        
        strm << sign << coeff_as_str << x_symbol << exponent << trailing_space;   
    }
    
    delete [] terms;
    
    return strm;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::operator>>()
PURPOSE:           Object input (overloading >> operator) member function 
                   for the Polynomial class
RETURNS:           Polynomial
NOTES:             
----------------------------------------------------------------------------- */
istream &operator >> (istream &strm, Polynomial &obj)
{    
    double x_val;
    double solution;
    
    cout << endl;
    cout << "Evaluate " << obj << " ..." << endl;
    cout << "... at x = ";
    strm >> x_val;
    
    solution = obj.evaluateX(x_val);
    
    cout << "SOLUTION: " << solution;
    cout << endl;
    
    return strm;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::getTerm()
PURPOSE:           Getter function for Polynomial objects that gets the values of
                   a specific term from a given index argument.
RETURNS:           An integer representing the term located at the specified index.
NOTES:             
----------------------------------------------------------------------------- */
int Polynomial::getTerm(int idx) const
{   
    return _terms_array[idx];
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::getArraySize()
PURPOSE:           Getter function for Polynomial objects that gets the number of
                   terms in the polynomial.
RETURNS:           An integer representing the polynomial's number of terms.       
NOTES:             
----------------------------------------------------------------------------- */
int Polynomial::getArraySize() const
{    
    return _array_size;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::getDegree()
PURPOSE:           Getter function for Polynomial objects that gets the degree of
                   the polynomial.
RETURNS:           An integer representing the polynomial's degree.
NOTES:             
----------------------------------------------------------------------------- */
int Polynomial::getDegree() const
{    
    return _degree;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::setTerm()
PURPOSE:           Setter function for Polynomial objects that sets the value of
                   a specific term in the polynomial at a given index.
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void Polynomial::setTerm(int idx, int val)
{
    if (idx > _degree)
        errorHandler(INDEX_OUT_OF_RANGE);
    _terms_array[idx] = val;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::errorHandler()
PURPOSE:           Handles errors in processing internal Polynomial object data
RETURNS:           Nothing (Void function)
NOTES:             
----------------------------------------------------------------------------- */
void Polynomial::errorHandler(const int ERROR_CODE)
{
    cout << endl << endl;
    cout << "ERROR " << ERROR_CODE << ": ";
    
    switch(ERROR_CODE)
    {
        case INDEX_OUT_OF_RANGE:
            cout << "Index is out of range.";
        default:
            break;
    }
    
    cout << endl << endl;
    exit(ERROR_CODE);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::polyMax()
PURPOSE:           Determines the larger polynomial between the calling 
                   Polynomial object and the Polynomial object to the 
                   right of the + or - operator.
RETURNS:           Polynomial representing the larger polynomial 
NOTES:             
----------------------------------------------------------------------------- */
Polynomial Polynomial::polyMax(const Polynomial &right)
{
    return (right.getArraySize() > getArraySize() ? right : *this);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::arrayMin()
PURPOSE:           Determines the smaller array size between the calling 
                   Polynomial object and the Polynomial object to the 
                   right of the + or - operator.
RETURNS:           integer representing the size of the smaller array 
NOTES:             
----------------------------------------------------------------------------- */
int Polynomial::arrayMin(const Polynomial &right)
{
    int array_size_left = getArraySize();
    int array_size_right = right.getArraySize();
    
    return MIN(array_size_left, array_size_right);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::evaluateX()
PURPOSE:           Evaluates a polynomial with a given value for x.
RETURNS:           A double representing the solution of the polynomial. 
NOTES:             
----------------------------------------------------------------------------- */
double Polynomial::evaluateX(double x) const
{
    double solution = getTerm(0);   // initialize with value of the constant term 
    
    for (int idx = 1; idx < _array_size; idx++)
    {
        double exp = static_cast<double>(idx);
        solution += _terms_array[idx] * pow(x,exp);
    }
    
    return solution;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     Polynomial::allZeros()
PURPOSE:           Determines if all the elements of an array between a given 
                   bounds are all equal to zero.
RETURNS:           A bool representing whether all elements are zero or not.
NOTES:             
----------------------------------------------------------------------------- */
bool Polynomial::allZeros(int index, const int num_steps, const int * arr) const
{
    for (; index < num_steps; index++)
    {
        if (arr[index] != 0)
             return false;
    }
    return true;
}