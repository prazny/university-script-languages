#ifndef LAB1_STRINGTOFLOATCONVENTER_H
#define LAB1_STRINGTOFLOATCONVENTER_H

#include "string"

using namespace std;
class StringToFloatConventer {
public:
    void assign(string newValue) {
        value = std::move(newValue);
        isConverted = false;
        convert();
    }
    bool isCorrect()  {
        try {
            float a = stof(value);
            return true;
        } catch (invalid_argument const &exc) {
            return false;
        }
    }

    void convert()  {
        if(isCorrect()) {
            convertedValue = stof(value);
        }
        isConverted = true;
    }

    float getConvertedValue()  {
        if(!isConverted) convert();
        if(isCorrect()) return convertedValue;
        else throw invalid_argument("Value cannot be converted.");
    };

private:
    string value;
    bool isConverted = false;
    float convertedValue;
};


#endif //LAB1_STRINGTOFLOATCONVENTER_H
