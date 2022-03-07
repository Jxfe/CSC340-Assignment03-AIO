#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
#include<map>
#include<list>
#include<algorithm>

using namespace std;

bool hasDigits(string&);

class Dictionary {
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
        string toString() {
            string test = word;         //Sets first letter to uppercase
            if(hasDigits(test) == true) {
                for(auto& s: test) {
                    s = toupper(s);
                }
            }
            test[0] = toupper(test[0]);
            return test + " [" + partOfSpeech + "] : " +definition;
        }
};

int main() {
    string fileLocation = "./Data.CS.SFSU.txt";
    map<string, vector<string>> hmap;
    bool fileOpen = false;
    ifstream fin(fileLocation);
    vector<Dictionary> dict;
    int counter = 0;
    bool isRunning = true;

    while(fileOpen == false) {
        ifstream fin(fileLocation);
        string line;
        if(fin.is_open()) {
            cout << "! Opening data file... " << fileLocation << endl;
            cout << "! Loading data..." << endl;

            while(getline(fin, line)) {
                int findDivide = line.find_first_of("|");
                int findArrow = line.find_first_of("-=>>");
                string word = line.substr(0, findDivide); //Gets Word
                string pos;
                string def;
                line.erase(0, findDivide + 1);            //Erases word and divider
                bool running = true;
                while(running) {
                    findArrow  = line.find_first_of("-=>>");
                    findDivide = line.find_first_of("|");
                    if(findDivide == -1) {
                        pos = line.substr(0, findArrow - 1);
                        line.erase(0, findArrow + 5);
                        def = line;
                        Dictionary temp(word, pos, def);
                        dict.push_back(temp);
                        break;
                    }
                    else {
                        pos = line.substr(0, findArrow - 1);
                        line.erase(0, findArrow + 5);
                        findDivide = line.find_first_of("|");
                        def = line.substr(0, findDivide);
                        line.erase(0, findDivide + 1);
                        Dictionary temp(word, pos, def);
                        dict.push_back(temp);
                    }
                }
            }
            break;
        }
        else {
            cout << "<!>ERROR<!> ===> File could not be opened." << endl;
            cout << "<!>ERROR<!> ===> Provided file path: " << fileLocation << endl;
            cout << "<!>Enter the CORRECT data file path: ";
            cin >> fileLocation;
        }
    }
    cout << "! Closing data file... " << fileLocation << endl;
    fin.close();
    cout << "====== DICTIONARY 340 C++ ===== " << endl;
    cout << "------ Keywords: 19" << endl;
    cout << "------ Definitions: 61" << endl << endl;

    //for (Dictionary i : dict)
    //{
    //    cout << i.toString() << "\n";
    //}

    do {
        string userInput;
        string word;
        string param;
        bool shouldPrint = true;
        counter++;
        
        cout << "Search [" << counter << "] ";
        cin >> userInput;

        for(auto& c: userInput) {
            c = tolower(c);
        }

        if(userInput == "!help" || userInput == "" || userInput == " ") {
            cout << "   |" << endl;
            cout << "   PARAMETER HOW-TO, please enter:" << "\n"
                << "   1. A search key -then 2. An optional part of speech -then" << "\n" 
                << "   3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
            cout << "   |" << endl;
        }
        else if(userInput == "!q" || userInput == "!quit") {
            isRunning = false;
            cout << endl << "-----THANK YOU-----" << endl;
            break;
        }

        cout << "   |" << endl;
        for (Dictionary i : dict)
        {
            if(i.getWord() == userInput) {
                cout << "   " <<  i.toString() << "\n";
            }
        }
        cout << "   |" << endl;

    }while(isRunning);

    return 0;
}

bool hasDigits(string& str) { //Checks if number is inside string
    return any_of(str.begin(), str.end(), ::isdigit);
}W