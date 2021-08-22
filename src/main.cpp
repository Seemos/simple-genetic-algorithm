#include <iostream>
#include <vector>
#include "genetic_algorithm.hpp"

// Parameters to control the evolution
unsigned max_iterations = 10;
unsigned fitness_target = 35;
unsigned fitness_best = 0;
unsigned number_elites = 2;
double probability_crossover = 0.9;
double probability_mutation = 0.1;

// Population parameters
unsigned size_population = 10;
unsigned size_genome = 8;
int gene_bound_upper = 1;
int gene_bound_lower = 0;

// Storing generations and best individuums
std::vector<genome> population_parents;
std::vector<genome> population_fertile;
std::vector<genome> population_children;
std::vector<genome> best_individuums;

int main(){
    printf("----------------------\n");
    printf("Genesis Population:\n");
    printf("----------------------\n");

    // Initialize/prepare populations
    population_parents = generate_random_population(size_population, size_genome, gene_bound_lower, gene_bound_upper);
    population_children.reserve(size_population);

    // Evolve new generations
    // loop is left when a maximum of iterations is reached
    // or a desired fitness has been reached
    for(int i = 0; i < max_iterations && fitness_target > fitness_best; i++){

        // Evaluate the fitness of each population member
        evaluate_population(population_parents);

        // Sort the population by the fitness of the members
        sort_population(population_parents);
        
        // Print the population to see the difference between
        // past generations
        print_population(population_parents);
        printf("----------------------\n");

        // Save the best individuum and its fitness
        // if an improvement has been made
        if (population_parents[0].fitness > fitness_best){
            fitness_best = population_parents[0].fitness;
            best_individuums.push_back(population_parents[0]);
        }

        // Copy the n best individuums into the child generation
        use_elitism(population_children, population_parents, number_elites);

        // use the parent generation to fill up the rest of the
        // child generation with modified versions
        fitness_proportionate_selection(population_fertile, population_parents);
        crossover(population_children, population_parents, probability_crossover, size_population - number_elites);
        mutate_population(population_children, probability_mutation, number_elites, gene_bound_lower, gene_bound_upper);
        
        // Set the children population as the new parent population
        // clear the population_children to prevent growing populations
        population_parents = population_children;
        population_fertile.clear();
        population_children.clear();
        
    }

    printf("Population of best individuums:\n");
    printf("----------------------\n");
    print_population(best_individuums);
    return 0;
}