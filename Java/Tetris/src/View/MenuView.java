package View;

import javax.swing.*;
import Controller.MenuController;

import java.awt.*;

public class MenuView extends JFrame // this class will inherit all functions of JFrame
{
    private JButton startButton;
    private JButton aboutButton;
    private JLabel gameName;
    private MenuController controller;

    public MenuView(MenuController controller)
    {
        super("TETRIS"); // referencing the base class to change frame's name
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // this operation will close created frame
    }

    public void initStartScreen()
    {
        this.setBounds(650, 300, 250, 300);
        this.setVisible(true);

        // parameters of button
        startButton = new JButton("Start");
        startButton.setSize(100, 30);
        startButton.setLocation(60, 50);

        aboutButton = new JButton("About");
        aboutButton.setSize(100, 30);
        aboutButton.setLocation(60, 90);

        // parameters of label
        gameName = new JLabel("TETRIS");
        gameName.setSize(100, 30);
        gameName.setLocation(90, 20);

        this.getContentPane().setLayout(null); // so that the elements do not stretch to full frame
        this.add(startButton); // adding button to frame
        this.add(aboutButton);
        this.add(gameName); // adding label to frame

        startButton.addActionListener(e -> {
            this.setVisible(false);
            startGame();
        });

        aboutButton.addActionListener(e -> {
            openAboutFrame();
        });
    }

    private void startGame()
    {
        /*JFrame gameField = new JFrame("Tetris");
        gameField.setBounds(650, 150, 400, 600);
        gameField.setVisible(true);

        gameField.getContentPane().setBackground(Color.white);*/

        GameBoard gameboard = new GameBoard();
        gameboard.start();
    }

    private void openAboutFrame()
    {
        JFrame aboutFrame = new JFrame("About");
        aboutFrame.setBounds(650, 300, 250, 250);
        aboutFrame.setVisible(true);

        JButton closeButton = new JButton("Close");
        closeButton.setLocation(60, 180);
        closeButton.setSize(100, 30);
        closeButton.addActionListener(e -> {
            aboutFrame.dispose();
        });

        aboutFrame.getContentPane().setLayout(null);
        aboutFrame.add(closeButton);
    }

}
