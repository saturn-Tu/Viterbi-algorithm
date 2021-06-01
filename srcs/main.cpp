#include "util.h"
using namespace std;

int main(int argc, char** argv) {
    if(argc != 3) {
        cout << "wrong format!\n";
        cout << "./viterbi [input file] [output file]\n";
        return 0;
    }
    Viterbi predictor;
    predictor.parse(argv[1]);
    return 0;
}