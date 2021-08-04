#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Leet {
using ID = const unsigned long;
}

enum class Level {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
};

class Client {
public:
    Client(const std::string name, Leet::ID _id)
        : m_name(name)
        , id(_id)
        , m_points(0)
    {
    }
    void setPoints(int points) { m_points = points; }
    int getPoints() const { return m_points; }

public:
    const Leet::ID id;

private:
    std::string m_name;
    int m_points;
};

class Contest {
public:
    Contest(const std::string name, Leet::ID _id, Level difficulty, const std::string creator_name)
        : m_name(name)
        , id(_id)
        , m_diff(difficulty)
        , m_creatorName(creator_name)
    {
    }

    void addContestant(Leet::ID userID) { contestants.push_back(userID); }
    const std::vector<Leet::ID>& listContestants() { return contestants; }
    Level getLevel() const { return m_diff; }
    void updateHistory(Leet::ID winnerID)
    {
        m_history.push_back({ winnerID, questions });
    }

    struct winLog {
        Leet::ID winnerID;
        std::vector<Leet::ID> questionSet;
    };

    const std::vector<winLog>& contestHistory() const { return m_history; }

public:
    const Leet::ID id;

protected:
    Level m_diff;
    std::string m_name;
    std::string m_creatorName;
    std::vector<Leet::ID> questions;
    std::vector<Leet::ID> contestants;
    std::vector<winLog> m_history;
};

class Question {
public:
    Question(const std::string name, Leet::ID _id, Level difficulty)
        : m_name(name)
        , id(_id)
        , m_diff(difficulty)
    {
    }

public:
    const Leet::ID id;

protected:
    Level m_diff;
    std::string m_name;
};
