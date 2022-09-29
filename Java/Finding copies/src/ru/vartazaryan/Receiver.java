package ru.vartazaryan;

import java.io.IOException;
import java.net.*;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

public class Receiver implements Runnable
{
    protected MulticastSocket socket = null;
    protected byte[] buf = new byte[256];
    private List<String> ips = new ArrayList<String>();

    @Override
    public void run()
    {
        /*List<String> tmp = new ArrayList<String>();
        ips = new CopyOnWriteArrayList<>(tmp);*/

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
                System.out.println("Received: " + res + " from " + packet.getAddress() + " " + packet.getPort());

                String packetPort = String.valueOf(packet.getPort());
                String packetAddress = String.valueOf(packet.getAddress());
                String fullAddress = packetAddress + " " + packetPort;

                /*if (!"end".equals(res))
                {
                    if(ips.size() == 0)
                        ips.add(fullAddress);

                    for(String i: ips)
                    {
                        if(fullAddress.equals(i))
                        {
                            break;
                        }
                        else
                        {
                            ips.add(fullAddress);
                        }
                    }

                    System.out.println("Live hosts: ");
                    for(String i: ips)
                    {
                        System.out.println(i);
                    }
                }*/
                if ("end".equals(res))
                {
                    ips.remove(fullAddress);
                    System.out.println("Live hosts: ");
                    for(String i: ips)
                    {
                           System.out.println(i);
                    }
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
