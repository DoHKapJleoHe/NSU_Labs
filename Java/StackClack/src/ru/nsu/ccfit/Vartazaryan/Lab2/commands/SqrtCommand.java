package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.CalcStack;

public class SqrtCommand implements Command
{
    @Override
    public void execute(CalcStack ctx, String[] args)
    {
        double num = ctx.pop();
        num = Math.sqrt(num);

        ctx.push(Double.toString(num));
    }
}
