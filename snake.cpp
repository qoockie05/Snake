#include "snake.h"
#include "screen.h"
#define NumberOfLevels 10
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
		printl("r - restart");
		gotoyx(y+2,x);
		printl("p - pause");
		gotoyx(y+3,x);
		printl("h - hide instructions");
		gotoyx(y+4,x);
		printl("q - quit game");
		gotoyx(y+5,x);
		printl("Arrows: move snake with arrows.");
	} else if(stan==PAUSE){
		
		gotoyx(y+snake[0].y,x+snake[0].x);
			printc('*');
			for(size_t i=1;i < snake.size();i++){
				gotoyx(y+snake[i].y,x+snake[i].x);
				printc('+');
			}
		gotoyx(y-1,x+1);
		printl("LEVEL: %d",NumberOfLevels-level);
		gotoyx(y+7,x+15);
		printl("PAUSED");
		gotoyx(y+8,x+15);
		printl("To resume enter: p");
		
	} else if(stan==RESTART){
		gotoyx(y-1,x+1);
		printl("LEVEL: %d",NumberOfLevels-level);
		gotoyx(y+snake[0].y,x+snake[0].x);
		printc('*');
		for(size_t i=1;i < snake.size();i++){
			gotoyx(y+snake[i].y,x+snake[i].x);
			printc('+');
			}
			gotoyx(y+food.y,x+food.x);
			printc('o');
	} else if(stan==END){
			
			gotoyx(y+snake[0].y,x+snake[0].x);
			printc('*');
			for(size_t i=1;i < snake.size();i++){
				gotoyx(y+snake[i].y,x+snake[i].x);
				printc('+');
			}
			
			gotoyx(y,x);
			printl("GAME OVER");
			gotoyx(y+1,x);
			printl("POINTS: %d",points);
	} else if(stan==RESUME){
			gotoyx(y-1,x+1);
			printl("LEVEL: %d",NumberOfLevels-level);
			gotoyx(y+snake[0].y,x+snake[0].x);
			printc('*');
			for(size_t i=1;i < snake.size();i++){
				gotoyx(y+snake[i].y,x+snake[i].x);
				printc('+');
				}
			gotoyx(y+food.y,x+food.x);
			printc('o');
			}
		}
	

bool CSnake::handleEvent(int key){
	if((stan==PAUSE || stan==HELP || stan==END) && (key != 'p' && key != 'h' && key != 'r' && key != -1)) {
		return CFramedWindow::handleEvent(key);
	}
	if(key=='p' && stan==PAUSE){
		stan=RESUME;
		return true;
	}
	if(key=='p' && (stan==RESTART || stan==RESUME)){
		stan=PAUSE;
		return true;
	}
	if(key=='h' && stan==HELP){
		reset_game();
		stan=RESTART;
		return true;
	}
	if(key=='h'){
		stan=HELP;
		return true;
	}
	if(key=='r'){
		reset_game();
		stan=RESTART;
		return true;
	} 
	if(key=='q'){
		exit(0);
	}
	if(stan==RESTART || stan==RESUME){
		if(key==KEY_UP && direction.y!=1){
			direction=CPoint(0,-1);
			return true;
		}
		if(key==KEY_DOWN && direction.y!=-1){
			direction=CPoint(0,1);
			return true;
		}
		if(key==KEY_LEFT && direction.x!=1){
			direction=CPoint(-1,0);
			return true;
		}
		if(key==KEY_RIGHT && direction.x!=-1){
			direction=CPoint(1,0);
			return true;
		}
		
		if(key==-1){
			time++;
			if(time>level){
				move_snake();
				time=0;
				return true;
			}
		}
	}

	return false;
}

void CSnake::reset_game(){
	stan=RESTART;
	snake.clear();
	snake.push_back(CPoint(5,5));
	snake.push_back(CPoint(4,5));
	snake.push_back(CPoint(3,5));
	
	direction = CPoint(1,0);
	place_food();
	points = 0;
	level = NumberOfLevels;
	
	
}
void CSnake::game_over(){
	stan=END;
}

void CSnake::place_food(){
	int height_size=geom.size.y - 2;
	int width_size=geom.size.x - 2;
	int x=geom.topleft.x+1;
	int y=geom.topleft.y+1;
	is_end=false;
	while(!is_end){
		is_end=true;
		food.x=(rand() % width_size-1) + 1;
		food.y=(rand() % height_size-1) + 1;
		
		for(size_t i=0;i < snake.size();i++){
			if(snake[i].x==food.x && snake[i].y==food.y){
				is_end=false;
				break;
			}
		}
	}
	
	
}
void CSnake::move_snake(){
	CPoint position = snake[0];
	position.x += direction.x;
	position.y +=direction.y;
	 
	int height_size=geom.size.y - 3;
	int width_size=geom.size.x - 3;
	for(size_t i=1;i<snake.size()-2;i++){
		if(position.x==snake[i].x && position.y==snake[i].y){
			game_over();
			return;
		}
	}
	
	if(position.x < 0) position.x = width_size;
	else if(position.x > width_size) position.x = 1;

    if(position.y < 0) position.y = height_size;
    else if(position.y > height_size) position.y = 1;
    
	if(position.x==food.x && position.y==food.y){
		snake.insert(snake.begin(),position);
		points++;
		place_food();
		if(points%3==0 && level>1) level--;
	} else{
		snake.insert(snake.begin(),position);
		snake.pop_back();
	}
}

