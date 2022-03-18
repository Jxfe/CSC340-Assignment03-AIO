/****************************************************************
*
* File: Assignment-03_PC_Dictionary.cpp
* By: Jeffrey Ma
* Date: 03/14/2022
*
* Description: Dictionary in C++ imports words from txt file
* Displays results dependent on given paramters from user.(Parts of Speech, Reverse, Distinct)
*
****************************************************************/
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
#include<map>
#include<list>
#include<algorithm>
#include<sstream>

using namespace std;

bool hasDigits(string&);
vector<string> processInput(string&);

class Dictionary {                                                                              //Custom Object class to store Word, Parts of Speech and Defintion in 1 Vector
    private:
        string word;
        string partOfSpeech;
        string definition;

    public:
        Dictionary(string w, string pos, string d) {
            word = w;
            partOfSpeech = pos;
            definition = d;
        }
        string getWord() {
            return word;
        }
        string getPartOfSpeech() {
            return partOfSpeech;
        }
        string getDefinition() {
            return definition;
        }
        void setWord(string s) {
            word = s;
        }
        void setPartOfSpeech(string s) {
            partOfSpeech = s;
        }
        void setDefinition(string s) {
            definition = s;
        }
        string toString() {                                                                     // to String method to print out in Dictionary
            string test = word;                                                                 //Sets first letter to uppercase as well as all characters if theres num in string
            if(hasDigits(test) == true) {
                for(auto& s: test) {
                    s = toupper(s);
                }
            }
            test[0] = toupper(test[0]);
            return test + " [" + partOfSpeech + "] : " +definition;
        }
        bool operator > (const Dictionary& str) const {                                         //Required to override the compare function
            return (partOfSpeech < str.partOfSpeech);
        }
        bool operator == (const Dictionary& str) const {                                        //Used to make comparisons
            string temp1 = str.definition;
            string temp2 = definition;
            for(auto& c: temp1) {                                                               //Swithes input to lowercase         
                temp1 = tolower(c);
            }
            for(auto& c: temp2) {                                                               //Swithes input to lowercase         
                temp2 = tolower(c);
            }
            if (partOfSpeech != str.partOfSpeech || temp1 != temp2) {
                return false;
            }
            return true;
        }       
};

vector<Dictionary> returnPartsOfSpeech(string, vector<Dictionary>);
vector<Dictionary> returnDistinct(vector<Dictionary>);
vector<Dictionary> returnReverse (vector<Dictionary>);
vector<string> pos = {"noun", "verb", "adjective", "adverb", "pronoun", "preposition", "conjunction", "interjection"};

int main() {
    string fileLocation = "./data.CS.SFSU.txt";                                                 //Stores text file location
    ifstream fin(fileLocation);
    vector<Dictionary> dict;
    vector<string> words;                                                                       //Stores words to later compare to input
    int counter = 0;                                                                            //Counter for Search[x] later

    while(true) {                                                                               //Loop to process String and check if file location is correct
        ifstream fin(fileLocation);
        string line;
        if(fin.is_open()) {                                                                     
            cout << "! Opening data file... " << fileLocation << endl;
            cout << "! Loading data..." << endl;

            while(getline(fin, line)) {                                                         //Reads each line 1 by one and processes it into a Vector
                int findDivide = line.find_first_of("|");
                int findArrow = line.find_first_of("-=>>");
                string word = line.substr(0, findDivide);                                       //Gets Word
                string temp = word;
                words.push_back(word);
                string pos;
                string def;
                line.erase(0, findDivide + 1);                                                  //Erases word and divider
                bool running = true;
                while(running) {                                                                //Loop to break down line and get definitions and parts of speech
                    findArrow  = line.find_first_of("-=>>");
                    findDivide = line.find_first_of("|");
                    if(findDivide == -1) {                                                      //If the divider is not found for next definition it returns -1
                        pos = line.substr(0, findArrow - 1);                                    //Gets Parts of Speech by using subtr to next Arrow
                        line.erase(0, findArrow + 5);                                           //Removes the Arrow and the rest should be definition
                        def = line;
                        def[0] = toupper(def[0]);
                        Dictionary temp(word, pos, def);
                        dict.push_back(temp);                                                   //Adds the newly made temp Dictionary instance to vector dict
                        break;                                                                  //breaks because the string has no more dividers so no more definitions
                    }
                    else {                                                                      //Same as above but divider is still there so it continues the while loop
                        pos = line.substr(0, findArrow - 1);
                        line.erase(0, findArrow + 5);
                        findDivide = line.find_first_of("|");
                        def = line.substr(0, findDivide);
                        def[0] = toupper(def[0]);
                        line.erase(0, findDivide + 1);
                        Dictionary temp(word, pos, def);
                        dict.push_back(temp);
                    }
                }
            }
            break;                                                                              //Breaks loop if file opened fine 
        }
        else {
            cout << "<!>ERROR<!> ===> File could not be opened." << endl;
            cout << "<!>ERROR<!> ===> Provided file path: " << fileLocation << endl;
            cout << "<!>Enter the CORRECT data file path: ";
            cin >> fileLocation;                                                                //Requests new file location because current one is wrong
        }
    }
    cout << "! Closing data file... " << fileLocation << endl;
    fin.close();
    //std::sort(dict.begin(), dict.end(),greater<Dictionary>());                                  //Sorts the vector by part of speech so adjective, adverb... noun
    cout << "====== DICTIONARY 340 C++ ===== " << endl;
    cout << "------ Keywords: " << words.size() << endl;
    cout << "------ Definitions: " << dict.size() << endl << endl;

    while(true) {                                                                               //Dictionary loop for the search function
        string userInput;                                                              
        vector<string> inputs;                                                                  //Vector used to store inputs
        bool isPos = false;                                                                     //bool value to see if parts of string is used
        counter++;                                                                              //Adds to above counter for Search[x]
        bool printHelp = false;
        cout << "Search [" << counter << "] ";
        getline(cin, userInput);                                                                //Gets line from user and assigns to userInput

        for(auto& c: userInput) {                                                               //Swithes input to lowercase         
            c = tolower(c);
        }
        inputs = processInput(userInput);                                                       //Assigns word and param to vector inputs


        if(inputs[0] == "!q" || inputs[0] == "!quit") {                                        //Breaks out of loop if requested
            cout << endl << "-----THANK YOU-----" << endl;
            break;
        }
        cout << "   |" << endl;
        if(inputs[0] == "!help" || inputs[0] == "" || inputs[0] == " ") {                       //Outputs help if requested
            cout << "   PARAMETER HOW-TO, please enter:" << "\n"
                << "   1. A search key -then 2. An optional part of speech -then" << "\n" 
                << "   3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
            printHelp = true;
        }


        vector<Dictionary> temp = dict;                                                         //New vector made so I dont modify original
        if(inputs.size() == 1) {                                                                //Does following actions if input size is 1
            if (find(words.begin(), words.end(), inputs[0]) != words.end()) {                   //Checks if word is in the dictionary
                for(Dictionary i : temp) {                                                      //Loops through dictionary and prints if it matches word
                    if(i.getWord() == inputs[0]) {
                        cout << "   " <<  i.toString() << "\n";
                    }
                }
            }
            else {
                if(printHelp == false) {
                    cout << "   <NOT FOUND> To be considered for the next release. Thank you." << endl;
                    cout << "   |" << endl;
                    cout << "   |" << endl;
                    cout << "   PARAMETER HOW-TO, please enter:" << "\n"
                    << "   1. A search key -then 2. An optional part of speech -then" << "\n" 
                    << "   3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
                }
            }
        }
        if(inputs.size() == 2) {                                                                //Does following actions if input size is 2            
            for(string s : pos) {
                if(inputs[1] == s) {
                    isPos = true;
                    temp = returnPartsOfSpeech(inputs[1], temp);
                }
            }
            if (inputs[1] == "distinct") {                                                      //Checks for Distinct in param 
                temp = returnDistinct(temp);
            }
            std::sort(dict.begin(), dict.end(),greater<Dictionary>());
            if (inputs[1] == "reverse") {                                                       //Checks for Reverse in param 
                temp = returnReverse(temp);
            }
            if(inputs[1] != "distinct" && inputs[1] != "reverse" && isPos == false) {           //Outputs error messages if param does not match Distinct, Reverse or Pos
                cout << "   <The entered 2nd parameter " << "'" << inputs[1] << "' is NOT a part of speech.>" << endl;
                cout << "   <The entered 2nd parameter " << "'" << inputs[1] << "' is NOT 'distinct'.>" << endl;
                cout << "   <The entered 2nd parameter " << "'" << inputs[1] << "' is NOT 'reverse'.>" << endl;
                cout << "   <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>" << endl;
            }
            for(Dictionary i : temp) {
                if(i.getWord() == inputs[0]) {
                    cout << "   " <<  i.toString() << "\n";
                }
            }
        }
        if(inputs.size() == 3) {                                                                //Does following actions if input size is 3
            for(string s : pos) {
                if(inputs[1] == s) {
                    isPos = true;
                    temp = returnPartsOfSpeech(inputs[1], temp);
                }
            }
            if (inputs[2] == "distinct" || inputs[1] == "distinct") {
                temp = returnDistinct(temp);
            }
            std::sort(dict.begin(), dict.end(),greater<Dictionary>());
            if (inputs[2] == "reverse" || inputs[1] == "reverse") {
                temp = returnReverse(temp);
            }
            
            if(inputs[1] != "distinct" && inputs[1] != "reverse" && isPos == false) {
                cout << "   <The entered 2nd parameter " << "'" << inputs[1] << "' is NOT a part of speech.>" << endl;
                cout << "   <The entered 2nd parameter " << "'" << inputs[1] << "' is NOT 'distinct'.>" << endl;
                cout << "   <The entered 2nd parameter " << "'" << inputs[1] << "' is NOT 'reverse'.>" << endl;
                cout << "   <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>" << endl;
            }
            if(inputs[2] != "distinct" && inputs[2] != "reverse") {
                cout << "   <The entered 3rd parameter " << "'" << inputs[2] << "' is NOT 'distinct'.>" << endl;
                cout << "   <The entered 3rd parameter " << "'" << inputs[2] << "' is NOT 'reverse'.>" << endl;
                cout << "   <The 3rd parameter should be 'distinct' or 'reverse'.> " << endl;
            }

            for(Dictionary i : temp) {
                    if(i.getWord() == inputs[0]) {
                        cout << "   " <<  i.toString() << "\n";
                    }
                }
        }
        if(inputs.size() == 4) {                                                                //Does following actions if input size is 4
            for(string s : pos) {
                if(inputs[1] == s) {
                    isPos = true;
                    temp = returnPartsOfSpeech(inputs[1], temp);
                }
            }
            if (inputs[2] == "distinct" || inputs[1] == "distinct") {
                temp = returnDistinct(temp);
            }
            std::sort(dict.begin(), dict.end(),greater<Dictionary>());
            if (inputs[1] == "reverse" || inputs[2] == "reverse" || inputs[3] == "reverse") {
                temp = returnReverse(temp);
            }
        
            if(inputs[1] != "distinct" && inputs[1] != "reverse" && isPos == false) {
                cout << "   <The entered 2nd parameter " << "'" << inputs[1] << "' is NOT a part of speech.>" << endl;
                cout << "   <The entered 2nd parameter " << "'" << inputs[1] << "' is NOT 'distinct'.>" << endl;
                cout << "   <The entered 2nd parameter " << "'" << inputs[1] << "' is NOT 'reverse'.>" << endl;
                cout << "   <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>" << endl;
            }
            if(inputs[2] != "distinct" && inputs[2] != "reverse") {
                cout << "   <The entered 3rd parameter " << "'" << inputs[2] << "' is NOT 'distinct'.>" << endl;
                cout << "   <The entered 3rd parameter " << "'" << inputs[2] << "' is NOT 'reverse'.>" << endl;
                cout << "   <The 3rd parameter should be 'distinct' or 'reverse'.> " << endl;
            }
            //cout << "Fuk" << endl;
            if(inputs[3] != "reverse") {
                cout << "   <The entered 4th parameter " << "'" << inputs[2] << "' is NOT 'reverse'.>" << endl;
                cout << "   <The 4th parameter should be 'reverse'.> " << endl;
                
            }
            for(Dictionary i : temp) {
                    if(i.getWord() == inputs[0]) {
                        cout << "   " <<  i.toString() << "\n";
                    }
             }
        }
        else if(inputs.size() > 4) {                                                            //If more then 4 params print help
            cout << "   PARAMETER HOW-TO, please enter:" << "\n"
                << "   1. A search key -then 2. An optional part of speech -then" << "\n" 
                << "   3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
        }
        cout << "   |" << endl;
    }
    return 0;
}

bool hasDigits(string& str) {                                                                   //Checks if number is inside string
    return any_of(str.begin(), str.end(), ::isdigit);
}

vector<string> processInput(string& str) {                                                      //Splits inputs using spaces
    vector<string> input;
    string temp;
    std::stringstream ss(str);
    while (getline(ss, temp, ' ')){
		input.push_back(temp);
	}
    return input;
}

vector<Dictionary> returnPartsOfSpeech(string partsOfSpeech, vector<Dictionary> v) {            //Returns Vector with just parts of speech
    vector<Dictionary> pos;
    for(Dictionary i : v) {                                                                     //Loops through entire param
        if(i.getPartOfSpeech() == partsOfSpeech) {                                              //If the Dictionary part of speech matches param it adds it to vector pos
            pos.push_back(i);
        }
    }
    return pos;
}

vector<Dictionary> returnDistinct(vector<Dictionary> v) {            
    vector<Dictionary> temp = v;            
    bool duplicateFound = false;
    if (temp.size() > 1) {
        temp.erase(unique(temp.begin(), temp.end()), temp.end()); // remove duplicates
    }
    return temp;
}

vector<Dictionary> returnReverse(vector<Dictionary> v) {                                        //Returns Vector with reversed param
    vector<Dictionary> reverse;
    for(int i = v.size() - 1 ; i >= 0; i--) {                                                   //Loops through Vector backwards
        reverse.push_back(v[i]);                                                                //Adds it to vector reverse as it loops backwards
    }
    return reverse;
}