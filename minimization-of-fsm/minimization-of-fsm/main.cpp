#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <array>
#include <vector>
#include <map>

enum class MachineType
{
    Moore = 1,
    Mealy = 2,
};

struct Machine
{
    std::vector<std::vector<int>> states;
    std::vector<std::vector<int>> outputs;
    int countX;
    int countY;
    MachineType type;
};

template<typename T>
T GetParameter(std::istream& stream)
{
    T result;
    return (stream >> result) ? result : 0;
}

Machine GetMealyMachine(std::istream& stream)
{
    Machine machine;
    machine.type = MachineType::Mealy;
    machine.countX = GetParameter<int>(stream);
    machine.countY = GetParameter<int>(stream);
    auto countQ = GetParameter<int>(stream);

    machine.states = std::vector<std::vector<int>>(countQ, std::vector<int>());
    machine.outputs = std::vector<std::vector<int>>(countQ, std::vector<int>());

    for (int indexOfX = 0; indexOfX < machine.countX; ++indexOfX)
    {
        for (int index = 0; index < countQ; ++index)
        {
            auto state = GetParameter<int>(stream);
            machine.states[index].push_back(state);

            auto output = GetParameter<int>(stream);
            machine.outputs[index].push_back(output);
        }
    }
    return machine;
}

Machine GetMooreMachine(std::istream& stream)
{
    Machine machine;
    machine.type = MachineType::Moore;
    machine.countX = GetParameter<int>(stream);
    machine.countY = GetParameter<int>(stream);
    auto countQ = GetParameter<int>(stream);

    machine.states = std::vector<std::vector<int>>(countQ, std::vector<int>());
    machine.outputs = std::vector<std::vector<int>>(countQ, std::vector<int>());

    for (int index = 0; index < countQ; ++index)
    {
        machine.outputs[index].push_back({ GetParameter<int>(stream) });
    }

    for (int index = 0; index < machine.countX; ++index)
    {
        for (int j = 0; j < countQ; ++j)
        {
            machine.states[j].push_back(GetParameter<int>(stream));
        }
    }

    return machine;
}

Machine GetMachine(int type, std::istream& stream)
{
    switch (static_cast<MachineType>(type))
    {
    case MachineType::Moore:
        return GetMooreMachine(stream);
    case MachineType::Mealy:
        return GetMealyMachine(stream);
    default:
        throw new std::invalid_argument("Invalid machine type");
    }
}

std::vector<int> GetClasses(const std::vector<std::vector<int>>& states, const std::vector<int>& classes)
{
    int k = 0;
    std::vector<int> result = std::vector<int>(states.size(), -1);
    for (size_t index = 0; index < result.size(); ++index)
    {
        if (result[index] != -1) { continue;  }
        for (size_t j = index; j < result.size(); ++j)
        {
            if (result[j] == -1 && (states[index] == states[j]) && (classes[index] == classes[j]))
            {
                result[j] = k;
            }
        }
        ++k;
    }
    return result;
}

void TransformByNewClasses(Machine& newMachine, std::vector<int>& classes)
{
    for (size_t i = 0; i < newMachine.states.size(); ++i)
    {
        for (size_t j = 0; j < newMachine.states[i].size(); ++j)
        {
            newMachine.states[i][j] = classes[newMachine.states[i][j]];
        }
    }
}

Machine Minimizate(const Machine& machine)
{
    auto newMachine = machine;
    auto prevClasses = std::vector<int>(machine.states.size(), -2);
    auto classes = GetClasses(newMachine.outputs, prevClasses);

    while (prevClasses != classes)
    {
        newMachine = machine;
        TransformByNewClasses(newMachine, classes);
        prevClasses = classes;

        classes = GetClasses(newMachine.states, classes);
    }

    std::vector<std::vector<int>> states;
    std::vector<std::vector<int>> outputs;
    std::vector<int> visited;
    for (size_t index = 0; index < classes.size(); ++index)
    {
        if (std::find(visited.begin(), visited.end(), classes[index]) == visited.end())
        {
            visited.push_back(classes[index]);
            states.push_back(newMachine.states[index]);
            outputs.push_back(newMachine.outputs[index]);
        }
    }
    newMachine.states = states;
    newMachine.outputs = outputs;
    return newMachine;
}

void PrintMooreMachine(std::ostream& ostream, const Machine& machine)
{
    ostream << static_cast<int>(machine.type) << std::endl;
    ostream << machine.countX << std::endl;
    ostream << machine.countY << std::endl;
    ostream << machine.states.size() << std::endl;

    for (size_t j = 0; j < machine.states.size(); ++j)
    {
        ostream << machine.outputs[j][0] << " ";
    }
    ostream << std::endl;

    for (int index = 0; index < machine.countX; ++index)
    {
        for (size_t j = 0; j < machine.states.size(); ++j)
        {
            ostream << machine.states[j][index] << " ";
        }
        ostream << std::endl;
    }
}

void PrintMealyMachine(std::ostream& ostream, const Machine& machine)
{
    ostream << static_cast<int>(machine.type) << std::endl;
    ostream << machine.countX << std::endl;
    ostream << machine.countY << std::endl;
    ostream << machine.states.size() << std::endl;

    for (int index = 0; index < machine.countX; ++index)
    {
        for (size_t j = 0; j < machine.states.size(); ++j)
        {
            ostream << machine.states[j][index] << " ";
            ostream << machine.outputs[j][index] << " ";
        }
        ostream << std::endl;
    }
}

void PrintMachineInDotFile(const std::string& fileName, const Machine& machine)
{
    std::ofstream ofs(fileName);

    ofs << "digraph G {" << std::endl;
    ofs << "node [shape = circle];" << std::endl;

    for (size_t index = 0; index < machine.states.size(); ++index)
    {
        for (size_t jindex = 0; jindex < machine.states[index].size(); ++jindex)
        {
            auto value = (jindex < machine.outputs[index].size()) ? machine.outputs[index][jindex] : machine.outputs[index][0];
            ofs << index << " -> " << machine.states[index][jindex]
                << " [ label = \"" << jindex + 1 << "/" << value << "\" ];" << std::endl;
        }
    }
    ofs << "}" << std::endl;
}

void PrintMachine(std::ostream& ostream, const std::string& dotFileName, const Machine& machine)
{
    switch (machine.type)
    {
    case MachineType::Moore:
        PrintMooreMachine(ostream, machine);
        PrintMachineInDotFile(dotFileName, machine);
        break;
    case MachineType::Mealy:
        PrintMealyMachine(ostream, machine);
        PrintMachineInDotFile(dotFileName, machine);
        break;
    default:
        throw new std::invalid_argument("Invalid machine type");
    }
}

void DoExecute(std::istream& streamIn, std::ostream& ostream, const std::string& dotFileName)
{
    std::string typeFSMachine;
    streamIn >> typeFSMachine;
    int type = std::stoi(typeFSMachine, nullptr, 10);

    auto machine = GetMachine(type, streamIn);
    auto minimizedMachine = Minimizate(machine);
    PrintMachine(ostream, dotFileName, minimizedMachine);
}

int main()
{
    std::string inFileName = "input.txt";
    std::string outFileName = "output.txt";
    std::ifstream streamIn(inFileName);
    std::ofstream streamOut(outFileName);
    DoExecute(streamIn, streamOut, "visualization.dot");
    return 0;
}
