package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.CalcStack;

public class PushCommand implements Command
{
    @Override
    public void execute(CalcStack ctx, String[] args)
    {
        ctx.push(args[1]);
    }
}
