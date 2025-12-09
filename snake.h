#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include <vector>
class CSnake:public CFramedWindow
{
private:
enum State{
	RESTART,
	HELP,
	PAUSE,
	RESUME,
	END
};
State stan;
CPoint direction;
CPoint food;
std::vector<CPoint> snake;
int points;
int time;
int level;
int snake_len;
bool is_end;

void reset_game();
void move_snake();
void place_food();
void game_over();

public:
  CSnake(CRect r, char _c = ' ');
  virtual void paint();
  virtual bool handleEvent(int key);

};

#endif
