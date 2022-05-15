package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.CalcStack;

public class PrintCommand implements Command
{
    @Override
    public void execute(String[] com_var_val)
    {
        System.out.println(CalcStack.peek());
    }
}
