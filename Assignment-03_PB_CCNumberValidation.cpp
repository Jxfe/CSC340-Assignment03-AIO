#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

bool isvalidcc(const string&);
int getDoubledVal(int& value);

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

bool isValidCC(const string& cardNum) { // Checks to ensure value is between 13 and 16
	int singleDigitValues = 0;
	int oddPlaceValues = 0;
	
	if(cardNum.length() < 13 || cardNum.length() > 16) {
		return false;
	}
	if(cardNum[0] != '4' || cardNum[0] != '5' || cardNum[0] != '6' || cardNum.substr(0,2) != "37") { // Checks to ensure value is one of the major cards
		return false;
	}

	for(int i = cardNum.length() - 1; i >= 0 ; i--) {
		int temp = cardNum[i] - '0';
		singleDigitValues += getDoubledVal(temp);
	}
	cout << singleDigitValues << endl;

	return true;
}

int getDoubledVal(int& value) {	//Returns the doubled value
	int doubled = value * 2;
	if(value > 9) {
		doubled = value % 10 + value / 10;
	}
	return doubled;
}