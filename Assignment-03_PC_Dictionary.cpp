#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
#include<map>
#include<list>
#include<algorithm>

using namespace std;

class Dictionary {
    private:
        string word;
        string partOfSpeech;
        vector<string> definition;

    public:
        Dictionary(string w, string pos, vector<string> d) {
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
        vector<string> getDefinition() {
            return definition;
        }
};

int main() {
    string fileLocation = "./Data.CS.SFSU.txt";
    map<string, vector<string>> hmap;
    bool fileOpen = false;
    ifstream fin(fileLocation);

    while(fileOpen == false) {
        ifstream fin(fileLocation);
        if(fin.is_open()) {
            cout << "! Opening data file... " << fileLocation << endl;
            cout << "! Loading data..." << endl;
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

    return 0;
}