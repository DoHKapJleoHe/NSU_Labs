package ru.vartazaryan;

import java.net.*;
import java.nio.charset.StandardCharsets;

public class Broadcaster implements Runnable
{
    protected MulticastSocket multicastSocket;
    protected InetAddress group;
    protected byte[] buf;
    private Boolean isFinished = false;

    @Override
    public void run()
    {
        try
        {
            int port = 1417;
            String address = "230.0.0.0";

            multicastSocket = new MulticastSocket(port);
            group = InetAddress.getByName(address);
           
            while(!isFinished)
            {
                buf = "hi".getBytes(StandardCharsets.UTF_8);
                DatagramPacket packet = new DatagramPacket(buf, buf.length, group, 1234);
                multicastSocket.send(packet);
                Thread.sleep(5000);
            }

            multicastSocket.leaveGroup(group);
            multicastSocket.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    /*public void stop()
    {
        isFinished = true;
        Thread.interrupted();
    }*/
}
