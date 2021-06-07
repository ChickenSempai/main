#pragma once


class Life
{
public:
	Life(Life&& other) noexcept;
	Life(const Life&);
	Life(): m_alive(true), m_fatness(0) {}
	Life& operator=(const Life& other);
	void devour(Life *other);
	void attack(Life *other);
	void setFatness(int fat);
	int getFatness();
	bool alive();
	virtual ~Life();

protected:
	bool m_alive;
	int m_fatness;

};


Life::Life(Life&& other) noexcept
{
	m_alive = other.m_alive;
	m_fatness = other.m_fatness;
	other.m_alive = false;
	other.m_fatness = 0;
}

Life::Life(const Life& other)
{
	m_alive = other.m_alive;
	m_fatness = other.m_fatness;
}

Life& Life::operator=(const Life& other) {
	m_alive = other.m_alive;
	m_fatness = other.m_fatness;
	return *this;
}

void Life::devour(Life* other)
{
	if (m_alive == false)
		return;

	m_fatness += other->m_fatness;
}

void Life::attack(Life* other)
{
	if (m_alive == false)
		return;

	other->m_alive = false;
}

void Life::setFatness(int fat)
{
	m_fatness = fat;
}

int Life::getFatness()
{
	return m_fatness;
}

bool Life::alive()
{
	return m_alive;
}

Life::~Life() {}