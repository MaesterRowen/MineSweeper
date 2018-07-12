#include "AnalogDisplay.h"

AnalogDisplay::AnalogDisplay( DWORD numDigits, DWORD startValue /*= 0UL*/)
{
    mPosX = 0.0f;
    mPosY = 0.0f;
    mDigits = numDigits;
    mValue = startValue;

    // Cache Texture Handles and RECTS for recovery later
    for( DWORD idx = 0; idx < DIGIT_COUNT; idx++ )
    {
        std::string name = "Sprites.Display_" + std::to_string(idx);
        mTextures[idx].Handle = Strata::ResourceManager::GetTextureHandle(name);
        const RECT * rect = Strata::ResourceManager::GetTextureRect(mTextures[idx].Handle);
        if( rect ) { 
            mTextures[idx].TextureRect = *(RECT*)rect;
        } else {
            mTextures[idx] = { 0, 0, 0, 0 };
        }
    }
}

AnalogDisplay::~AnalogDisplay( VOID )
{

}

VOID AnalogDisplay::SetPosition( FLOAT x, FLOAT y )
{
    mPosX = x;
    mPosY = y;
}

VOID AnalogDisplay::Draw( Strata::Renderer& renderer, DWORD layer )
{
    // Loop through each digit and draw
    DWORD val = mValue;
    for( DWORD idx = 0; idx < mDigits; idx++ )
    {
        // Break down the number into digits, based on the current digit
        DWORD exp = powf(10.0f, mDigits - idx - 1);
        DWORD digit = val / exp;
        val -= (exp * digit);

        // Determine the dest rect
        RECT destRect; 
        destRect.left = mPosX + idx * DIGIT_WIDTH;
        destRect.right = destRect.left + DIGIT_WIDTH;
        destRect.top = mPosY;
        destRect.bottom = destRect.top + DIGIT_HEIGHT;

        // Color factor
        Strata::COLOR color;
        color.AsDWORD = MAKE_RGBA(255,255,255,255);

        // Draw this digit to the renderer
        renderer.Draw( destRect, mTextures[digit].TextureRect, mTextures[digit].Handle, layer, color );
    }
}