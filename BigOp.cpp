// BigOpWeb.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>

#include "Existence.h"
#include "Cleanse.h"
#include "CreationChamber.h"
#include "StateViper.h"
#include <chrono>
#include <thread>
#include <semaphore>

int main()
{
    Existence* mainRealm = Existence::getExistence();
    mainRealm->createDimension();
    Dimension* unicornWorld = mainRealm->getDimension(0);
    CreationChamber omniomut;
    unicornWorld->putAgent(omniomut);
    unicornWorld->putAgents(omniomut, 30);
    CleanseFat rheaper;
    DummyCleanse dumhe;
    CleanseFat biggerRheaper;
    rheaper.setNext(&dumhe)->setNext(&biggerRheaper);
    
    mainRealm->createDimension();
    mainRealm->createDimension();
    mainRealm->createDimension();
    mainRealm->createDimension();
    mainRealm->createDimension();
    mainRealm->startSimulation();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    mainRealm->stopSimulation();

    rheaper.setFatThreshold(0, 3);
    biggerRheaper.setFatThreshold(4, 5);
    rheaper.execute(*unicornWorld);

    StateViper vooper;
    
    for(int i = 0; i< 30; i++)
        vooper.act();
    std::cout << "StateViper is:" << vooper.getFatness() << " fat level" << std::endl;
}
