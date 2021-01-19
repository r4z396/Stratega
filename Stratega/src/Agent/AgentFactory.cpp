#include <Agent/AgentFactory.h>
#include <Agent/RandomAgent.h>

#include <Agent/RuleBased/CombatAgent.h>
#include <Agent/RuleBased/PushAgent.h>

#include <Agent/DoNothingAgent.h>
#include <Agent/OSLAAgent.h>
#include <Agent/TreeSearchAgents/BFSAgent.h>
#include <Agent/RHEAAgent/RHEAAgent.h>
#include <Agent/TreeSearchAgents/BeamSearchAgent.h>
#include <Agent/TreeSearchAgents/DFSAgent.h>
#include <Agent/TreeSearchAgents/MCTSAgent.h>
#include <Agent/PortfolioRHEA/PortfolioRHEAAgent.h>
#include <Agent/PortfolioGreedySearchAgent.h>
#include <Agent/MetaPortfolioOptimizer/MetaPOAgent.h>
#include <Agent/MOPortfolioRHEA/MOPortfolioRHEAAgent.h>
#include <Agent/PortfolioOnlineEvolution/POEAgent.h>

namespace SGA
{
	bool AgentFactory::registerAgentFn(const std::string& name, const AgentGenerator& agentFn)
	{
		if (agentGeneratorLookup.find(name) == agentGeneratorLookup.end())
		{
			agentGeneratorLookup.emplace(name, agentFn);
			return true;
		}

		return false;
	}

	bool AgentFactory::registerAgentFn(const std::string& name, const AgentGeneratorParams& agentFn)
	{
		if (agentGeneratorParamsLookup.find(name) == agentGeneratorParamsLookup.end())
		{
			agentGeneratorParamsLookup.emplace(name, agentFn);
			return true;
		}

		return false;
	}

	std::unique_ptr<Agent> AgentFactory::createAgent(const std::string& name)
	{
		auto it = agentGeneratorLookup.find(name);
		if (it == agentGeneratorLookup.end())
		{
			return nullptr;
		}

		return std::unique_ptr<Agent>(it->second());
	}

	std::unique_ptr<Agent> AgentFactory::createAgent(const std::string& name, YAML::Node params)
	{
		auto it = agentGeneratorParamsLookup.find(name);
		if (it == agentGeneratorParamsLookup.end())
		{
			return nullptr;
		}

		return std::unique_ptr<Agent>(it->second(params));
	}

	AgentFactory& AgentFactory::getDefaultFactory()
	{
		static AgentFactory factory;

		// Register agents available in the Stratega framework
		factory.registerAgent<DoNothingAgent>("DoNothingAgent");
		factory.registerAgent<RandomAgent>("RandomAgent");
		factory.registerAgent<CombatAgent>("CombatAgent");
		factory.registerAgent<PushAgent>("PushAgent");
		factory.registerAgent<BFSAgent>("BFSAgent");
		factory.registerAgent<RHEAAgent, RHEAParams>("RHEAAgent");
		factory.registerAgent<OSLAAgent>("OSLAAgent");
		factory.registerAgent<BeamSearchAgent>("BeamSearchAgent");
		factory.registerAgent<DFSAgent>("DFSAgent");
		factory.registerAgent<MCTSAgent, MCTSParameters>("MCTSAgent");
		factory.registerAgent<PortfolioRHEAAgent, PortfolioRHEAParams>("PortfolioRHEAAgent");
		factory.registerAgent<PortfolioGreedySearchAgent, PortfolioGreedySearchParams>("PGSAgent");
		factory.registerAgent<MetaPOAgent, MetaPOParams>("MetaPOAgent");
		factory.registerAgent<MOPortfolioRHEAAgent, MOPortfolioRHEAParams>("MOPRHEAAgent");
		factory.registerAgent<POEAgent, POEParams>("POEAgent");
		
		return factory;
	}

}
