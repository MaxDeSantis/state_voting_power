//Testing polynomial multiplication


#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>

using namespace::std;
int main(int argc, char* argv[]) {

    int i, j, k;
    vector<int> v1 = {1, 2, 3, 0, 7, 10};
    vector<int> v2 = {5, 6, 7};

    vector<int> v3(v1.size() + v2.size());

    for(i = 0; i < v1.size(); i++) {
        for(j = 0; j < v2.size(); j++) {
            k = i + j;
            v3.at(k) = v3.at(k) + (v1.at(i) * v2.at(j));
        }
    }

    
    for(int x = 0; x < v3.size() - 1; x++){
        printf(" %dx^%d +", v3.at(x), x);
    }
    printf("%dx^%d\n", v3.at(v3.size() - 1), v3.size() - 1);


    return 0;
}