#pragma once
#include <sstream>
#include <string>
#include "FSMachine.h"

class MealyMachineOutputStream
{
public:
    void Write(const MealyMachine& machine) const
    {
        WriteParameters(machine);
        WriteTableOfState(machine);
    }
private:
    void WriteParameters(const MealyMachine& machine) const
    {
        std::cout
            << (size_t)FSMachineEnum::Mealy << std::endl
            << machine.GetCountXParameters() << std::endl
            << machine.GetCountYParameters() << std::endl
            << machine.GetCountQState() << std::endl;
    }

    void WriteTableOfState(const MealyMachine& machine) const
    {
        auto tableOfState = machine.GetTableOfState();

        for (auto& row : tableOfState)
        {
            for (auto& cell : row)
            {
                std::cout << cell.first << " " << cell.second << " ";
            }
            std::cout << std::endl;
        }
    }
};

class MooreMachineOutputStream
{

public:
    void Write(const MooreMachine& machine) const
    {
        WriteParameters(machine);
        WriteYState(machine);
        WriteTableOfState(machine);
    }
private:
    void WriteParameters(const MooreMachine& machine) const
    {
        std::cout
            << (size_t)FSMachineEnum::Moore << std::endl
            << machine.GetCountXParameters() << std::endl
            << machine.GetCountYParameters() << std::endl
            << machine.GetCountQState() << std::endl;
    }

    void WriteYState(const MooreMachine& machine) const
    {
        auto yState = machine.GetYState();

        for (auto item : yState)
        {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    void WriteTableOfState(const MooreMachine& machine) const
    {
        auto tableOfState = machine.GetTableOfState();

        for (auto& row : tableOfState)
        {
            for (auto cell : row)
            {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }
};
