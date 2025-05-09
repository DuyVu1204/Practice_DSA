#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm> 
#include <stdexcept> 
#include <cctype>    
#include <cmath>     
#include <fstream>

struct BigInt;// struct big integer
int compareMagnitude(const std::string& s1, const std::string& s2);// comparsion a and b
bool lessThan(const BigInt& a, const BigInt& b);// a<b
bool greaterThan(const BigInt& a, const BigInt& b);// a>b
bool equalTo(const BigInt& a, const BigInt& b);// a=b
std::string addStrings(std::string num1, std::string num2);// a+b, a and b are both positive
std::string subtractStrings(std::string num1, std::string num2);// a-b, a and b are both positive, a>b
BigInt add(const BigInt& a, const BigInt& b);// a + b 
BigInt subtract(const BigInt& a, const BigInt& b);// a - b
BigInt divide(const BigInt& dividend, const BigInt& divisor);// a/b
BigInt multiplyBasic(const BigInt& a, const BigInt& b);// a*b basic
BigInt powerOf10(BigInt num, size_t power);// a^(10*power)
BigInt karatsuba(const BigInt& num1, const BigInt& num2);// a*b use karatsuba
BigInt multiply(const BigInt& a, const BigInt& b);// a*b 
int precedence(char op);// Operator precedence
BigInt applyOperator(const BigInt& a, const BigInt& b, char op);// apply 2 number calculation operator
BigInt calculationExpression(const std::string& expression);// expression calculation

//BigInt Structure
struct BigInt {
    std::string digits; // Store magnitude, no leading zeros unless value is 0
    bool isNegative;    // Sign flag

    // Default constructor value 0
    BigInt() : digits("0"), isNegative(false) {}

    // Constructor from string
    BigInt(std::string s) 
    {
        if (s.empty()) 
        {
            digits = "0"; isNegative = false; return;
        }
        if (s[0] == '-') 
        {
            isNegative = true; digits = s.substr(1);
            if (digits.empty()) { digits = "0"; isNegative = false; } // Handle "-"
        }
        else 
        {
            isNegative = false; digits = s;
        }
        size_t first_digit = digits.find_first_not_of('0');
        if (std::string::npos == first_digit) 
        {
            digits = "0"; isNegative = false;
        }
        else 
        {
            digits = digits.substr(first_digit);
        }
        if (digits == "0") 
        { 
            isNegative = false; 
        }
    }
    // Convert BigInt back to string representation
    std::string toString() const 
    {
        if (digits == "0") return "0";
        return (isNegative ? "-" : "") + digits;
    }
    // Check if the BigInt value is zero
    bool isZero() const {
        return digits == "0";
    }
};

std::ostream& operator<<(std::ostream& os, const BigInt& num) {
    os << num.toString(); // Sử dụng hàm thành viên toString()
    return os;
}

//               Comparison Functions 
int compareMagnitude(const std::string& s1, const std::string& s2) {
    if (s1.length() < s2.length()) 
        return -1;
    if (s1.length() > s2.length())
        return 1;
    int cmp = s1.compare(s2);
    if (cmp < 0) 
    {
        return -1;
    }
    else if (cmp > 0) 
    {
        return 1;
    }
    else {
        return 0;
    }
}

//a<b
bool lessThan(const BigInt& a, const BigInt& b) {
    if (a.isNegative && !b.isNegative) return true;
    if (!a.isNegative && b.isNegative) return false;
    int magComp = compareMagnitude(a.digits, b.digits);
    return a.isNegative ? (magComp > 0) : (magComp < 0);
}

//a>b
bool greaterThan(const BigInt& a, const BigInt& b) {
    return !lessThan(a, b) && !equalTo(a, b);
}

//a=b
bool equalTo(const BigInt& a, const BigInt& b) {
    return a.digits == b.digits && a.isNegative == b.isNegative;
}

//                  Arithmetic Helpers 
std::string addStrings(std::string num1, std::string num2) {
    std::string sum_rev = "";
    int i = static_cast<int>(num1.length()) - 1;
    int j = static_cast<int>(num2.length()) - 1;
    int carry = 0;
    while (i >= 0 || j >= 0 || carry) 
    {
        int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j--] - '0' : 0;
        // x+y+carry
        int currentSum = digit1 + digit2 + carry;
        sum_rev += std::to_string(currentSum % 10);
        carry = currentSum / 10;
    }
    std::reverse(sum_rev.begin(), sum_rev.end());
    return sum_rev.empty() ? "0" : sum_rev;
}
std::string subtractStrings(std::string num1, std::string num2) { // num1 >= num2 magnitude
    std::string diff_rev = "";
    int n1 = static_cast<int>(num1.length());
    int n2 = static_cast<int>(num2.length());
    std::reverse(num1.begin(), num1.end());
    std::reverse(num2.begin(), num2.end());
    int carry = 0; // borrow
    for (int i = 0; i < n2; i++) 
    {
        // x-y-carry
        int sub = ((num1[i] - '0') - (num2[i] - '0') - carry);
        if (sub < 0) { sub = sub + 10; carry = 1; }
        else { carry = 0; }
        diff_rev.push_back(sub + '0');
    }
    for (int i = n2; i < n1; i++) 
    {
        int sub = ((num1[i] - '0') - carry);
        if (sub < 0) { sub = sub + 10; carry = 1; }
        else { carry = 0; }
        diff_rev.push_back(sub + '0');
    }
    std::reverse(diff_rev.begin(), diff_rev.end());
    size_t first_digit = diff_rev.find_first_not_of('0');
    if (std::string::npos == first_digit) return "0";
    return diff_rev.substr(first_digit);
}

//  BigInt Arithmetic Operations (add, subtract, divide,,multiply) 
BigInt add(const BigInt& a, const BigInt& b) {
    BigInt result;
    if (a.isNegative == b.isNegative) //check negative
    {
        result.digits = addStrings(a.digits, b.digits);
        result.isNegative = a.isNegative;
    }
    else 
    {
        int magComp = compareMagnitude(a.digits, b.digits);// compare two number
        if (magComp == 0) 
        { 
            result.digits = "0"; result.isNegative = false; 
        }
        else if (magComp > 0) 
        { 
            result.digits = subtractStrings(a.digits, b.digits); result.isNegative = a.isNegative; 
        }
        else 
        { 
            result.digits = subtractStrings(b.digits, a.digits); result.isNegative = b.isNegative;
        }
    }
    if (result.digits == "0") result.isNegative = false;
    return result;
}
BigInt subtract(const BigInt& a, const BigInt& b) {
    BigInt negB = b;
    if (!negB.isZero()) negB.isNegative = !b.isNegative;
    return add(a, negB);
}

BigInt divide(const BigInt& dividend, const BigInt& divisor) {
    if (divisor.isZero()) throw std::runtime_error("Division by zero");
    if (dividend.isZero()) return BigInt("0");
    bool resultNegative = (dividend.isNegative != divisor.isNegative);
    BigInt absDividend = dividend; absDividend.isNegative = false;
    BigInt absDivisor = divisor; absDivisor.isNegative = false;
    if (lessThan(absDividend, absDivisor)) 
    return BigInt("0");
    if (equalTo(absDividend, absDivisor)) 
    { 
        BigInt one("1"); one.isNegative = resultNegative; return one; 
    }
    std::string quotient_str = "";
    BigInt current_part_bi("0");
    for (char digit_char : absDividend.digits) 
    {
        current_part_bi = powerOf10(current_part_bi, 1);
        current_part_bi = add(current_part_bi, BigInt(std::string(1, digit_char)));
        if (lessThan(current_part_bi, absDivisor)) 
        {
            if (!quotient_str.empty()) quotient_str += "0";
        }
        else 
        {
            int current_q_digit = 0;
            for (int q = 9; q >= 1; --q)
            {
                BigInt product = multiply(absDivisor, BigInt(std::to_string(q))); // Uses hybrid Karatsuba
                if (!greaterThan(product, current_part_bi)) 
                {
                    current_q_digit = q;
                    current_part_bi = subtract(current_part_bi, product);
                    break;
                }
            }
            quotient_str += std::to_string(current_q_digit);
        }
    }
    if (quotient_str.empty()) quotient_str = "0";
    size_t first_digit = quotient_str.find_first_not_of('0');
    if (std::string::npos == first_digit) quotient_str = "0";
    else quotient_str = quotient_str.substr(first_digit);
    BigInt result(quotient_str); result.isNegative = resultNegative;
    if (result.digits == "0") result.isNegative = false;
    return result;
}


//    multiply basic for the base case of karatsuba
BigInt multiplyBasic(const BigInt& a, const BigInt& b) {
    if (a.isZero() || b.isZero()) 
    return BigInt("0");

    std::string num1 = a.digits; std::string num2 = b.digits;
    int n1 = static_cast<int>(num1.length());
    int n2 = static_cast<int>(num2.length());
    std::vector<int> result_vec(n1 + n2, 0);
    int i_n1 = 0, i_n2 = 0;
    // browse num1
    for (int i = n1 - 1; i >= 0; i--) 
    {
        int carry = 0; int digit1 = num1[i] - '0'; i_n2 = 0;
        //browse num2
        for (int j = n2 - 1; j >= 0; j--) 
        {
            int digit2 = num2[j] - '0';
            int sum = digit1 * digit2 + result_vec[i_n1 + i_n2] + carry;
            carry = sum / 10; result_vec[i_n1 + i_n2] = sum % 10; i_n2++;
        }
        if (carry > 0) result_vec[i_n1 + i_n2] += carry;
        i_n1++;
    }
    if (result_vec.empty()) 
    return BigInt("0"); // processing number

    int i = static_cast<int>(result_vec.size()) - 1; // switch to integer

    // compare
    while (i >= 0 && result_vec[i] == 0)
    {
        i--;
    }

    if (i < 0) return BigInt("0"); // Product is 0

    std::string s = "";

    // the loop will stop when i<0
    while (i >= 0) 
    {
        s += std::to_string(result_vec[i--]);
    }
    BigInt res_bi(s); res_bi.isNegative = (a.isNegative != b.isNegative);
    if (res_bi.digits == "0") res_bi.isNegative = false;
    return res_bi;
}

// Helper to multiply a BigInt by 10^power
BigInt powerOf10(BigInt num, size_t power) {
    if (num.isZero() || power == 0)
        return num;
    // append quantity 0 at string
    num.digits.append(power, '0');
    return num;
}

// Karatsuba threshold
const size_t KARATSUBA_THRESHOLD = 32; // size for threshold comparison

// Karatsuba
BigInt karatsuba(const BigInt& num1, const BigInt& num2) {
    if (num1.isZero() || num2.isZero()) return BigInt("0");

    // Base Case: Use multiply basic for small numbers
    if (num1.digits.length() < KARATSUBA_THRESHOLD || num2.digits.length() < KARATSUBA_THRESHOLD)
    {
        return multiplyBasic(num1, num2);
    }

    // Pad lengths for splitting
    size_t n1_len = num1.digits.length();
    size_t n2_len = num2.digits.length();
    size_t n = std::max(n1_len, n2_len);
    if (n % 2 != 0) n++;

    std::string s1 = num1.digits; std::string s2 = num2.digits;
    while (s1.length() < n) s1.insert(0, "0");
    while (s2.length() < n) s2.insert(0, "0");

    size_t m = n / 2;

    // Split numbers into halves 
    BigInt a(s1.substr(0, m));       
    a.isNegative = false;
    BigInt b(s1.substr(m, n - m));   
    b.isNegative = false;
    BigInt c(s2.substr(0, m));       
    c.isNegative = false;
    BigInt d(s2.substr(m, n - m));   
    d.isNegative = false;

    // Recursive steps
    BigInt z2 = karatsuba(a, c); // a*c
    BigInt z0 = karatsuba(b, d); // b*d

    BigInt a_plus_b = add(a, b);//a+b
    BigInt c_plus_d = add(c, d);//c+d
    BigInt z1_term1 = karatsuba(a_plus_b, c_plus_d); // (a+b)*(c+d)
    BigInt z1 = subtract(subtract(z1_term1, z2), z0); // z1 = (a+b)*(c+d) - a*c- b*d

    // Combine results: result = z2 * 10^(2*m) + z1 * 10^m + z0
    BigInt term1 = powerOf10(z2, 2 * m);
    BigInt term2 = powerOf10(z1, m);

    BigInt result_abs = add(add(term1, term2), z0); // result 

    // Set the correct sign for the final result based on the sign of the initial input
    result_abs.isNegative = (num1.isNegative != num2.isNegative);
    if (result_abs.digits == "0") result_abs.isNegative = false;

    // Remove potential leading zeros 
    if (!result_abs.isZero()) 
    {
        size_t first_digit = result_abs.digits.find_first_not_of('0');
        if (first_digit != 0 && first_digit != std::string::npos) 
        {
            result_abs.digits = result_abs.digits.substr(first_digit);
        }
    }
    return result_abs;
}

// multiply two strings use karatsuba 
BigInt multiply(const BigInt& a, const BigInt& b) {
    return karatsuba(a, b);
}

//     Expression Evaluation Logic 
int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}


BigInt applyOperator(const BigInt& a, const BigInt& b, char op) {
    // check divided zero throw error
    if (op == '/' && b.isZero()) throw std::runtime_error("Division by zero");
    switch (op) {
    case '+': return add(a, b);// a+b
    case '-': return subtract(a, b);// a-b
    case '*': return multiply(a, b);// a*b
    case '/': return divide(a, b);// a/b
    }
    throw std::runtime_error("Invalid operator in applyOp: " + std::string(1, op));// throw operator error at that location
}

// algorithm Shunting Yard, convert infix to suffix and evaluate that suffix expression
BigInt calculationExpression(const std::string& expression) {
    std::stack<BigInt> values;// operand stack
    std::stack<char> ops;// operator stack and '('
    std::string currentNumber;// temporary number string is built
    bool expectingOperand = true;// true: expects number or '('
                                 // false: expected operator or ')'
    int parenthesesBalance = 0;// track opening and closing parentheses

    for (int i = 0; i < static_cast<int>(expression.length()); ++i) 
    {
        char c = expression[i];
        if (isspace(c))// ignore whitespace
         continue;

        if (isdigit(c)) 
        {
            //if not expected operand is error
            if (!expectingOperand && currentNumber.empty()) 
            {
                throw std::runtime_error("Malformed expression: Unexpected number '" + std::string(1,c) + "' after an expression/value.");
            }
            currentNumber += c;
            expectingOperand = false; // After a digit, we expect an operator
        } else 
        {
            // Process the number just constructed (if there is one AND it is not just a '-')
            if (!currentNumber.empty() && !(currentNumber.length() == 1 && currentNumber[0] == '-')) 
            {
                values.push(BigInt(currentNumber));
                currentNumber = "";
            }
            // If currentNumber is just '-' (from an invalid minus sign), throw an error.
            else if (currentNumber.length() == 1 && currentNumber[0] == '-') 
            {
                 throw std::runtime_error("Malformed expression: Dangling unary minus. Negative numbers must be enclosed in parentheses like '(-5)'.");
            }
            if (c == '(') 
            {
                if (!expectingOperand) 
                {
                   //check if the '(' is not in the correct position, it only comes before and after the operator
                    throw std::runtime_error("Malformed expression: Unexpected '(' after a value or expression. Operator missing?");
                }
                // handle negative numbers
                if (c == '(') 
                {
                    // check negative number
                    if (i + 1 < static_cast<int>(expression.length()) && expression[i+1] == '-') 
                    { 
                        std::string negativeNumberToken = "-";
                        int j = i + 2;// start taking digits of that negative number
                        while (j < static_cast<int>(expression.length()) && isdigit(expression[j])) 
                        { 
                            negativeNumberToken += expression[j];
                            j++;
                        }
                        if (negativeNumberToken.length() > 1 && j < static_cast<int>(expression.length()) && expression[j] == ')') 
                        { 
                            values.push(BigInt(negativeNumberToken));
                            i = j;
                            expectingOperand = false;
                            continue;
                        } 
                        else
                        {
                            ops.push(c);
                            parenthesesBalance++;
                            expectingOperand = true;
                        }
                    } 
                    else
                    {
                        ops.push(c);
                        parenthesesBalance++;
                        expectingOperand = true;
                    }
                }
            }
            else if (c == ')') 
            {
                parenthesesBalance--;//decrement the counter variable
                if (parenthesesBalance < 0) throw std::runtime_error("Malformed expression: Mismatched parentheses, extra ')'");
                if (expectingOperand) 
                {// eg: "( )" or "(5+)"
                    if(!ops.empty() && ops.top() == '(')
                        throw std::runtime_error("Malformed expression: Empty parentheses '()' or operator missing before ')'");
                    throw std::runtime_error("Malformed expression: Unexpected ')' or operator missing inside parentheses.");
                }
                //compute the operators inside the parentheses
                while (!ops.empty() && ops.top() != '(') 
                {
                    char op = ops.top(); ops.pop();
                    if (values.size() < 2) throw std::runtime_error("Malformed expression: Missing operand for '" + std::string(1, op) + "' inside ()");
                    BigInt val2 = values.top();//get the second operand
                     values.pop(); 
                     BigInt val1 = values.top(); // get the first operand
                     values.pop();
                    values.push(applyOperator(val1, val2, op));// calculate the 2 operands we just took
                }
                if (ops.empty()) throw std::runtime_error("Malformed expression: Mismatched parentheses, no matching '('");
                ops.pop(); // Pop '('
                expectingOperand = false;
            }
            else if (c == '+' || c == '*' || c == '/' || c == '-') 
            {
                // error if expecting operand but operator is found is error
                if (expectingOperand) 
                {
                     throw std::runtime_error("Malformed expression: Operator '" + std::string(1, c) + "' where operand expected. All negative numbers must be in parentheses like '(-5)'.");
                }
                // calculate operator precedence
                while (!ops.empty() && ops.top() != '(' && precedence(ops.top()) >= precedence(c)) 
                {
                    char op = ops.top(); ops.pop();
                    if (values.size() < 2) throw std::runtime_error("Malformed expression: Missing operand for '" + std::string(1, op) + "'");
                    BigInt val2 = values.top();// operand 2
                    values.pop(); 
                    BigInt val1 = values.top();//operand 1
                    values.pop();
                    values.push(applyOperator(val1, val2, op)); // calculate 2 operands
                }
                ops.push(c);// push the current operator onto the stack
                expectingOperand = true;// wait operand
            }
            else // error if invalid character encountered
            {
                throw std::runtime_error("Invalid character in expression: '" + std::string(1, c) + "'");
            }
        }
    } // End for loop

    // Handle the last number (if there is one and it's not just a '-')
    if (!currentNumber.empty() && !(currentNumber.length() == 1 && currentNumber[0] == '-')) 
    {
        values.push(BigInt(currentNumber));
        expectingOperand = false;
    } else if (currentNumber.length() == 1 && currentNumber[0] == '-')
    {
       // Floating minus sign at the end
        throw std::runtime_error("Malformed expression: Expression ends with a solitary minus sign. Negative numbers must be like '(-5)'.");
    }

    if (expectingOperand) 
    {
        // If the expression is not empty and not just whitespace
        bool isEmptyOrWhitespaceOnly = true;
        for(char ch_in_exp : expression)
        { 
            if(!isspace(ch_in_exp))
            { 
                isEmptyOrWhitespaceOnly = false; break; 
            } 
        }
        if(!isEmptyOrWhitespaceOnly)
            throw std::runtime_error("Malformed expression: Ends with an operator or is incomplete.");
    }
    if (parenthesesBalance != 0) throw std::runtime_error("Malformed expression: Mismatched parentheses, unclosed '('");

    // calculate remaining operators in the stack
    while (!ops.empty()) 
    {
        char op = ops.top(); ops.pop();
        if (values.size() < 2) throw std::runtime_error("Malformed expression: Missing operand for '" + std::string(1, op) + "' at end");
        BigInt val2 = values.top();
         values.pop(); 
        BigInt val1 = values.top(); 
         values.pop();
        values.push(applyOperator(val1, val2, op));
    }

   // the value stack must have exactly 1 value left in the expression
    if (values.size() != 1) 
    {
       // handle cases where the expression is empty or contains only whitespace
        bool isEmptyOrWhitespaceOnly = true;
        for(char ch_in_exp : expression)
        { 
            if(!isspace(ch_in_exp))
            { 
                isEmptyOrWhitespaceOnly = false; break; 
            } 
        }
        if(expression.empty() || isEmptyOrWhitespaceOnly) 
        {
             throw std::runtime_error("Malformed expression: Expression is empty or contains only whitespace");
        }
        throw std::runtime_error("Malformed expression: Invalid final stack state. Resulting values: " + std::to_string(values.size()));
    }
    // return the final result
    return values.top();                        
}

int main(int argc, char* argv[]) 
{
    if (argc != 3) 
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        std::cerr << "Example: " << argv[0] << " tests.txt output_YourStudentID.txt\n";
        return 1; 
    }

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];

    std::ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) 
    {
        //try to print to output file input file cannot be opened
        std::cerr << "Error: Failed to open input file: " << inputFilename << std::endl;
        std::ofstream tempErrOut(outputFilename);
        if (tempErrOut.is_open()) 
        {
            tempErrOut << "Error: Failed to open input file: " << inputFilename << std::endl;
            tempErrOut.close();
        }
        return 1; 
    }
    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) 
    {
        std::cerr << "Error: Failed to open output file: " << outputFilename << std::endl;
        if (inputFile.is_open()) 
        {
            inputFile.close();
        }
        return 1; 
    }
    std::string line;
    int line_num = 0;
    while (std::getline(inputFile, line))//read line by line
     {
        line_num++;
        try 
        {
            if (line.find_first_not_of(" \t\n\v\f\r") == std::string::npos) 
            {
                continue;
            }
            BigInt result = calculationExpression(line); 
            outputFile << result.toString() << std::endl;
        }
        catch (const std::exception& e) 
        {
            outputFile << "Error" << std::endl;
        }
    }
    inputFile.close();
    outputFile.close();
    return 0; 
}