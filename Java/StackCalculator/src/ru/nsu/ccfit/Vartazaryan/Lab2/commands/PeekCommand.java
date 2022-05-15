package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.CalcStack;

public class PeekCommand implements Command
{
    @Override
    public void execute(String[] com_var_val)
    {
        double n = CalcStack.peek();
        System.out.println(n);
    }
}
