/* This file puts together the working of the students implementation of getMovieRecs. It will ultimately show whether
 * or not the student's implementation works and how it will look on the client side. It contains the main
 * prepopulated map that acts as a database of all of "Olivia's movie recommendations." There are also some helper functions
 * prewritten that will guarantee that the Set of strings being passed into getMovieRecs are valid keys for the prepopulated map.
 * Student Code written by: Olivia Avila
 * Citation: Created helper functions: cleanInput and createWords based off my A1 implementation of soundex.
 * File: main.cpp
 * --------------
 * Sample QT project
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "testing/SimpleTest.h"
#include "getmovie.h"
#include "map.h"
#include "set.h"
#include "/Users/elsaavila/Desktop/106B/starter-assign4/pqheap.h"
#include "/Users/elsaavila/Desktop/106B/starter-assign4/datapoint.h"
#include "strlib.h"
using namespace std;



/* Takes in a string and will return it with just lowercased letters (no puncts).
*/
string cleanInput(string token){
    string result = "";

    for (char elem: token){
        elem = toLowerCase(elem);
        if (isalpha(elem)){
            result += elem;
        }
    }
    return result;
}

/* Takes in user's input and creates a set of strings or words. It cuts out spaces.
*/
Set<string> createWords(string bodyText){
    Set<string> tokens;
    Vector <string> noSpaces = stringSplit(bodyText, " ");
    for (string elem: noSpaces){
        string cleanedToken = cleanInput(elem);
        if (cleanedToken != ""){
            tokens.add(cleanedToken);
        }
    }
    return tokens;

}


/*
 * This sample main brings up testing menu.
 */
int main() {
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }
    Vector <DataPoint> printList;

    //Prepopulated map
    Map <string, Vector <DataPoint>> allMaps = {{"horror", {{"It", 8}, {"Get Out", 1}, {"Scary Movie", 5}, {"Us", 2}, {"Midsommar", 3}, {"Heriditary", 3}, {"Little Shop of Horrors", 6},
                                                            {"Sorry To Bother You", 4}, {"Parasite", 1}}},
                                                {"romance", {{"The Proposal", 1}, {"The Notebook", 4}, {"High School Musical", 5}, {"Scary Movie", 5}, {"Thelma & Louise", 1}, {"Inception", 1}, {"White Chicks", 6},
                                                             {"Little Shop of Horrors", 6}, {"Mean Girls", 2}, {"Steel Magnolias", 1}, {"But I'm A Cheerleader", 7}, {"Legally Blonde", 3}, {"Some Like It Hot", 4},
                                                             {"When Harry Met Sally", 6}}},
                                                {"comedy", {{"The Proposal", 1}, {"Scary Movie", 5}, {"White Chicks", 6}, {"Thelma & Louise", 1}, {"High School Musical", 5}, {"Men In Black", 7}, {"Steel Magnolias", 1},
                                                            {"Man from U.N.C.L.E.", 4}, {"Mean Girls", 2}, {"Little Shop of Horrors", 6}, {"Some Like It Hot", 4}, {"When Harry Met Sally", 6},
                                                            {"Sorry To Bother You", 4}, {"9 to 5", 3}, {"But I'm A Cheerleader", 7}, {"Legally Blonde", 3}, {"Ferris Bueller's", 3}}},
                                                {"action", {{"White Chicks", 6}, {"Thelma & Louise", 1}, {"Inception", 1}, {"Scary Movie", 5}, {"Men In Black", 7}, {"Man from U.N.C.L.E.", 4}, {"Die Hard", 7}}},
                                                {"drama", {{"Steel Magnolias", 1}, {"The Notebook", 4}, {"Inception", 1}, {"Thelma & Louise", 1}, {"Scary Movie", 5}, {"Man from U.N.C.L.E.", 4},
                                                           {"Sorry To Bother You", 4}, {"Parasite", 1}}}
                                               };


    cout << "Hello! Welcome to Olivia's movie recommendations! The genres to pick from are: Horror, Romance, Comedy, Action, and Drama" << endl;
    string userWant = getLine("Please pick which genre(s) you want to see in your movie options (RETURN to quit): ");
    while (userWant != ""){
        Set <string> input;
        Set <string> brokenDown = createWords(userWant);
        for (string elem: brokenDown){
            if (allMaps.containsKey(elem)){
                input.add(cleanInput(elem));
            }
        }

        printList = getMovieRecs(allMaps, input);

        cout << ""<< endl;
        cout << "Okay! So for the genre(s) of "<< input << "..." << endl;
        cout << "Here are my movie recommendations: "<< printList << endl;
        cout <<"Enjoy!" <<endl;

        cout << "" << endl;

        userWant = getLine("Please pick which genre(s) you want to see in your movie options (RETURN to quit): ");
    }

    cout <<""<< endl;
    cout<< "All Done! Hooray! Watch those movies with some popcorn or cookies! Yum. (Peace Out CS106B)" << endl;

    return 0;
}



/* * * * * TESTS BELOW THIS POINT* * * * * */
/*DO NOT EDIT BELOW*/
PROVIDED_TEST("Checks that cleanInput works"){
    string test = "horror";
    string after = "horror";
    EXPECT_EQUAL(cleanInput(test), after);

    test = "hOrrOr";
    after = "horror";
    EXPECT_EQUAL(cleanInput(test), after);

    test = "HORROR";
    after = "horror";
    EXPECT_EQUAL(cleanInput(test), after);

    test = "h$%^Or";
    after = "hor";
    EXPECT_EQUAL(cleanInput(test), after);

    test = "$%^";
    after = "";
    EXPECT_EQUAL(cleanInput(test), after);

}

PROVIDED_TEST("Checks that createWords work"){
    string input = "horror action romance";
    Set <string> expected = {"horror", "action", "romance"};
    EXPECT_EQUAL(createWords(input), expected);

    input = "horror";
    expected = {"horror"};
    EXPECT_EQUAL(createWords(input), expected);

    input = "horror 846770 tupac";
    expected = {"horror", "tupac"};
    EXPECT_EQUAL(createWords(input), expected);

    input = "hor@%^or 846770 tupac";
    expected = {"horor", "tupac"};
    EXPECT_EQUAL(createWords(input), expected);

}
