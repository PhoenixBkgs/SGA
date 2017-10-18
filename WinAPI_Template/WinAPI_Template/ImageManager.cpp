#include "stdafx.h"
#include "ImageManager.h"


ImageObject * ImageManager::AddImage(string Key, int Width, int Height)
{
    ImageObject* image = AddImage(Key, "", Width, Height);

    return image;
}

ImageObject * ImageManager::AddImage(string Key, const char * Filename, int Width, int Height)
{
    //  overlapping check by tagname
    ImageObject* image = FindImage(Key);
    if (image == NULL)
    {
        image = new ImageObject;
        image->Setup(Filename, Width, Height);
        m_mapImage.insert(pair<string, ImageObject*>(Key, image));
        //m_mapImage.insert(make_pair(Key, image));     //  other way for insert
    }

    return image;
}

ImageObject * ImageManager::FindImage(string Key)
{
    m_mapIter = m_mapImage.find(Key);
    //  Find correct
    if (m_mapIter != m_mapImage.end())
        return m_mapIter->second;
    else
        return NULL;
}

void ImageManager::DeleteImage(string Key)
{
    m_mapIter = m_mapImage.find(Key);
    if (m_mapIter != m_mapImage.end())
    {
        //  release memory of image
        SAFE_DELETE(m_mapIter->second);

        //  erase map data
        m_mapImage.erase(Key);
    }
}

void ImageManager::DeleteImageAll()
{
    m_mapIter = m_mapImage.begin();
    while (m_mapIter != m_mapImage.end())
    {
        SAFE_DELETE(m_mapIter->second);
        m_mapIter = m_mapImage.erase(m_mapIter);
    }
}

void ImageManager::Render(string Key, HDC hdc)
{
    ImageObject* image = FindImage(Key);
    if (image)
    {
        image->Render(hdc);
    }
}
