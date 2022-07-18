#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

class EnvVar {
private:
    string name;
    bool isNecessary;
    vector<string> *values;
public:
    EnvVar() {
        values = new vector<string>();
        isNecessary = false;
    }

    ~EnvVar() {
        values->clear();
        delete values;
    }

    void setName(string newName) {
        name = std::move(newName);
    }

    string getName() {
        return name;
    }

    void setIsNecessary(bool newValue) {
        isNecessary = newValue;
    }

    void addValue(const string value) {
        values->push_back(value);
    }

    string getFvalue() {
        return values->at(0);
    }

    void showIfNecessaryVar() {
        if (isNecessary) {
            bool isFirst = true;
            cout << name << " = ";
            for (auto &value: *values) {
                if (!isFirst) cout << "\t";
                cout << value << endl;
                isFirst = false;
            }
            if (values->empty()) cout << endl;
        }
    }

};

vector<EnvVar *> *getEnvVars(const vector<string> &envpList) {
    vector<EnvVar *> *envVars;
    envVars = new vector<EnvVar *>();
    for (const auto &envp: envpList) {
        size_t firstEq = envp.find('=');
        EnvVar *newEnvVar;
        newEnvVar = new EnvVar;
        newEnvVar->setName(envp.substr(0, firstEq));
        string values = envp.substr(firstEq + 1) + ";";
        string val;
        size_t pos;
        while ((pos = values.find(';')) != std::string::npos) {
            val = values.substr(0, pos);
            values.erase(0, pos + 1);
            newEnvVar->addValue(val);
            //cout << val << endl;
        }
        envVars->push_back(newEnvVar);
    }
    return envVars;
}

string toLowerCase(string inp) {
    string output = std::move(inp);
    transform(output.begin(), output.end(), output.begin(), [](unsigned char c) { return std::tolower(c); });
    return output;
}

void processSearch(const string &search, vector<EnvVar *> *envVars, bool isCaseSensitive) {
    for (auto &envVar: *envVars) {
        if(isCaseSensitive) {
            if (envVar->getName().find(search) != string::npos)
                envVar->setIsNecessary(true);
        } else {
            if (toLowerCase(envVar->getName()).find(toLowerCase(search)) != string::npos)
                envVar->setIsNecessary(true);
        }

    }
}

bool isStringEquals(const char *string1, const char *string2) {
    if (strlen(string1) != strlen(string2)) return false;

    for (int i = 0; i < strlen(string1); i++)
        if (string1[i] != string2[i]) return false;

    return true;
}


int main(int argc, char *argv[], char *envp[]) {
    vector<string> *envpList;
    vector<string> *searchList;
    envpList = new vector<string>();
    searchList = new vector<string>();
    bool isCaseSensitive = true;

    for (int i = 1; i < argc; i++) {
        if (isStringEquals(argv[i], "-ncs"))
            isCaseSensitive = false;
        else
            searchList->push_back(argv[i]);
    }

    while (*envp != nullptr) {
        envpList->push_back(*envp++);
    }

    vector<EnvVar *> *envVars = getEnvVars(*envpList);
    envpList->clear();
    delete envpList;

    for (auto &search: *searchList) {
        processSearch(search, envVars, isCaseSensitive);
    }


    searchList->clear();
    delete searchList;

    for (auto &var: *envVars) {
        var->showIfNecessaryVar();
    }

    for(auto & envVar : *envVars) {
        delete envVar;
    }
    envVars->clear();
    delete envVars;

    return 0;
}


