#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace ::std;
class bigint
{
public:
    /**
     * @brief pad the value to the given length
     *
     * @param new_size
     */
    void pad(size_t new_size)
    {
        while (values.size() < new_size)
        {
            values.insert(values.begin(), 0); // Pad with zeros at the beginning
        }
    }
    bigint();
    bigint(const string &);
    bigint(const int64_t &);

    // these functions will be given access to the values (private)
    bigint &operator+=(const bigint &);
    bigint &operator-=(const bigint &);
    bigint &operator*=(const bigint &);

    // set for both string and int64_t
    void set(const string &);
    void set(const int64_t &);

    friend ostream &operator<<(ostream &, const bigint &);

    // get and set functions done here to make it cleaner
    char get_sign() const
    {
        return sign;
    }

    void set_sign(const char &newsign)
    {
        sign = newsign;
    }

    const vector<uint8_t> &get_values() const
    {
        return values;
    }

private:
    // in private digits are saved into a vector and the sign of the vector is saved as a char.
    vector<uint8_t> values = {};
    char sign;
};

bool operator<(bigint &, bigint &);
bool operator>(bigint &, bigint &);

bool operator<=(bigint &, bigint &);
bool operator>=(bigint &, bigint &);

bool operator==(bigint &, bigint &);
bool operator!=(bigint &, bigint &);

/**
 * @brief Construct a new bigint::bigint object for no values given
 *
 */
bigint::bigint()
{
    set("0");
}

/**
 * @brief Construct a new bigint::bigint object for a string given
 *
 * @param val
 */
bigint::bigint(const string &val)
{
    set(val);
}

/**
 * @brief Construct a new bigint::bigint object for a int64 number
 *
 * @param val
 */
bigint::bigint(const int64_t &val)
{
    set(val);
}

/**
 * @brief Set the bigint object for int64_t value.
 *
 * @param val
 */
void bigint::set(const int64_t &val)
{
    // convert number a string and then send it to the other set function
    string str = to_string(val);
    set(str);
}

/**
 * @brief set function for a string.
 *
 * @param val
 */
void bigint::set(const string &val)
{
    values.clear(); // Clear existing values
    sign = '+';     // Default sign is positive

    // for loop goes through all the characters
    for (size_t i = 0; i < val.size(); ++i)
    {
        // first character (for sign checking)
        char c = val[i];

        // first case and if a sign is given
        if (i == 0 && (c == '+' || c == '-'))
        {
            sign = c;
            continue; // Skip
        }

        // Check if digit
        if (isdigit(c))
        {
            values.push_back(c - '0'); // push value to the vector,
        }
        else
        {
            // error checking for non numbers
            throw invalid_argument("Number is not valid!");
        }
    }
}

/**
 * @brief displaying the value.
 *
 * @param out
 * @param obj
 * @return ostream&
 */
ostream &operator<<(std::ostream &out, const bigint &obj)
{
    if (obj.sign == '-')
        out << '-';
    for (int8_t val : obj.values)
        out << static_cast<int>(val);
    return out;
}

/**
 * @brief helper function for comparing bigint objects
 *
 * @param firstVal
 * @param secondVal
 * @return true
 * @return false
 */
bool comparehelper(bigint &firstVal, bigint &secondVal)
{
    // get the length of the values, increment without 0s
    size_t startIndexFirst = 0;
    //
    while (startIndexFirst < firstVal.get_values().size() && firstVal.get_values()[startIndexFirst] == 0)
    {
        ++startIndexFirst;
    }

    size_t startIndexSecond = 0;
    while (startIndexSecond < secondVal.get_values().size() && secondVal.get_values()[startIndexSecond] == 0)
    {
        ++startIndexSecond;
    }

    /// lengths w/o leading zeroes
    size_t lengthFirst = firstVal.get_values().size() - startIndexFirst;
    size_t lengthSecond = secondVal.get_values().size() - startIndexSecond;

    // compare lengths and return the larger one
    if (lengthFirst < lengthSecond)
    {
        return true;
    }
    else if (lengthFirst > lengthSecond)
    {
        return false;
    }

    // Lengths are equal, compare digit by digit
    for (size_t i = 0; i < lengthFirst; ++i)
    {
        if (firstVal.get_values()[startIndexFirst + i] < secondVal.get_values()[startIndexSecond + i])
        {
            return true;
        }
        else if (firstVal.get_values()[startIndexFirst + i] > secondVal.get_values()[startIndexSecond + i])
        {
            return false;
        }
    }
    return false;
}

/**
 * @brief check if the bigints are equal.
 *
 * @param firstval
 * @param secondval
 * @return true
 * @return false
 */
bool operator==(bigint &firstval, bigint &secondval)
{
    // code is the same as the helper function comparehelper except the handling of equals is different
    //  get the length of the values, increment without 0s
    size_t startIndexFirst = 0;
    while (startIndexFirst < firstval.get_values().size() && firstval.get_values()[startIndexFirst] == 0)
    {
        ++startIndexFirst;
    }

    // Find the first non-zero digit in secondVal
    size_t startIndexSecond = 0;
    while (startIndexSecond < secondval.get_values().size() && secondval.get_values()[startIndexSecond] == 0)
    {
        ++startIndexSecond;
    }

    // Compare the lengths of the numbers without leading zeros
    size_t lengthFirst = firstval.get_values().size() - startIndexFirst;
    size_t lengthSecond = secondval.get_values().size() - startIndexSecond;

    if (lengthFirst != lengthSecond)
    {
        return false;
    }

    // Lengths are equal, compare digit by digit, if they aren't then return false else true
    for (size_t i = 0; i < lengthFirst; ++i)
    {
        if (firstval.get_values()[startIndexFirst + i] != secondval.get_values()[startIndexSecond + i])
        {
            return false;
        }
    }
    // Numbers are equal in magnitude
    return true; // Or return true based on how you want to treat equal values
}

/**
 * @brief operator for checking if two bigints are not equal
 *
 * @param firstval
 * @param secondval
 * @return true
 * @return false
 */
bool operator!=(bigint &firstval, bigint &secondval)
{
    return !(firstval == secondval);
}

/**
 * @brief operator for checking if the second bigint is greater than the first.
 *
 * @param firstval
 * @param secondval
 * @return true
 * @return false
 */
bool operator<(bigint &firstval, bigint &secondval)
{
    // Handle different signs
    if (firstval.get_sign() == '-' && secondval.get_sign() == '+')
        return true;
    else if (firstval.get_sign() == '+' && secondval.get_sign() == '-')
        // this is positive, other is negative
        return false;

    // since we already checked different signs, we just have to check one sign
    if (firstval.get_sign() == '-')
    {
        return !comparehelper(firstval, secondval);
    }
    else
    {
        // Both are positive
        return comparehelper(firstval, secondval);
    }
}

/**
 * @brief operator for checking if the first bigint is greater than the second.
 *
 * @param firstval
 * @param secondval
 * @return true
 * @return false
 */
bool operator>(bigint &firstval, bigint &secondval)
{
    return secondval < firstval;
}

/**
 * @brief operator for checking if the second bigint is greater or equal than the first.
 *
 * @param firstval
 * @param secondval
 * @return true
 * @return false
 */
bool operator<=(bigint &firstval, bigint &secondval)
{
    if ((firstval < secondval) || (firstval == secondval))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief operator for checking if the first bigint is greater or equal than the second.
 *
 * @param firstval
 * @param secondval
 * @return true
 * @return false
 */
bool operator>=(bigint &firstval, bigint &secondval)
{
    return secondval <= firstval;
}

/**
 * @brief operator for negating a bigint
 * @param bigobj
 * @return bigint
 */
bigint operator-(const bigint &bigobj)
{
    // make a duplicate so the value isnt changed
    bigint newval = bigobj;
    if (newval.get_sign() == '+')
    {
        newval.set_sign('-');
    }
    else
    {
        newval.set_sign('+');
    }

    return newval;
}

/**
 * @brief add two bigints but change the first
 *
 * @param rhs
 * @return bigint&
 */
bigint &bigint::operator+=(const bigint &rhs)
{
    // Create temporary copies
    bigint temp_lhs = *this;
    bigint temp_rhs = rhs;

    // make the temp values the same length by padding
    size_t maxLength = max(temp_lhs.values.size(), temp_rhs.values.size());
    temp_lhs.pad(maxLength);
    temp_rhs.pad(maxLength);

    // length of the result set as the maximumlength
    vector<uint8_t> result(maxLength, 0);
    uint8_t carry = 0;

    // Perform addition on the temporary copies
    for (int i = maxLength - 1; i >= 0; --i)
    {
        int sum = temp_lhs.values[i] + (i < temp_rhs.values.size() ? temp_rhs.values[i] : 0) + carry;
        carry = sum / 10;
        result[i] = sum % 10;
    }

    // in the case of carry
    if (carry)
    {
        result.insert(result.begin(), carry);
    }

    // Assign the result back to this object
    // using move function from 9.2.3 lecture notes
    this->values = move(result);
    return *this;
}

/**
 * @brief subtract two bigints but change the first
 *
 * @param rhs
 * @return bigint&
 */
bigint &bigint::operator-=(const bigint &rhs)
{
    /*if the signs aren't the same then it follows this pattern:
        -a - (+b) = - a - b meaning it adds
        +a - (-b) = + a + b meaning it adds
    so both cases, we add
    */
    if (this->sign != rhs.sign)
    {
        bigint temp_rhs = rhs;
        temp_rhs.sign = '+'; // Make rhs positive for addition
        *this += temp_rhs;
        return *this;
    }

    // Check if *this is smaller than rhs
    bool IsSmaller = false;
    if (this->values.size() < rhs.values.size())
    {
        IsSmaller = true;
    }
    // compare sizes
    else if (this->values.size() == rhs.values.size())
    {
        for (size_t i = 0; i < values.size(); ++i)
        {
            if (values[i] < rhs.values[i])
            {
                IsSmaller = true;
                break;
            }
            else if (values[i] > rhs.values[i])
            {
                break;
            }
        }
    }

    if (IsSmaller)
    {
        // If *this is smaller, swap *this and rhs, and negate the result
        bigint temp = *this;
        *this = rhs;
        *this -= temp;
        sign = (sign == '+' ? '-' : '+'); // Flip sign
        return *this;
    }

    // subtraction
    size_t maxLength = max(values.size(), rhs.values.size());
    this->pad(maxLength);
    bigint temp_rhs = rhs;
    temp_rhs.pad(maxLength);

    int borrow = 0;
    for (int i = maxLength - 1; i >= 0; --i)
    {
        int diff = values[i] - temp_rhs.values[i] - borrow;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        this->values[i] = diff;
    }

    // Remove leading zeros
    // find_if from 7.6.2
    auto it = find_if(this->values.begin(), this->values.end(), [](uint8_t digit)
                      { return digit != 0; });
    if (it == this->values.end())
    {
        values.clear();
        values.push_back(0);
        sign = '+'; // Zero should have a positive sign
    }
    else
    {
        // from 7.6.3
        values.erase(values.begin(), it);
    }

    return *this;
}

/**
 * @brief subtracting bigint and int64_t without changing any values
 *
 * @param bigval
 * @param regval
 * @return bigint
 */
bigint operator-(bigint &bigval, const int64_t &regval)
{
    // Checking the signs and performing the operation accordingly
    if (bigval.get_sign() == '+' && regval >= 0)
    {
        bigval -= regval; // Case 1: Both positive
    }
    else if (bigval.get_sign() == '+' && regval < 0)
    {
        bigval += abs(regval); // Case 2: bigint positive, int64_t negative
    }
    else if (bigval.get_sign() == '-' && regval >= 0)
    {
        bigval += regval; // Case 3: bigint negative, int64_t positive
    }
    else
    {                          // bigval.sign == '-' && regval < 0
        bigval += abs(regval); // Case 4: Both negative
    }

    return bigval;
}

/**
 * @brief adding two bigints without changing any values
 *
 * @param bigval
 * @param regval
 * @return bigint
 */
bigint operator+(const bigint &bigval, const int64_t &regval)
{
    // check signs and perform arithematic on temp so no changes are made to original values
    bigint temp = bigval;
    if (bigval.get_sign() == '+' && regval >= 0)
    {
        temp += regval; // Case 1: Both positive
    }
    else if (bigval.get_sign() == '+' && regval < 0)
    {
        temp -= abs(regval); // Case 2: bigint positive, secondvalue negative
    }
    else if (bigval.get_sign() == '-' && regval >= 0)
    {
        temp -= regval; // Case 3: bigint negative, secondvalue positive
    }
    else
    {
        temp += regval; // Case 4: Both negative
    }

    return temp;
}

/**
 * @brief add two bigint values
 *
 * @param firstval
 * @param secval
 * @return bigint
 */
bigint operator+(const bigint &firstval, const bigint &secval)
{
    // check signs and perform arithematic on temp so no changes are made to original values
    bigint temp = firstval;
    bigint temp2 = secval;
    if (firstval.get_sign() == '+' && secval.get_sign() == '+')
    {
        temp += secval; // Case 1: both positive
    }
    else if (firstval.get_sign() == '+' && secval.get_sign() == '-')
    {
        // change sign
        temp2.set_sign('+');
        temp -= temp2; // Case 2: bigint positive, secondvalue negative
    }
    else if (firstval.get_sign() == '-' && secval.get_sign() == '+')
    {
        temp -= secval; // Case 3: bigint negative, secondvalue positive
    }
    else
    {
        temp += secval; // Case 4: both negative
    }

    return temp;
}

/**
 * @brief subtract two bigint values
 *
 * @param firstval
 * @param secval
 * @return bigint
 */
bigint operator-(const bigint &firstval, const bigint &secval)
{
    bigint new_firstval = firstval;
    bigint new_secval = secval;
    // Checking the signs and performing the operation accordingly
    if (firstval.get_sign() == '+' && secval.get_sign() == '+')
    {
        return new_firstval -= secval; // Case 1: Both positive
    }
    else if (firstval.get_sign() == '+' && secval.get_sign() == '-')
    {
        return new_firstval += secval; // Case 2: bigint positive, int64_t negative
    }
    else if (firstval.get_sign() == '-' && secval.get_sign() == '+')
    {
        return new_firstval += secval; // Case 3: bigint negative, int64_t positive
    }
    else
    { // bigval.sign == '-' && regval < 0
        new_secval.set_sign('+');
        new_firstval.set_sign('+');
        return new_secval += new_firstval; // Case 4: Both negative
    }
}

/**
 * @brief multiple two bigints and change the first
 *
 * @param rhs
 * @return bigint&
 */
bigint &bigint::operator*=(const bigint &rhs)
{
    // Determine the sign of the result
    char resultSign = (sign == rhs.sign) ? '+' : '-';

    size_t lhsSize = values.size();
    size_t rhsSize = rhs.values.size();
    vector<uint8_t> result(lhsSize + rhsSize, 0);

    // for loop to go through digits
    /*
    algorithm is based on how it was taught to us in elementary school where the second number multiplies each of its values
    starting from least significant.
    */
    for (size_t i = 0; i < lhsSize; ++i)
    {
        int carry = 0;
        for (size_t j = 0; j < rhsSize || carry; ++j)
        {
            // start from least significant
            int lhs_dig = values[lhsSize - 1 - i];

            // get current digit from rhs
            int rhs_dig = j < rhsSize ? rhs.values[rhsSize - 1 - j] : 0;

            // multiply for product
            int product = lhs_dig * rhs_dig;
            // add product, current carry
            int sum = product + carry + result[i + j];

            carry = sum / 10;
            result[i + j] = sum % 10;
        }
    }

    // Remove leading zeros
    while (result.size() > 1 && result.back() == 0)
    {
        result.pop_back();
    }

    // Handle the case where result is zero
    if (result.empty())
    {
        result.push_back(0);
        resultSign = '+';
    }
    // reverse it for proper order
    reverse(result.begin(), result.end());

    // Assign the result back to this object
    values = result;
    sign = resultSign;

    return *this;
}

/**
 * @brief multiply two bigint values
 *
 * @param firstval
 * @param secval
 * @return bigint
 */
bigint operator*(bigint &firstval, bigint &secval)
{
    bigint repl = firstval;
    return repl *= secval;
}
