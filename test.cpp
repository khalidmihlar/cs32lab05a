#include <iostream>
#include "tddFuncs.h"
#include "WordCount.h"
#include <sstream>
#include <string>
using namespace std;

int main(){
    WordCount bruh;
    stringstream os;
	bruh.incrWordCount("Sentence");
    bruh.incrWordCount("is");
    bruh.incrWordCount("a");
    bruh.incrWordCount("sentence");
    bruh.dumpWordsSortedByWord(os);
    return 0;
}