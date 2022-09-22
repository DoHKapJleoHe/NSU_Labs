package ru.vartazaryan;

import java.net.*;
import java.nio.charset.StandardCharsets;

public class Broadcaster implements Runnable
{
    protected MulticastSocket multicastSocket;
    protected InetAddress group;
    protected byte[] buf;

    @Override
    public void run()
    {
        try
        {
            int port = 1234;
            String address = "230.0.0.0";

            multicastSocket = new MulticastSocket(port);
            group = InetAddress.getByName(address);

            buf = "end".getBytes(StandardCharsets.UTF_8);
            DatagramPacket packet = new DatagramPacket(buf, buf.length, group, 4446);
            multicastSocket.send(packet);
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}
