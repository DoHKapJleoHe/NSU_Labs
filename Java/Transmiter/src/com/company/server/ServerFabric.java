package com.company.server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ServerFabric
{
        static private final ExecutorService executors = Executors.newFixedThreadPool(10);

        public static void main(String[] args) throws IOException
        {
            int port = Integer.parseInt(args[1]); //?
            ServerSocket server = new ServerSocket(port);
            System.out.println("Starting server...");

            //Make server shut down condition
            while (!server.isClosed())
            {
                System.out.println("Waiting for client...");
                Socket client = server.accept();
                System.out.println("Client accepted!");

                executors.execute(new Server(client));
            }

            executors.shutdown();
        }
}
