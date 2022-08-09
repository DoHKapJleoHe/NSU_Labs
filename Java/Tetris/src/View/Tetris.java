package View;

import Controller.GameController;

import javax.swing.*;

public class Tetris extends JFrame
{
    public Tetris()
    {
        setSize(200, 400);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        GameBoard gameBoard = new GameBoard();
        add(gameBoard);
        gameBoard.start();

    }
}
