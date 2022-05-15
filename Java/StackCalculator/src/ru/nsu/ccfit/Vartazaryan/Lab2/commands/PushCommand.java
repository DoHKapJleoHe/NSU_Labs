package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.CalcStack;

public class PushCommand implements Command
{
    @Override
    public void execute(String[] args)
    {
        CalcStack.push(args[1]);
    }
}
