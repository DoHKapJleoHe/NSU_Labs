package ru.nsu.ccfit.Vartazaryan.Lab2.commands;

import ru.nsu.ccfit.Vartazaryan.Lab2.Calculator.CalcStack;

public interface Command
{
    public void execute(CalcStack ctx, String[] args);
}
