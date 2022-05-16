package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.CalcStack;

public class PeekCommand implements Command
{
    @Override
    public void execute(CalcStack ctx, String[] com_var_val)
    {
        double n = ctx.peek();
        System.out.println(n);
    }
}
