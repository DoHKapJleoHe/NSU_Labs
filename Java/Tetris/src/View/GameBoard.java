package View;

import javax.swing.*;
import javax.swing.text.View;

public class GameBoard extends JPanel
{
    public static final int BOARD_WIDTH = 10;
    public static final int BOARD_HEIGHT = 22;
    private Timer timer;
    private int linesDestroyed = 0;
    private Figure.Shapes[] board;
    private Figure currentFigure;
    private boolean fallingFinished = false;
    private int curX = 0;
    private int curY = 0;

    public GameBoard()
    {
        board = new Figure.Shapes[BOARD_WIDTH * BOARD_HEIGHT]; // each element of this array is a figure(mb it is correct to say that each element is a piece of a figure)
    }

    public void start()
    {
        timer.start();
        fallingFinished = false;

        newFigure();
    }

    private void newFigure()
    {
        currentFigure = new Figure(); // creating new figure to drop
        currentFigure.setFigure(Figure.Shapes.Lineshape);

        curX = BOARD_WIDTH / 2;
        curY = 0;

        if(!tryToMove())
        {

        }

    }

    private boolean tryToMove(Figure.Shapes Figure, int newX, int newY)
    {
        for(int i = 0; i < 4; i++) // checking each part of figure
        {
            int

            if (figureAt(x, y) != View.Figure.Shapes.Noshape) {
                return false;
            }
        }

    }

    private Figure.Shapes figureAt(int x, int y)
    {
        return board[x + BOARD_WIDTH * y];
    }

    private void clearBoard()
    {
        for(int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
        {
            board[i] = Figure.Shapes.Noshape;
        }
    }


}
