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
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <iostream>

const int QUOTA = 270;

using namespace std;
using namespace boost::multiprecision;

vector<struct polyTerm> polyMultiply(vector<struct polyTerm> v1, vector<struct polyTerm> v2);
void polyPrint(vector<struct polyTerm> v1);

struct polyTerm{
    int128_t coeff = 1;
    int exp = 0;
};

struct polyTerm makePoly(int128_t sCoeff, int sExp);

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

    vector<int128_t> stateSwings(vals.size());
    int128_t totalSwings = 0;

    vector<polyTerm> mainVec;
    vector<polyTerm> vec2(2);
    vector<polyTerm> vec1;

    //mainVec.at(0).coeff = 1;

    //Loop through every state
    for(int i = 0; i < vals.size(); i++) { //testing with CA, TX, NY
        mainVec.clear();
        mainVec.push_back(makePoly(1, 0));

        //printf("made it to i: %d\n", i);
        cout << "Current main state : " << postCodes[i] << "\n";

        //Multiply by all other states
        for(int j = 0; j < vals.size(); j++) {
            //printf("made it to j: %d\n", j);

            //Don't multiply if it's our "special" state
            if(i != j) {
                //cout << "Current sub state : " << postCodes[j] << "\n";
                vec1 = mainVec;
                vec2.at(1).exp = vals.at(j);
                mainVec = polyMultiply(vec1, vec2);
            }
            
        }
        //printf("made it here1\n");
        sort(mainVec.begin(),
            mainVec.end(),
            [](const polyTerm &a, const polyTerm&b) {
            return a.exp < b.exp;
        });
        //polyPrint(mainVec);
        //printf("made it here2\n");
        //Here we have a generating function for our specified state i
        for(int k = QUOTA - 1; k >= QUOTA - vals.at(i); k--) {
            //printf("made it here3\n");
            //Sum up the coefficients of the possible swing values (263 - 269 for OK)

            //Need to find the index of the term that has exponents of k
            const auto p = find_if(mainVec.begin(), mainVec.end(), [k](const polyTerm &term) {return term.exp == k;});

            if(p != mainVec.end()) {
                //printf("Swing found! %d\n", k);
                stateSwings.at(i) = stateSwings.at(i) + mainVec.at(p - mainVec.begin()).coeff;
                //cout << "State swings for " << postCodes[i] << " : " << stateSwings.at(i) << "\n";
            }
        }
        //Update total swings
        totalSwings = totalSwings + stateSwings.at(i);
        //cout << "Total swings: " << totalSwings << "\n";
        //printf("made it here3\n");
    }

    for(int x = 0; x < vals.size(); x++) {
        //printf("made it to x: %d\n", x);
        auto swings = cpp_bin_float_quad(stateSwings.at(x));
        auto allSwings = cpp_bin_float_quad(totalSwings);
        auto powerIndex =  swings / allSwings;
        cout << postCodes[x] << " : " << powerIndex << "\n";
    }
    
    

    //polyPrint(mainVec);
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
        cout << v1.at(i).coeff << "x^" << v1.at(i).exp << " + ";
        if( ((i % 10) == 0) && i != 0) {printf("\n");}
    }
    cout << v1.at(v1.size()-1).coeff << "x^" << v1.at(v1.size()-1).exp << "\n";
}

struct polyTerm makePoly(int128_t sCoeff, int sExp) {
    struct polyTerm tempPoly = {sCoeff, sExp};
    return tempPoly;
}