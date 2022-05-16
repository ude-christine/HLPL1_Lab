#include "std_lib_facilities.h"

constexpr char number = '8';
constexpr char quit = 'x';
constexpr char print = '=';
constexpr char result = '=';
constexpr char let = '#';
constexpr char name = 'a';
constexpr char sroot = 's';
constexpr char bpower = 'p';
const string declkey = "#";
const string squareroot = "sqrt";
const string power = "pow";
const string quitkey = "exit";

double expression();

double term();

double primary();

class variable { // This class holds variables names and values
  public: // This indicates the properties are public
  string name; // This property is the variable's name
  double value; // This property is the variable's value
};

vector<variable> var_table;

bool is_declared(string var) { // This function checks if a variable is defined. It returns true if it is defined and false if it is not.
  for (auto v: var_table)
    if (v.name == var) return true;
  return false;
}

double define_name(string var, double val) { // This function defines a variable and returns the value of the variable
  if (is_declared(var)) error("declared twice"); // Check if the variable had been already declared
  var_table.push_back(variable{var, val});
  return val;
}

double get_value(string val) { // This function gets value of a declared variable
  for (auto v: var_table)
    if (v.name == val) return v.value;
  error("Variable not found");
  return 0;
}

class Token { // This class holds operators, operands and names of variables
  public:
  char kind;
  double value;
  string name;

  Token() : kind(0) {}

  Token(char ch) : kind(ch), value(0) {}

  Token(char ch, double val) : kind(ch), value(val) {}

  Token(char ch, string n) : kind(ch), name(n) {}
};

class Token_stream { // Stream of tokens
  public:
  Token_stream();

  Token get();

  void putback(Token t);

  void ignore(char c);

  private:
  bool full;
  Token buffer;
};

Token_stream::Token_stream() : full(false), buffer(0) {}

void Token_stream::putback(Token t) {
  if (full) error("Token_stream buffer is full");
  buffer = t;
  full = true;
}

// Token holds operators, operands and names of variables

Token Token_stream::get() { // Get characters from cin (cin is character input)
  if (full) {
    full = false;
    return buffer; // If buffer is not empty, return value from it
  }
  char ch;
  cin >> ch;

  switch (ch) { // Switches on the character to determine what block to run depending on what character was entered.
    case quit:
    case print:
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
      return Token(ch); // If it is an operator or comma then return it
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.': {
      cin.putback(ch);
      double val = 0;
      cin >> val;
      return Token(number, val);
    }
    default: {
      if (isalpha(ch)) { // This checks if the character is an alphabet
        string s;
        s += ch;
        while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
        cin.putback(ch);
        if (s == declkey) return Token(let); // If user declares the variable then return '#'
        if (s == squareroot) return Token(sroot);
        if (s == power) return Token(bpower);
        if (s == quitkey) return Token(quit); // This quits the program
        else if (is_declared(s))
          return Token(number, get_value(s));
        return Token(name, s);
      }

      error("Bad token"); // If none of the cases above are handled, this it will be considered a bad token.
      return 0;
    }
  }
}


void Token_stream::ignore(char c) { // Ignores all characters before specific symbol
  if (full && c == buffer.kind) {
    full = false;
    return;
  }

  full = false;

  char ch = 0;
  while (cin >> ch)
    if (ch == c) return;
}

Token_stream ts;

void clean_up_mess() { // Ignores all characters before '=' if an exception was thrown
  ts.ignore(print);
}

double declaration() { // Declares a name of the variable
  Token t = ts.get();
  if (t.kind != name) error("Variable name expected"); // If there is no name return an error
  string var_name = t.name;

  Token t2 = ts.get();
  if (t2.kind != '=') error("= expected in declaration"); // If there is no '=' symbol used to assign a value

  double d = expression(); // Process the provided value
  define_name(var_name, d);
  return d;
}

double statement() { // Distinguishes between declarations and expressions
  Token t = ts.get();
  switch (t.kind) {
    case let:
      return declaration();
    default:
      ts.putback(t);
      return expression();
  }

}

void calculate() {
  while (cin)
    try {
      Token t = ts.get();
      while (t.kind == print) t = ts.get();
      if (t.kind == quit) return;
      ts.putback(t);
      cout << result << statement() << endl;
    }
    catch (exception &e) {
      cerr << e.what() << endl;
      clean_up_mess();
    }
}

int main()

try {

  cout << "Welcome to our simple calculator.\n";
  cout << "Please enter expressions using floating - point numbers.\n";
  cout << "Make use of one or more of the operators [(,),-,+,/,%,=,*].\n";
  cout << "Press the key '=' to print out your result and 'x' to exit the code!\n";

  define_name("pi", 3.1415926535); // Pre-defined variable 'pi'
  define_name("k", 1000); //Pre-defined variable 'k'

  calculate(); // Performs calculations

  return 0;
}
catch (exception &e) { // Describe the error
  cerr << e.what() << endl;
  return 1;
}
catch (...) { // Throws an unknown exception
  cerr << "some error\n";
  return 2;
}

double primary() {
  Token t = ts.get();
  switch (t.kind) {
    case '(': {
      double d = expression();
      Token t = ts.get();

      if (t.kind != ')') error(") expected!");

      return d;

    }
    case number:
      return t.value;
    case '-':
      return -primary();
    case '+':
      return primary();
    case sroot: { // Calculate square root of number or group of numbers

      t = ts.get();
      if (t.kind != '(')
        error("'(' expected");

      double d = expression();
      if (d < 0)
        error("Invalid expression!"); // Print error message if negative number was entered to sqrt

      t = ts.get();
      if (t.kind != ')')
        error("')' expected"); // If there wasn't any ')' return an error

      return sqrt(d);
    }

    case bpower: {

      t = ts.get();
      if (t.kind != '(')
        error("'(' expected");

      double d = expression();

      int i = narrow_cast<int>(expression());

      t = ts.get();
      if (t.kind != ')')
        error("')' expected");


      return pow(d, i);

    }
    default:
      error("primary expected"); // Return an error if an inappropriate character was provided
      return 0;

  }
}


double term() { // Performs '*', '/' '%' operations
  double left = primary();
  Token t = ts.get();
  while (true) {
    switch (t.kind) {
      case '*': // Performs multiplication operation.
        left *= primary();
        t = ts.get();
        break;
      case '/': // Performs division operation.
        left /= primary();
        t = ts.get();
        break;
      case '%': { // Performs modulo operation

        int i1 = narrow_cast<int>(left);
        int i2 = narrow_cast<int>(primary());
        if (i2 == 0) error("Zero divider in %"); // This checks if the divider is 0 and throws and error
        left = i1 % i2;
        t = ts.get();
        break;
      }
      default:
        ts.putback(t);  // If nothing was done putback to the stream
        return left;
    }
  }
}

double expression() { // Performs '+' and '-' operations
  double left = term();
  Token t = ts.get();

  while (true) {
    switch (t.kind) {
      case '+': // This performs an addition operation
        t = ts.get();
        break;
      case '-': // This performs a subtraction operation
        left -= term();
        t = ts.get();
        break;
      default:
        ts.putback(t);
        return left;
    }
  }
}
