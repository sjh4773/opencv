# opencv C++

        #include <opencv2/opencv.hpp>
        #include <iostream>
        
        using namespace cv;
        using namespace std;
        
        int main()
        {
            
            
            // 이미지 출력
        
            Mat img_src;
            img_src = imread("cybertruck.PNG", IMREAD_COLOR);
        
            // 이미지를 그레이영상으로 바꿈
            Mat img_gray;
            cvtColor(img_src, img_gray, COLOR_BGR2GRAY);
        
            imshow("Src", img_src);
            imshow("gray", img_gray);
        
            waitKey(0);
            destroyAllWindows();
        
        
            
            
            
            // 동영상 출력
        
            Mat frame;
            VideoCapture cap("ass.webm");
        
            if (!cap.isOpened()) {
                cout << "동영상을 열 수 없습니다." << endl;
                return -1;
            }
        
            while (1) {
                bool ret = cap.read(frame);
        
                imshow("Video", frame);
                int key = waitKey(33);
                if (key == 27) // ESC 키
                    break;
            }
            cap.release();
            destroyAllWindows();
        
            
            
            
            
            // 동영상 흑백 변환
        
            Mat frame;
            Mat frame_gray;
            VideoCapture cap("ass.webm");
        
            if (!cap.isOpened()) {
                cout << "동영상을 열 수 없습니다." << endl;
                return -1;
            }
        
            while (1) {
                bool ret = cap.read(frame);
                cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        
        
                imshow("Video", frame_gray);
                int key = waitKey(33);
                if (key == 27) // ESC 키
                    break;
            }
            cap.release();
            destroyAllWindows();
        
        
            
            
            
            // 이미지 45도 회전
        
            Mat img_src;
            img_src = imread("cybertruck.PNG", IMREAD_COLOR);
            int height = img_src.rows;
            int width = img_src.cols;
        
            Mat matrix = getRotationMatrix2D(
                Point(width / 2, height / 2), // 회전할 때 중심점
                45, // 회전 각도
                1); // 이미지 배율
        
            Mat img_dst;
            warpAffine(img_src, img_dst, matrix, Size(width, height));
        
            imshow("Src", img_src);
            imshow("Rotation Result", img_dst);
        
            waitKey(0);
            destroyAllWindows();
        
            
        
        
            // 이미지 Flip
            // 0: 상하대칭, 1: 좌우대칭
        
            Mat img_src;
            img_src = imread("cybertruck.PNG", IMREAD_COLOR);
        
            Mat img_dst;
            flip(img_src, img_dst, 0);
        
        
            imshow("src", img_src);
            imshow("flip", img_dst);
        
            waitKey();
            destroyAllWindows();
        
        
            
            // 이미지 resize
        
            Mat img_src;
            img_src = imread("cybertruck.PNG", IMREAD_COLOR);
        
            
            Mat img_dst1;
            pyrDown(img_src, img_dst1); // 화면 1/4배 감소
        
            Mat img_dst2;
            pyrUp(img_src, img_dst2, Size(img_src.cols * 2, img_src.rows * 2)); // 화면 4배 확대
        
            // resize(img_src, img_dst1, Size(200, 200), INTER_LINEAR);
            // resize(img_src, img_dst1, Size(), 0.9, 0.2);
        
        
            imshow("Src", img_src);
            imshow("img_down", img_dst1);
            imshow("img_up", img_dst2);
        
            waitKey(0);
            destroyAllWindows();
        
        
        
        
            // 동영상 흑백변환 -> 45도 회전 -> 좌우대칭
        
        
            Mat frame;
            Mat frame_gray;
            VideoCapture cap("ass.webm");
        
        
            if (!cap.isOpened()) {
                cout << "동영상을 열 수 없습니다." << endl;
                return -1;
            }
        
            while (1) {
                bool ret = cap.read(frame);
                int height = frame.rows;
                int width = frame.cols;
                cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        
                Mat matrix = getRotationMatrix2D(
                Point(width / 2, height / 2), // 회전할 때 중심점
                45, // 회전 각도
                1); // 이미지 배율
        
                Mat img_rot;
                warpAffine(frame_gray, img_rot, matrix, Size(width, height));
        
                Mat img_flip;
                flip(img_rot, img_flip, 1); // 좌우 대칭
        
                imshow("Video", img_flip);
                int key = waitKey(33);
                if (key == 27) // ESC 키
                    break;
            }
            cap.release();
            destroyAllWindows();
        
            
        
            
            // 동영상 흑백변환 -> 45도 회전 -> 좌우대칭 -> 화면 크기 1/2로 줄이기
        
        
            Mat frame;
            Mat frame_gray;
            VideoCapture cap("ass.webm");
        
        
            if (!cap.isOpened()) {
                cout << "동영상을 열 수 없습니다." << endl;
                return -1;
            }
        
            while (1) {
                bool ret = cap.read(frame);
                int height = frame.rows;
                int width = frame.cols;
                cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        
                Mat matrix = getRotationMatrix2D(
                Point(width / 2, height / 2), // 회전할 때 중심점
                45, // 회전 각도
                1); // 이미지 배율
                Mat img_rot;
                warpAffine(frame_gray, img_rot, matrix, Size(width, height));
        
                Mat img_flip;
                flip(img_rot, img_flip, 1); // 좌우 대칭
        
                Mat img_resize;
                pyrDown(img_flip, img_resize, Size(img_flip.cols / 2, img_flip.rows / 2)); // 화면 1/2로 변환
        
                imshow("Video", img_resize);
                int key = waitKey(33);
                if (key == 27) // ESC 키
                    break;
            }
            cap.release();
            destroyAllWindows();
            
        
            
            
            
            
            // 동영상 흑백변환 -> 45도 회전 -> 좌우대칭 -> 화면 가로,세로비율을 0.4배
        
        
            Mat frame;
            Mat frame_gray;
            VideoCapture cap("ass.webm");
        
        
            if (!cap.isOpened()) {
                cout << "동영상을 열 수 없습니다." << endl;
                return -1;
            }
        
            while (1) {
                bool ret = cap.read(frame);
                int height = frame.rows;
                int width = frame.cols;
                cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        
                Mat matrix = getRotationMatrix2D(
                Point(width / 2, height / 2), // 회전할 때 중심점
                45, // 회전 각도
                1); // 이미지 배율
                Mat img_rot;
                warpAffine(frame_gray, img_rot, matrix, Size(width, height));
        
                Mat img_flip;
                flip(img_rot, img_flip, 1); // 좌우 대칭
        
                Mat img_resize;
                resize(img_flip, img_resize, Size(), 0.4, 0.4); // 화면 비율 0.4
        
                imshow("Video", img_resize);
                int key = waitKey(33);
                if (key == 27) // ESC 키
                    break;
            }
            cap.release();
            destroyAllWindows();
            
        
        
        
            // 이미지 출력
        
            Mat img_src;
            img_src = imread("cybertruck.PNG", IMREAD_COLOR);
            int height = img_src.rows;
            int width = img_src.cols;
        
            int w1 = width / 4;
            int h1 = height / 4;
        
        
            Mat img_crop;
            img_crop = img_src(Rect(w1, h1, width / 2, height / 2)).clone();
        
            cvtColor(img_crop, img_crop, COLOR_BGR2GRAY);
            cvtColor(img_crop, img_crop, COLOR_GRAY2BGR);
        
            img_crop.copyTo(img_src(Rect(w1, h1, width / 2, height / 2)));
        
            imshow("Src", img_src);
            
        
            waitKey(0);
            destroyAllWindows();
        
            
        
        
            // 이미지에 사각형 그리기
        
            Mat img = imread("chess.jpg", 1);
        
            Mat img_rectangle;
            img.copyTo(img_rectangle);
        
            rectangle(img_rectangle, Rect(Point(60, 370), Point(470, 1250)), Scalar(0, 0, 255), 1, 8, 0);
            rectangle(img_rectangle, Rect(Point(1150, 650), Point(1480, 1200)), Scalar(0, 0, 255), 1, 8, 0);
        
        
            pyrDown(img_rectangle, img_rectangle);
        
            imshow("img",img_rectangle);
            
        
            waitKey(0);
            destroyAllWindows();
        
        
            
            
            // 이미지 출력
        
            
            Mat img_src;
            img_src = imread("chess.PNG", IMREAD_COLOR);
            int height = img_src.rows;
            int width = img_src.cols;
        
            Mat img_crop1;
            img_crop1 = img_src(Rect(30, 200, 200, 600)).clone();
        
            cvtColor(img_crop1, img_crop1, COLOR_BGR2GRAY);
            cvtColor(img_crop1, img_crop1, COLOR_GRAY2BGR);
        
            img_crop1.copyTo(img_src(Rect(30, 200, 200, 600)));
        
            Mat img_crop2;
            img_crop2 = img_src(Rect(400, 260, 570, 330)).clone();
        
            cvtColor(img_crop2, img_crop2, COLOR_BGR2GRAY);
            cvtColor(img_crop2, img_crop2, COLOR_GRAY2BGR);
        
            img_crop2.copyTo(img_src(Rect(400, 260, 570, 330)));
        
        
        
            imshow("Src", img_src);
            
        
            waitKey(0);
            destroyAllWindows();
        
        
        }



	
