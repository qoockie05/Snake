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
		gotoyx(y+7,x+15);
		printl("PAUSED");
		
	} else if(stan==RESUME){
		gotoyx(y,x+1);
		printl("POINTS: %d",points);
		for(size_t i=0;i < snake.size();i++){
			gotoyx(y+snake[i].y,x+snake[i].x);
			printc('*');
			}
		gotoyx(y+food.y,x+food.x);
		printc('o');
		}
	
}
bool CSnake::handleEvent(int key){
	if((stan==PAUSE || stan==HELP) && (key==KEY_UP || key==KEY_DOWN || key==KEY_LEFT || key==KEY_RIGHT)) {
		return CFramedWindow::handleEvent(key);
	}
	if(key=='p'){
		stan=PAUSE;
		return true;
	}
	if(key=='h'){
		stan=HELP;
		return true;
	}
	if(key=='r'){
		reset_game();
		stan=RESUME;
		return true;
	} 
	if(stan==RESUME){
		if(key==KEY_UP && direction.y==0){
			direction=CPoint(0,-1);
			return true;
		}
		if(key==KEY_DOWN && direction.y==0){
			direction=CPoint(0,1);
			return true;
		}
		if(key==KEY_LEFT && direction.x==0){
			direction=CPoint(-1,0);
			return true;
		}
		if(key==KEY_RIGHT && direction.x==0){
			direction=CPoint(1,0);
			return true;
		}
		
		if(key==-1){
			time++;
			if(time>4){
				move_snake();
				time=0;
				return true;
			}
		}
	}
	return false;
}

void CSnake::reset_game(){
	stan=RESUME;
	snake.clear();
	snake.push_back(CPoint(5,5));
	snake.push_back(CPoint(4,5));
	snake.push_back(CPoint(3,5));
	
	direction = CPoint(1,0);
	
	points = 0;
	place_food();
	
}
void CSnake::place_food(){
	int height_size=geom.size.y - 2;
	int width_size=geom.size.x - 2;
	
	bool end=false;
	while(!end){
		end=true;
		food.x=(rand() % width_size) + 1;
		food.y=(rand() % height_size) + 1;
		
		for(size_t i=0;i < snake.size();i++){
			if(snake[i].x==food.x && snake[i].y==food.y){
				end=false;
				break;
			}
		}
	}
	
	
}
void CSnake::move_snake(){
	CPoint position = snake[0];
	position.x += direction.x;
	position.y +=direction.y;
	
	int height_size=geom.size.y - 2;
	int width_size=geom.size.x - 2;
	
	if(position.x<1){ position.x = width_size; }
	else if (position.x > width_size){ position.x = 1; }
	if(position.y<1){ position.y = height_size; }
	else if (position.y > height_size){ position.y = 1; }
	
	snake.insert(snake.begin(),position);
	snake.pop_back(); //do usuniecia
}
