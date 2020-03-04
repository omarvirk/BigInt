#include "BigInt.hpp"
#include <cctype>
#include <cstdlib>

BigInt::BigInt()
{
    data = to_string(0);
    isNegative = false;
}

BigInt::BigInt(int x)
{
    data = to_string(x);
    
    if (data[0] == '-')
    {
        isNegative = true;
    }
    else
    {
        isNegative = false;
    }
}

BigInt::BigInt(string x)
{
    int index = 0;
    string container;
    
    //Skips leading blanks
    while (isspace(x[index]))
    {
        index++;
    }
    if (x[index] == '+' || isdigit(x[index]))
    {
        isNegative = false;
        container.push_back('+');
        check_strings_for_digit(container, x, index);
    }
    else if (x[index] == '-')
    {
        isNegative = true;
        container.push_back('-');
        check_strings_for_digit(container, x, index);
    }
    else
    {
        cout << "The format of the string " << x << " is not valid" << endl;
        cout << "Please provide a string that starts with + or -.\n"
        << "Exiting..." << endl;
        exit(1);
    }
    
    data = container;
}

ostream& operator<<(ostream& out, const BigInt& right)
{
    BigInt temp;
    
    temp.data.pop_back();
    for (int i = 0; i < right.data.size(); i++)
    {
        if (right.data[i] != '+')
        {
            temp.data.push_back(right.data[i]);
        }
    }
    
    out << temp.data;
    return out;
}

BigInt operator+(const BigInt& left, const BigInt& right)
{
    BigInt smaller_str, bigger_str, temp;
    
    temp.add_zeros_in_front_of_smaller_str_and_change_sign(left, right, smaller_str, bigger_str, temp.isNegative);
    temp.data.pop_back();
    temp.add_two_objects(smaller_str, bigger_str, temp);
    temp.reverse_string(temp.data);
    
    return temp;
}

BigInt operator-(const BigInt& left, const BigInt& right)
{
    BigInt smaller_str, bigger_str, temp;
    
    temp.add_zeros_in_front_of_smaller_str_and_change_sign(left, right, smaller_str, bigger_str, temp.isNegative);
    temp.data.pop_back();
    temp.substract_two_objects(smaller_str, bigger_str, temp);
    temp.reverse_string(temp.data);
    
    return temp;
}

BigInt operator*(const BigInt& left, const BigInt& right)
{
    BigInt smaller_str, bigger_str, temp;
    
    temp.add_zeros_in_front_of_smaller_str_and_change_sign(left, right, smaller_str, bigger_str, temp.isNegative);
    temp.data.pop_back();
    temp.multiply_two_objects(smaller_str, bigger_str, temp);
    temp.reverse_string(temp.data);
    
    return temp;
}

BigInt operator/(const BigInt& left, const BigInt& right)
{
    BigInt temp, left_object, right_object;
    
    
    temp.data.pop_back();
    left_object.data.pop_back();
    right_object.data.pop_back();
    
    for (int i = 0; i < left.data.size(); i++)
    {
        left_object.data.push_back((char)left.data[i]);
    }
    for (int i = 0; i < right.data.size(); i++)
    {
        right_object.data.push_back((char)right.data[i]);
    }
    
    if (right_object > left_object)
    {
        temp.data.push_back('0');
    }
    else if (right_object == left_object)
    {
        temp.data.push_back('1');
    }
    else
    {
        temp.divide_two_objects(left_object, right_object, temp);
    }
    
    if (left.isNegative != right.isNegative)
    {
        temp.data[0] = '-';
    }
    
    return temp;
}

bool operator<(const BigInt& left, const BigInt& right)
{
    bool answer = false;
    
    if (left.isNegative != right.isNegative) //Both objects have different sign
    {
        if (left.isNegative == true)
        {
            answer = true;
        }
        else
        {
            answer = false;
        }
    }
    else //Both object have the same sign
    {
        if (left.isNegative == true) //If they are both negatives
        {
            if (left.data.size() < right.data.size()) //right object is bigger
            {
                answer = false;
            }
            else if (left.data.size() > right.data.size()) //Left object is bigger
            {
                answer = true;
            }
            else //same size
            {
                for (int i = 1; i < left.data.size(); i++)
                {
                    if (left.data[i] < right.data[i])
                    {
                        answer = false;
                        break;
                    }
                    else if(left.data[i] > right.data[i])
                    {
                        answer = true;
                        break;
                    }
                }
            }
        }
        else //They are both positive
        {
            if (left.data.size() < right.data.size()) //right object is bigger
            {
                answer = true;
            }
            else if (left.data.size() > right.data.size()) //Left object is bigger
            {
                answer = false;
            }
            else //same size
            {
                for (int i = 1; i < left.data.size(); i++)
                {
                    if (left.data[i] < right.data[i])
                    {
                        answer = true;
                        break;
                    }
                    else if(left.data[i] > right.data[i])
                    {
                        answer = false;
                        break;
                    }
                }
            }
        }
    }
    
    return answer;
}

bool operator>(const BigInt& left, const BigInt& right)
{
    bool answer = false;
    
    if (left.isNegative != right.isNegative) //Both objects have different sign
    {
        if (left.isNegative == false)
        {
            answer = true;
        }
        else
        {
            answer = false;
        }
    }
    else //Both object have the same sign
    {
        if (left.isNegative == true) //If they are both negatives
        {
            if (left.data.size() > right.data.size()) //left object is bigger
            {
                answer = false;
            }
            else if (left.data.size() < right.data.size()) //right object is bigger
            {
                answer = true;
            }
            else //same size
            {
                for (int i = 1; i < left.data.size(); i++)
                {
                    if (left.data[i] < right.data[i])
                    {
                        answer = true;
                        break;
                    }
                    else if(left.data[i] > right.data[i])
                    {
                        answer = false;
                        break;
                    }
                }
            }
        }
        else //They are both positive
        {
            if (left.data.size() < right.data.size()) //right object is bigger
            {
                answer = false;
            }
            else if (left.data.size() > right.data.size()) //Left object is bigger
            {
                answer = true;
            }
            else //same size
            {
                for (int i = 1; i < left.data.size(); i++)
                {
                    if (left.data[i] < right.data[i])
                    {
                        answer = false;
                        break;
                    }
                    else if(left.data[i] > right.data[i])
                    {
                        answer = true;
                        break;
                    }
                }
            }
        }
    }
    
    return answer;
}

bool operator==(const BigInt& left, const BigInt& right)
{
    bool answer;
    int i;
    
    if (left.data.size() == right.data.size() && left.isNegative == right.isNegative)
    {
        for (i = 1; i < left.data.size(); i++)
        {
            if (left.data[i] != right.data[i])
            {
                answer = false;
                break;
            }
        }
        
        if (i == left.data.size())
        {
            answer = true;
        }
    }
    else
    {
        answer = false;
    }
    
    return answer;
}

void BigInt::add_two_objects(BigInt smaller_object, BigInt bigger_object, BigInt& container)
{
    int carry = 0;
    int number;
    
    if (smaller_object.isNegative == bigger_object.isNegative) //If both objects have the same sign
    {
        for (int i = bigger_object.data.size() - 1; i > 0; i--)
        {
            if ((int)(bigger_object.data[i] - '0') + (int)(smaller_object.data[i] - '0') + carry > 9)
            {
                number = (int)(bigger_object.data[i] - '0') + (int)(smaller_object.data[i] - '0') + carry;
                carry = 1;
                container.data.push_back((char)(number - 10 + '0'));
            }
            else
            {
                container.data.push_back(carry + (int)(smaller_object.data[i] + bigger_object.data[i]) - '0');
                carry = 0;
            }
        }
        if (carry == 1)
        {
            container.data.push_back(carry + '0');
            carry = 0;
        }
    }
    else //If they have different signs
    {
        for (int i = bigger_object.data.size() - 1; i > 0; i--)
        {
            int temp;
            int big_string_element = ((bigger_object.data[i] - '0'));
            int small_string_element = (smaller_object.data[i] - '0');
            
            if (big_string_element >= small_string_element)
            {
                container.data.push_back((abs((bigger_object.data[i] - smaller_object.data[i] + '0'))));
            }
            else //The number at the ith position in the small string is larger than in the bigger string
            {
                number = (int)(bigger_object.data[i] - '0') + 10;
                temp = number - (int)(smaller_object.data[i] - '0');
                container.data.push_back(temp + '0');
                
                if (bigger_object.data[i - 1] != '0' && isdigit(bigger_object.data[i - 1])) //IF the number before is not zero
                {
                    bigger_object.data[i - 1] = (int)(bigger_object.data[i - 1]) - 1; //Subtract 1 from it
                }
                else if (bigger_object.data[i - 1] == '0' && isdigit(bigger_object.data[i - 1])) //The number is 0, so we can't simply subtract from it
                {
                    for (int j = i - 2; j > 0; j--) //Look at the previous element
                    {
                        if (bigger_object.data[j] != '0' && isdigit(bigger_object.data[j])) //If that element is not zero
                        {
                            bigger_object.data[j] = (int)bigger_object.data[j] - 1; //Subtract the carry from it
                            for (int k = j + 1; k < i; k++)
                            {
                                bigger_object.data[k] = '9'; //Make all the zeros up to the number that we added and pushed 9
                            }
                        }
                    }
                }
            }
        }
    }
    
    //Removes the leading zeros from the string (non important)
    for (int i = container.data.size() - 1; i > 0; i--)
    {
        if (container.data[i] == '0')
        {
            container.data.pop_back();
        }
        else
        {
            break;
        }
    }
    
    if (container.isNegative)
    {
        container.data.push_back('-');
    }
    else
    {
        container.data.push_back('+');
    }
    
    return;
}

void BigInt::substract_two_objects(BigInt smaller_object, BigInt bigger_object, BigInt& container)
{
    int carry = 0;
    int number;
    
    if (smaller_object.isNegative == bigger_object.isNegative) //If both objects have the same sign
    {
        for (int i = bigger_object.data.size() - 1; i > 0; i--)
        {
            int temp;
            int big_string_element = ((bigger_object.data[i] - '0'));
            int small_string_element = (smaller_object.data[i] - '0');
            
            if (big_string_element >= small_string_element)
            {
                container.data.push_back((abs((bigger_object.data[i] - smaller_object.data[i] + '0'))));
            }
            else //The number at the ith position in the small string is larger than in the bigger string
            {
                number = (int)(bigger_object.data[i] - '0') + 10;
                temp = number - (int)(smaller_object.data[i] - '0');
                container.data.push_back(temp + '0');
                
                if (bigger_object.data[i - 1] != '0' && isdigit(bigger_object.data[i - 1])) //IF the number before is not zero
                {
                    bigger_object.data[i - 1] = (int)(bigger_object.data[i - 1]) - 1; //Subtract 1 from it
                }
                else if (bigger_object.data[i - 1] == '0' && isdigit(bigger_object.data[i - 1])) //The number is 0, so we can't simply subtract from it
                {
                    for (int j = i - 2; j > 0; j--) //Look at the previous element
                    {
                        if (bigger_object.data[j] != '0' && isdigit(bigger_object.data[j])) //If that element is not zero
                        {
                            bigger_object.data[j] = (int)bigger_object.data[j] - 1; //Subtract the carry from it
                            for (int k = j + 1; k < i; k++)
                            {
                                bigger_object.data[k] = '9'; //Make all the zeros up to the number that we added and pushed 9
                            }
                        }
                    }
                }
            }
        }
    }
    else //If they have different signs
    {
        for (int i = bigger_object.data.size() - 1; i > 0; i--)
        {
            if ((int)(bigger_object.data[i] - '0') + (int)(smaller_object.data[i] - '0') + carry > 9)
            {
                number = (int)(bigger_object.data[i] - '0') + (int)(smaller_object.data[i] - '0') + carry;
                carry = 1;
                container.data.push_back((char)(number - 10 + '0'));
            }
            else
            {
                container.data.push_back(carry + (int)(smaller_object.data[i] + bigger_object.data[i]) - '0');
                carry = 0;
            }
        }
        if (carry == 1)
        {
            container.data.push_back(carry + '0');
            carry = 0;
        }
    }
    
    //Removes the leading zeros from the string (non important)
    for (int i = container.data.size() - 1; i > 0; i--)
    {
        if (container.data[i] == '0')
        {
            container.data.pop_back();
        }
        else
        {
            break;
        }
    }
    
    if (container.isNegative)
    {
        container.data.push_back('-');
    }
    else
    {
        container.data.push_back('+');
    }
    
    return;
}

void BigInt::multiply_two_objects(BigInt smaller_object, BigInt bigger_object, BigInt& container)
{
    BigInt str_holder;
    BigInt str;
    int index = 1;
    int number_int, carry = 0;
    string number_str;
    
    str_holder.data.pop_back();
    str.data.pop_back();
    
    for (int i = smaller_object.data.size() - 1; i > 0; i--, index++)
    {
        for (int j = bigger_object.data.size() - 1; j > 0; j--) //multiplying the large object by the smaller object
        {
            if ((int)(bigger_object.data[j] - '0') * (int)(smaller_object.data[i] - '0') + carry > 9)
            {
                number_int = (int)(bigger_object.data[j] - '0') * (int)(smaller_object.data[i] - '0') + carry;
                number_str = to_string(number_int);
                str.data.push_back(number_str[1]);
                carry = (int)(number_str[0] - '0');
            }
            else
            {
                str.data.push_back((int)(bigger_object.data[j] - '0') * (int)(smaller_object.data[i] - '0') + carry + '0');
                carry = 0;
            }
        }
        
        if (carry != 0)
        {
            str.data.push_back(carry + '0');
            carry = 0;
        }
        
        for (int i = 0; i < str.data.size(); i++)
        {
            container.data.push_back('0');
        }
        
        str_holder.add_objects_after_being_multiply(str, container, str_holder);
        
        for (int i = 0; i < index; i++)
        {
            str.data.push_back('0');
        }
    }
    
    //Removes the leading zeros from the string (non important)
    for (int i = container.data.size() - 1; i > 0; i--)
    {
        if (container.data[i] == '0')
        {
            container.data.pop_back();
        }
        else
        {
            break;
        }
    }
    
    if (smaller_object.isNegative == bigger_object.isNegative)
    {
        container.isNegative = false;
        container.data.push_back('+');
    }
    else
    {
        container.isNegative = true;
        container.data.push_back('-');
    }
}

void BigInt::add_objects_after_being_multiply(BigInt& str, BigInt& temp, BigInt& container)
{
    int number, carry = 0;
    
    for (int i = 0; i < str.data.size(); i++)
    {
        if ((int)(str.data[i] - '0') + (int)(temp.data[i] - '0') + carry > 9)
        {
            number = (int)(str.data[i] - '0') + (int)(temp.data[i] - '0') + carry;
            carry = 1;
            container.data.push_back((char)(number - 10 + '0'));
        }
        else
        {
            container.data.push_back(carry + (int)(str.data[i] + temp.data[i]) - '0');
            carry = 0;
        }
    }
    
    if (carry == 1)
    {
        container.data.push_back(carry + '0');
        carry = 0;
    }
    
    temp.data.resize(container.data.size());
    temp.data = container.data;
    temp.data.push_back('0');
    str.data.clear();
    container.data.clear();
}

void BigInt::divide_two_objects(BigInt left_object, BigInt right_object, BigInt& container)
{
    BigInt temp;
    BigInt holder;
    BigInt multiplier("+9");
    int index;
    
    temp.data.pop_back();
    holder.data.pop_back();
    container.data.push_back('+');
    for (index = 0; index < right_object.data.size(); index++)
    {
        temp.data.push_back((char)(left_object.data[index]));
    }
    
    for (int i = index; i < left_object.data.size(); i++)
    {
        if (temp < right_object)
        {
            temp.data.push_back((char)left_object.data[i]);
        }
        else
        {
            i--;
        }
        
        for (int j = 9; j >= 0; j--)
        {
            multiplier.data[1] = (j + '0');
            if (multiplier*right_object < temp || multiplier*right_object == temp)
            {
                holder = multiplier*right_object;
                container.data.push_back(j + '0');
                break;
            }
        }
        
        temp = temp - holder;
        
        if (temp.data[1] == '0')
        {
            temp.data.pop_back();
        }
    }
}

void BigInt::reverse_string(string& str)
{
    string temp;
    int j;
    
    for (int i = str.size() - 1; i >= 0; i--)
    {
        temp.push_back(str[i]);
    }
    
    str = temp;
}

void BigInt::check_strings_for_digit(string& container, string check_str, int index)
{
    if (!isdigit(check_str[index]))
    {
        index++;
    }
    
    if (!isdigit(check_str[index]))
    {
        cout << "Tried to construct an invalid BigInt from string:\n"
        << check_str << endl;
        cout << "Exiting..." << endl;
        exit(1);
    }
    
    while (isdigit(check_str[index]))
    {
        container.push_back(check_str[index]);
        index++;
    }
}

void BigInt::add_zeros_in_front_of_smaller_str_and_change_sign(const BigInt& left, const BigInt& right, BigInt& small, BigInt& large, bool& sign)
{
    string container;
    int i;
    int j = 1;
    
    //Looking at the bigger number
    if (left.data.size() < right.data.size())
    {
        small.data.resize(left.data.size());
        small = left;
        large.data.resize(right.data.size());
        large = right;
        sign = right.isNegative;
    }
    else if (left.data.size() > right.data.size())
    {
        small.data.resize(right.data.size());
        small = right;
        large.data.resize(left.data.size());
        large = left;
        sign = left.isNegative;
    }
    else //Strings have the same size
    {
        small.data.resize(left.data.size());
        large.data.resize(left.data.size());
        
        for (i = 1; i < left.data.size(); i++)
        {
            if (left.data[i] < right.data[i])
            {
                large = right;
                small = left;
                sign = right.isNegative;
                break;
            }
            else if (left.data[i] > right.data[i])
            {
                large = left;
                small = right;
                sign = left.isNegative;
                break;
            }
        }
        if (i == left.data.size())
        {
            large = left;
            small = right;
            sign = false;
        }
    }
    
    if (left.data.size() != right.data.size())
    {
        container.resize(large.data.size());
        container[0] = small.data[0];
        for (int i = 1; i <= large.data.size() - small.data.size(); i++)
        {
            container[i] = '0';
        }
        for (int i = large.data.size() - small.data.size() + 1; i < large.data.size(); i++)
        {
            container[i] = small.data[j];
            j++;
        }
        
        small.data.resize(container.size());
        small.data = container;
    }
}
