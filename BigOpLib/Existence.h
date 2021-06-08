#pragma once

#include <vector>
#include <string>
#include "Dimension.h"
#include <mutex>

class Existence
{
public:
	static Existence* getExistence();
	const std::vector <Dimension>& listDimensions() const;
	Existence(Existence&) = delete;
	void operator=(const Existence &) = delete;
	Dimension& operator [](int i);
	Dimension* getDimension(int i);
	void createDimension();
	void startSimulation();
	void stopSimulation();
protected:
	Existence() {};

	static Existence* m_existence;
	std::vector <Dimension> m_dimensions;
};

Existence* Existence::m_existence = nullptr;

std::mutex ex_mutex;

Existence* Existence::getExistence() {

	const std::lock_guard<std::mutex> lock(ex_mutex);

	if (m_existence != nullptr)
		return m_existence;
	else {
		m_existence = new Existence;
		return m_existence;
	}

}

const std::vector<Dimension>& Existence::listDimensions() const
{
	return m_dimensions;
}

Dimension& Existence::operator[](int i)
{
	return m_dimensions[i];
}

Dimension* Existence::getDimension(int i) {
	return &(m_dimensions[i]);
}

void Existence::createDimension()
{
	m_dimensions.push_back(Dimension());
}

void Existence::startSimulation()
{
	for (auto& dimension : m_dimensions) {
		dimension.startSimulation();
	}
}

void Existence::stopSimulation()
{
	for (auto& dimension : m_dimensions) {
		dimension.stopSimulation();
	}
}

