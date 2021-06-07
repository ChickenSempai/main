#pragma once
#include "Life.h"
#include <utility>
#include <iostream>
class Drone :public Life
{
public:
    Drone() noexcept:Life(){}
    Drone(Drone&& other) noexcept: Life(std::move(other)) {}
    Drone(const Drone& other) :Life(other){}
    ~Drone() {}

};

class MegaDrone :public Drone
{
public:
    MegaDrone(MegaDrone&& other) noexcept: Drone(std::move(other)) {}
    MegaDrone(Drone&& other) noexcept: Drone(std::move(other)) {}
    MegaDrone(const MegaDrone& other) : Drone(other) {}
    MegaDrone() {}
    ~MegaDrone() {}
};
