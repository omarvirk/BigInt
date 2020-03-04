#include <iostream>
#include <string>
using namespace std;

class BigInt
{
public:
    BigInt(); //Initializes the BigInt to zero;
    BigInt(int x); //Initializes the BigInt to have the same value as x
    explicit BigInt(string x); //Initializes the BigInt to have the value of the given string,
    //BUT must check that the string is valid or exit(1) otherwise.
    
    friend ostream& operator<<(ostream& out, const BigInt& right);
    friend BigInt operator+(const BigInt& left, const BigInt& right);
    friend BigInt operator-(const BigInt& left, const BigInt& right);
    friend BigInt operator*(const BigInt& left, const BigInt& right);
    friend BigInt operator/(const BigInt& left, const BigInt& right);
    friend bool operator<(const BigInt& left, const BigInt& right);
    friend bool operator>(const BigInt& left, const BigInt& right);
    friend bool operator==(const BigInt& left, const BigInt& right);
    
private: //Private Functions
    void check_strings_for_digit(string& container, string check_str, int index);
    void add_zeros_in_front_of_smaller_str_and_change_sign(const BigInt& left, const BigInt& right, BigInt& small, BigInt& large, bool& sign);
    void reverse_string(string& str);
    void add_two_objects(BigInt smaller_object, BigInt bigger_object, BigInt& container);
    void substract_two_objects(BigInt smaller_object, BigInt bigger_object, BigInt& container);
    void multiply_two_objects(BigInt smaller_object, BigInt bigger_object, BigInt& container);
    void add_objects_after_being_multiply(BigInt& str, BigInt& temp, BigInt& container);
    void divide_two_objects(BigInt left_object, BigInt right_object, BigInt& container);
    
private: // Private Variables
    string data;
    bool isNegative;
};
