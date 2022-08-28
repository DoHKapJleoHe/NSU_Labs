package Controller;

import View.Figure;
import View.GameBoard;

import static View.GameBoard.BOARD_WIDTH;

public class GameController
{
    private GameBoard board;

    public GameController(GameBoard gb)
    {
        this.board = gb;
    }

    public Figure rotateRight(Figure figure)
    {
        if(figure.getFigure() == Figure.Shapes.Squareshape)
            return figure;

        var result = new Figure();

        for (int i = 0; i < 4; i++)
        {
            result.setX(i, result.pieceY(i));
            result.setY(i, -result.pieceX(i));
        }

        return result;
    }

    public void rotateLeft()
    {

    }

    public void moveRight(int x)
    {
        int newX = board.getCurX() + 1;

        board.setCurX(newX);
    }

    public void moveLeft(int x)
    {
        int newX = board.getCurX() - 1;

        board.setCurX(newX);
    }
}
