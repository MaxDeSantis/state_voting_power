/*
    Author: Max DeSantis
    Desc. : This program computes the Banzhaf power of the states within the United States electoral college. It uses generating functions to do so.

*/


#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace::std;

vector<struct polyTerm> polyMultiply(vector<struct polyTerm> v1, vector<struct polyTerm> v2);
void polyPrint(vector<struct polyTerm> v1);

struct polyTerm{
    int64_t coeff = 1;
    int exp = 0;
};

int main(int argc, char* argv[]) {


    vector<int> vals = {55, 38, 29, 29, 20, 20, 18, 16, 16, 15,
                        14, 13, 11, 11, 11, 11, 10, 10, 10, 10,
                        10, 9, 9, 9, 8, 7, 7, 7, 6, 6, 6, 6, 6,
                        6, 6, 5, 5, 5, 4, 4, 4, 4, 4, 3, 3, 3,
                        3, 3, 3, 3, 3};
    string postCodes[] = {"CA", "TX", "FL", "NY", "IL", "PA", "OH", "GA", "MI", "NC",
                        "NJ", "VA", "AZ", "TN", "IN", "MA", "WA", "MN", "MO", "WI",
                        "MD", "CO", "AL", "SC", "KY", "OR", "OK", "CT", "NV", "UT", "KS", "IA", "AR",
                        "LA", "MS", "NM", "NE", "WV", "ID", "RI", "NH", "ME", "HI", "MT", "WY", "SD",
                        "ND", "DC", "DE", "VT", "AK"};

    vector<polyTerm> mainVec(1);
    vector<polyTerm> vec2(2);
    vector<polyTerm> vec1;

    //vector<int> vals = {2, 2, 4, 10, 16, 4, 5};

    mainVec.at(0).coeff = 1;

    for(int i = 0; i < vals.size(); i++) {
        vec1 = mainVec;
        vec2.at(1).exp = vals.at(i);
        mainVec = polyMultiply(vec1, vec2);
    }

    sort(mainVec.begin(),
    mainVec.end(),
    [](const polyTerm &a, const polyTerm&b) {
        return a.exp < b.exp;
    });

    polyPrint(mainVec);
    return 0;
}

vector<struct polyTerm> polyMultiply(vector<struct polyTerm> v1, vector<struct polyTerm> v2) {
    vector<struct polyTerm> tempVec;
    struct polyTerm tempTerm;

    for(int i = 0; i < v1.size(); i++) {

        for(int j = 0; j < v2.size(); j++) {

            tempTerm.exp = v1.at(i).exp + v2.at(j).exp;

            tempTerm.coeff = (v1.at(i).coeff * v2.at(j).coeff);

            if(tempTerm.exp < 270) {
                const auto p = find_if(tempVec.begin(), tempVec.end(), [tempTerm](const polyTerm &term) {return term.exp == tempTerm.exp;});
            
                if(p != tempVec.end()) {
                    tempVec.at(p - tempVec.begin()).coeff = tempVec.at(p - tempVec.begin()).coeff + tempTerm.coeff;
                }
                else {
                    tempVec.push_back(tempTerm);
                }
            }
        }
    }

    return tempVec;
}

void polyPrint(vector<struct polyTerm> v1) {
    for(int i = 0; i < v1.size()-1; i++) {
        printf("%dx^%d + ", v1.at(i).coeff, v1.at(i).exp);
        if( ((i % 10) == 0) && i != 0) {printf("\n");}
    }
    printf("%dx^%d\n", v1.at(v1.size()-1).coeff, v1.at(v1.size()-1).exp);
}