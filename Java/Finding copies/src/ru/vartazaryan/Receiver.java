package ru.vartazaryan;

import java.io.IOException;
import java.net.*;

public class Receiver extends Thread
{
    protected MulticastSocket socket = null;
    protected byte[] buf = new byte[256];

    public void run()
    {
        try {
            socket = new MulticastSocket(4446);

            InetAddress inetAddress = InetAddress.getByName("230.0.0.0");
            InetSocketAddress group = new InetSocketAddress(inetAddress, socket.getPort());
            NetworkInterface netInf = NetworkInterface.getByName("bge0");

            socket.joinGroup(group, netInf);
            while (true) {
                System.out.println("Waiting.....");

                DatagramPacket packet = new DatagramPacket(buf, buf.length);
                socket.receive(packet);

                String res = new String(packet.getData(), 0, packet.getLength());
                System.out.println("Received: " + res);
                if ("end".equals(res)) {
                    break;
                }
            }
            socket.leaveGroup(group, netInf);
            socket.close();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
}
