package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.calculator.CalcStack;

public class PopCommand implements Command
{
    @Override
    public void execute(CalcStack ctx, String[] args)
    {
        double n = ctx.pop();
        System.out.println(n);
    }
}
