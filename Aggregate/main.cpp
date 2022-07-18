
#include "string"
#include "iostream"
#include "StringToFloatConventer.h"
#include "ConsoleReader.h"
#include "Env/Env.h"
#include "Aggregate.h"

using namespace std;
int main(int argc, char *argv[], char *envp[]) {

    try {
        Env env(argc, argv);
        string operation = env.getParam("operation");

        StringToFloatConventer *converter;
        converter = new StringToFloatConventer;

        ConsoleReader<float> reader(converter);
        reader.readLines();

        Aggregate aggregate(reader.getValues());
        aggregate.run(operation);

        cout<<aggregate.getResult();
    } catch(const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
    }






}