#include <string>

using namespace std;

class BigInt{
public:
    BigInt(); // Initializes the BigInt to zero.
    BigInt(int x); //Initializes the BigInt to have the same value as x
    explicit BigInt(string x);//Initalizes the BigInt to have the value of the given string BUT
    //must check that the string is valid or exit(1) otherwise.
    friend ostream& operator<<(ostream& out, const BigInt& right);
private:
    bool isNegative;
    string data;
};
