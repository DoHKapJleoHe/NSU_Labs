package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.calculator.CalcStack;

public class SqrtCommand implements Command
{
    @Override
    public void execute(CalcStack ctx, String[] args)
    {
        double num = ctx.pop();
        num = Math.sqrt(num);

        ctx.push(num);
    }
}
