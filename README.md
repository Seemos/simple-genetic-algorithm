# simple-genetic-algorithm
A basic implementation of a genetic algorithm with the goal to find optimal solutions for the Knapsack problem.

As a basis for an individual integer sequences are used, which allows an adaptation to further problems, provided that possible solutions can be encoded as a series of integers.

## Basic concept
Genetic algorithms try to find solutions for a problem by mimicing the process of evolution. The main idea is that a solution consists of a sequence of numerical values representing a genome. The environment is represented by an evaluation function (e.g. accuracy or maximum output). A group of such solutions is called population. While running the algorithm, populations are replaced by their children, which were generated using the concepts of crossover and mutation until some criteria for stopping the evolution is met. This process is shown in the image below:
![](images/genetic_algorithm.png)