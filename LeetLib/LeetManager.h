#pragma once

#include <LeetLibrary.h>
#include <unordered_map>
#include <set>
#include <random>

namespace 
{
    using client_table = std::unordered_map <Leet::ID, std::shared_ptr<Client>> ;
    using contest_table = std::unordered_map <Leet::ID, std::shared_ptr<Contest>> ;
    using question_table = std::unordered_map <Leet::ID, std::shared_ptr<Question>> ;
}

class LeetManager {
public:

    std::shared_ptr <Client> createUser(std::string name);

    std::shared_ptr <Contest> createContest(std::string name, const Level difficulty, std::string contest_creator);

    std::shared_ptr <Question> createQuestion(std::string name, Level difficulty);

    int updateClientPoints(Leet::ID, int points);

    const std::vector <Leet::ID> &listQuestion(Level difficulty);

    const std::vector <Leet::ID> &listContest(Level difficulty);
    void attendContest(Leet::ID contest_ID, Leet::ID userID)
    {
         m_contests[contest_ID]->addContestant(userID); 
    }
    void runContest(Leet::ID contest_ID);
    void withdrawContest(Leet::ID contest_ID);

private:
    client_table m_clients;
    contest_table m_contests;
    question_table m_questions;

    std::vector <Leet::ID> questionsLow;
    std::vector <Leet::ID> questionsMedium;
    std::vector <Leet::ID> questionsHigh;

    std::vector <Leet::ID> contestsLow;
    std::vector <Leet::ID> contestsMedium;
    std::vector <Leet::ID> contestsHigh;

    std::set <Leet::ID> idClients;
    std::set <Leet::ID> idContests;
    std::set <Leet::ID> idQuestions;

    std::default_random_engine randGenerator;

private:
    Leet::ID uniqueIdClient(){ return uniqueId(idClients); }
    Leet::ID uniqueIdContest(){ return uniqueId(idContests); }
    Leet::ID uniqueIdQuestion(){ return uniqueId(idQuestions); }

    Leet::ID uniqueId(std::set <Leet::ID> &idBase);

    void addToContestList(Level diff, Leet::ID id);

    void addToQuestionList(Level diff, Leet::ID id);

};

std::shared_ptr <Client> LeetManager::createUser(std::string name){
    Leet::ID id = uniqueIdClient();
    m_clients.insert({id, std::make_shared<Client>(Client(name, id))});
    return m_clients[id];
}

std::shared_ptr <Contest> LeetManager::createContest(std::string name, const Level difficulty, std::string contest_creator){
    Leet::ID id = uniqueIdContest();
    addToContestList(difficulty, id);
    m_contests.insert( {id, std::make_shared<Contest> (Contest(name, id, difficulty, contest_creator)) });
    return m_contests[id];
}

std::shared_ptr <Question> LeetManager::createQuestion(std::string name, Level difficulty){
    Leet::ID id = uniqueIdQuestion();
    addToQuestionList(difficulty, id);
    m_questions.insert({id, std::make_shared<Question>(Question(name, id, difficulty))});
    return m_questions[id];
}

int LeetManager::updateClientPoints(Leet::ID userID, int pointsIncrement) {
    m_clients[userID]->setPoints(m_clients[userID]->getPoints() + pointsIncrement);
}

const std::vector <Leet::ID> &LeetManager::listQuestion(Level difficulty) {
    switch (difficulty)
    {
    case Level::LOW:
        return questionsLow;
    case Level::MEDIUM:
        return questionsMedium;
    case Level::HIGH:
        return questionsHigh;
    }
}

const std::vector <Leet::ID> &LeetManager::listContest(Level difficulty) {
    switch (difficulty)
    {
    case Level::LOW:
        return contestsLow;
    case Level::MEDIUM:
        return contestsMedium;
    case Level::HIGH:
        return contestsHigh;
    }
}

    Leet::ID LeetManager::uniqueId(std::set <Leet::ID> &idBase){
    unsigned long id = 0;
    std::uniform_int_distribution<Leet::ID> distribution;
    while (idBase.count(id) > 0)
        id = distribution(randGenerator);
    idClients.insert((Leet::ID)id);
    return id;
}

    void LeetManager::addToContestList(Level diff, Leet::ID id){
    switch (diff)
    {
    case Level::LOW:
        contestsLow.push_back(id); return;
    case Level::MEDIUM:
        contestsMedium.push_back(id); return;
    case Level::HIGH:
        contestsHigh.push_back(id); return;
    default:
        return;
    }
}

void LeetManager::addToQuestionList(Level diff, Leet::ID id){
    switch (diff)
    {
    case Level::LOW:
        questionsLow.push_back(id); return;
    case Level::MEDIUM:
        questionsMedium.push_back(id); return;
    case Level::HIGH:
        questionsHigh.push_back(id); return;
    default:
        return;
    }
}

void LeetManager::runContest(Leet::ID contest_ID){
    auto active = m_contests[contest_ID];
    size_t participantsAmount = active->listContestants().size();

    std::uniform_int_distribution<Leet::ID> distribution(0, participantsAmount);

    size_t winner = distribution(randGenerator);
    Leet::ID winnerID = active->listContestants()[winner];

    this->updateClientPoints(winnerID, static_cast<int>(active->getLevel()));
    active->updateHistory(winnerID);
}

void LeetManager::withdrawContest(Leet::ID contest_ID)  {
    idContests.erase(contest_ID);
    int index = 0;
    switch(m_contests[contest_ID]->getLevel())
    {
    case Level::LOW:
        while (questionsLow[index++] != contest_ID);
        questionsLow.erase(questionsLow.begin() + index);
        break;
    case Level::MEDIUM:
        while (questionsMedium[index++] != contest_ID);
        questionsLow.erase(questionsMedium.begin() + index);
        break;
    case Level::HIGH:
        while (questionsHigh[index++] != contest_ID);
        questionsLow.erase(questionsHigh.begin() + index);
        break;
    }
    m_contests.erase(contest_ID);
}