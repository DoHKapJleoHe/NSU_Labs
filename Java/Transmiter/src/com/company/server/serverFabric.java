package com.company.server;

import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class serverFabric
{
        static ExecutorService executors = Executors.newFixedThreadPool(2);

        public static void main(String[] args)
        {
            int port = 8081;
            try(ServerSocket server = new ServerSocket(port);)
            {
                System.out.println("Starting server!");

                while (!server.isClosed())
                {
                    Socket client = server.accept();
                }
            }
            catch (Exception e)
            {
                e.printStackTrace();
            }

        }
}
