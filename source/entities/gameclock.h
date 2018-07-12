#ifndef _GAMECLOCK_H_
#define _GAMECLOCK_H_ 

#include "analogdisplay.h"

class GameClock : public AnalogDisplay 
{
public:
    GameClock( VOID );
    ~GameClock( VOID );

    VOID Tick( FLOAT elapsedTime );

    VOID SetLimit( FLOAT limit );
    BOOL AtLimit( VOID );
    VOID Reset( VOID );

private:

    FLOAT mTime;
    FLOAT mLimit;

};

#endif 