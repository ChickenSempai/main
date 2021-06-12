
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <set>
#include <random>

namespace {
    typedef unsigned long ID;
}

class LeetManager{
public:

    std::shared_ptr <Client> createUser(std::string name){
        ID id = uniqueIdClient();
        m_clients.insert({id, std::make_shared<Client>(Client(name, id))});
        return m_clients[id];
    }
    
    std::shared_ptr <Question> createQuestion(std::string name){
        ID id = uniqueIdQuestion();
        m_questions.insert({id, std::make_shared<Question>(Question(name, id))});
        return m_questions[id];
    }

    std::shared_ptr <Question> createQuestion(std::string name){
        ID id = uniqueIdQuestion();
        m_questions.insert({id, std::make_shared<Question>(Question(name, id))});
        return m_questions[id];
    }



private:
    std::unordered_map <ID, std::shared_ptr<Client>> m_clients;
    std::unordered_map <ID, std::shared_ptr<Contest>> m_contests;
    std::unordered_map <ID, std::shared_ptr<Question>> m_questions;
    std::set <ID> idClients;
    std::set <ID> idContests;
    std::set <ID> idQuestions;

    std::default_random_engine idGenerator;
    std::uniform_int_distribution<ID> distribution;

private:
    ID uniqueIdClient(){ return uniqueId(idClients); }
    ID uniqueIdContest(){ return uniqueId(idContests); }
    ID uniqueIdQuestion(){ return uniqueId(idQuestions); }

    ID uniqueId(std::set <ID> &idBase){
        ID id = 0;
        while (idBase.count(id) > 0)
            id = distribution(idGenerator);
        idClients.insert(id);
        return id;
    }

};

class Client{
public:
    Client(const std::string name, const long int _id):m_name(name), id(_id), m_points(0) {}
    void setPoints(const int points){ m_points = points; }
    int getPoints() const { return m_points; } 
private:
    const std::string m_name;
    const long int id;
    int m_points;
};


class Contest{
public:
    Contest(const std::string name, const long int _id):m_name(name), id(_id) {}
private:
    const std::string m_name;
    const long int id;
};

class Question{
public:
    Question(const std::string name, const long int _id):m_name(name), id(_id){}

private:
    const std::string m_name;
    const long int id;
};























int main (){
    return 0;
}