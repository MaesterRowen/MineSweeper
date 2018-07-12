#ifndef _ANALOGDISPLAY_H_
#define _ANALOGDISPLAY_H_

#include <strata/strata.h>

#define DIGIT_COUNT     10
#define DIGIT_WIDTH     13.0f
#define DIGIT_HEIGHT    23.0f

class AnalogDisplay
{
public:
    AnalogDisplay( DWORD numDigits, DWORD value = 0UL);
    virtual ~AnalogDisplay( VOID );

    VOID Update(VOID);
    VOID Draw( Strata::Renderer& renderer, DWORD layer  );

    // Helper Methods
    VOID SetPosition( FLOAT x, FLOAT y );

    FLOAT GetX() { return mPosX; }
    FLOAT GetY() { return mPosY; }
    FLOAT GetWidth() { return mDigits * DIGIT_WIDTH; }
    FLOAT GetHeight() { return DIGIT_HEIGHT;}

    VOID SetValue( DWORD value ) { mValue = value; }
    DWORD GetValue( VOID ) { return mValue; }

protected: 
    struct {
        DWORD Handle;
        RECT TextureRect;
    } mTextures[DIGIT_COUNT];

    FLOAT mPosX;
    FLOAT mPosY;
    DWORD mDigits;

    DWORD mValue;
};

#endif