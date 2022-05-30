package ru.nsu.ccfit.Vartazaryan.Lab2.factory;

import ru.nsu.ccfit.Vartazaryan.Lab2.commands.Command;

import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.InvocationTargetException;
import java.util.Properties;

public class ComFac
{
    /*Factory is a thing that creates commands by given name. Then you can use made command to some stuff.
      Class.forName("ru.nsu.ccfit.vartazaryan.lab2.someClass") - returns object of "class" class initialized by "someClass"
      getConstructor() - returns object of "constructor" class of class "someClass
      newInstance() - creates object of "someClass" class by constructor, that was returned from getConstructor()"*/

    public ComFac() {}

    public Command getCommand(String name) throws ClassNotFoundException, NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException
    {
        Properties prop = new Properties();
        InputStream stream;
        try
        {
            stream = ComFac.class.getResourceAsStream("commands.properties");
            prop.load(stream);
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
        String pat = prop.getProperty(name);

        Class.forName(pat);
        return (Command)Class.forName(pat).getConstructor().newInstance();
    }
}
