package com.company.client;

import java.io.*;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class Client
{
    private final String path;
    private final int serverPort;
    private final byte[] buf = new byte[4096];

    public Client(String path, int serverPort)
    {
        this.serverPort = serverPort;
        this.path = path;
    }

    public void run() throws IOException
    {
        Socket clientSocket = new Socket("127.0.0.1", serverPort);
        try(    DataInputStream in = new DataInputStream(clientSocket.getInputStream()); // to send smth
                DataOutputStream out = new DataOutputStream(clientSocket.getOutputStream());)
        {
            File file = new File(path);
            String textToSend = " File name :" + file.getName();

            out.writeLong(file.length());

            out.writeUTF(textToSend);

            //out.writeInt((int)file.length());

            FileInputStream reader = new FileInputStream(file.getPath());
            int sendBytes = 0;
            int totalSendBytes = 0;

            while (reader.available() > 0)
            {
                sendBytes = reader.read(buf);
                totalSendBytes += sendBytes;
                out.write(buf, 0, sendBytes);
            }
            int bytesFromServer = in.readInt();
            System.out.println("Was send " + totalSendBytes + " bytes");
            System.out.println("Server got " + bytesFromServer + " bytes");
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

        clientSocket.close();
    }

}
