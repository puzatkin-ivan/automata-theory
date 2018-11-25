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

void MergeStates(StateList& prevStates, const std::vector<int>& indexOfStates, std::vector<int>& finalState)
{
    auto firstIndex = indexOfStates[0];
    for (auto index : indexOfStates)
    {
        if (firstIndex == index) { continue; }
        for (size_t j = 0; j < prevStates[firstIndex].size(); ++j)
        {
            auto& firstCell = prevStates[firstIndex][j];
            auto& cell = prevStates[index][j];
            InsertUniqueStates(firstCell, cell);
        }

        for (size_t i = 0; i < prevStates.size(); ++i)
        {
            for (size_t j = 0; j < prevStates[i].size(); ++j)
            {
                for (size_t k = 0; k < prevStates[i][j].size(); ++k)
                {
                    if (prevStates[i][j][k] == index)
                    {
                        prevStates[i][j][k] = firstIndex;
                    }
                }
            }
        }
        prevStates.erase(prevStates.begin() + index);

        auto indexIt = std::find(finalState.begin(), finalState.end(), index);
        if (std::find(finalState.begin(), finalState.end(), index) != finalState.end())
        {
            if (std::find(finalState.begin(), finalState.end(), firstIndex) == finalState.end())
            {
                finalState.push_back(firstIndex);
            }
            finalState.erase(indexIt);
        }
    }
}

void TransformAutomate(StateList& prevStates, std::vector<std::vector<int>>& newStates, std::vector<int>& finalState)
{
    auto rowOfTable = std::vector<int>(prevStates[0].size(), -1);

    for (size_t i = 0; i < prevStates.size(); ++i)
    {
        auto newRow = rowOfTable;
        for (size_t j = 0; j < prevStates[i].size(); ++j)
        {
            if (!prevStates[i][j].empty())
            {
                newRow[j] = prevStates[i][j][0];
                if (prevStates[i][j].size() > 1)
                {
                    MergeStates(prevStates, prevStates[i][j], finalState);
                }
            }
        }
        newStates.push_back(newRow);
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

    auto stateList = GetStateListOfAutomate(streamIn, countState, countX);
    std::vector<std::vector<int>> newStateList;

    TransformAutomate(stateList, newStateList, finalState);
    
    streamOut << countX << std::endl;
    streamOut << stateList.size() << std::endl;
    streamOut << finalState.size() << std::endl;
    PrintFinalState(streamOut, finalState);
    streamOut << std::endl;
    PrintTable(streamOut, newStateList);
    PrintTableInDotFile(fileNameForVisualization, newStateList, finalState);
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

