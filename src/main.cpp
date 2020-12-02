/*
    Author: Max DeSantis
    Desc. : This program computes the Banzhaf power of the states within the United States electoral college. It uses generating functions to do so.

*/


#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace::std;

vector<int> polyMultiply(vector<int> v1, vector<int> v2);
void polyPrint(vector<int> v1);

int main(int argc, char* argv[]) {


    int voteCounts[] = {55, 38, 29, 29, 20, 20, 18, 16, 16, 15,
                        14, 13, 11, 11, 11, 11, 10, 10, 10, 10,
                        10, 9, 9, 9, 8, 7, 7, 7, 6, 6, 6, 6, 6,
                        6, 6, 5, 5, 5, 4, 4, 4, 4, 4, 3, 3, 3,
                        3, 3, 3, 3, 3};
    string postCodes[] = {"CA", "TX", "FL", "NY", "IL", "PA", "OH", "GA", "MI", "NC",
                        "NJ", "VA", "AZ", "TN", "IN", "MA", "WA", "MN", "MO", "WI",
                        "MD", "CO", "AL", "SC", "KY", "OR", "OK", "CT", "NV", "UT", "KS", "IA", "AR",
                        "LA", "MS", "NM", "NE", "WV", "ID", "RI", "NH", "ME", "HI", "MT", "WY", "SD",
                        "ND", "DC", "DE", "VT", "AK"};

    vector<int> v1(51, 0);
    vector<int> v2 = {1};
    for(int i = 0; i < 4; i++) {
        v1.at(voteCounts[i]) = 1;
        v2 = polyMultiply(v1, v2);
        
        fill(v1.begin(), v1.end(), 0);
    }
    polyPrint(v2);
    return 0;
}

vector<int> polyMultiply(vector<int> v1, vector<int> v2) {
    int i, j, k;
    
    vector<int> v3(v1.size() + v2.size());

    for(i = 0; i < v1.size(); i++) {
        for(j = 0; j < v2.size(); j++) {
            k = i + j;
            v3.at(k) = v3.at(k) + (v1.at(i) * v2.at(j));
        }
    }

    return v3;
}

void polyPrint(vector<int> v) {
    int size = v.size();
    for(int x = 0; x < size - 1; x++){
        printf(" %dx^%d +", v.at(x), x);
    }
    printf("%dx^%d\n", v.at(size - 1), size - 1);
    return;
}