//
// Created by biumr on 06.04.2022.
//

#ifndef LAB1_AGGREGATE_H
#define LAB1_AGGREGATE_H

#include <utility>

#include "iostream"
#include "vector"

using namespace std;

class Aggregate {
public:
    explicit Aggregate(vector<float> newValues) {
        values = std::move(newValues);
        result =  0;
    }

    void run(const string& operation) {
        if(operation == "avg")
            result = getAverage();
        else if(operation == "min")
            result = getMin();
        else if(operation == "max")
            result = getMax();
        else if(operation == "sum")
            result = getSum();
        else if(operation == "dev")
            result = getSum();
        else if(operation == "sum")
            result = getSum();
        else
            throw invalid_argument("Correct operation not given.");
    }

    float getResult() const {
        return result;
    }

private:
    vector<float> values;
    float result;

    float getAverage() {
        if (values.empty()) return 0;
        float sum = 0;
        for (auto &value: values) {
            sum += value;
        }

        return sum / values.size();
    }

    float getSum() {
        float sum =0;
        for (auto &value: values)
            sum += value;

        return sum;
    }

    float getMin() {
        if (values.empty()) {
            throw std::invalid_argument( "Not enough numbers." );
        }
        float min = values.at(0);
        for (auto &value: values) {
            if(value < min)
                min = value;
        }

        return min;
    }

    float getMax() {
        if (values.empty()) {
            throw std::invalid_argument( "Not enough numbers." );
        }
        float max = values.at(0);
        for (auto &value: values) {
            if(value > max)
                max = value;
        }

        return max;
    }

    float count() {
        return values.size();
    }

    float dev() {
        if (values.empty()) {
            throw std::invalid_argument( "Not enough numbers." );
        }
        float avg = getAverage();

        float sum = 0;
        for (auto &value: values) {
            sum += pow(value - avg, 2);
        }
        return  sqrt(sum/values.size());
    }

    float median() {
        if(values.size()%2 == 0)
            return values.at(values.size()/2);
        else {
            return (values.at(values.size()/2) + values.at(values.size()/2 + 1))/2;
        }
    }


};


#endif //LAB1_AGGREGATE_H
