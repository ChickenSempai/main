#pragma once

#include "Life.h"
#include "Drone.h"

#include <utility>
#include <type_traits>
#include <cassert>
#include <iostream>

class GeneBank {
public:
    virtual void mutate(Life& unit) = 0;
};

class PowerGeneBank : public GeneBank {
public:
    
    void mutate(Life& unit) override {
        unit.setFatness(unit.getFatness() * 2 );
    }
};

class WeakGeneBank : public GeneBank {
public:
    void mutate(Life& unit) override {
        unit.setFatness(unit.getFatness() / 2);
    }
};

class EvolveChamber
{
public:
    template <class lowerEvol, class higherEvol>
    higherEvol* evolve(lowerEvol&& unit) {
        
        assert((std::is_base_of<lowerEvol, higherEvol>::value));
           
        
        return new higherEvol(std::move(unit));
    }

    void setGeneBank(GeneBank& bank) {
        m_bank = &bank;
    }

    void mutateUnit(Life& unit) {
        std::cout << "Unit mutated and its color changed" << std::endl;
        if (m_bank != nullptr)
            m_bank->mutate(unit);
    }

private:
    GeneBank* m_bank = nullptr;
};

