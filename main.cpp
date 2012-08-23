#include <iostream>
#include "url_gen.cpp"
using namespace std;

int main () {
    UrlGenerator urlgen;
    cout << "next url" << urlgen.next("http://abrut.us") << " mapped to abrut.us" << endl;
}
