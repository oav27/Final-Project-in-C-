/* This file contains the public function prototypes of getmovie.
 * Student Code written by Olivia Avila
*/
#pragma once

#include "map.h"
#include "set.h"
#include <string>
#include "vector.h"
#include "/Users/elsaavila/Desktop/106B/starter-assign4/pqheap.h"
#include "/Users/elsaavila/Desktop/106B/starter-assign4/datapoint.h"



#ifndef GETMOVIE_H
#define GETMOVIE_H

#endif // GETMOVIE_H

/* This function creates a vector of DataPoints in alphabetical order, while keeping them in order in terms of priority.
*/
Vector <DataPoint> alphabetize(Vector<DataPoint> check);

/* This function will create a vector or list of datapoints that represent all the movies that meets the user's wants in
 * terms of genres they want to see represented in their movie recommendations. The available movies come from a prepopulated map
*/
Vector <DataPoint> getMovieRecs(Map<std::string, Vector<DataPoint>>& allMovies, Set <std::string> userWants);
