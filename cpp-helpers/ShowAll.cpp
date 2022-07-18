#include <iostream>

using namespace std;
int main(int argc, char *argv[], char *envp[]) {
    while(*envp != nullptr) {
        cout<<*envp++<<endl;
    }
    cout<<endl;
    for(int i=1; i<argc; i++) {
        cout <<argv[i]<<endl;
    }

    return 0;
}
