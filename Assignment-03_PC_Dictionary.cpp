#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
#include<map>
#include<list>
#include<algorithm>
#include<sstream>
#include<algorithm>

using namespace std;

bool hasDigits(string&);
vector<string> processInput(string&);

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
        bool operator > (const Dictionary& str) const
        {
            return (partOfSpeech < str.partOfSpeech);
        }
};

vector<Dictionary> returnPartsOfSpeech(string, vector<Dictionary>);
vector<Dictionary> returnDistinct(vector<Dictionary>);
vector<Dictionary> returnReverse (vector<Dictionary>);

int main() {
    string fileLocation = "./data.CS.SFSU.txt";
    bool fileOpen = false;
    ifstream fin(fileLocation);
    vector<Dictionary> dict;
    vector<string> words;
    vector<string> pos = {"noun", "verb", "adjective", "adverb", "pronoun", "preposition", "conjunction", "interjection"};
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
                words.push_back(word);
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
    std::sort(dict.begin(), dict.end(),greater<Dictionary>());  //Sorts the vector by part of speech so adjective, adverb... noun
    cout << "====== DICTIONARY 340 C++ ===== " << endl;
    cout << "------ Keywords: " << words.size() << endl;
    cout << "------ Definitions: " << dict.size() << endl << endl;

    while(true) {
        string userInput;
        vector<string> inputs;
        bool shouldPrint = true;
        counter++;
        
        cout << "Search [" << counter << "] ";
        getline(cin, userInput);

        for(auto& c: userInput) { // swithes input to lowercase
            c = tolower(c);
        }
        inputs = processInput(userInput); //Assigns word and param to inputs

        cout << "   |" << endl;
        if(inputs[0] == "!help" || inputs[0] == "" || inputs[0] == " ") {
            cout << "   PARAMETER HOW-TO, please enter:" << "\n"
                << "   1. A search key -then 2. An optional part of speech -then" << "\n" 
                << "   3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
        }
        else if(inputs[0] == "!q" || inputs[0] == "!quit") {
            isRunning = false;
            cout << endl << "-----THANK YOU-----" << endl;
            break;
        }


        vector<Dictionary> temp = dict;
        if(inputs.size() == 1) {
            if (find(words.begin(), words.end(), inputs[0]) != words.end()) {
                for(Dictionary i : temp) {
                    if(i.getWord() == inputs[0]) {
                        cout << "   " <<  i.toString() << "\n";
                    }
                }
            }
            else {
                cout << "   <Not found.>" << endl;
            }
        }
        if(inputs.size() == 2) {
            
            if (inputs[1] == "distinct") {
                temp = returnDistinct(temp);
            }
            if (inputs[1] == "reverse") {
                temp = returnReverse(temp);
            }
            if (find(inputs.begin(), inputs.end(), inputs[1]) != inputs.end()) {
                temp = returnPartsOfSpeech(inputs[1], temp);
            }

            for(Dictionary i : temp) {
                    if(i.getWord() == inputs[0]) {
                        cout << "   " <<  i.toString() << "\n";
                    }
                }
        }
        if(inputs.size() == 3) {
            if (inputs[2] == "distinct") {
                temp = returnDistinct(temp);
            }
            if (inputs[2] == "reverse") {
                temp = returnReverse(temp);
            }
            if (find(inputs.begin(), inputs.end(), inputs[1]) != inputs.end()) {
                temp = returnPartsOfSpeech(inputs[1], temp);
            }

            for(Dictionary i : temp) {
                    if(i.getWord() == inputs[0]) {
                        cout << "   " <<  i.toString() << "\n";
                    }
                }
        }
        if(inputs.size() == 4) {
            if (inputs[2] == "distinct") {
                temp = returnDistinct(temp);
            }
            if (inputs[2] == "reverse") {
                temp = returnReverse(temp);
            }
            if (find(inputs.begin(), inputs.end(), inputs[1]) != inputs.end()) {
                temp = returnPartsOfSpeech(inputs[1], temp);
            }
            if (inputs[3] == "reverse") {
                temp = returnReverse(temp);
            }

            for(Dictionary i : temp) {
                    if(i.getWord() == inputs[0]) {
                        cout << "   " <<  i.toString() << "\n";
                    }
                }
        }
        else if(inputs.size() > 4) { //If more then 4 params
            cout << "   PARAMETER HOW-TO, please enter:" << "\n"
                << "   1. A search key -then 2. An optional part of speech -then" << "\n" 
                << "   3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
        }


        cout << "   |" << endl;
    }
    return 0;
}

bool hasDigits(string& str) { //Checks if number is inside string
    return any_of(str.begin(), str.end(), ::isdigit);
}

vector<string> processInput(string& str) { //Splits inputs using spaces
    vector<string> input;
    string temp;
    std::stringstream ss(str);
    while (getline(ss, temp, ' ')){
		input.push_back(temp);
	}
    
    //for(auto&s : input) {
    //    cout << s << endl;
    //}
    return input;
}

vector<Dictionary> returnPartsOfSpeech(string partsOfSpeech, vector<Dictionary> v) {
    vector<Dictionary> pos;
    for(Dictionary i : v) {
        if(i.getPartOfSpeech() == partsOfSpeech) {
            pos.push_back(i);
        }
    }
    return pos;
}

vector<Dictionary> returnDistinct(vector<Dictionary> v) {
    vector<Dictionary> distinct;
    return distinct;
}

vector<Dictionary> returnReverse(vector<Dictionary> v) {
    vector<Dictionary> reverse;
    for(int i = v.size() - 1 ; i >= 0; i--) {
        reverse.push_back(v[i]);
    }
    return reverse;
}