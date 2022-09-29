package com.company;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Server extends IOException
{
    private int port;

    public Server(int port)
    {
        this.port = port;
    }

    public void run() throws IOException
    {
        ServerSocket serverSocket = new ServerSocket(port); // <1000 are sys ports

        Socket clientSocket = serverSocket.accept(); // waiting for client

        Scanner in = new Scanner(clientSocket.getInputStream());
        PrintWriter out = new PrintWriter(clientSocket.getOutputStream());




        clientSocket.close();
        serverSocket.close();
    }
}
