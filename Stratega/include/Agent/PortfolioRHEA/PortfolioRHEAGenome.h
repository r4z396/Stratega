#pragma once
#include <ForwardModel/Action.h>

#include <random>
#include <vector>

#include <ForwardModel/TBSForwardModel.h>
#include <Agent/PortfolioRHEA/PortfolioRHEAParams.h>

namespace SGA {

	class PortfolioRHEAGenome
	{

	private:
		std::vector<Action<Vector2i>> actions;
		std::vector<int> portfolioIndices;
		double value = 0;

	public:
		// creates a random PortfolioGenome
		PortfolioRHEAGenome(TBSForwardModel& forwardModel, TBSGameState gameState, PortfolioRHEAParams& params);
		
		// creates a copy of an existing Portfolio Genome
		PortfolioRHEAGenome(const PortfolioRHEAGenome& other) = default;

		std::vector<Action<Vector2i>>& getActions() { return actions; };
		std::vector<int>& getPortfolioVector() { return portfolioIndices; };

		void mutate(TBSForwardModel& forwardModel, TBSGameState gameState, PortfolioRHEAParams& params, std::mt19937& randomGenerator);
		
		double getValue() const { return value; };
		void setValue(const double value) { this->value = value; };

		void shift(TBSForwardModel& forwardModel, TBSGameState gameState, PortfolioRHEAParams& params);
		void toString() const;
		static PortfolioRHEAGenome crossover(TBSForwardModel& forwardModel, TBSGameState gameState, PortfolioRHEAParams& params, std::mt19937& randomGenerator, PortfolioRHEAGenome& parent1, PortfolioRHEAGenome& parent2);
		
	private:
		PortfolioRHEAGenome(std::vector<Action<Vector2i>>& actions, std::vector<int>& portfolioIndices, double value);
		static void applyActionToGameState(const TBSForwardModel& forwardModel, TBSGameState& gameState, std::unique_ptr<ActionSpace<Vector2i>>& actionSpace,  const Action<Vector2i>& action, PortfolioRHEAParams& params);
		

	};
}
