package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.CalcStack;

public class SqrtCommand implements Command
{
    @Override
    public void execute(String[] args)
    {
        double num = CalcStack.pop();
        num = Math.sqrt(num);

        CalcStack.push(Double.toString(num));
    }
}
