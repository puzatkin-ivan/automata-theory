#pragma once
#include <string>
#include <memory>
#include <utility>
#include <vector>

using MealyTableOfState = std::vector<std::vector<std::pair<size_t, size_t>>>;
using MooreTableOfState = std::vector<std::vector<size_t>>;

enum class FSMachineEnum
{
    Mealy = 2,
    Moore = 1,
};

class IFSMachine
{
public:
    virtual void Minimizate() = 0;
    virtual size_t GetCountXParameters() const = 0;
    virtual size_t GetCountYParameters() const = 0;
    virtual size_t GetCountQState() const = 0;
    virtual ~IFSMachine() = default;
};

class CFSMachine : public IFSMachine
{
public:
    CFSMachine(size_t countXParameters, size_t countYParameters, size_t countQState)
        :m_countXParameters(countXParameters)
        , m_countYParameters(countYParameters)
        , m_countQState(countQState)
    {
    }

    size_t GetCountXParameters() const { return m_countXParameters; };
    size_t GetCountYParameters() const { return m_countYParameters; };
    size_t GetCountQState() const { return m_countQState; }
private:
    size_t m_countXParameters;
    size_t m_countYParameters;
    size_t m_countQState;
};

class MealyMachine : public CFSMachine
{
public:
    MealyMachine(const MealyTableOfState& tableOfState, const std::vector<size_t> parameters)
        :CFSMachine(parameters[0], parameters[1], parameters[2])
        , m_tableOfState(tableOfState)
    {
    }

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

class MooreMachine : public CFSMachine
{
public:
    MooreMachine(
        const MooreTableOfState& tableOfState,
        const std::vector<size_t>& yState,
        const std::vector<size_t>& parameters)
        :CFSMachine(parameters[0], parameters[1], parameters[2])
        , m_tableOfState(tableOfState)
        , m_yState(yState)
    {
    }

    std::vector<size_t> GetYState() const
    {
        return m_yState;
    }

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
    std::vector<size_t> m_yState;
};
