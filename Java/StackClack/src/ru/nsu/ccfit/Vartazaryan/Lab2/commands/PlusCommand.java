package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.CalcStack;

public class PlusCommand implements Command
{
    @Override
    public void execute(CalcStack ctx, String[] args)
    {
        double num1 = ctx.pop();
        double num2 = ctx.pop();
        double num3 = num1 + num2;

        ctx.push(num3);
    }
}
