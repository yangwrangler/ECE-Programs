###############################################################################
/* This program accepts a string from the console and reports whether or not it is a palindrome.
Examples:   "abba" is a palindrome
"abbb" is not a palindrome

Created by: Panayioti C. Kitsos
*/
##############################################################################

#include<iostream>
#include<string>
using namespace std;

int main(int argc, char* argv[])
{
    string str;
    cout << "Enter strings to test; when done, enter a ." << endl;

    while (true)
    {
        cin >> str;
        if (str ==".")
            break;

        size_t length = str.length();
        bool isPalindrome = true;
        for (size_t i = 0; i < length/2; i++)
        {
            if (str[i] != str[length - i - 1])
            {
                isPalindrome = false;
                break;
            }
        }

        cout << "\"" << str << "\" is " << (isPalindrome ? "" : "not ")
            << "a palindrome." << endl;
    }
    return 0;
}

