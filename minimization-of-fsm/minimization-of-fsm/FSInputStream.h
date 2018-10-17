#pragma once
#include "FSMachine.h"

class IFSMachineInputStream
{
public:
    virtual std::vector<size_t> ReadParameters() = 0;
    virtual ~IFSMachineInputStream() = default;
};

class CFSMachineInputStream : public IFSMachineInputStream
{
public:
    std::vector<size_t> ReadParameters() override
    {
        size_t countX, countY, countQ;
        std::cin >> countX >> countY >> countQ;
        return {countX, countY, countQ};
    };
};

class MealyMachineInputStream : public CFSMachineInputStream
{
public:
    MealyTableOfState ReadTableOfState(const std::vector<size_t>& params)
    {
        MealyTableOfState result;
        for (size_t i = 0; i < params[0]; ++i)
        {
            std::vector<std::pair<size_t, size_t>> row;
            for (size_t j = 0; j < params[2]; ++j)
            {
                int state, out;
                std::cin >> state >> out;
                std::pair<size_t, size_t> cell = {state, out};
                row.push_back(cell);
            }
            result.push_back(row);
        }
        return result;
    }
};

class MooreMachineInputStream : public CFSMachineInputStream
{
public:
    std::vector<size_t> ReadYState(const std::vector<size_t>& params)
    {
        std::vector<size_t> yParameters;
        for (size_t index = 0; index < params[2]; ++index)
        {
            size_t y;
            std::cin >> y;
            yParameters.push_back(y);
        }
        return yParameters;
    }
    MooreTableOfState ReadTableOfState(const std::vector<size_t>& params)
    {
        MooreTableOfState result;
        for (size_t i = 0; i < params[0]; ++i)
        {
            result.push_back(ReadYState(params));
        }
        return result;
    }
};

