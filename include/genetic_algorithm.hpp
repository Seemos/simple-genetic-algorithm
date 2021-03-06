#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include <vector>
#include <stdlib.h>

typedef struct{
    double fitness;
    std::vector<int> genes;
}genome;

// random population is used at the beginning to initialize the base generation
std::vector<genome> generate_random_population(unsigned size_population, unsigned size_genome, int lower_bound, int upper_bound);

// Evaluating
void calculate_fitness(genome& individuum);
void evaluate_population(std::vector<genome>& population);

// Sorting
bool compare_fitness(const genome& genome_left, const genome& genome_right);
void sort_population(std::vector<genome>& population);

// Generating the new generation
void use_elitism(std::vector<genome>& population_children, std::vector<genome>& population_parents, unsigned n_individuums);
void crossover(std::vector<genome>& population_children, std::vector<genome>& population_parents, double probability, unsigned n_individuums);
void mutate_population(std::vector<genome>& population, double probability, unsigned n_ignored, int lower_bound, int upper_bound);

// Debug
void print_population(std::vector<genome>& population);

#endif