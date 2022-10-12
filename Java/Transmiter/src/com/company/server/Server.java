package com.company.server;

import com.company.client.Client;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;


public class Server implements Runnable
{
    private final byte[] buffer = new byte[4096];
    private String pathName;
    private File newFile = null;
    private Socket client;

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
            int length = 0;

            entryText = in.readUTF();

            if(isFileName(entryText))
            {
                String fileName = entryText.substring(12);
                String currentPathName = "C:\\Users\\eduar\\Desktop\\ForTCP\\" + fileName;
                pathName = currentPathName;
                try
                {
                    newFile = new File(currentPathName);
                    newFile.createNewFile();
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
            }

            getFileData(in);
            System.out.println("Server finished copying data!");

            in.close();
            out.close();

            client.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

    }

    private void getFileData(DataInputStream inputStream) throws IOException {
        System.out.println("Server started copying data...");

        FileOutputStream writer = new FileOutputStream(newFile.getPath());

        while (inputStream.available() > 0)
        {
            System.out.println("Copying...");
            inputStream.read(buffer);

            writer.write(buffer);
        }
        writer.close();
    }

    private boolean isFileName(String name)
    {
        if(name.contains("File name :"))
        {
            System.out.println("Server got file!");
            return true;
        }
        else
        {
            return false;
        }
    }
}

