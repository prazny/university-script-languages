//
// Created by biumr on 06.04.2022.
//

#ifndef LAB1_CONSOLEREADER_H
#define LAB1_CONSOLEREADER_H

#include "vector"
#include "iostream"
#include "string"
#include "StringToFloatConventer.h"

using namespace std;

template<typename T>
class ConsoleReader {
public:
    explicit ConsoleReader(StringToFloatConventer *newConventer) {
        conventer = newConventer;
    }

    void readLines() {
        string lineText;
        while (getline(cin, lineText)) {
            conventer->assign(lineText);
            if (conventer->isCorrect())
                values.push_back(conventer->getConvertedValue());
        }
    }


    vector<T> getValues() {
        return values;
    }

private:
    StringToFloatConventer *conventer;
    vector<T> values;
};


#endif //LAB1_CONSOLEREADER_H
