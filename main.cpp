// Jason Whitlow (0593858)
// CSCI26
// Programming Assignment 4: Lexographic Permutation
// the program accepts a list of integers as input
// the program then outputs the next lexicographic permutation of the input list

#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getUserInput();                     // returns user input as a vector                             
void printVec(vector<int> const &inputVec);     // prints a vector
void nextPerm(vector<int> &inputVec);           // finds the next permutation and stores it in inputVec
void bubbleSort(vector<int> &inputVec);         // sorts a vector


int main()
{
    cout << "  User will enter a list of integers separated by spaces." << endl
         << "  The program will then output the next Lexocographic Permutation of the list."<< endl
         << "  For example '5 4 2 99 54' is a valid entry." << endl
         << "    1. The list of integers must contain only positive integers." << endl
         << "    2. The list must contain only digits and spaces." << endl 
         << "    3. Repeated integers will be removed from the list." << endl
         << "    4. If the last permutation is entered, no changes will be made to the list." << endl
         << endl;

    vector<int> inputVec;   
    bool exit = false;
    while (!exit)
    {
        // prompt user for input
        inputVec = getUserInput();
        cout << "Your Input was: ";
        printVec(inputVec);
        
        // generate next permutation and print
        nextPerm(inputVec);
        cout << "The next permutation is: ";
        printVec(inputVec);
        cout << endl;

        string e;
        cout << "Exit? type 'e' to exit, enter to continue: ";
        getline(cin, e);

        if (e == "e" || e == "E")
            exit = true;
    }

    return 0;
}

// accepts user input as string and returns input as a vector
// string should be in the form "16 72 599 4"
vector<int> getUserInput()
{
    bool validInput;
    string input;
    vector<int> inputVec;

    // input validation
    validInput = false;
    while (!validInput)
    {
        cout << "Enter a list of integers: ";
        getline(cin, input);

        // remove leading spaces
        int counter = 0;
        while (input[counter] == ' ')
            counter++;
        input = input.substr(counter, input.length()-counter);

        // remove trailing spaces
        counter = input.length()-1;
        while (input[counter] == ' ')
            counter--;
        input = input.substr(0, counter + 1);

        // special case for empty string
        if (input == "")
        {
            cout << "Input cannot be blank!" << endl;
            continue;
        }

        // check for correct formatting
        // string format: "5 4 99 100"
        validInput = true;
        inputVec.clear();
        for (size_t i = 0; i < input.length(); i++)
        {
            // check if input is a digit
            if (input[i] != ' ' && !isdigit(input[i]))
            {
                validInput = false;
                break;
            }

            // remove internal spaces
            while (input[i] == ' ')
                i++;

            // store integer in buffer
            string bufferStr = "";
            while (isdigit(input[i]))
            {
                bufferStr.push_back(input[i]);
                i++;
            }

            // prevent integer overflow
             int nextVal;
            try
            {
                nextVal = stoi(bufferStr);
            }
            catch(const exception& e)
            {
                cout << "One or more numbers is too large" << '\n';
                validInput = false;
            }

            // if nextVal does not already exist in inputVec, add nextVal to inputVec
            //int nextVal = stoi(bufferStr);
            bool isDuplicate = false;
            for (size_t i = 0; i < inputVec.size(); i++)
                if(inputVec[i] == nextVal) isDuplicate = true;  
            if (!isDuplicate) inputVec.push_back(nextVal);
        }
    }
    return inputVec;
}

// print vector
void printVec(vector<int> const &inputVec)
{
    for (int i = 0; i < inputVec.size(); i++)
        cout << inputVec.at(i) << ' ';
    cout << endl;
}

// accepts a vector as input and modifies the vector to be the next lexicographic permutation
void nextPerm(vector<int> &inputVec)
{
    // special case, size less than 2
    if (inputVec.size()<2) return;

    // special case, last permutation
    bool isLastPerm = true;
    for (size_t i = 0; i < inputVec.size()-1; i++)
    {
        if (inputVec[i]>inputVec[i+1])
            continue;
        isLastPerm=false;
    }
    if (isLastPerm) return;

    // moving from right to left, find the first decreasing value
    int leftIndex = inputVec.size()-1; 
    int temp = inputVec.size()-1;     
    while (leftIndex > 0 && inputVec[leftIndex] < inputVec[leftIndex -1])
    {
        if (inputVec[leftIndex-1] > inputVec[temp]) 
            temp = leftIndex-1;
        leftIndex --;
    }
    leftIndex --;  

    // special case
    // if leftIndex equals 0 and inputVec[0] > inputVec[1]
    // then the vector is already in decreasing order
    if (leftIndex == 0 && inputVec[0] > inputVec[1]) return;

    // find the smallest value after leftIndex that is larger than leftIndex
    // in other words... if we have the vector 1 2 4 9 8 7 6 5 3
    // leftIndex will be set to 4 and temp will be set to 5 (the smallest value that is larger than 4)
    int rightIndex = inputVec.size()-1;
    while (leftIndex < rightIndex)
    {
        
        //cout << "rightIndex" << rightIndex << endl;
        //cout << "leftIndex" << leftIndex << endl;
        if (inputVec[rightIndex]>inputVec[leftIndex] && inputVec[rightIndex] < inputVec[temp]) 
            temp = rightIndex;
        rightIndex = rightIndex -1;
    }

    // swap the values of leftIndex and temp
    int tempValue = inputVec[temp];
    inputVec[temp] = inputVec[leftIndex];
    inputVec[leftIndex] = tempValue;

    // reorder everything to the right of leftIndex in increasing order
    vector<int> tempVec(inputVec.begin()+leftIndex+1, inputVec.end());
    bubbleSort(tempVec);
    leftIndex++;
    for (size_t i = 0; i < tempVec.size(); i++)
        inputVec[leftIndex + i] = tempVec[i];

    return;
}

// sorts a vector in ascending order using bubble sort
void bubbleSort(vector<int> &inputVec)
{
    int temp;
    bool swap = true;
    while(swap)
    {
        swap = false;
        for (size_t i = 0; i < inputVec.size()-1; i++)
        {
            if (inputVec[i]>inputVec[i+1])
            {
                temp = inputVec[i];
                inputVec[i]= inputVec[i+1];
                inputVec[i+1]=temp;
                swap = true;
            }
        }
    }
}