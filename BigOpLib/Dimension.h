#pragma once

#include <vector>

#include "EvolveChamber.h"
#include "CreationChamber.h"


class Dimension
{
public:
	void startSimulation();
	bool running();
	void putAgents( CreationChamber&, size_t);
	void putAgent(CreationChamber&);
	std::vector<Life> &listInhabitants();
	void deleteAgent(const size_t);
	void deleteAgent(std::vector<Life>::iterator);
	void clearDimension() {};
private:
	bool m_running = false;
	std::vector<Life> m_life;
};

void Dimension::startSimulation()
{
}

bool Dimension::running()
{
	return false;
}

void Dimension::putAgents(CreationChamber& creator, size_t size)
{
	while (size--)
		putAgent(creator);
}

void Dimension::putAgent(CreationChamber& creator)
{
	m_life.push_back(std::move(*creator.create()));
}

std::vector <Life>& Dimension::listInhabitants()
{
	return m_life;
}

void Dimension::deleteAgent(const size_t pos)
{
	m_life.erase(m_life.begin() + pos);
}

void Dimension::deleteAgent(std::vector<Life>::iterator agentIt)
{
	m_life.erase(agentIt);
}

