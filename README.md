# Final-Project-in-C++
***Final Project Created Based on Learnings of Abstract Data Structures***



The problem that has been created is: assume that you are a streaming company, and you want to give movie recommendations to your customers based off of genres that they select for their movie preferences. So, with a prepopulated list of genres, and all the movies that fall under that genre, you need to be able to find all the movies that match all the genres that the customer wants to see in their movie recommendations.

 
To give a small example. Below are movie genres, and the respective movies that fit into the genre:
   
Romance: The Proposal, The Notebook

Comedy: The Proposal, Twins


Horror: Us, Get Out, Hereditary


Let’s say the customer or user wants to see a movie that has a romance and comedy in it. With a prepopulated list of movies under each genre, you should write a function that will go through the genres, select the movies that are under each genre, and find the movies that match both romance and comedy. In this case, the project should return the movie “The Proposal.” 

A small lesson on DataPoint plus explanation of constraint:
DataPoint is a type of struct created that has two variables of information within it. A string called “label” and a double called “priority.” Due to the way that DataPoint was constructed, you cannot create a Set or a Map of Datapoints (Map <DataPoint>, ...). DataPoint was the creation of the CS106B instructors prior to my project.

This code implementation was made to not be case sensitive, and using different abstrat data structures such as priority queue heaps, maps, and vectors.

***Display of Code at Work, and the Recommendation Tool at Use Below***




![Screen Shot 2023-03-27 at 11 56 14 PM](https://github.com/user-attachments/assets/e96e514f-0f68-452b-8ea9-6f51eb1bbe63)
