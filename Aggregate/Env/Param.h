//
// Created by biumr on 06.04.2022.
//

#ifndef LAB1_PARAM_H
#define LAB1_PARAM_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>


using namespace std;
class Param {
private:
    string value;
    string name;
public:

    explicit Param(string param, const string &startWith = "-") {


        if (size_t pos = param.find(startWith) != string::npos) {
            param = param.substr(pos );
            vector<string> exp = explode(param, '=');
            name = exp.at(0);
            value = exp.at(1);
        } else {
            name = "";
            value = "";
        }
    }

    string getName() {
        return name;
    }
    string getValue() {
        return value;
    }

    static vector<string> explode(string const &s, char delim) {
        vector<std::string> result;
        istringstream iss(s);

        for (string token; getline(iss, token, delim);) {
            result.push_back(move(token));
        }
        return result;
    }


};


#endif //LAB1_PARAM_H
