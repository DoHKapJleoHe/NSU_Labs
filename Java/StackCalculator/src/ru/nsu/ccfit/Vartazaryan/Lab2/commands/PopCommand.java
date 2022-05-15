package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.CalcStack;

public class PopCommand implements Command
{
    @Override
    public void execute(String[] args)
    {
        double n = CalcStack.pop();
        System.out.println(n);
    }
}
