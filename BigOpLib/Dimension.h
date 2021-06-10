#pragma once

#include <vector>

#include "EvolveChamber.h"
#include "CreationChamber.h"
#include <mutex>
#include <thread>
#include <future>
#include <memory>

std::mutex simulationMutex;

class Dimension
{
public:
	Dimension(Dimension&& other)noexcept;
	Dimension(const Dimension&) = default;
	Dimension() = default;
	void startSimulation();
	void stopSimulation();
	void startSimulationTimed(size_t iterations);
	bool running();
	void putAgents( CreationChamber&, size_t);
	void putAgent(CreationChamber&);
	const std::vector<Life> &listInhabitants();
	void deleteAgent(const size_t);
	void deleteAgent(std::vector<Life>::iterator);
	void clearDimension();
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
	void realityAlgorithmIter(size_t iterations) {
		while (iterations--) {
			for (auto& unit : m_life) {
				//there could have been some logic
				//but not today...
				unit.getFatness();
			}
		}
		m_running = false;
	}
protected:
	std::vector<Life> m_life;
	bool m_running = false;

private:
	std::thread* th;
};



Dimension::Dimension(Dimension&& other) noexcept : m_life(other.m_life) {
	m_running = other.m_running;
	th = other.th;
	other.m_running = false;
	other.th = nullptr;
}

void Dimension::startSimulation()
{
	if (m_running)
		return;
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

void Dimension::startSimulationTimed(size_t iterations)
{
	if (m_running)
		return;
	m_running = true;
	std::thread(&Dimension::realityAlgorithmIter, this, iterations).detach();
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
	if (m_running)
		return;
	m_life.push_back(std::move(*creator.create()));
}

const std::vector <Life>& Dimension::listInhabitants()
{
	return m_life;
}

void Dimension::deleteAgent(const size_t pos)
{
	if (m_running)
		return;
	m_life.erase(m_life.begin() + pos);
}

void Dimension::deleteAgent(std::vector<Life>::iterator agentIt)
{
	if (m_running)
		return;
	m_life.erase(agentIt);
}

void Dimension::clearDimension()
{
	if (m_running)
		return;
	m_life.clear();
}

