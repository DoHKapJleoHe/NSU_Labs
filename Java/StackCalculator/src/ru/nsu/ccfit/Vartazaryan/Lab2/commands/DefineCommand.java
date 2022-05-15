package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.CalcStack;

public class DefineCommand implements Command
{
//    void DEFINE (String var, Double val)
//    {
//        CalcStack.addVar(var, val);
//    }

    @Override
    public void execute(String[] args)
    {
        // args[0] = command, args[1] = variable, args[2] = value

        CalcStack.addVar(args[1], Double.parseDouble(args[2]));
    }
}
