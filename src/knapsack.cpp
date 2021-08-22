#include "genetic_algorithm.hpp"
#include "knapsack.hpp"

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