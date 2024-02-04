#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;

enum Direction { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };

class Ball
{

private:
    int x, y;
    int baseX, baseY;
    Direction direction;

public:
    Ball(int posX, int posY)
    {
        baseX = posX;
        baseY = posY;
        x = posX; y = posY;
        direction = STOP;
    }

    void reset()
    {
        x = baseX;
        y = baseY;
        direction = STOP;
    }

    void changeDirection(Direction d)
    {
        direction = d;
    }

    void randomDirection()
    {
        direction = (Direction)((rand() % 6) + 1);
    }

    inline int getX()
    {
        return x;
    }

    inline int getY()
    {
        return y;
    }

    inline Direction getDir()
    {
        return direction;
    }

    void move()
    {
        switch (direction)
        {
            case STOP:
                break;
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UPLEFT:
                x--;
                y--;
                break;
            case DOWNLEFT:
                x--;
                y++;
                break;
            case UPRIGHT:
                x++;
                y--;
                break;
            case DOWNRIGHT:
                x++;
                y++;
                break;
            default:
                break;
        }
    }

    friend ostream & operator<<(ostream & o, Ball b)
    {
        o << "Ball [" << b.x << "," << b.y << "][" << b.direction << "]" << endl;
        return o;
    }
};

class Paddle
{

private:
    int x, y;
    int baseX, baseY;

public:
    Paddle()
    {
        x = y = 0;
    }

    Paddle(int posX, int posY) : Paddle()
    {
        baseX = posX;
        baseY = posY;
        x = posX;
        y = posY;
    }

    inline void reset()
    {
        x = baseX;
        y = baseY;
    }

    inline int getX()
    {
        return x;
    }

    inline int getY()
    {
        return y;
    }

    inline void moveUp()
    {
        y--;
    }

    inline void moveDown()
    {
        y++;
    }

    friend ostream & operator<<(ostream & o, Paddle p)
    {
        o << "Paddle [" << p.x << "," << p.y << "]";
        return o;
    }

};

class GameManager
{

private:
    int width, height;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    Ball * ball;
    Paddle * player1;
    Paddle * player2;

public:
    GameManager(int w, int h)
    {
        srand(time(NULL));
        quit = false;
        up1 = 'z';
        up2 = 'o';
        down1 = 's';
        down2 = 'l';
        score1 = score2 = 0;
        width = w;
        height = h;
        ball = new Ball(w / 2, h / 2);
        player1 = new Paddle(1, h / 2 - 3);
        player2 = new Paddle(w - 2, h / 2 - 3);
    }

    ~GameManager()
    {
        delete ball, player1, player2;
    }

    void scoreUp(Paddle * player)
    {
        if (player == player1)
            score1++;
        else if (player == player2)
            score2++;

        ball->reset();
        player1->reset();
        player2->reset();
    }

    void draw()
    {
        system("cls");
        for (int i = 0; i < width + 2; i++)
            cout << "\xB2";
        cout << endl;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; width++)
            {
                int ballX = ball->getX();
                int ballY = ball->getY();
                int player1X = player1->getX();
                int player2X = player2->getX();
                int player1Y = player1->getY();
                int player2Y = player2->getY();

                if (j == 0)
                    cout << "\xB2";

                if (ballX == j && ballY == i)
                    cout << "O";
                else if (player1X == j && player1Y == i)
                    cout << "\xDB";
                else if (player2X == j && player2Y == i)
                    cout << "\xDB";

                else if (player1X == j && player1Y + 1 == i)
                    cout << "\xDB";
                else if (player1X == j && player1Y + 2 == i)
                    cout << "\xDB";
                else if (player1X == j && player1Y + 3 == i)
                    cout << "\xDB";

                else if (player2X == j && player2Y + 1 == i)
                    cout << "\xDB";
                else if (player2X == j && player2Y + 2 == i)
                    cout << "\xDB";
                else if (player2X == j && player2Y + 3 == i)
                    cout << "\xDB";
                else
                    cout << " ";

                if (j == width - 1)
                    cout << "\xB2";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "\xB2";
        cout << endl;

        cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;
    }

    void input()
    {
        ball->move();

        int ballX = ball->getX();
        int ballY = ball->getY();
        int player1X = player1->getX();
        int player2X = player2->getX();
        int player1Y = player1->getY();
        int player2Y = player2->getY();

        if (_kbhit())
        {
            char current = _getch();

            if (current == up1)
                if (player1Y > 0)
                    player1->moveUp();
            if (current == up2)
                if (player2Y > 0)
                    player2->moveUp();
            if (current == down1)
                if (player1Y + 4 < height)
                    player1->moveDown();
            if (current == down2)
                if (player2Y + 4 < height)
                    player2->moveDown();

            if (ball->getDir() == STOP)
                ball->randomDirection();

            if (current == 'q')
                quit = true;
        }
    }
};


int main()
{
    Paddle p1(0, 0);
    Paddle p2(10, 0);
    cout << p1 << endl;
    cout << p2 << endl;
    p1.moveUp();
    p2.moveDown();
    cout << p1 << endl;
    cout << p2 << endl;
    return 0;
}
