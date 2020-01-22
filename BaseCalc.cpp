/*######################################################
Program for doing arithmetic in Bases from 2 to 10

Daniel Harrington

2018-03-27
#######################################################*/


#include <iostream>
#include <vector> 
#include <algorithm> 
#include <math.h>
#include <numeric>

  /*###################################################################

               Transforming UserNum to Base 10

  UserNum is broken into digits in one vector
  while a second vector uses the digit values to convert the number
  into Base10 components.

  The Function then returns the sum of the Base10 components as an int

  ######################################################################*/

  int Base_Ten_Conversion(int Number, std::vector < int > & UserNumDigitArray, int UserBase) {

    //>>>>>>>>>>>>>>Finding Number of Digits>>>>>>>>>>>
    int length;
    int tempNumber = Number;
    for (length = 0; tempNumber > 0; length++) {
      tempNumber = floor(tempNumber / 10);
    }

    //>>>>>>>Initializing Required Values For Loop>>>>>
    tempNumber = Number;
    std::vector < int > UserNum_Base10_Array;
    int cellNum = 1;
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Loop breaking the Usernum into Digits For UserNumDigitArray
    while also converting to Base10 in UserNum_Base10_Array
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for (int digitPlace = pow(10, (length - 1)); digitPlace > 0; digitPlace /= 10) {
      UserNumDigitArray.push_back(floor(tempNumber / digitPlace));
      UserNum_Base10_Array.push_back(floor((tempNumber / digitPlace) * pow(UserBase, length - cellNum)));
      tempNumber = tempNumber % digitPlace;
      cellNum += 1;
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>Adding together the Base 10 components>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //Sum of all cells in UserNum_Base10_Array
    int Num_Base10 = std::accumulate(UserNum_Base10_Array.begin(), UserNum_Base10_Array.end(), 0);
    //Funtion Returns Integer Value of UserNum in Base 10
    return Num_Base10;
  }

/*########################################################
                     Main

Requests User Input For UserBase, UserNum1,
UserNum2, Operation and Continue

Outputs To User Converted Numbers and Operation Results

########################################################*/

int main() {
  //>>>>>>>>>>>>>>>>>>>>>>>>Declaring+Filling UserBase>>>>>>>>>>>>>>>>>>>>>>
  {
    std::cout << "Please enter the base of the numbers you wish input." << '\n';
    int UserBase;
    //User Input
    std::cin >> UserBase;
    //>>>>>>>>>>>>>>>>>If statement handling invalid input>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if (UserBase > 9 || UserBase < 2) {
      std::cout << "Invalid Base Entered. Please only enter bases from 2-9." << '\n';
      //Restarts Program
      main();
    }
    //Program Continues
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Taking user input and passing it to the function for conversion
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    //Declaring variables to store user input
    int UserNum1;
    int UserNum2;
    //User Input
    std::cout << "Enter Your First Number" << '\n';
    std::cin >> UserNum1;
    std::cout << "Enter Your Second Number" << '\n';
    std::cin >> UserNum2;
    if (UserNum2 > UserNum1) {
      std::swap(UserNum1, UserNum2);
    }
    //Arrays For Upcoming Function
    std::vector < int > UserNum1DigitArray;
    std::vector < int > UserNum2DigitArray;
    //Passing UserNums To Base_Ten_Conversion function
    int UserNum1_Base10 = Base_Ten_Conversion(abs(UserNum1), UserNum1DigitArray, UserBase);
    int UserNum2_Base10 = Base_Ten_Conversion(abs(UserNum2), UserNum2DigitArray, UserBase);
    //>>>>>>>>>>>>>>>>>While loop handling invalid input>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //Finding Highest Value Digits Inputted

    if (( * std::max_element(UserNum1DigitArray.begin(), UserNum1DigitArray.end()) >= UserBase) || ( * std::max_element(UserNum2DigitArray.begin(), UserNum2DigitArray.end()) >= UserBase)) {
      //Error Message

      std::fill(UserNum1DigitArray.begin(), UserNum1DigitArray.end(), 0);
      std::fill(UserNum2DigitArray.begin(), UserNum2DigitArray.end(), 0);
      std::cout << "The number(s) you have entered contain numbers not available in base " << UserBase << "." << '\n';
      //Request New Inputs in UserBase
      std::cout << "Please enter two numbers in base " << UserBase << "." << '\n' << '\n';
      std::cout << "Enter Your First Number" << '\n';
      std::cin >> UserNum1;
      std::cout << "Enter Your Second Number" << '\n';
      std::cin >> UserNum2;
      //Passing UserNums To Base_Ten_Conversion function
      UserNum1_Base10 = Base_Ten_Conversion(abs(UserNum1), UserNum1DigitArray, UserBase);
      UserNum2_Base10 = Base_Ten_Conversion(abs(UserNum2), UserNum2DigitArray, UserBase);
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Outputs>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //Show user converted numbers
    std::cout << "Your numbers in base 10 are: " << UserNum1_Base10 * (UserNum1 / abs(UserNum1)) << " and " << UserNum2_Base10 * (UserNum2 / abs(UserNum2)) << '\n';
    std::cout << "Please choose an operation (*,-,/,+) to do between the first and second number entered." << '\n';
    //Invalid operation handling
    bool Error=true;
    int AnswerBase10;
    char operation;
    char negative = ' ';
    while (Error == true) {
      std::cin >> operation;
      if ((UserNum1 / abs(UserNum2)) < 0) {
        negative = '-';
      }
      if (negative == operation) {
        operation = '+';
      }

      switch (operation) {
      case '+':
        AnswerBase10 = abs(UserNum1_Base10) + abs(UserNum2_Base10);
        Error = false;
        break;
      case '-':
        AnswerBase10 = abs(UserNum1_Base10) - abs(UserNum2_Base10);
        Error = false;
        break;
      case '/':
        AnswerBase10 = abs(UserNum1_Base10) / abs(UserNum2_Base10);
        Error = false;
        break;
      case '*':
        AnswerBase10 = abs(UserNum1_Base10) * abs(UserNum2_Base10);
        Error = false;
        break;
      default:
        Error = true;
        std::cout << "Invalid Input. Please choose one of the following operations. (*,/,+,-)" << '\n';
        break;
      }
      int decomposingNum = abs(AnswerBase10);
      std::vector < int > remainders;
      while (decomposingNum > 0) {
        remainders.push_back(decomposingNum % UserBase);
        decomposingNum = decomposingNum / UserBase;
      }
      std::reverse(remainders.begin(), remainders.end());
      std::cout << "In Base" << UserBase << " " << UserNum1 << operation << "(" << UserNum2 << ")" << "= " << negative;
      for (std::vector < int > ::const_iterator i = remainders.begin(); i != remainders.end(); ++i)
        std::cout << * i;
    }
    std::cout << '\n';
    std::cout << "In Base 10 the answer is :" << AnswerBase10 << '\n';
    char continueOption;
    std::cout << "Would you like to continue your calculations? (y/n)" << '\n';
    std::cin >> continueOption;
    if (continueOption == 'y')
      main();

  }
}
