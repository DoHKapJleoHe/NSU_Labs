package ru.vartazaryan;

import java.io.IOException;

public class Main
{
    public static void main(String[] args)
    {
        Receiver receiver = new Receiver();
        Broadcaster broadcaster = new Broadcaster();

        Thread receiverThread = new Thread(receiver);
        receiverThread.start();

        Thread broadcasterThread = new Thread(broadcaster);
        broadcasterThread.start();
    }
}
