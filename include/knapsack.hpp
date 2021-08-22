#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP

const int max_volume = 32;
const int values[8]  = {1, 2, 3, 4, 5, 6, 7, 8};
const int volumes[8] = {8, 7, 6, 5, 4, 3, 2, 1};

void calculate_fitness(genome& individuum);

#endif