package View;

import View.GameBoard;

import javax.swing.*;

public class Tetris extends JFrame
{
    public Tetris()
    {
        GameBoard gameBoard = new GameBoard();
        add(gameBoard);

        gameBoard.newFigure();

        setSize(200, 400);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }
}
