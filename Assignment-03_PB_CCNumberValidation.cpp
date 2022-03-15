/****************************************************************
*
* File: Assignment-03_PB_CCNumberValidation.cpp
* By: Jeffrey Ma
* Date: 03/14/2022
*
* Description: Verifies Credit Card #
*
****************************************************************/
#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

bool isvalidcc(const string&);
int getDoubledVal(string value);
int getOddVal(string value);

int main()
{
    //
    // PLEASE DO NOT CHANGE function main
    //
    vector<string> cardnumbers = {
         "371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
        "4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
        "5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
        "4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
        "5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
         "372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
        "4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
        "5556551555555557", "6011316011016011"
    };

    int i;
    vector<string>::iterator itr;

    for (i = 1, itr = cardnumbers.begin(); itr != cardnumbers.end(); ++itr, i++) {
        cout << setw(2)  << i << " " 
             << setw(17) << *itr 
             << ((isvalidcc(*itr)) ? " is valid" : " is not valid") << endl;
    }

    return 0;
}

bool isvalidcc(const string& str) {
    int singleDigitValues = 0;
    int oddPlaceValues = 0;
    int sum = 0;

    if(str.length() < 13 || str.length() > 16) {                                            //Checks to make sure card length is correct
        return false;
    }
    if(!(str[0] == '4' || str[0] == '5' || str[0] == '6' || str.substr(0, 2) == "37")) {    //Checks to ensure it is one of the 4 credit card providers
        return false;
    }

    singleDigitValues = getDoubledVal(str);                                                    //Instruction B 
    oddPlaceValues = getOddVal(str);                                                        //Instruction C
    sum = oddPlaceValues + singleDigitValues;

    if(sum%10 != 0) {                                                                        //Checks to make sure that value is divisible by 10
        return false;
    }
    return true;
}

int getOddVal(string value) {                                                                 // Returns sum of all odd place values
    int sum = 0;
    for(int i = value.length() - 1 ; i >= 0 ; i -= 2) {
        sum += value[i] - '0';
    }
    return sum;
}

int getDoubledVal(string value) {                                                            //Returns adding up all single nums from A
    int sum = 0;
    for (int i = value.length() - 2; i >= 0; i -= 2)
    {
        int temp = (value[i] - '0') * 2;
        if(temp > 9) {
            temp = temp/10 + temp%10;
        }
        sum += temp;
    }
    return sum;
}