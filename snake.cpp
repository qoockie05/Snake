#include "snake.h"
#include "screen.h"
CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
	stan = HELP;
}

void CSnake::paint(){
	CFramedWindow::paint();
	int x=geom.topleft.x+1;
	int y=geom.topleft.y+1;
	if(stan==HELP){
		gotoyx(y,x);
		printl("SNAKE");
		gotoyx(y+1,x);
		printl("r - resume");
		gotoyx(y+2,x);
		printl("p - pause");
		gotoyx(y+3,x);
		printl("h - hide instructions");
		gotoyx(y+4,x);
		printl("Arrows: move snake with arrows.");

		
	} else if(stan==PAUSE){
		
	} else if(stan==RESUME){
		
		}
	
}
bool CSnake::handleEvent(int key){
	if(key==KEY_UP || key==KEY_DOWN || key==KEY_LEFT || key==KEY_RIGHT) return CFramedWindow::handleEvent(key);
	if(key=='r'){
		
	}
	return false;
}
