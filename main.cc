#include <iostream>
#include "conio.h" //used because repl.it doesn't have <conio.h> :/


using namespace std;

enum eDir {STOP = 0,LEFT = 1,UPLEFT = 2,DOWNLEFT = 3,RIGHT = 4,UPRIGHT = 5,DOWNRIGHT = 6};
// case of ball and ball position
class cBall
{
private:
  int x,y;
  int originalX, originalY;
  eDir dir;
public:

  cBall(int posX, int posY)
  {
    originalX = posX;
    originalY = posY;
    x = posX; y = posY;
    dir = STOP;
 
   
  }
   void Reset()
    {
      x = originalX; y = originalY;
      dir = STOP;
    }


    void changeDIR(eDir d)
     {
       dir = d;
     } 

  void randDIR()
  {
    dir = (eDir)((rand() % 6) + 1);
  }

  inline int getX() { return x; }
  inline int getY() { return y; }
  inline eDir getdir() { return dir; }
  void move()
  {
    switch(dir)
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
        x--,y--;
        break;
      case DOWNLEFT:
        x--,y++;
        break;
      case UPRIGHT:
        x++,y--;
        break;
      case DOWNRIGHT:
        x++,y++;
      break;
      default:
        break;

    }
  }
  //friend ostream & operator<<(ostream & o, cBall c)
   //{
    //o <<"Ball [" << c.x << "," << c.y << "][" << c.dir << "]";
    //return o;
   //}

};
// case of paddle aka player
class cPaddle
{
  private:

    int x,y;
    int originalX,originalY;      
  public:
    cPaddle()
  {
    x = y = 0;
  }
  cPaddle(int posX, int posY) :cPaddle()
  {
    originalX = posX;
    originalY = posY;
    x = posX;
    y = posY;
  }

  inline void Reset() {x = originalX; y = originalY; }
  inline int getX() { return x; }
  inline int getY() { return y; }
  inline void moveUp() {y--;}
  inline void moveDown() {y++;}


//friend ostream & operator<<(ostream & o, cPaddle c)
  //{
    //o <<"Paddle [" << c.x << "," << c.y << "]";
    //return o;
  //}


};
//draws the game
class cGM
{
    private:
      int width, height;
      int score1, score2;
      char up1,down1,up2,down2;
      bool quit;
      cBall *ball;
      cPaddle *p1;
      cPaddle *p2;
    public:
      cGM(int w, int h)
      {
          srand(time(NULL));
          quit = false;
          up1 = 'w'; up2 = 'i';
          down1 = 's'; down2 = 'k';
          score1 = score2 = 0;
          width = w; height = h;
          ball = new cBall(w / 2, h / 2);
          p1 = new cPaddle(1 , h / 2 - 3);
          p2 = new cPaddle(w - 2, h / 2 - 3);
      }
    ~cGM()
    { 
      delete ball;
      delete p1;
      delete p2;
    }
    void SCRUp(cPaddle * p)
    {
      if(p == p1) {score1++;}
      else if(p == p2) {score2++;}
      ball -> Reset();
      p1 -> Reset();
      p2 -> Reset();
    }
    void draw()
    {
      system("clear");
      for(int i = 0; i < width + 2; i++)
        cout << "#";
      cout << endl;
      
      for (int i = 0; i < height + 2; i++)
        {
          for(int j = 0; j < width; j++)
          {
            int ballx = ball -> getX();
            int bally = ball -> getY();
            int p1x = p1 -> getX();
            int p1y = p1 -> getY();
            int p2x = p2 -> getX();
            int p2y = p2 -> getY();
            if(j == 0)
              cout << "#";
             
            if(ballx == j && bally == i)
             cout << "0"; //the ball
              
             else if(p1x == j && p1y == i)
              cout << "\xB2"; // p1
                else if(p1x == j && p1y + 1 == i)
              cout << "\xB2"; // p1
               else if(p1x == j && p1y +2 == i)
              cout << "\xB2"; // p1
               else if(p1x == j && p1y + 3 == i)
              cout << "\xB2"; // p1
            
             else if(p2x == j && p2y == i)
              cout << "\xB2"; //p2
                else if(p2x == j && p2y + 1 == i)
              cout << "\xB2"; //p2
               else if(p2x == j && p2y + 2== i)
              cout << "\xB2"; //p2
               else if(p2x == j && p2y + 3 == i)
              cout << "\xB2"; //p2 
              
             else
               cout << " ";

            if(j == width - 1)
              cout << "#";
             
          }
          cout << endl; 
     
        }
         
      for(int i = 0; i < width + 2 ; i++)
         cout << "#";
      cout << endl;
      
      cout << "Score 1: " << score1 << "  " << "Score 2: " << score2 << " i_luv_u";
    

    }
    void input()
    {
       ball->move();
       int ballx = ball -> getX();
            int bally = ball -> getY();
            int p1x = p1 -> getX();
            int p1y = p1 -> getY();
            int p2x = p2 -> getX();
            int p2y = p2 -> getY();
      
      if(kbhit())
      {
        char current = getch();
        if (current == up1)
          if (p1y > 0)
            p1 -> moveUp();
        if (current == up1)
          if (p2y > 0)
            p1 -> moveUp();

        if (current == down1)
          if (p1y + 4 < height)
            p1 -> moveDown();

        if (current == down1)
          if (p2y + 4 < height)
            p2 -> moveDown();

        if(ball -> getdir() == STOP)
          ball -> randDIR();

        if (current == 'l')
          quit = true;
      }
    }
    void logic()
    {
        int ballx = ball -> getX();
            int bally = ball -> getY();
            int p1x = p1 -> getX();
            int p1y = p1 -> getY();
            int p2x = p2 -> getX();
            int p2y = p2 -> getY();

      // left paddle
      for(int i = 0; i < 4; i++ )
        if (ballx == p1x + 1)
          if (bally == p1x + i)
            ball ->  changeDIR((eDir)((rand() % 3) + 4));
      // right paddle
      
      for(int i = 0; i < 4; i++ )
        if (ballx == p2x - 1)
          if (bally == p2x + i )
            ball ->  changeDIR((eDir)((rand() % 3) + 1));
            //bottom wall
      
      if(bally == height - 1)
        ball->changeDIR(ball -> getdir() == DOWNRIGHT ? UPRIGHT : UPLEFT);

      //top wall
      if(bally == 0)
        ball->changeDIR(ball -> getdir() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
    
      //right wall
      if (ballx == width - 1)
        SCRUp(p1);
        
      //left wall
      if (bally == 0)
        SCRUp(p2);
    
    }

    void run()
    {
      while(!quit)
      {
        draw();
        input();
        logic();
      }
    }

    
};

int main() {
 cGM c(40,20);
 c.run();
 
  return 0;
} 
