package View;

import Controller.GameController;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

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
    private GameController gameController;

    public GameBoard(GameController gc)
    {
        this.gameController = gc;
        setFocusable(true);

        // each element of this array is a figure(mb it is correct to say that each element is a piece of a figure)
        board = new Figure.Shapes[BOARD_WIDTH * BOARD_HEIGHT];
        for(int i = 0; i < BOARD_HEIGHT; i++)
        {
            for(int j = 0; j < BOARD_WIDTH; j++)
            {
                board[i * BOARD_WIDTH + j] = Figure.Shapes.Noshape;
            }
        }

        addKeyListener(new TAdapter());
    }

    public void start()
    {
        timer = new Timer(400, new ActionListener() {
            //this function will be called by timer each "delay" ms.
            @Override
            public void actionPerformed(ActionEvent e) {
                //The actionPerformed() method checks if the falling has finished.
                // If so, a new piece will be created. If not, the falling piece goes one line down.

                if(fallingFinished) //if created figure dropped down
                {
                    fallingFinished = false;
                    newFigure();
                }
                else
                {
                    oneLineDown(); // dropping figure on one line down
                    repaint();
                }
            }
        });
        newFigure();

        fallingFinished = false;

        timer.start();
    }

    private void oneLineDown()
    {
        if (tryToMove(currentFigure, curX, curY - 1))
        {
            curY -= 1;
            repaint();
        }
        else
        {
            pieceFinishedDropping();
            fallingFinished = true;

            repaint();
        }
    }

    public void newFigure()
    {
        currentFigure = new Figure(); // creating new figure to drop
        currentFigure.setFigure(Figure.Shapes.Lineshape);

        curX = BOARD_WIDTH / 2;
        curY = BOARD_HEIGHT - 2;

        if(!tryToMove(currentFigure, curX, curY))
        {
            currentFigure.setFigure(Figure.Shapes.Noshape);
            timer.stop();
        }
    }

    private boolean tryToMove(Figure figure, int newX, int newY)
    {
        for(int i = 0; i < 4; i++) // checking each part of figure
        {
            // here i check if i can move each part of figure
            int x = curX + currentFigure.pieceX(i);
            int y = curY - currentFigure.pieceY(i);

            if (x <= 0 || x >= BOARD_WIDTH || y <= 0 || y >= BOARD_HEIGHT)
                return false;
            if(figureAt(x, y - 1) != Figure.Shapes.Noshape)
                return false;
        }

        currentFigure = figure;
        return true;
    }

    private void pieceFinishedDropping()
    {
        for (int i = 0; i < 4; i++)
        {
            // standard coordinate system: y - grows up, x - grows right.
            // as figures falling from the top of the board, new x-coordinate should be counted by adding
            // each pieces x-coordinate to current x-coordinate. And y-coordinate should be counted by subtracting
            // each pieces y-coordinate from current y-coordinate.

            int x = curX + currentFigure.pieceX(i);
            int y = curY - currentFigure.pieceY(i);

            board[x + y * BOARD_WIDTH] = currentFigure.getFigure();

        }

    }

    private Figure.Shapes figureAt(int x, int y)
    {
        return board[x + BOARD_WIDTH * y];
    }

    private int squareWidth()
    {
        return (int) (getSize().getWidth() / BOARD_WIDTH);
    }

    private int squareHeight()
       {
            return (int) (getSize().getHeight() / BOARD_HEIGHT);
    }

    // figures consist of 4 pieces. each piece is a square. this function will draw this squares
    private void drawSquare(Graphics graphics, int x, int y, Figure.Shapes figure)
    {
        Color[] colors = {new Color(0, 0, 0), new Color(204, 102, 102),
                new Color(102, 204, 102), new Color(102, 102, 204),
                new Color(204, 204, 102), new Color(204, 102, 204),
                new Color(102, 204, 204), new Color(218, 170, 0)
        };

        Color color = colors[figure.ordinal()];

        graphics.setColor(color);
        graphics.fillRect(x + 1, y + 1, squareWidth(),squareHeight());

    }

    @Override
    public void paint(Graphics graphics)
    {
        int boardTop = (int) getSize().getHeight() - BOARD_HEIGHT * squareHeight();

        // painting figures that remain in the bottom of the field
        for(int i = 0; i < BOARD_HEIGHT; i++)
        {
            for (int j = 0; j < BOARD_WIDTH; j++)
            {
                //  standard coordinate system: y - grows up, x - grows right.
                // that's why second argument of figureAt method is "BOARD_HEIGHT - i - 1"
                // -1 because coordinate system starts from 0
                Figure.Shapes figure = figureAt(j, BOARD_HEIGHT - i - 1);

                if(figure == Figure.Shapes.Noshape)
                {
                    drawSquare(graphics, j * squareWidth(), boardTop + i * squareHeight(), figure);
                }
            }
        }

        // painting falling figure
        if(currentFigure.getFigure() != Figure.Shapes.Noshape)
        {
            for (int i = 0; i < 4; ++i)
            {
                int x = curX + currentFigure.pieceX(i);
                int y = curY - currentFigure.pieceY(i);

                drawSquare(graphics, 0 + x * squareWidth(),
                        boardTop + (BOARD_HEIGHT - y - 1) * squareHeight(), currentFigure.getFigure());
            }
        }
    }

    class TAdapter extends KeyAdapter // this will control keyboard usage
    {
        @Override
        public void keyPressed(KeyEvent e)
        {
            int code = e.getKeyCode();

            switch (code) {
                case KeyEvent.VK_LEFT -> curX -= 1;
                case KeyEvent.VK_RIGHT -> curX += 1;
            }
        }
    }

}
