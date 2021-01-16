#include<bits/stdc++.h>                //Header file for all most commonly used header files like iostream,vector,etc
#include<conio.h>                      //Header file used bcoz we used system("CLS")
#include<windows.h>                    //Header file for sleep funtion which is used to slow the speed
                                        // took help from stack over flow to slow the speed of snake

using namespace std;                   //std used for std::cout and std::cin
//Using namespace are used when we need to use same word for so many times
//you can also define your namespace also
//        namespace your_namespace_name{
//          int a; int b;
//         }
// Like    using namespace your_namespace_name;

bool gameover;                         // A boolean character to check if game is over or not
const int width=20;                    //Boundaries of Board
const int height=20;                    
int x,y,bubbleX,bubbleY,score;                  //x-> x-cordinate of snake        y-> y-cordinate of snake
                                                //bubbleX -> x-position of food         bubbleY -> y-position of food
int inc_tail_x[100],inc_tail_y[100];             //array for length of snake which increases
//  Board is of 20*20 i.e. 400 
//and we used length of snake 100*100 ho here is more space used 
//intensionally i created this issue

int length_tail;                             // length of snake which increases as it eats food
string name;                                 // your name 

enum edirection{STOP=0,LEFT,RIGHT,UP,DOWN};            //Stuctured direction
edirection dir;

void setup(){                                   // setup funtion 
      gameover=false;                           // gameover initially assigned to false as game starts
      dir=STOP;                                 // initially snake is stopped until any key is not pressed
      x=rand()%height;                             // Random height of snake
      y=rand()%width;                              // Random x position of snake
      bubbleX=(rand()%width);                         //Random y-position of bubble or food
      bubbleY=(rand()%height);                        //Random x-position of bubble or food
      score=0;                                        // Initially score is made 0;
}

void draw(){
   system("CLS");
   //INTRO PART
   

      for(int i=0;i<width+2;i++)                                   //Loop for upper boundary
         cout<<"==";
      cout<<endl;
      for(int i=0;i<height;i++){                                    //Loops for left and right boundary
         for(int j=0;j<2*width;j++){
            if(j==0)
               cout<<"||";
            if(i==y && j==x)                                         // Condition to check for position of head
               cout<<"^";                                           // Snake head
            else if(i==bubbleY && j==bubbleX)                     // Condition to check for position of bubble or food
               cout<<"B";                                            //food
            else{
               bool print=false;                                      // Just a flag to check condition
               for(int k=0;k<length_tail;k++){                       // Loop for snake tail to increase
                  if(inc_tail_x[k]==j && inc_tail_y[k]==i){           //
                     cout<<"o";
                     print=true;
                  }
               }
               if(print==false)                                      // if food is not eaten then printed blank space
                  cout<<" ";
            }
            if(j==2*width-1)                                         // Right boundary
               cout<<"||";
         }
         cout<<endl;
      }
      for(int i=0;i<width+2;i++){                                    // Loop for bottom boundary
         cout<<"==";
      }
      cout<<endl<<endl;
      cout<<"USERNAME : "<<name;                                  //Your name
      cout<<"Score : "<<score<<endl<<endl;                                 // Your Score
      
}

void input(){                                                  // Input funtion
   if(_kbhit()){                                               // _kbhit() funtion used for keyboard key hit
      switch (_getch())                                        // _getch() funtion used to get the key presed (a,s,d,w)
      {                                                      // Cases for key pressed
      case 'a':                                                
         dir=LEFT;
         break;
      case 'd':
         dir=RIGHT;
         break;
      case 'w':
         dir=UP;
         break;
      case 's':
         dir=DOWN;
         break;
      case 'x':                                             // if pressed x then gamefinishes and exits
      gameover=true;
         break;
      }
   }
}

void logic(){                                                        //Logic function for snake movement
      int prev_cord_x=inc_tail_x[0];                                 //prev_cord_x for keep record for previos x-position
      int prev_cord_y=inc_tail_y[0];                                // prev_cord_x for keep record for previos y-position
      int sec_prev_cord_x,sec_prev_cord_y;                         // sec_prev_cord_x and sec_prev_cord_y used to keep track of 
                                                                     // second last position of snake
      inc_tail_x[0]=x;                                             //initial x-position of snake
      inc_tail_y[0]=y;                                               //initial y-position of snake
      for(int i=1;i<length_tail;i++){                               // Loop to move the snake with positions

                                                               // Explanation of Logic   (movement of snake)
                                                                  //    ^       |      o        |    o     ooooo             
         sec_prev_cord_x=inc_tail_x[i];                           //    o       |      o    ^   |    o<ooooo   o        
         sec_prev_cord_y=inc_tail_y[i];                           //    ooooo   |      oooooo   |    ooooooooooo   

         inc_tail_x[i]=prev_cord_x;                               // (1st move)    (2nd move)        (3rd move)                                   
         inc_tail_y[i]=prev_cord_y;                               // ( simply )   (2 dir move )      (its himself)                            
         prev_cord_x=sec_prev_cord_x;                             //                                                     
         prev_cord_y=sec_prev_cord_y;                             //                                                    
      }
      switch (dir)                                               // switch statement for controlling direction
      {
      case LEFT:
         x--;
         break;
      case RIGHT:
         x++;
         break;
      case UP:                                                  // when going up y-- its not like regular coordinate system
         y--;
         break;
      case DOWN:
         y++;
         break;
      default:
         break;
      }
      // if(x>width || x<0 || y>height || y<0)                     // this condition is used if we want game to be over if snake
      //    gameover=true;                                         // hits the wall

      if(x>=width) x=0 ;else if(x<0) x=width-1;                    // this condition is used if we don't want game to be over 
      if(y>=height) y=0;else if(y<0) y=height-1;                   // if snake hits the wall

      for(int i=0;i<length_tail;i++){                                  // Loop to make game over if we hit ourself
         if(inc_tail_x[i]==x && inc_tail_y[i]==y){                     
            gameover=true;
         }
      }
      if(x==bubbleX && y==bubbleY){                                  // condition if we eat food
         score+=10;                                                  // score increases by 10
         bubbleX=(rand()%width);                                     // again position of food is randomised
         bubbleY=(rand()%height);
         length_tail++;                                              // tail of snake increases by 1
      }
}

int main(){                                                       // Main program execution occurs from here
      cout<<endl<<endl;
      cout<<"Hello this is just simple Snake game....."<<endl;
      cout<<"C-O-N-T-R-O-L-S"<<endl;
      cout<<" a - LEFT \n d - RIGHT \n w - UP \n s - DOWN"<<endl;
      cout<<endl<<endl;
      cout<<"Hey Guys do not take tension of the screen flickring it too simple snake game...."<<endl;
      cout<<endl;
      cout<<endl<<endl;
      cout<<"\t \t \t \t Creator : @its_shyam640"<<endl;
   cout<<"Enter Name : ";
   getline(cin,name);                                                   // Enter your name
   cout<<endl<<endl;
   
   setup();                                                          
   while(!gameover){
      draw();
      input();                                            // Calling of all funtions
      logic();
      Sleep(1);                                           
   }
   return 0;
}






