#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Param {
private:
    string value;
    int position;
    int quality;
public:

    explicit Param(string newVal, int pos) {
        value = std::move(newVal);
        position = pos;
        quality = 0;
    }

    int getPos() {
        return position;
    }

    int getQuality(const string& text) {
        size_t pos = 0;
        quality = 0;
        while ((pos = text.find(value, pos)) != std::string::npos) {
            quality++;
            pos += value.length();
        }
        return quality;
    }
};

int main(int argc, char *argv[], char *envp[]) {
    vector<Param*> *params;
    params = new vector<Param*>();
    for (int i=1; i<argc; i++) {
        Param *param;
        param = new Param(argv[i], i);
        params->push_back(param);
    }

    string text;
    string textLoc;
    while(getline(cin, textLoc)) {
        text += textLoc;
    }

    int max = 0;
    int pos = 0;
    for(auto &param: *params) {
        int qualityLoc = param->getQuality(text);
        if(qualityLoc > max) {
            max = qualityLoc;
            pos = param->getPos();
        }
    }

    for(auto & param : *params) {
        delete param;
    }
    params->clear();
    delete params;

    return pos;
}