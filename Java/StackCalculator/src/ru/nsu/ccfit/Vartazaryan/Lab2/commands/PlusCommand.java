package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.CalcStack;

public class PlusCommand implements Command
{
    @Override
    public void execute(String[] args)
    {
        double num1 = CalcStack.pop();
        double num2 = CalcStack.pop();
        double num3 = num1 + num2;

        CalcStack.push(Double.toString(num3));
    }
}
