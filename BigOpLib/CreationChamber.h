#pragma once

#include "Life.h"
#include "Drone.h"


class CreationChamber
{
public:
	virtual Life* create() {
		return new Life;
	}
};

class DroneCreationChamber : public CreationChamber 
{
public:
	Life* create() override {
		return new Drone;
	}
};

class MegaDroneCreationChanger : public CreationChamber
{
public:
	Life* create() override {
		return new MegaDrone;
	}
};