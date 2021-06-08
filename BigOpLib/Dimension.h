#pragma once

#include <vector>

#include "EvolveChamber.h"
#include "CreationChamber.h"
#include <mutex>
#include <thread>

std::mutex simulationMutex;

class Dimension
{
public:
	Dimension(Dimension&& other);
	Dimension(Dimension&) = default;
	Dimension() = default;
	void startSimulation();
	void stopSimulation();
	bool running();
	void putAgents( CreationChamber&, size_t);
	void putAgent(CreationChamber&);
	std::vector<Life> &listInhabitants();
	void deleteAgent(const size_t);
	void deleteAgent(std::vector<Life>::iterator);
	void clearDimension() {};
	~Dimension() { stopSimulation(); }
protected:
	void realityAlgorithm() {
		while (m_running == true) {
			for (auto& unit: m_life) {
				//there could have been some logic
				//but not today...
				unit.getFatness();
			}
		}
	}

protected:
	std::vector<Life> m_life;
	bool m_running = false;

private:
	std::thread* th;
};



Dimension::Dimension(Dimension&& other) : m_life(other.m_life) {
	m_running = other.m_running;
	th = other.th;
	other.m_running = false;
	other.th = nullptr;
}

void Dimension::startSimulation()
{
	const std::lock_guard<std::mutex> lock(simulationMutex);
	m_running = true;

	th = new std::thread(&Dimension::realityAlgorithm, this);
}

void Dimension::stopSimulation()
{
	m_running = false;
	if (th != nullptr && th->joinable()) {
		th->join();
		delete th;
	}
}

bool Dimension::running()
{
	return m_running;
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

