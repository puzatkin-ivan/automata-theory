#include "stdafx.h"
#include <iostream>
#include "FSInputStream.h"
#include "FSOutputStream.h"


int main()
{
    try
    {
        std::string typeFSMachine;
        std::cin >> typeFSMachine;
        int type = std::stoi(typeFSMachine, nullptr, 10);

        if (type == (int)FSMachineEnum::Mealy)
        {
            MealyMachineInputStream stream;
            auto params = stream.ReadParameters();
            auto tableOfState = stream.ReadTableOfState(params);
            MealyMachine machine(tableOfState, params);
            machine.Minimizate();
            MealyMachineOutputStream outStream;
            outStream.Write(machine);
        }
        else if (type == (int)FSMachineEnum::Moore)
        {
            MooreMachineInputStream stream;
            auto params = stream.ReadParameters();
            auto yState = stream.ReadYState(params);
            auto tableOfState = stream.ReadTableOfState(params);

            MooreMachine machine(tableOfState, yState, params);
            machine.Minimizate();
            MooreMachineOutputStream outStream;
            outStream.Write(machine);
        }
        else
        {
            throw std::invalid_argument("Invalid machine type.");
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

