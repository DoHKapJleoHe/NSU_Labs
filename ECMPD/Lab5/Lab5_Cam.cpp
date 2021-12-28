#include <stdio.h>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>

#include <sys/times.h>
#include <unistd.h>


using namespace cv;
using namespace std;

int main()
{
    struct tms start_change, end_change, start, end, read_start, read_end, show_start, show_end;
    long clocks_per_sec = sysconf(_SC_CLK_TCK);

    // РёРЅРёС†РёР°Р»РёР·РёСЂСѓРµРј Р·Р°С…РІР°С‚ РІРёРґРµРѕ, РёСЃРїРѕР»СЊР·СѓСЏ РґС„РѕР»С‚РЅСѓСЋ РєР°РјРµСЂСѓ
    VideoCapture cap(0);
    if(!cap.isOpened())
    {
        std::cerr << "ERROR! Unable to open the camera\n";
        return 1;
    }
    
    long clock = 0;
    Mat frame, frame_gray, frame_gray_rotated; // РєРѕРЅС‚РµР№РЅРµСЂ РґР»СЏ РёР·РѕР±СЂР°Р¶РµРЅРёР№
    while(1)
    {
        times(&start);

        times(&read_start);
        cap.read(frame);
        times(&read_end);
        
        times(&start_change);
        frame_gray = frame.clone();
        cvtColor(frame_gray, frame_gray, COLOR_BGR2GRAY);
        flip(frame_gray, frame_gray_rotated, 1);
        times(&end_change);

        times(&show_start);
        imshow("APP1", frame);
        times(&show_end);
        
        imshow("APP2", frame_gray_rotated);
        char key = (char) waitKey(30);
        if (key == 'q' || key == 27)
        {
            break;
        }

        times(&end);
        clock = end.tms_utime - start.tms_utime;
    }

long changeTime = end_change.tms_utime - start_change.tms_utime;
long showTime = show_end.tms_utime - show_start.tms_utime;
long readTime = read_end.tms_utime - read_start.tms_utime;

cout << "Р’СЂРµРјСЏ РІРІРѕРґР°: " << (double)readTime / clocks_per_sec << endl;
cout << "Р’СЂРµРјСЏ РёР·РјРµРЅРµРЅРёСЏ: " << (double)changeTime / clocks_per_sec << endl;
cout << "Р’СЂРµРјСЏ РїРѕРєР°Р·Р°: " << (double)showTime / clocks_per_sec << endl;
cout <<"FPS: " << (double)clock / clocks_per_sec << endl;

cap.release();
destroyAllWindows();
return 0;
}
