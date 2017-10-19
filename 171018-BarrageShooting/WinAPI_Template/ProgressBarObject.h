#pragma once
class ProgressBarObject
{
private:
    ImageObject*        m_imgBack;      //  Background img
    ImageObject*        m_imgFront;     //  Foreground img
    RECT                m_rt;           //  Draw position
    UnitPos             m_nPos;         //  Center position
    UnitSize            m_nSize;        //  Size
    int                 m_nCurrWidth;   //  Progress bar width

public:
    ProgressBarObject(string szBgImgTag, string szFgImgTag, UnitPos Pos, UnitSize Size);
    ~ProgressBarObject();

#pragma region SET
    void    SetProgress(double DestProgress, double CurrProgress);

#pragma endregion

};

