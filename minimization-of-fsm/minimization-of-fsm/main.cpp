#include "stdafx.h"
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <vector>

using MealyTableOfState = std::vector<std::vector<std::pair<int, int>>>;
using MooreTableOfState = std::vector<std::vector<int>>;

enum class FSMachineEnum
{
    Mealy = 1,
    Moore = 2,
};

class IFSMachine
{
public:
    virtual void Minimizate() = 0;
    virtual ~IFSMachine() = default;
};

class MealyMachine : public IFSMachine
{
public:
    MealyTableOfState GetTableOfState() const
    {
        return m_tableOfState;
    };
    void Minimizate() override
    {
        m_tableOfState.empty();
    }
private:
    MealyTableOfState m_tableOfState;
};

class MooreMachine : public IFSMachine
{
public:
    MooreTableOfState GetTableOfState() const
    {
        return m_tableOfState;
    };

    void Minimizate() override
    {
        m_tableOfState.empty();
    }
private:
    MooreTableOfState m_tableOfState;
};

std::unique_ptr<IFSMachine> CreateFSMachine(int type)
{
    if (type == (int)FSMachineEnum::Mealy)
    {
        return std::make_unique<MealyMachine>();
    }
    else if (type == (int)FSMachineEnum::Moore)
    {
        return std::make_unique<MooreMachine>();
    }
    else
    {
        throw std::invalid_argument("Invalid type fsmachine.");
    }
}

int main()
{
    try
    {
        std::string typeFSMachine;
        std::cin >> typeFSMachine;
        int type = std::stoi(typeFSMachine, nullptr, 10);

        auto machine = CreateFSMachine(type);
        machine->Minimizate();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

