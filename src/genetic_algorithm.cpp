#include "genetic_algorithm.hpp"
#include "knapsack_data.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

// Generates a base population of a given size
// genes are randomized between the lower and
// the upper bound (inclusive)
std::vector<genome> generate_random_population(unsigned size_population, unsigned size_genome, int lower_bound, int upper_bound){
    std::vector<genome> population;
    population.reserve(size_population);
    for(unsigned i = 0; i < size_population; i++){
        genome individuum;
        individuum.genes.reserve(size_genome);
        for(unsigned j = 0; j < size_genome; j++){
            individuum.genes.push_back(rand()%(1 + upper_bound - lower_bound) + lower_bound);
        }
        individuum.fitness = 0;
        population.push_back(individuum);
    }
    return population;
}

// calculates the problem specific fitness of each individuum
void calculate_fitness(genome& individuum){
    int value = 0;
    int volume = 0;
    for(unsigned i = 0; i < individuum.genes.size(); i++){
        if(individuum.genes[i] == 1){
            value += values[i];
            volume += volumes[i];
        }
    }
    if(volume > max_volume) individuum.fitness = 0;
    else individuum.fitness = value;
}

// calculate the fitness of the whole population
void evaluate_population(std::vector<genome>& population){
    for(auto& instance : population){
        calculate_fitness(instance);
    }
}

// comparefunction to pass as a parameter into std::sort
// determines if the left genome should be ordered before
// the right genome
bool compare_fitness(const genome& genome_left, const genome& genome_right){
    return genome_left.fitness > genome_right.fitness;
}

// sorts the individuums in the population by their fitness value
// higher fitness leads to a lower index
void sort_population(std::vector<genome>& population){
    std::sort(population.begin(), population.end(), &compare_fitness);
}

// copies the n individuums with the best fitness into
// the next generation in order to not loose their genes
void use_elitism(std::vector<genome>& population_children, std::vector<genome>& population_parents, unsigned n_individuums){
    for(unsigned i = 0; i < n_individuums; i++){
        population_children.push_back(population_parents[i]);
    }
}

// fills the population by randomly choosing two genomes as parents
// and forming two children by mixing the genes of the parents by
// a given probability, otherwise two individuums from the parent
// population are copied into the child population
void crossover(std::vector<genome>& population_children, std::vector<genome>& population_parents, double probability, unsigned n_individuums){
    unsigned size_population = population_parents.size();
    unsigned size_individuum = population_parents[0].genes.size();

    for(unsigned i = 0; i < n_individuums / 2; i++){
        unsigned index_mother = rand()%(size_population/2);
        unsigned index_father = rand()%(size_population/2);
        genome mother = population_parents[index_mother];
        genome father = population_parents[index_father];

        if (rand()%1 <= probability){
            unsigned poc = rand()%size_individuum;
            genome daughter;
            genome son;
            daughter.genes.reserve(size_individuum);
            son.genes.reserve(size_individuum);
            for(unsigned i = 0; i < poc; i++){
                daughter.genes.push_back(mother.genes[i]);
                son.genes.push_back(father.genes[i]);
            }
            for(unsigned i = poc; i < size_individuum; i++){
                daughter.genes.push_back(father.genes[i]);
                son.genes.push_back(mother.genes[i]);
            }
            population_children.push_back(daughter);
            population_children.push_back(son);
        }
        else{
            population_children.push_back(father);
            population_children.push_back(mother);
        }
    }
}

// modifies genes of the individuums to create an increased
// diversity and make up for the loss in the gene pool caused
// by the selection / crossover process
void mutate_population(std::vector<genome>& population, double probability, unsigned n_ignored, int lower_bound, int upper_bound){
    std::uniform_real_distribution<double> distribution (0, 1);
	std::default_random_engine engine;
    double probability_decrement = probability / 2;
    double mutation;
    for(unsigned i = n_ignored; i < population.size(); i++){
        for(auto& gene : population[i].genes){
            mutation = distribution(engine);
            if(mutation <= probability){
                if(mutation < probability_decrement && gene > lower_bound){
                    gene--;
                }
                else if (gene < upper_bound){
                    gene++;
                }
            }
        }
    }
}

//USED FOR DEBUG ONLY
//not suitable for a more complex tasks when
//working with a reasonable population size
void print_population(std::vector<genome>& population){
    for(auto& individuum : population){
        printf("Genes: ");
        for(auto gene : individuum.genes){
            printf("%i\t", gene);
        }
        printf("Fitness: %lf\n", individuum.fitness);
    }
}