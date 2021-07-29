#include<iostream>
#include<conio.h>
#include<dos.h>
#include <windows.h>
#include <time.h>
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define ESC 27                  //Detects the escape key.
using namespace std;




string name = "";




class graphics{					//BASE CLASS
private:
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //GetStdHandle it gets a handle which you can use to write to the console.
        COORD CursorPosition;                        //SetConsoleCursorPosition uses that handle
public:
    char keys[10];
    int keyPos[10][2];

    //obj3.setcursor(0,0);
    graphics(){
    setcursor(0,0);             //Initial position of the cursor,When using the system predefined cursor, it should be set to null.
}

void gotoxy(int x, int y){
	CursorPosition.X = x;       //The x and y coordinates are the column and row of a screen buffer character cell.
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);  //A COORD structure that specifies the new cursor position, in characters.
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;//The visibility of the cursor. If the cursor is visible, this member is TRUE.
	lpCursor.dwSize = size;      //The percentage of the character cell that is filled by the cursor. This value is between 1 and 100
	SetConsoleCursorInfo(console,&lpCursor);
}
void drawBorder(){                          //Drawing the screen
	for(int i=0; i<SCREEN_WIDTH; i++){
		gotoxy(i,SCREEN_HEIGHT); cout<<"±";
	}

	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(0,i); cout<<"±";
		gotoxy(SCREEN_WIDTH,i); cout<<"±";
	}
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(WIN_WIDTH,i); cout<<"±";
	}
  }


};

class alphabets{                        //Derived class
private:

public:
    graphics obj;


void genAlphabet(int ind){
	obj.keys[ind] = 65+rand()%25;           //Generating random numbers using rand().
	obj.keyPos[ind][0] = 2 + rand()%(WIN_WIDTH-2);       //INERITENCE
	obj.keyPos[ind][1] = 1;
}
void drawAlphabet(int ind){
	if( obj.keyPos[ind][0] != 0 ){
		obj.gotoxy(obj.keyPos[ind][0], obj.keyPos[ind][1]);   cout<<obj.keys[ind];
	}
}
void eraseAlphabet(int ind){			//if same word is pressed by the keyboard it gets erased
	if( obj.keyPos[ind][0] != 0 ){
		obj.gotoxy(obj.keyPos[ind][0], obj.keyPos[ind][1]);   cout<<" ";
	}
}
void resetAlphabet(int ind){		//another word appears when a word gets erased and so on
	eraseAlphabet(ind);
	genAlphabet(ind);
}


};

class game{         //DERIVED CLASS
private:

public:
    //graphics a1.obj;
    alphabets a1;
    int score = 0;

void mainScreen(){
    do{
		system("cls");
		a1.obj.gotoxy(10,5); cout<<" -------------------------- ";              //INERITENCE
		a1.obj.gotoxy(10,6); cout<<" |     TYPING  TUTOR      | ";
		a1.obj.gotoxy(10,7); cout<<" |           BY           | ";
		a1.obj.gotoxy(10,8); cout<<" |     KHAFI UL KONAIN    | ";
		a1.obj.gotoxy(10,9); cout<<" --------------------------";
		a1.obj.gotoxy(10,11); cout<<"Select option: ";
		a1.obj.gotoxy(10,12); cout<<"1. Start Game";
		a1.obj.gotoxy(10,13); cout<<"2. Instructions";
		a1.obj.gotoxy(10,14); cout<<"3. Quit";

		char op = getche();

		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') break;
	}while(1);
}

void gameover(){
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\t   Player Name : "<<name<<endl<<endl;
	cout<<"\t\t   Player Score: "<<score<<endl<<endl;
	cout<<"\t\tPress ESCAPE key to go back to menu.";
	//getch(ESC);
	while(1){
		if(kbhit()){ 			//"if(kbhit())"It returns a non-zero integer if a key is pressed then it returns a non zero value, otherwise returns zero.
			char ch = getch();
			if(ch==ESC){
				break;
			}
		}
	}
}

void getPlayerName(){

	a1.obj.gotoxy(18, 5);cout<<"Enter Player Name: ";		  // Getting Player name in Gameplay
	a1.obj.gotoxy(38, 5);cin >> name;

	a1.obj.gotoxy(WIN_WIDTH + 5, 8);cout<<"Name: "<<name<<endl;	    //INERITENCE

    a1.obj.gotoxy(18, 7);cout<<"Press any key to start";
    getch();

	a1.obj.gotoxy(18, 7);cout<<"                      ";			// Clearing Play Area

	a1.obj.gotoxy(18, 5);cout<<"                      ";
	a1.obj.gotoxy(38, 5);cout<<"                      ";
}

void updateScore(){
	a1.obj.gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

void instructions(){

	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n On Left side you will see falling characters ";
	cout<<"\n You have to keep them away from touching the base";
	cout<<"\n Press respective key from keyboard to keep playing";
	cout<<"\n\n Press 'Escape' to exit";
	cout<<"\n\nPress any key to go back to menu";
	getch();				//Get char entry from the console
}

void play(){
	score = 0;				//Set initial score to 0.
	for(int i=0; i<10; i++){
		a1.obj.keyPos[i][0] = a1.obj.keyPos[i][1] = 1;
	}

	system("cls");			//the Windows command prompt clears the output screen of the program.
	a1.obj.drawBorder();
	updateScore();

	for(int i=0; i<10; i++)
		a1.genAlphabet(i);

    a1.obj.gotoxy(WIN_WIDTH + 5, 2);cout<<"Typing Tutor";
	a1.obj.gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	a1.obj.gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";

	getPlayerName();


	while(1){
		if(kbhit()){		// Determines if a keyboard key was pressed
			char ch = getch();
			for(int i=0; i<10; i++){
				if( ch == a1.obj.keys[i] || ch-32 == a1.obj.keys[i] ){
					a1.resetAlphabet(i);
					score++;
					updateScore();
				}
			}
			if(ch==27){                 //ASCII value for escape key, we used this so that the console only responds to the escape key
				break;
			}
		}



		for(int i=0; i<10; i++)
			a1.drawAlphabet(i);

		Sleep(300);			//The sleep() function is used to delay the execution of the program for some period of time.

		for(int i=0; i<10; i++){
			a1.eraseAlphabet(i);
			a1.obj.keyPos[i][1] += 1;
			if( a1.obj.keyPos[i][1] > SCREEN_HEIGHT ){
				gameover();
				return;
			}
		}
	}
}
};




int main()
{

	srand( (unsigned)time(NULL));		//Using time for rand function.
	game gameplay;
	gameplay.mainScreen();



	return 0;
}
