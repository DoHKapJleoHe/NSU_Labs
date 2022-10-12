package com.company.server;

import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ServerFabric
{
        static ExecutorService executors = Executors.newFixedThreadPool(3);

        public static void main(String[] args)
        {
            int port = 8081;
            try(ServerSocket server = new ServerSocket(port);)
            {
                System.out.println("Starting server...");

                //Make server shut down condition
                while (!server.isClosed())
                {
                    System.out.println("Waiting for client...");
                    Socket client = server.accept();
                    System.out.println("Client accepted!");

                    executors.execute(new Server(client));
                }
            }
            catch (Exception e)
            {
                e.printStackTrace();
            }

            executors.shutdown();
        }
}
