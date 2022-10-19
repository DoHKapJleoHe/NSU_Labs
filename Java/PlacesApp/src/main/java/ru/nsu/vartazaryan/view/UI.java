package ru.nsu.vartazaryan.view;

import javax.swing.*;

public class UI
{
    public static void main(String[] args)
    {
        JFrame frame = new JFrame();
        frame.setBounds(300, 0, 1000, 800);
        frame.getContentPane().setLayout(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);

        JButton findButton = new JButton("Find!");
        findButton.setBounds(30, 30, 100, 30);
        findButton.setVisible(true);
        frame.add(findButton);

        JList<String> data = new JList();
    }
}
