#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>

#include <SearchSpace.h>

namespace SGA
{
	
    class Mutator
    {
    private:
        SearchSpace* _searchSpace;
        bool _swapMutate;
        bool _randomChaosMutate;
        float _mutationPointProbability;
        bool _flipAtLeastOne;
        std::mt19937 _randomGenerator;
    	
    public:
        Mutator(SearchSpace* searchSpace, bool swapMutate, bool randomChaosMutate, float mutationPointProbability, bool flipAtLeastOne);
        std::vector<int> mutate(std::vector<int>& point, std::mt19937& randomGenerator) const;

        [[nodiscard]] std::string getName() const { return "Mutator"; };
    	

	private:
        static std::vector<int> swapMutation(std::vector<int>& point, std::mt19937& randomGenerator);
        void mutateValue(std::vector<int>& point, const int dim, std::mt19937& randomGenerator) const;

    };
    
}