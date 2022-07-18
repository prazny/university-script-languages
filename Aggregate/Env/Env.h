#ifndef LAB1_ENV_H
#define LAB1_ENV_H

#include "string"
#include "vector"
#include "Param.h"

using namespace std;
class Env {

public:
    Env(int argc, char *argv[]) {
        params = new vector<Param*>();
        for (int i=1; i<argc; i++) {
            Param *param;
            param = new Param(argv[i]);
            params->push_back(param);
        }
    }

    ~Env() {
        params->clear();
        delete params;
    }

    string getParam(const string& name) {
        for(auto param: *params) {
            if(param->getName() == name) {
                return param->getValue();
            }

        }
        return "";
    }

private:
    vector<Param*> *params;
};


#endif //LAB1_ENV_H
