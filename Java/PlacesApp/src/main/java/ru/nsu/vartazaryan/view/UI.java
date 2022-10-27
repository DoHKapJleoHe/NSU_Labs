package ru.nsu.vartazaryan.view;

import ru.nsu.vartazaryan.controller.Controller;

import javax.swing.*;

public class UI
{
    private static final Controller controller = new Controller();

    public static void main(String[] args)
    {
        JFrame frame = new JFrame();
        frame.setBounds(300, 0, 1000, 800);
        frame.getContentPane().setLayout(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);

        JButton findButton = new JButton("Find!");
        findButton.setBounds(30, 30, 100, 25);
        findButton.setVisible(true);
        frame.add(findButton);

        JTextField textField = new JTextField("Write here text...");
        textField.setVisible(true);
        textField.setBounds(160, 30, 300, 25);
        frame.add(textField);

        findButton.addActionListener(e -> {
            //TODO: make list to collect info from find-function
            controller.find(textField.getText());
        });
    }
}
