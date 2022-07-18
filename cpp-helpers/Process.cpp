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

vector<string> explode(string s, const string &delimiter) {
    size_t pos = 0;
    std::string subs;
    vector<std::string> result;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        subs = s.substr(0, pos);
        result.push_back(subs);
        s = s.substr(pos + delimiter.length());
    }
    if (!s.empty())
        result.push_back(s);
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
    static string getKey(string param, const string &startWith = "--") {
        if (size_t pos = param.find(startWith) != string::npos) {
            param = param.substr(pos + 1);
            vector<string> exp = explode(param, '=');
            return exp.at(0);
        } else {
            return "";
        }
    }

    static string getValue(string param, const string &startWith = "--") {
        if (size_t pos = param.find(startWith) != string::npos) {
            param = param.substr(pos + 1);
            vector<string> exp = explode(param, '=');
            return exp.at(1);
        } else {
            return "";
        }
    }


};


int main(int argc, char *argv[]) {
    // DEFAULT OPTIONS
    int ignoreFirst = 0;
    int ignoreLast = 0;
    string delimiter = ",";
    string separator = "\t";
    string select;
    // END OPTIONS

    vector<int> project;

    string param;
    for (int i = 1; i < argc; i++) {
        string key = Param::getKey(argv[i]);
        string value = Param::getValue(argv[i]);

        if (key == "ignorefirst")
            ignoreFirst = stoi(value);
        else if (key == "ignorelast")
            ignoreLast = stoi(value);
        else if (key == "delimiter")
            delimiter = value;
        else if (key == "separator")
            separator = value;
        else if (key == "project") {
            auto projectValues = explode(value, ',');
            for (auto &val: projectValues) {
                project.push_back(stoi(val));
            }
        } else if (key == "select")
            select = value;
    }
    vector<string> entry;

    bool isEmpty = true;
    string textLoc;
    while (getline(cin, textLoc)) {
        isEmpty = false;
        if (ignoreFirst > 0)
            textLoc = textLoc.substr(ignoreFirst);

        if (ignoreLast > 0)
            textLoc = textLoc.substr(0, textLoc.length() - ignoreLast);

        textLoc = replaceAll(textLoc, delimiter, "\t");
        textLoc = replaceAll(textLoc, "\t", separator);


        if (select.empty() || (!select.empty() && textLoc.find(select) != string::npos))
            entry.push_back(textLoc);
    }

    if(isEmpty) return 2;
    if (entry.empty()) return 1;

    bool isFirstRow = true;
    for (auto &val: entry) {
        if (!isFirstRow) cout << endl;
        if (project.empty()) {
            cout << val;
            isFirstRow = false;
        }
        else {
            auto columns = explode(val, separator);
            bool isFirstCol = true;
            for (int &col_no: project) {
                if ((col_no - 1) < columns.size()) {
                    if (!isFirstCol) cout << separator;
                    cout << columns.at(col_no - 1);
                }
                isFirstCol = false;
                isFirstRow = false;
            }
        }
    }


    return 0;
}