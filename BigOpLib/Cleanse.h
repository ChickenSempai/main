#pragma once

#include "Dimension.h"
#include "Life.h"
class Cleanse
{
public:
	Cleanse* setNext(Cleanse*);
	void execute(Dimension&);
	virtual ~Cleanse() = 0;
protected:
	Cleanse* m_next = nullptr;
private:
	virtual void m_execute(Dimension&) = 0;
};

Cleanse* Cleanse::setNext(Cleanse* next) {
	m_next = next;
	return next;
}

void Cleanse::execute(Dimension& dimension) {
	m_execute(dimension);
	if (m_next != nullptr)
		m_next->execute(dimension);
}

Cleanse::~Cleanse() {}

class CleanseFat : public Cleanse
{
public:
	void setFatThreshold(int low, int high);
	~CleanseFat() {}
private:
	int m_fatLowThreshold = 0;
	int m_fatHighThreshold = 0;
private:
	void m_execute(Dimension& dimension) {
		std::vector <Life> inhabits = dimension.listInhabitants();
		for (int i = 0; i < dimension.listInhabitants().size(); i++) {
			if (inhabits[i].getFatness() >= m_fatLowThreshold 
				&& inhabits[i].getFatness() < m_fatHighThreshold) {
				dimension.deleteAgent(i--);
				
			}
		}
	}
};

void CleanseFat::setFatThreshold(int low, int high) {
	m_fatLowThreshold = low;
	m_fatHighThreshold = high;
}

class DummyCleanse : public Cleanse
{
public:
	~DummyCleanse(){}
private:
	void m_execute(Dimension& dimension) {
		std::cout << "I'm a Dummy Cleanse thine majesty, I can't do anything with this mess!" << std::endl;
	}
};