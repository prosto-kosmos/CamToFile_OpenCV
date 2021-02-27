#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include "opencv2/core/utility.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <ctype.h>

using namespace cv;
using namespace std;

int GetFPS(VideoCapture cap){
    // Mat frame;
    // for(int i = 0; i < 50; i++){
    //     cap >> frame;
    //     auto start = std::chrono::system_clock::now();
    //     cap >> frame;
    //     auto end = std::chrono::system_clock::now();
    //     std::chrono::duration<double> elapsed_seconds = end-start;
    //     cout<<"fps double: "<<1.0 / elapsed_seconds.count()<<endl;
    //     // int fps = round(1.0 / elapsed_seconds.count());
    // }
    return 10;
}

int main(){
    VideoCapture cap;
    int camNum = 0;
    bool paused = false;
    cap.open(camNum);

    // int codec = cap.get(CAP_PROP_FOURCC); // выбор кодека VideoWriter::fourcc('M', 'P', '4', '2'
    // ('M','P','4','V')('M','P','E','G') ('X','V','I','D'); 
    int codec = VideoWriter::fourcc('M','J','P','G');
    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);
    // int fps = cap.get(CAP_PROP_FPS);
    int fps = GetFPS(cap);
    

    if( !cap.isOpened() )
    {
        cout << "***Could not initialize capturing...***\n";
        cout << "See camNum\n";
        return 0;
    }
    namedWindow( "CamShift Demo", WindowFlags::WINDOW_FULLSCREEN);
    Mat frame;
    int frameInOneFileCounter = 0;
    int durationOneFileSeconds = 5;
    int nameFileCounter = 1;
    string prefix_path = "./video";
    string media_container = ".mkv";
    std::unique_ptr<VideoWriter> video = std::make_unique<VideoWriter>(prefix_path + to_string(nameFileCounter) + media_container, codec, fps, Size(frame_width,frame_height), true);
 
    while(true){
        if( !paused ){
            cap >> frame;
            if( frame.empty() )
                break;
            
            // обработка
            if(fps * durationOneFileSeconds < frameInOneFileCounter){
                video = std::make_unique<VideoWriter>(prefix_path + to_string(nameFileCounter) + media_container, codec, fps, Size(frame_width,frame_height), true);
                nameFileCounter+=1;
                frameInOneFileCounter = 0;
            }
            video->write(frame);
            frameInOneFileCounter += 1;
        }

        resize(frame, frame, Size(960, 540), 100, 100, 1);
        imshow("CamShift Demo", frame);

        // Обработка нажатия клавиш
        char c = (char)waitKey(10);
        if( c == 27 )
            break;
        switch(c)
        {
        case 'p':
            paused = !paused;
            break;
        default:
            ;
        }
    }
    return 0;
}