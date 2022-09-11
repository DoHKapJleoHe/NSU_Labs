package ru.vartazaryan;

import javax.xml.crypto.Data;
import java.io.IOException;
import java.net.*;

public class BroadcastingClient
{
    private DatagramSocket datagramSocket;
    private InetAddress group;
    private byte[] buf;

    public void broadcast(String message) throws IOException {
        datagramSocket = new DatagramSocket();
        group = InetAddress.getByName("230.0.0.0");
        buf = message.getBytes();

        DatagramPacket packet = new DatagramPacket(buf, buf.length, group, 4446);
        datagramSocket.send(packet);
    }
}
