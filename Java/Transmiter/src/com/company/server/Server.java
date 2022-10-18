package com.company.server;

import java.io.*;
import java.net.Socket;
import java.nio.ByteBuffer;

public class Server implements Runnable
{
    private final byte[] buffer = new byte[4096];
    private String pathName = "C:\\Users\\eduar\\Desktop\\ForTCP\\";
    private File newFile = null;
    private final Socket client;
    private final String cut = "File name";

    public Server(Socket client)
    {
        this.client = client;
    }

    @Override
    public void run()
    {
        try
        {
            //Initializing chanel for reading from socket
            DataInputStream in = new DataInputStream(client.getInputStream());
            //Initializing chanel for writing in socket
            DataOutputStream out = new DataOutputStream(client.getOutputStream());

            String entryText;
            long length = 0L;

            length = in.readLong();
            System.out.println("File length = " + length + " bytes");

            entryText = in.readUTF();
            String fileName = entryText;
            String currentPathName = pathName + fileName;
            try
            {
                if(!fileNameAlreadyExist(currentPathName))
                {
                    newFile = new File(currentPathName);
                    newFile.createNewFile();
                }
                else
                {
                    System.out.println("Bro, there is file like yours...");
                }
            }
            catch (Exception e)
            {
                e.printStackTrace();
            }

            int readByte = 0;
            readByte = getFileData(in, length);

            if(readByte == length)
                out.writeUTF("All data received!");

            in.close();
            out.close();

            client.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

    }

    private int getFileData(DataInputStream inputStream, long length) throws IOException
    {
        System.out.println("Server started copying data...");
        int readByte = 0;
        int totalReadBytes = 0;

        FileOutputStream writer = new FileOutputStream(newFile.getPath());

        long curSpeed, totalSpeed;
        long threeSeconds = 3000000000L;
        long fullTime = System.nanoTime();

        while ((readByte = inputStream.read(buffer)) < length)
        {
            long startTime = System.nanoTime(); // ???

            totalReadBytes += readByte;
            writer.write(buffer, 0, readByte);

            if(startTime / threeSeconds == 0)
            {
                curSpeed = readByte / 3;
                System.out.println("Current speed = " + curSpeed);

                startTime = 0;
            }
            if (totalReadBytes >= length) {break;}
        }

        writer.close();
        System.out.println("Server finished copying data!");

        return totalReadBytes;
    }

    private boolean fileNameAlreadyExist(String name)
    {
        File file = new File(pathName + name);

        return file.exists();
    }
}

