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
    g_pImgManager->AddImage("gem", "images/img-gem.bmp", 25, 9);
    m_sprGem->SetBodyImg(g_pImgManager->FindImage("gem"));
    m_sprGem->SetupForSprites(5, 1);
}

void MapGenerator::Setup(string MapFilename)
{
    m_szFilename = MapFilename;
    m_nMapSize = { 3000, 900 };
    m_nMapCol = 20;
    m_nMapRow = 6;
    //  read map data
    ifstream i;
    i.open("data/map.txt", ios_base::in);
    string szTemp;
    while (i >> szTemp)
    {
        m_szMapData.append(szTemp);
    }
    i.close();

    m_nTileSize = 150;

    g_pImgManager->AddImage("worldmap"
                            , 3000
                            , 900);

    m_imgWorldMap = g_pImgManager->FindImage("worldmap");
    RECT rt = { 0, 0, m_imgWorldMap->GetWidth(), m_imgWorldMap->GetHeight() };
    FillRect(m_imgWorldMap->GetMemDC(), &rt, m_brushTransparent);

    //  bg tile setup "m_sprtile[4]"
    for (int row = 0; row < m_nMapRow; row++)
    {
        for (int col = 0; col < m_nMapCol; col++)
        {
            m_sprTile->GetBodyImg()->SpritesRender(m_imgWorldMap->GetMemDC()
                                        , col * m_nTileSize
                                        , row * m_nTileSize
                                        , m_nTileSize
                                        , m_nTileSize
                                        , 4, 0
                                        , 255);
            char logMsg[256];
            sprintf(logMsg, "col : %d / row : %d", col, row);
            g_pLogManager->WriteLog(EL_DEBUG, logMsg);
        }
    }

    //  tile setup each case
    /*
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
            case TILE_EMPTY:
            {
                break;
            }
            case WALL:
            {
                tImage = *m_sprTile;
                tImage.SetFrameX(0);
                break;
            }
            case SPIKE_LEFT:
            case SPIKE_TOP:
            case SPIKE_RIGHT:
            case SPIKE_BOTTOM:
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
            case GEM_AMETHYST:
            case GEM_GOLD:
            case GEM_JADE:
            case GEM_EMERALD:
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
                tImage.GetBodyImg()->SpritesRender(m_imgWorldMap->GetMemDC()
                    , col * m_nTileSize * m_dMagnifier
                    , row * m_nTileSize * m_dMagnifier
                    , m_nTileSize * m_dMagnifier
                    , m_nTileSize * m_dMagnifier
                    , tImage.GetFrameX(), tImage.GetFrameY()
                    , 255);
            }
            else
            {
                break;
            }
        }
    }
    */
    SaveMap(m_imgWorldMap->GetMemDC());
}

void MapGenerator::SaveMap(HDC hdc)
{
    HDC h_screen_dc = hdc;

    // ���� ���� �ػ󵵸� ��´�.
    int width = 3000;
    int height = 900;

    // DIB�� ������ �����Ѵ�.
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

    // DIB�� ���� �̹��� ��Ʈ ������ ������ ������ ����
    BYTE *p_image_data = NULL;

    // dib_define�� ���ǵ� �������� DIB�� �����Ѵ�.
    HBITMAP h_bitmap = ::CreateDIBSection(h_screen_dc, &dib_define, DIB_RGB_COLORS, (void **)&p_image_data, 0, 0);

    // �̹����� �����ϱ� ���ؼ� ���� DC�� �����Ѵ�. ���� DC������ ���������� ��Ʈ�ʿ� �����Ͽ�
    // �̹��� ������ ���� �� ���� �����̴�.
    HDC h_memory_dc = ::CreateCompatibleDC(h_screen_dc);

    // ���� DC�� �̹����� ������ ��Ʈ���� �����Ѵ�.
    HBITMAP h_old_bitmap = (HBITMAP)::SelectObject(h_memory_dc, h_bitmap);

    // ���� ��ũ�� ȭ���� ĸ���Ѵ�.
    ::BitBlt(h_memory_dc, 0, 0, width, height, h_screen_dc, 0, 0, SRCCOPY);

    // ������ ��Ʈ������ �����Ѵ�.
    ::SelectObject(h_memory_dc, h_old_bitmap);

    // ���� DC�� �����Ѵ�.
    DeleteDC(h_memory_dc);

    // DIB ������ ��� ������ �����Ѵ�.
    BITMAPFILEHEADER dib_format_layout;
    ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
    dib_format_layout.bfType = *(WORD*)"BM";
    dib_format_layout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dib_define.bmiHeader.biSizeImage;
    dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // DIB ������ �����Ѵ�.
    string szFilename = "images/map.bmp";
    FILE *p_file = fopen(szFilename.c_str(), "wb");
    if (p_file != NULL) {
        fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);
        fwrite(&dib_define, 1, sizeof(BITMAPINFOHEADER), p_file);
        fwrite(p_image_data, 1, dib_define.bmiHeader.biSizeImage, p_file);
        fclose(p_file);
    }

    // ����ߴ� ��Ʈ�ʰ� DC �� �����Ѵ�.
    if (NULL != h_bitmap) DeleteObject(h_bitmap);
    if (NULL != h_screen_dc) ::ReleaseDC(NULL, h_screen_dc);
}
