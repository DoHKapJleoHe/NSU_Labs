package com.company.server;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;


public class Server implements Runnable
{
    private final int port;
    private final byte[] buffer = new byte[4096];
    private String pathName;
    private File newFile = null;

    public Server(int port)
    {
        this.port = port;
    }

    @Override
    public void run()
    {
        try
        {
            ServerSocket serverSocket = new ServerSocket(port); // <1000 are sys ports

            System.out.println("Waiting for client...");

            Socket clientSocket = serverSocket.accept(); // waiting for client
            System.out.println("Client was accepted!");

            //Initializing chanel for reading from socket
            DataInputStream in = new DataInputStream(clientSocket.getInputStream());
            //Initializing chanel for writing in socket
            DataOutputStream out = new DataOutputStream(clientSocket.getOutputStream());

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

            clientSocket.close();
            serverSocket.close();
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

