#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <utility>
#include <algorithm>

using StateList = std::vector<std::vector<std::vector<int>>>;

int GetParameterOfAutomate(std::istream& stream)
{
    int param;
    stream >> param;
    return param;
}

void ProcessStateString(StateList& result, size_t index, std::string& row)
{
    if (row.empty())
    {
        return;
    }
    std::stringstream stream(row);
    while (!stream.eof())
    {
        int state = GetParameterOfAutomate(stream);
        int output = GetParameterOfAutomate(stream);
        result[index][output].push_back(state);
        std::sort(result[index][output].begin(), result[index][output].end());
    }
}

StateList GetStateListOfAutomate(std::istream& stream, int countState, int countX)
{
    auto rowOfTable = std::vector<std::vector<int>>(countX, std::vector<int>());
    auto result = StateList((size_t)countState, rowOfTable);

    std::string row;
    std::getline(stream, row);
    for (size_t index = 0; index < result.size(); ++index)
    {
        if (std::getline(stream, row))
        {
            ProcessStateString(result, index, row);
        }
    }
    return result;
}

std::vector<int> GetFinalState(std::istream& stream, int countFinalState)
{
    std::vector<int> result;
    for (int index = 0; index < countFinalState; ++index)
    {
        result.push_back(GetParameterOfAutomate(stream));
    }
    return result;
}

void PrintFinalState(std::ostream& ostream, const std::vector<int>& outputVector)
{
    for (size_t index = 0; index < outputVector.size(); ++index)
    {
        ostream << outputVector[index] << " ";
    }
}

void PrintTable(std::ostream& ostream, const std::vector<std::vector<int>>& table)
{
    for (size_t index = 0; index < table[0].size(); ++index)
    {
        for (const auto& row : table)
        {
            ostream << row[index] << " ";
        }
        ostream << std::endl;
    }
}

void InsertUniqueStates(std::vector<int>& lhs, std::vector<int>& rhs)
{
    for (auto state : rhs)
    {
        if (state != -1 && std::find(lhs.begin(), lhs.end(), state) != lhs.end())
        {
            lhs.push_back(state);
        }
    }
    std::sort(lhs.begin(), lhs.end());
}

std::vector<std::vector<int>> MergeState(std::vector<std::vector<int>>& lhs, const std::vector<std::vector<int>>& rhs)
{
    for (size_t index = 0; index < lhs.size(); ++index)
    {
        auto& first = lhs[index];
        auto second = rhs[index];
        for (size_t j = 0; j < second.size(); ++j)
        {
            if (std::find(first.begin(), first.end(), second[j]) == first.end())
            {
                first.push_back(second[j]);
            }
        }
        std::sort(first.begin(), first.end());
    }
    return lhs;
}

std::vector<std::vector<int>> MakeState(const StateList& states, std::vector<int> indexOfStates, std::vector<std::vector<int>>& queue)
{
    auto result = states[indexOfStates.front()];
    for (size_t index = 1; index < indexOfStates.size(); ++index)
    {
        result = MergeState(result, states[indexOfStates[index]]);
    }
    for (auto& item : result)
    {
        if (!item.empty() && std::find(queue.begin(), queue.end(), item) == queue.end())
        {
            queue.push_back(item);
        }
    }
    return result;
}

int Find(std::vector<std::vector<int>>& queue, const std::vector<int>& search)
{
    for (size_t index = 0; index < queue.size(); ++index)
    {
        auto item = queue[index];
        if (item == search)
        {
            return (int)index;
        }
    }
    return -1;
}

bool isFinalState(std::vector<int>& finalState, std::vector<int>& search)
{
    for (auto state : search)
    {
        if (std::find(finalState.begin(), finalState.end(), state) != finalState.end())
        {
            return true;
        }
    }
    return false;
}

void TransformAutomate(StateList& prevStates, std::vector<std::vector<int>>& newStates, std::vector<int>& finalState, std::vector<int>& newFinalState)
{
    std::vector<std::vector<int>> queue;
    std::vector<int> startState = { 0 };
    queue.push_back(startState);
    if (isFinalState(finalState, startState))
    {
        newFinalState.push_back(0);
    }

    for (size_t index = 0; index < queue.size(); ++index)
    {
        auto& state = queue[index];
        std::vector<int> result;
        auto newState = MakeState(prevStates, state, queue);

        for (auto item : newState)
        {
            auto it = Find(queue, item);
            if (isFinalState(finalState, item) && std::find(newFinalState.begin(), newFinalState.end(), it) == newFinalState.end())
            {
                newFinalState.push_back(it);
            }
            result.push_back(it);
        }
        newStates.push_back(result);
    }
}

void PrintTableInDotFile(const std::string& fileName, std::vector<std::vector<int>>& table, const std::vector<int>& finalState)
{
    std::ofstream ofs(fileName);

    std::stringstream stream;
    PrintFinalState(stream, finalState);
    ofs << "digraph G {" << std::endl;
    ofs << "node [shape = doublecircle];" << stream.str() << ";" << std::endl;
    ofs << "node [shape = circle];" << std::endl;

    for (size_t index = 0; index < table.size(); ++index)
    {
        for (size_t jindex = 0; jindex < table[index].size(); ++jindex)
        {
            if (table[index][jindex] == -1) { continue; }
            ofs << index << " -> " << table[index][jindex] << " [ label = \"" << jindex << "\" ];" << std::endl;
        }
    }
    ofs << "}" << std::endl;
}

void doExecute(std::istream& streamIn, std::ostream& streamOut, const std::string& fileNameForVisualization)
{
    int countX = GetParameterOfAutomate(streamIn);
    int countState = GetParameterOfAutomate(streamIn);
    int countFinalState = GetParameterOfAutomate(streamIn);
    
    std::vector<int> finalState = GetFinalState(streamIn, countFinalState);
    std::vector<int> newFinalState;

    auto stateList = GetStateListOfAutomate(streamIn, countState, countX);
    std::vector<std::vector<int>> newStateList;

    TransformAutomate(stateList, newStateList, finalState, newFinalState);
    streamOut << countX << std::endl;
    streamOut << stateList.size() << std::endl;
    streamOut << newFinalState.size() << std::endl;
    PrintFinalState(streamOut, newFinalState);
    streamOut << std::endl;
    PrintTable(streamOut, newStateList);
    PrintTableInDotFile(fileNameForVisualization, newStateList, newFinalState);
}

int main()
{
    std::string inFileName = "input.txt";
    std::string outFileName = "output.txt";
    std::ifstream streamIn(inFileName);
    std::ofstream streamOut(outFileName);

    if (!streamIn.is_open() || !streamOut.is_open())
    {
        std::cerr << "Files aren't open." << std::endl;
        return 1;
    }

    doExecute(streamIn, streamOut, "visualization.dot");
    return 0;
}
