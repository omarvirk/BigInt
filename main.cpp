#include "BigInt.hpp"

int main()
{
    BigInt a("-1000");
    BigInt b("+999");
    cout << "1 - Testing the \"+\" operator" << endl;
    cout << b << "+" << a << endl << "= " << b + a << endl;
    a = BigInt("99999999999999999999999999999999999999999999999999999999999999999999999999999999");
    b = BigInt("1");
    cout << "  " << a << "+" << b << endl << "= " << a + b << endl;
    
    cout << endl;
    cout << "2 - Testing the \"-\" operator" << endl;
    a = BigInt("1000");
    b = BigInt("999");
    cout << a << "-" << b << endl << "= " << a - b << endl;
    a = BigInt("10000000000000000000000000000000000000000000000000000000000000000000000000000000");
    b = BigInt("1");
    cout << "  " << a << "-" << b << endl << "= " << a - b << endl;
    
    cout << endl;
    cout << "3 - Testing the \"<\" operator" << endl;
    cout << "Expecting 1, got: " << (BigInt("-30") < BigInt("-1")) << endl;
    cout << "Expecting 0, got: " << (BigInt("-1") < BigInt("-3")) << endl;
    cout << "Expecting 0, got: " << (BigInt("30") < BigInt("-1")) << endl;
    cout << "Expecting 1, got: " << (BigInt("30") < BigInt("300")) << endl;
    cout << "Expecting 0, got: " << (BigInt("-30") < BigInt("-300")) << endl;
    cout << "Expecting 0, got: " << (BigInt("-300") < BigInt("-301")) << endl;
    cout << "Expecting 1, got: " << (BigInt("300") < BigInt("301")) << endl;
    
    cout << endl;
    cout << "4 - Testing the \">\" operator" << endl;
    cout << "Expecting 0, got: " << (BigInt("-30") > BigInt("-1")) << endl;
    cout << "Expecting 1, got: " << (BigInt("-1") > BigInt("-3")) << endl;
    cout << "Expecting 1, got: " << (BigInt("30") > BigInt("-1")) << endl;
    cout << "Expecting 0, got: " << (BigInt("30") > BigInt("300")) << endl;
    cout << "Expecting 1, got: " << (BigInt("-30") > BigInt("-300")) << endl;
    cout << "Expecting 1, got: " << (BigInt("-300") > BigInt("-301")) << endl;
    cout << "Expecting 0, got: " << (BigInt("300") > BigInt("301")) << endl;
    
    cout << endl;
    cout << "5 - Testing the \"==\" operator" << endl;
    cout << "Expecting 0, got: " << (BigInt("-30") == BigInt("30")) << endl;
    cout << "Expecting 0, got: " << (BigInt("1") == BigInt("10")) << endl;
    cout << "Expecting 0, got: " << (BigInt("-30") == BigInt("-3")) << endl;
    cout << "Expecting 0, got: " << (BigInt("-777") == BigInt("-787")) << endl;
    cout << "Expecting 0, got: " << (BigInt("777") == BigInt("778")) << endl;
    cout << "Expecting 1, got: " << (BigInt("0123456789") == BigInt("0123456789")) << endl;
    cout << "Expecting 1, got: " << (BigInt("-0123456789") == BigInt("-0123456789")) << endl;
    
    cout << endl;
    cout << "6 - Testing the \"*\" operator" << endl;
    a = BigInt("100");
    b = BigInt("100");
    cout << a << " * " << b << endl
    << "Expecting 10000 got" << endl
    << "          " << a*b << endl;
    cout << endl;
    a = BigInt("1234");
    b = BigInt("-678");
    cout << a << " * " << b << endl
    << "Expecting -836652 got" << endl
    << "          " << a*b << endl;
    cout << endl;
    a = BigInt("-123456789012345678901234567890");
    b = BigInt("-987654321");
    cout << a << " * " << b << endl
    << "Expecting 121932631124828532112482853211126352690 got" << endl
    << "          " << a*b << endl;
    
    cout << endl;
    cout << "7 - Testing the \"/\" operator" << endl;
    a = BigInt("100");
    b = BigInt("100");
    cout << a << "/" << b << endl
    << "Expecting 1 got" << endl
    << "          " << a / b << endl;
    cout << endl;
    a = BigInt("15");
    b = BigInt("12345");
    cout << a << "/" << b << endl
    << "Expecting 0 got" << endl
    << "          " << a / b << endl;
    cout << endl;
    a = BigInt("7550");
    b = BigInt("75");
    cout << a << "/" << b << endl
    << "Expecting 100 got" << endl
    << "          " << a / b << endl;
    cout << endl;
    a = BigInt("13846127");
    b = BigInt("-75");
    cout << a << "/" << b << endl
    << "Expecting -184615 got" << endl
    << "          " << a / b << endl;
    return 0;
}
