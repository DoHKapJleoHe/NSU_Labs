package ru.vartazaryan;

import java.io.IOException;
import java.net.*;

public class Receiver
{
    protected MulticastSocket socket = null;
    protected byte[] buf = new byte[256];

    public void run() throws IOException {
        socket = new MulticastSocket(4446);

        InetAddress inetAddress = InetAddress.getByName("230.0.0.0");
        InetSocketAddress group = new InetSocketAddress(inetAddress, socket.getPort());
        NetworkInterface netInf = NetworkInterface.getByName("bge0");

        socket.joinGroup(group, netInf);

    }
}
