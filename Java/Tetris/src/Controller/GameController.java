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

    public void rotateRight(Figure figure)
    {

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
