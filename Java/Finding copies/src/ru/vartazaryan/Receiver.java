package ru.vartazaryan;

import java.io.IOException;
import java.net.*;

public class Receiver implements Runnable
{
    protected MulticastSocket socket = null;
    protected byte[] buf = new byte[256];

    @Override
    public void run()
    {
        try {
            int port = 1234;
            String address = "230.0.0.0";

            socket = new MulticastSocket(port);
            InetAddress group = InetAddress.getByName(address);

            socket.joinGroup(group);
            while (true) {
                System.out.println("Waiting.....");

                DatagramPacket packet = new DatagramPacket(buf, buf.length);
                socket.receive(packet);

                String res = new String(packet.getData(), 0, packet.getLength());
                System.out.println("Received: " + res + "from" + group.getHostAddress());
                if ("end".equals(res))
                {
                    break;
                }
            }
            socket.leaveGroup(group);
            socket.close();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
}
