#pragma once
#include "SingletonBase.h"
#include "ImageObject.h"

#define g_pImgManager ImageManager::GetInstance()
/*
Map : dictionary(Key - Value)
Key = first
Value = second
*/

class ImageManager : public SingletonBase<ImageManager>
{
private:
    map<string, ImageObject*>               m_mapImage;
    map<string, ImageObject*>::iterator     m_mapIter;

public:
    ImageObject* AddImage(string Key, int Width, int Height);
    ImageObject* AddImage(string Key, const char* Filename, int Width, int Height);

    //  Search image and remove
    ImageObject* FindImage(string Key);
    void DeleteImage(string Key);
    void DeleteImageAll();

    void Render(string Key, HDC hdc);
    void Render(string Key, HDC hdc, UnitPos DestPos);
	void Render(string Key, HDC hdc, int destX, int destY, int destW, int destH, int srcX, int srcY, int srcW, int srcH, int alpha);
};