package View;

import Controller.GameController;

import javax.swing.*;

public class Tetris extends JFrame
{
    private GameController gc;
    public Tetris(GameController gc)
    {
        this.gc = gc;

        setSize(200, 400);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        GameBoard gameBoard = new GameBoard(gc);
        add(gameBoard);
        gameBoard.start();

    }
}
