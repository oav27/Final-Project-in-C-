/* This file contains functions that when working together will create a list of movies that meet the user's criteria of
 * representing all the genres that they want to see in their movie recommendations. The file contains two solutions.
 * Solution 2 is commented out, but to test if it works, just uncomment Solution 2 and comment out Solution 1.
 * Student Code written by Olivia Avila
 * Citation: Used PQ Heap from assignment 4, so this includes the use of DataPoint struct. Went to Group Office Hours
 * to brainstorm/exhange ideas for Solution 2 and for alphabetized helper function.
*/

#include "map.h"
#include "search.h"
#include "set.h"
#include "strlib.h"
#include "vector.h"
#include "testing/SimpleTest.h"
#include "simpio.h"
#include "/Users/elsaavila/Desktop/106B/starter-assign4/pqheap.h"
#include "/Users/elsaavila/Desktop/106B/starter-assign4/datapoint.h"


using namespace std;

/* Helper Function. Will take in a sorted vector and then will make sure that it is datapoints that have the same priority will
 * be in alphabetized order. If they are not, then they will be rearranged.
*/
Vector <DataPoint> alphabetize(Vector<DataPoint> check){
    for (int i = 0; i < check.size(); i++){
        if (i != check.size()-1){
            int next = i + 1;
            while (check[i].priority == check[next].priority){
                if (check[i].label > check[next].label){
                    DataPoint temp = check[i];
                    check[i] = check[next];
                    check[next] = temp;
                }
                next++;
                if (next == check.size()){
                    break;
                }
            }
        }
    }
    return check;
}

/* This function is the student implementation part of the project. This is where the student will create the getMovieRecs function.
 * The function will take in two arguments, a prepopulated map and a set of strings. The set of strings will represent the genres that
 * the movies must belong to in the map. (The student is guaranteed that the set of strings being passed in will be valid keys to the map.
 * The function should return a vector of datapoints, or movie elements that are in sorted and
 * alphabetized order.
 * There are two solutions.
*/
Vector <DataPoint> getMovieRecs(Map<string, Vector<DataPoint>>& allMovies, Set<string> userWants){
    //Solution 1
    Vector <DataPoint> vec;
    Vector <DataPoint> finalMovies = {};

    if (userWants.isEmpty()){
        return finalMovies;
    }
    for (string elem: userWants){
        vec += allMovies[elem];
    }

    if (userWants.size() == 1){
        finalMovies = vec;
    }
    else{
        for (int i = 0; i < vec.size(); i++){
            DataPoint curr = vec[i];
            int counter = 0;
            int shouldBe = userWants.size();
            for (int next = i +1; next < vec.size(); next ++){
                if (curr == vec[next]){
                    counter ++;
                }
            }
            if (counter > 0){
                counter ++;
            }
            if (counter == shouldBe){
                finalMovies.add(curr);
            }
        }
    }

    //Now we pq it!
    PQHeap pq;
    for (int i = 0; i < finalMovies.size(); i++) {
        pq.enqueue(finalMovies[i]);
    }

    for (int i = 0; !pq.isEmpty(); i++) {
        finalMovies[i] = pq.dequeue();
    }

    finalMovies = alphabetize(finalMovies);

    return finalMovies;
}

//    //Solution 2

//    Vector< DataPoint> vec;
//    Map <string, int> movieCountMap;

//    Vector <DataPoint> finalMovies;
//    if (userWants.isEmpty()){
//        return finalMovies;
//    }
//    for (string elem: userWants){
//        vec += allMovies[elem];
//    }

//    if (userWants.size() == 1){
//        finalMovies = vec;
//    }

//    else{
//        for (DataPoint elem: vec){
//            if (!movieCountMap.containsKey(elem.label)){
//                movieCountMap[elem.label] = 1;
//            }
//            else{
//                movieCountMap[elem.label] ++;
//            }
//        }
//    }

//    Vector <string> keys = movieCountMap.keys();
//    Vector <string> movieNames;
//    Set <string> listAlreadyHas;
//    for (string elem: keys){
//        if (movieCountMap[elem] == userWants.size()){
//            movieNames.add(elem);
//        }
//    }

//    for (string name: movieNames){
//        for (DataPoint elem: vec){
//            if (elem.label == name && !listAlreadyHas.contains(name)){
//                finalMovies.add(elem);
//                listAlreadyHas.add(name);
//            }
//        }
//    }


//    //Now we pq it!
//    PQHeap pq;
//    for (int i = 0; i < finalMovies.size(); i++) {
//        pq.enqueue(finalMovies[i]);
//    }

//    for (int i = 0; !pq.isEmpty(); i++) {
//        finalMovies[i] = pq.dequeue();
//    }

//    finalMovies = alphabetize(finalMovies);

//    return finalMovies;
//}

/* * * * * *PROVIDED TESTS * * * * * */
/* DO NOT EDIT BEYOND THIS POINT */

//If student implementation passes these tests, then congrats! You did it! Student should also write their own test cases as well
PROVIDED_TEST("Checks if getMovieRecs works"){
    Map <string, Vector <DataPoint>> miniMap = {{"horror", {{"It", 8}, {"Get Out", 1}, {"Scary Movie", 5}, {"Us", 2}, {"Midsommar", 3}, {"Heriditary", 3}}},
                                                {"romance", {{"The Proposal", 1}, {"The Notebook", 4}, {"High School Musical", 5}, {"Scary Movie", 5}}},
                                                {"comedy", {{"The Proposal", 1}, {"Scary Movie", 5}, {"White Chicks", 6}, {"Thelma & Louise", 1}, {"High School Musical", 5}, {"Men In Black", 7}, {"Steel Magnolias", 1}, {"Man from U.N.C.L.E.", 4}, {"Mean Girls", 2}}},
                                                {"action", {{"White Chicks", 6}, {"Thelma & Louise", 1}, {"Inception", 1}, {"Scary Movie", 5}, {"Men In Black", 7}, {"Man from U.N.C.L.E.", 4}}},
                                                {"drama", {{"Steel Magnolias", 1}, {"The Notebook", 4}, {"Inception", 1}, {"Thelma & Louise", 1}, {"Scary Movie", 5}}}
                                                };

    Set <string> userRequest = {"horror", "drama"};
    Vector <DataPoint> finalList;
    finalList = getMovieRecs(miniMap, userRequest);
    EXPECT_EQUAL(finalList, {{"Scary Movie", 5}});

    userRequest = {"romance", "drama"};
    finalList = getMovieRecs(miniMap, userRequest);
    EXPECT_EQUAL(finalList, {{"The Notebook", 4}, {"Scary Movie", 5}});

    userRequest = {"horror", "romance", "comedy", "action", "drama"};
    finalList = getMovieRecs(miniMap, userRequest);
    EXPECT_EQUAL(finalList, {{"Scary Movie", 5}});

    userRequest = {"romance", "comedy"};
    finalList = getMovieRecs(miniMap, userRequest);
    EXPECT_EQUAL(finalList, {{"The Proposal", 1}, {"High School Musical", 5}, {"Scary Movie", 5}});

    userRequest = {"action"};
    finalList = getMovieRecs(miniMap, userRequest);
    EXPECT_EQUAL(finalList,{{"Inception", 1}, {"Thelma & Louise", 1}, {"Man from U.N.C.L.E.", 4}, {"Scary Movie", 5}, {"White Chicks", 6},  {"Men In Black", 7}});

    userRequest = {"comedy", "drama"};
    finalList = getMovieRecs(miniMap, userRequest);
    EXPECT_EQUAL(finalList, {{"Steel Magnolias", 1}, {"Thelma & Louise", 1}, {"Scary Movie", 5}});

}


PROVIDED_TEST("Checks if alphabetize works"){
    Vector <DataPoint> test = {{"Thelma & Louise", 1},{"Steel Magnolias", 1},  {"Scary Movie", 5}};
    Vector <DataPoint> expect = {{"Steel Magnolias", 1}, {"Thelma & Louise", 1}, {"Scary Movie", 5}};

    EXPECT_EQUAL(alphabetize(test), expect);
}
