package ru.vartazaryan;

import java.io.IOException;

public class Main
{
    public static void main(String[] args)
    {
        Receiver receiver = new Receiver();
        receiver.run();
        try
        {
            Thread.sleep(1000);
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

        BroadcastingClient publisher = new BroadcastingClient();
        try
        {
            publisher.broadcast("Hi!");
            publisher.broadcast("I am John!");
            publisher.broadcast("Hehe");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
