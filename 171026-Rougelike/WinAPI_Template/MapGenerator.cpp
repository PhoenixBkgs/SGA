#include "stdafx.h"
#include "MapGenerator.h"

MapGenerator::MapGenerator()
{
    m_brushTransparent = CreateSolidBrush(RGB(255, 0, 255));
    LoadImageResources();
}


MapGenerator::~MapGenerator()
{
}

void MapGenerator::LoadImageResources()
{
    m_sprTile = new SpritesObject;
    g_pImgManager->AddImage("tile-cave", "images/tile-cave.bmp", 100, 20);
    m_sprTile->SetBodyImg(g_pImgManager->FindImage("tile-cave"));
    m_sprTile->SetupForSprites(5, 1);

    m_sprObstacle = new SpritesObject;
    g_pImgManager->AddImage("obstacle", "images/img-spike.bmp", 80, 20);
    m_sprObstacle->SetBodyImg(g_pImgManager->FindImage("obstacle"));
    m_sprObstacle->SetupForSprites(4, 1);

    m_sprGem = new SpritesObject;
    g_pImgManager->AddImage("gem", "images/img-gem.bmp", 100, 20);
    m_sprGem->SetBodyImg(g_pImgManager->FindImage("gem"));
    m_sprGem->SetupForSprites(5, 1);
}

void MapGenerator::Setup(string MapFilename)
{
    g_pLogManager->WriteLog(EL_INFO, "Load map data : " + MapFilename);
    m_szFilename = MapFilename;;
    string filepath = "data/";
    filepath.append(m_szFilename);

    m_nMapCol = 0;
    m_nMapRow = 0;

    //  read map data
    bool    isFirst = true;
    ifstream i;
    i.open(filepath, ios_base::in);
    string szTemp;
    while (i >> szTemp)
    {
        if (isFirst)
        {
            m_nMapCol = szTemp.length();
            isFirst = false;
        }
        m_nMapRow++;
        m_szMapData.append(szTemp);
    }

    char logMsg[128];
    sprintf_s(logMsg, "Col : %d / Row : %d", m_nMapCol, m_nMapRow);
    g_pLogManager->WriteLog(EL_INFO, logMsg);

    i.close();
    m_nTileSize = 150;
    m_nMapSize = { m_nMapCol * m_nTileSize, m_nMapRow * m_nTileSize };

    g_pImgManager->AddImage("worldmap"
        , m_nMapSize.w
        , m_nMapSize.h);

    g_pImgManager->AddImage("background"
        , m_nMapSize.w
        , m_nMapSize.h);

    m_imgWorldMap = g_pImgManager->FindImage("worldmap");
    m_imgBackground = g_pImgManager->FindImage("background");

    RECT rt = { 0, 0, m_imgWorldMap->GetWidth(), m_imgWorldMap->GetHeight() };
    FillRect(m_imgWorldMap->GetMemDC(), &rt, m_brushTransparent);

    //  bg tile setup "m_sprtile[4]"
    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 20; col++)
        {
            m_sprTile->GetBodyImg()->TileRender(m_imgBackground->GetMemDC()
                , col * m_nTileSize, row * m_nTileSize
                , m_nTileSize, m_nTileSize
                , 4, 0
                , 255);
        }
    }

    //  tile setup each case
    TILE_TYPE tileType;
    int idx = 0;
    for (int row = 0; row < m_nMapRow; row++)
    {
        for (int col = 0; col < m_nMapCol; col++)
        {
            SpritesObject tImage;
            tImage.SetBodyImg(NULL);
            char tCh = m_szMapData.at(idx);
            int tNum = atoi(&tCh);
            tileType = (TILE_TYPE)tNum;
            idx++;
            switch (tileType)
            {
            case TILE_EMPTY:    //  0
            {
                break;
            }
            case WALL:          //  1
            {
                tImage = *m_sprTile;
                tImage.SetFrameX(0);
                break;
            }
            case SPIKE_LEFT:    //  2
            case SPIKE_TOP:     //  3
            case SPIKE_RIGHT:   //  4
            case SPIKE_BOTTOM:  //  5
            {
                tImage = *m_sprObstacle;
                switch (tileType)
                {
                case SPIKE_LEFT:
                    tImage.SetFrameX(0);
                    break;
                case SPIKE_TOP:
                    tImage.SetFrameX(1);
                    break;
                case SPIKE_RIGHT:
                    tImage.SetFrameX(2);
                    break;
                case SPIKE_BOTTOM:
                    tImage.SetFrameX(3);
                    break;
                }
                break;
            }
            case GEM_AMETHYST:  //  6
            case GEM_GOLD:      //  7
            case GEM_JADE:      //  8
            case GEM_EMERALD:   //  9
            {
                tImage = *m_sprGem;
                switch (tileType)
                {
                case GEM_AMETHYST:
                    tImage.SetFrameX(0);
                    break;
                case GEM_GOLD:
                    tImage.SetFrameX(1);
                    break;
                case GEM_JADE:
                    tImage.SetFrameX(2);
                    break;
                case GEM_EMERALD:
                    tImage.SetFrameX(3);
                    break;
                }
                break;
            }
            }
            if (tImage.GetBodyImg() != NULL)
            {
                tImage.GetBodyImg()->TileRender(m_imgWorldMap->GetMemDC()
                    , col * m_nTileSize, row * m_nTileSize
                    , m_nTileSize, m_nTileSize
                    , tImage.GetFrameX(), tImage.GetFrameY()
                    , 255);
            }
        }
    }

    SaveMap(m_imgWorldMap->GetMemDC(), "map.bmp");     //  foreground image
    SaveMap(m_imgBackground->GetMemDC(), "bg.bmp");   //  background image
}

void MapGenerator::SaveMap(HDC hdc, string Filename)
{
    HDC h_screen_dc = hdc;

    // 현재 맵의 해상도를 얻는다.
    int width = m_nMapSize.w;
    int height = m_nMapSize.h;

    // DIB의 형식을 정의한다.
    BITMAPINFO dib_define;
    dib_define.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    dib_define.bmiHeader.biWidth = width;
    dib_define.bmiHeader.biHeight = height;
    dib_define.bmiHeader.biPlanes = 1;
    dib_define.bmiHeader.biBitCount = 24;
    dib_define.bmiHeader.biCompression = BI_RGB;
    dib_define.bmiHeader.biSizeImage = (((width * 24 + 31) & ~31) >> 3) * height;
    dib_define.bmiHeader.biXPelsPerMeter = 0;
    dib_define.bmiHeader.biYPelsPerMeter = 0;
    dib_define.bmiHeader.biClrImportant = 0;
    dib_define.bmiHeader.biClrUsed = 0;

    // DIB의 내부 이미지 비트 패턴을 참조할 포인터 변수
    BYTE *p_image_data = NULL;

    // dib_define에 정의된 내용으로 DIB를 생성한다.
    HBITMAP h_bitmap = ::CreateDIBSection(h_screen_dc, &dib_define, DIB_RGB_COLORS, (void **)&p_image_data, 0, 0);

    // 이미지를 추출하기 위해서 가상 DC를 생성한다. 메인 DC에서는 직접적으로 비트맵에 접근하여
    // 이미지 패턴을 얻을 수 없기 때문이다.
    HDC h_memory_dc = ::CreateCompatibleDC(h_screen_dc);

    // 가상 DC에 이미지를 추출할 비트맵을 연결한다.
    HBITMAP h_old_bitmap = (HBITMAP)::SelectObject(h_memory_dc, h_bitmap);

    // 현재 스크린 화면을 캡쳐한다.
    ::BitBlt(h_memory_dc, 0, 0, width, height, h_screen_dc, 0, 0, SRCCOPY);

    // 본래의 비트맵으로 복구한다.
    ::SelectObject(h_memory_dc, h_old_bitmap);

    // 가상 DC를 제거한다.
    DeleteDC(h_memory_dc);

    // DIB 파일의 헤더 내용을 구성한다.
    BITMAPFILEHEADER dib_format_layout;
    ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
    dib_format_layout.bfType = *(WORD*)"BM";
    dib_format_layout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dib_define.bmiHeader.biSizeImage;
    dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // DIB 파일을 생성한다.
    string szFilepath = "images/";
    szFilepath.append(Filename);
    FILE *p_file = fopen(szFilepath.c_str(), "wb");
    if (p_file != NULL) {
        fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);
        fwrite(&dib_define, 1, sizeof(BITMAPINFOHEADER), p_file);
        fwrite(p_image_data, 1, dib_define.bmiHeader.biSizeImage, p_file);
        fclose(p_file);
    }

    // 사용했던 비트맵과 DC 를 해제한다.
    if (NULL != h_bitmap) DeleteObject(h_bitmap);
    if (NULL != h_screen_dc) ::ReleaseDC(NULL, h_screen_dc);
}