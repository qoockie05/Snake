#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"

class CSnake:public CFramedWindow
{
private:
enum State{
	HELP,
	PAUSE,
	RESUME
};
State stan;

public:
  CSnake(CRect r, char _c = ' ');
  virtual void paint();
  virtual bool handleEvent(int key);

};

#endif
