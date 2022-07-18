#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> explode(string const &s, char delim) {
    vector<std::string> result;
    istringstream iss(s);

    for (string token; getline(iss, token, delim);) {
        result.push_back(move(token));
    }
    return result;
}

string replaceAll(string str, const string &from, const string &to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

class Param {
public:
    static string getKey(string param) {
        param = replaceAll(param, "-", "");

        vector<string> exp = explode(param, '=');
        return exp.at(0);
    }

    static string getValue(string param) {
        param = replaceAll(param, "-", "");
        vector<string> exp = explode(param, '=');
        if (exp.size() > 1)
            return exp.at(1);
        else return "";
    }
};

int main(int argc, char *argv[]) {
    int lines = 0;
    bool e = false;
    string param;
    for (int i = 1; i < argc; i++) {
        string key = Param::getKey(argv[i]);
        string value = Param::getValue(argv[i]);

        if (key == "lines")
            lines = stoi(value);
        else if (key == "e")
            e = true;
    }

    string textLoc;
    int showed = 0;
    while (getline(cin, textLoc) && showed < lines) {
        if (showed > 0)cout << endl;
        cout << textLoc;
        showed++;
    }

    if (showed < lines && !e) {
        cerr << "Zabraklo " << lines - showed << " linii do wypisania!";
    }

    if (showed < lines)
        return 2;
    return 0;
}

