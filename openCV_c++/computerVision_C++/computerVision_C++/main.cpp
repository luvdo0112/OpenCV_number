//==================================�󺧸� ����(������ ����)===========================================
#include <iostream>  
#include <opencv2/core/mat.hpp>  
#include <opencv2/imgcodecs.hpp>  
#include <opencv2/imgproc.hpp>  
#include <opencv2/highgui.hpp>  

using namespace cv;
using namespace std;

int main() {
    Mat img_gray, img_color, img_binary;

    img_gray = imread("labelingTest.png", IMREAD_GRAYSCALE);

    threshold(img_gray, img_binary, 127, 255, THRESH_BINARY);
    cvtColor(img_gray, img_color, COLOR_GRAY2BGR);


    Mat img_labels, stats, centroids;
    int numOfLables = connectedComponentsWithStats(img_binary, img_labels,
        stats, centroids, 8, CV_32S);


    //�󺧸��� �̹����� Ư�� ���� �÷��� ǥ�����ֱ�  
    for (int y = 0; y < img_labels.rows; ++y) {

        int* label = img_labels.ptr<int>(y);
        Vec3b* pixel = img_color.ptr<Vec3b>(y);


        for (int x = 0; x < img_labels.cols; ++x) {


            if (label[x] == 3) {
                pixel[x][2] = 0;
                pixel[x][1] = 255;
                pixel[x][0] = 0;
            }
        }
    }


    //�󺧸� �� �̹����� ���� ���簢������ �ѷ��α� 
    for (int j = 1; j < numOfLables; j++) {
        int area = stats.at<int>(j, CC_STAT_AREA);
        int left = stats.at<int>(j, CC_STAT_LEFT);
        int top = stats.at<int>(j, CC_STAT_TOP);
        int width = stats.at<int>(j, CC_STAT_WIDTH);
        int height = stats.at<int>(j, CC_STAT_HEIGHT);


        rectangle(img_color, Point(left, top), Point(left + width, top + height),
            Scalar(0, 0, 255), 1);

        putText(img_color, to_string(j), Point(left + 20, top + 20),
            FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
    }


    imshow("result", img_color);
    waitKey(0);
}

//// =============================================Ű���� �󺧸�==================================
//#include <opencv2/core/core.hpp> 
//#include <opencv2/highgui/highgui.hpp> 
//#include <opencv2/imgproc/imgproc.hpp>
//
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//void labeling_stats()
//{
//
//	Mat src = imread("dddd.png", IMREAD_GRAYSCALE);
//	resize(src, src, Size(500, 400));
//
//	if (src.empty()) {
//		cerr << "image load error" << endl;
//		return;
//	}
//
//	Mat bin;
//	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
//
//	Mat labels, stats, centroid;
//	int cnt = connectedComponentsWithStats(bin, labels, stats, centroid);
//
//	Mat dst;
//	cvtColor(src, dst, COLOR_GRAY2BGR);
//
//	for (int i = 1; i < cnt; ++i) {
//		int* label = stats.ptr<int>(i);
//
//		if (label[4] < 20) continue;
//		rectangle(dst, Rect(label[0], label[1], label[2], label[3]), Scalar(0, 255, 255));
//	}
//
//	imshow("src", src);
//	imshow("dst", dst);
//
//	waitKey();
//	destroyAllWindows();
//}
//
//int main()
//{
//	Mat image = imread("keyboard.jpg", 0);
//	if (!image.data)
//		return 0;
//
//	resize(image, image, Size(500, 400));
//	//namedWindow("original image"); 
//	//imshow("original image", image); 
//
//	// ������ ��� �� ��� 
//	Mat binaryFixed;
//	Mat binaryAdaptive;
//	threshold(image, binaryFixed, 160, 255, THRESH_BINARY);
//
//	/*
//	������ �Ϻο��� �ؽ�Ʈ�� �����Ǵ� ������ ����
//	�̷��� ������ �غ��ϱ� ���ؼ�
//	�� ȭ���� �̿����� ����ϴ� ���� ���ȭ�� ���
//	��, ������ ���ȭ(Adaptive Threshold)�� ����
//	*/
//	//cv::namedWindow("Fixed Threshold"); 
//	//cv::imshow("Fixed Threshold", binaryFixed); 
//
//
//	/* ���� ���� ���
//	��� ȭ�Ҹ� ��ȸ�ϸ鼭 ������ �̿��� ����� ���
//	*/
//
//	/* �Լ��� �̿��Ͽ� ������ ���ȭ */
//	int blockSize = 21; // �̿� ũ�� 
//	int threshold = 10; //ȭ�Ҹ� (���-��� ��)�� �� 
//
//	adaptiveThreshold(image, // �Է¿��� 
//		binaryAdaptive, // ����ȭ ��� ���� 
//		255, // �ִ� ȭ�� �� 
//		ADAPTIVE_THRESH_MEAN_C, // Adaptive �Լ� 
//		THRESH_BINARY, // ����ȭ Ÿ�� 
//		blockSize, // �̿�ũ�� 
//		threshold); // threshold used 
//
//	cv::namedWindow("Adaptive Threshold");
//	cv::imshow("Adaptive Threshold", binaryAdaptive);
//
//	/* �Լ��� �̿����� �ʰ� ���� ���� */
//	Mat binary = image.clone();
//	int nl = binary.rows; // number of lines 
//	int nc = binary.cols; // total number of elements per line 
//
//	Mat iimage;
//	integral(image, iimage, CV_32S);
//	/*
//	��� ȭ�Ҹ� ��ȸ�ϸ鼭 ������ �̿��� ����� ���
//	�����͸� �̿��Ͽ� ������ ��ȸ
//	*/
//	int halfSize = blockSize / 2;
//	for (int j = halfSize; j < nl - halfSize - 1; j++) {
//
//		// j���� �ּ� ��� 
//		uchar* data = binary.ptr<uchar>(j);
//		int* idata1 = iimage.ptr<int>(j - halfSize);
//		int* idata2 = iimage.ptr<int>(j + halfSize + 1);
//
//		// ���� �� ȭ�� 
//		for (int i = halfSize; i < nc - halfSize - 1; i++) {
//
//			// �� ��� 
//			int sum = (idata2[i + halfSize + 1] - idata2[i - halfSize] - idata1[i + halfSize + 1] + idata1[i - halfSize]) / (blockSize * blockSize);
//			// ������ ���ȭ ���� 
//			if (data[i] < (sum - threshold))
//				data[i] = 0;
//			else
//				data[i] = 255;
//		}
//	}
//	//cv::namedWindow("Adaptive Threshold (integral)"); 
//	//cv::imshow("Adaptive Threshold (integral)", binary); 
//
//
//	/* ���� �����ڸ� �̿��Ͽ� ������ ���ȭ */
//	Mat filtered;
//	Mat binaryFiltered;
//	boxFilter(image, filtered, CV_8U, Size(blockSize, blockSize));
//	filtered = filtered - threshold;
//	binaryFiltered = image >= filtered;
//
//	namedWindow("Adaptive Threshold (filtered)");
//	imshow("Adaptive Threshold (filtered)", binaryFiltered);
//
//	labeling_stats();
//
//	waitKey(0);
//	return 0;
//
//}


// ========================================adaptive thresholding �ǽ�==============================
//#include <opencv2/core/core.hpp> 
//#include <opencv2/highgui/highgui.hpp> 
//#include <opencv2/imgproc/imgproc.hpp>
//
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	Mat image = imread("keyboard.jpg", 0);
//	if (!image.data)
//		return 0;
//
//	resize(image, image, Size(), 0.6, 0.6);
//	namedWindow("original image");
//	imshow("original image", image);
//
//	// ������ ��� �� ��� 
//	Mat binaryFixed;
//	Mat binaryAdaptive;
//	threshold(image, binaryFixed, 160, 255, THRESH_BINARY);
//
//	/*
//	������ �Ϻο��� �ؽ�Ʈ�� �����Ǵ� ������ ����
//	�̷��� ������ �غ��ϱ� ���ؼ�
//	�� ȭ���� �̿����� ����ϴ� ���� ���ȭ�� ���
//	��, ������ ���ȭ(Adaptive Threshold)�� ����
//	*/
//	cv::namedWindow("Fixed Threshold");
//	cv::imshow("Fixed Threshold", binaryFixed);
//
//
//	/* ���� ���� ���
//	��� ȭ�Ҹ� ��ȸ�ϸ鼭 ������ �̿��� ����� ���
//	*/
//
//	/* �Լ��� �̿��Ͽ� ������ ���ȭ */
//	int blockSize = 21; // �̿� ũ�� 
//	int threshold = 10; //ȭ�Ҹ� (���-��� ��)�� �� 
//
//	adaptiveThreshold(image, // �Է¿��� 
//		binaryAdaptive, // ����ȭ ��� ���� 
//		255, // �ִ� ȭ�� �� 
//		ADAPTIVE_THRESH_MEAN_C, // Adaptive �Լ� 
//		THRESH_BINARY, // ����ȭ Ÿ�� 
//		blockSize, // �̿�ũ�� 
//		threshold); // threshold used 
//
//	cv::namedWindow("Adaptive Threshold");
//	cv::imshow("Adaptive Threshold", binaryAdaptive);
//
//	/* �Լ��� �̿����� �ʰ� ���� ���� */
//	Mat binary = image.clone();
//	int nl = binary.rows; // number of lines 
//	int nc = binary.cols; // total number of elements per line 
//
//	Mat iimage; integral(image, iimage, CV_32S);
//	/*
//	��� ȭ�Ҹ� ��ȸ�ϸ鼭 ������ �̿��� ����� ���
//	�����͸� �̿��Ͽ� ������ ��ȸ
//	*/
//	int halfSize = blockSize / 2;
//	for (int j = halfSize; j < nl - halfSize - 1; j++) {
//
//		// j���� �ּ� ��� 
//		uchar* data = binary.ptr<uchar>(j);
//		int* idata1 = iimage.ptr<int>(j - halfSize);
//		int* idata2 = iimage.ptr<int>(j + halfSize + 1);
//
//		// ���� �� ȭ�� 
//		for (int i = halfSize; i < nc - halfSize - 1; i++) {
//
//			// �� ��� 
//			int sum = (idata2[i + halfSize + 1] - idata2[i - halfSize] - idata1[i + halfSize + 1] + idata1[i - halfSize]) / (blockSize * blockSize);
//			// ������ ���ȭ ���� 
//			if (data[i] < (sum - threshold))
//				data[i] = 0;
//			else
//				data[i] = 255;
//		}
//	}
//	cv::namedWindow("Adaptive Threshold (integral)");
//	cv::imshow("Adaptive Threshold (integral)", binary);
//
//
//	/* ���� �����ڸ� �̿��Ͽ� ������ ���ȭ */
//	Mat filtered;
//	Mat binaryFiltered;
//	boxFilter(image, filtered, CV_8U, Size(blockSize, blockSize));
//	filtered = filtered - threshold;
//	binaryFiltered = image >= filtered;
//
//	namedWindow("Adaptive Threshold (filtered)");
//	imshow("Adaptive Threshold (filtered)", binaryFiltered);
//
//	waitKey(0);
//	return 0;
//
//}

// Basic Method
//#include <opencv2/opencv.hpp> 
//#include <opencv2/core.hpp> 
//#include <opencv2/videoio.hpp> 
//#include <opencv2/highgui.hpp> 
//#include <stdio.h> 
//#include <iostream> 
//using namespace cv; 
//using namespace std;
//
//int main() 
//{ 
//	Mat image, thresh; 
//	int thresh_T, low_cnt, high_cnt, low_sum, high_sum, i, j, th; 
//	thresh_T = 200; // �ʱ� threshold �� 
//	th = 10; // �ʱ� threshold�� ���� threshold�� ���� ������ ���� 
//	low_cnt = high_cnt = low_sum = high_sum = 0; 
//	image = imread("111.jpg", 0); 
//	cout << "threshold value:" << thresh_T << endl; 
//	while(1) { 
//		for(j = 0; j < image.rows ; j++) { 
//			for(i = 0; i < image.cols; i ++) { 
//				if(image.at<uchar>(j, i) < thresh_T) { 
//					low_sum += image.at<uchar>(j, i); 
//					low_cnt++; 
//				} else {
//					high_sum += image.at<uchar>(j, i); 
//					high_cnt++; 
//				} 
//			} 
//		} if(abs(thresh_T - (low_sum / low_cnt + high_sum / high_cnt) / 2.0f) < th) 
//		{ 
//			break; 
//		} else { 
//			thresh_T = (low_sum / low_cnt + high_sum / high_cnt) / 2.0f; 
//			cout << "threshold value:" << thresh_T << endl; 
//			low_cnt = high_cnt = low_sum = high_sum = 0; 
//		} 
//	} 
//
//	threshold(image, thresh, thresh_T , 255, THRESH_BINARY); 
//	imshow("Input image", image); 
//	imshow("thresholding", thresh); 
//	waitKey(0); 
//
//}



//// This code is written by Sunita Nayak at BigVision LLC. It is based on the OpenCV project. It is subject to the license terms in the LICENSE file found in this distribution and at http://opencv.org/license.html
//
//// Usage example: ./colorizeImage.out greyscaleImage.png
//
//#include <opencv2/dnn.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace cv::dnn;
//using namespace std;
//
//// the 313 ab cluster centers from pts_in_hull.npy (already transposed)
//static float hull_pts[] = {
//    -90., -90., -90., -90., -90., -80., -80., -80., -80., -80., -80., -80., -80., -70., -70., -70., -70., -70., -70., -70., -70.,
//    -70., -70., -60., -60., -60., -60., -60., -60., -60., -60., -60., -60., -60., -60., -50., -50., -50., -50., -50., -50., -50., -50.,
//    -50., -50., -50., -50., -50., -50., -40., -40., -40., -40., -40., -40., -40., -40., -40., -40., -40., -40., -40., -40., -40., -30.,
//    -30., -30., -30., -30., -30., -30., -30., -30., -30., -30., -30., -30., -30., -30., -30., -20., -20., -20., -20., -20., -20., -20.,
//    -20., -20., -20., -20., -20., -20., -20., -20., -20., -10., -10., -10., -10., -10., -10., -10., -10., -10., -10., -10., -10., -10.,
//    -10., -10., -10., -10., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 10., 10., 10., 10., 10., 10., 10.,
//    10., 10., 10., 10., 10., 10., 10., 10., 10., 10., 10., 20., 20., 20., 20., 20., 20., 20., 20., 20., 20., 20., 20., 20., 20., 20.,
//    20., 20., 20., 30., 30., 30., 30., 30., 30., 30., 30., 30., 30., 30., 30., 30., 30., 30., 30., 30., 30., 30., 40., 40., 40., 40.,
//    40., 40., 40., 40., 40., 40., 40., 40., 40., 40., 40., 40., 40., 40., 40., 40., 50., 50., 50., 50., 50., 50., 50., 50., 50., 50.,
//    50., 50., 50., 50., 50., 50., 50., 50., 50., 60., 60., 60., 60., 60., 60., 60., 60., 60., 60., 60., 60., 60., 60., 60., 60., 60.,
//    60., 60., 60., 70., 70., 70., 70., 70., 70., 70., 70., 70., 70., 70., 70., 70., 70., 70., 70., 70., 70., 70., 70., 80., 80., 80.,
//    80., 80., 80., 80., 80., 80., 80., 80., 80., 80., 80., 80., 80., 80., 80., 80., 90., 90., 90., 90., 90., 90., 90., 90., 90., 90.,
//    90., 90., 90., 90., 90., 90., 90., 90., 90., 100., 100., 100., 100., 100., 100., 100., 100., 100., 100., 50., 60., 70., 80., 90.,
//    20., 30., 40., 50., 60., 70., 80., 90., 0., 10., 20., 30., 40., 50., 60., 70., 80., 90., -20., -10., 0., 10., 20., 30., 40., 50.,
//    60., 70., 80., 90., -30., -20., -10., 0., 10., 20., 30., 40., 50., 60., 70., 80., 90., 100., -40., -30., -20., -10., 0., 10., 20.,
//    30., 40., 50., 60., 70., 80., 90., 100., -50., -40., -30., -20., -10., 0., 10., 20., 30., 40., 50., 60., 70., 80., 90., 100., -50.,
//    -40., -30., -20., -10., 0., 10., 20., 30., 40., 50., 60., 70., 80., 90., 100., -60., -50., -40., -30., -20., -10., 0., 10., 20.,
//    30., 40., 50., 60., 70., 80., 90., 100., -70., -60., -50., -40., -30., -20., -10., 0., 10., 20., 30., 40., 50., 60., 70., 80., 90.,
//    100., -80., -70., -60., -50., -40., -30., -20., -10., 0., 10., 20., 30., 40., 50., 60., 70., 80., 90., -80., -70., -60., -50.,
//    -40., -30., -20., -10., 0., 10., 20., 30., 40., 50., 60., 70., 80., 90., -90., -80., -70., -60., -50., -40., -30., -20., -10.,
//    0., 10., 20., 30., 40., 50., 60., 70., 80., 90., -100., -90., -80., -70., -60., -50., -40., -30., -20., -10., 0., 10., 20., 30.,
//    40., 50., 60., 70., 80., 90., -100., -90., -80., -70., -60., -50., -40., -30., -20., -10., 0., 10., 20., 30., 40., 50., 60., 70.,
//    80., -110., -100., -90., -80., -70., -60., -50., -40., -30., -20., -10., 0., 10., 20., 30., 40., 50., 60., 70., 80., -110., -100.,
//    -90., -80., -70., -60., -50., -40., -30., -20., -10., 0., 10., 20., 30., 40., 50., 60., 70., 80., -110., -100., -90., -80., -70.,
//    -60., -50., -40., -30., -20., -10., 0., 10., 20., 30., 40., 50., 60., 70., -110., -100., -90., -80., -70., -60., -50., -40., -30.,
//    -20., -10., 0., 10., 20., 30., 40., 50., 60., 70., -90., -80., -70., -60., -50., -40., -30., -20., -10., 0.
//};
//
//int main(int argc, char **argv)
//{
//    
//    string imageFileName;
//    // Take arguments from commmand line
//    if (argc < 2)
//    {
//        cout << "Please input the greyscale image filename." << endl;
//        cout << "Usage example: ./colorizeImage.out greyscaleImage.png" << endl;
//        return 1;
//    }
//    
//    imageFileName = argv[1];
//    Mat img = imread(imageFileName);
//    if (img.empty())
//    {
//        cout << "Can't read image from file: " << imageFileName << endl;
//        return 2;
//    }
//    
//    string protoFile = "./models/colorization_deploy_v2.prototxt";
//    string weightsFile = "./models/colorization_release_v2.caffemodel";
//    //string weightsFile = "./models/colorization_release_v2_norebal.caffemodel";
//
//    double t = (double) cv::getTickCount();
//    
//    // fixed input size for the pretrained network
//    const int W_in = 224;
//    const int H_in = 224;
//    Net net = dnn::readNetFromCaffe(protoFile, weightsFile);
//    
//    // setup additional layers:
//    int sz[] = {2, 313, 1, 1};
//    const Mat pts_in_hull(4, sz, CV_32F, hull_pts);
//    Ptr<dnn::Layer> class8_ab = net.getLayer("class8_ab");
//    class8_ab->blobs.push_back(pts_in_hull);
//    Ptr<dnn::Layer> conv8_313_rh = net.getLayer("conv8_313_rh");
//    conv8_313_rh->blobs.push_back(Mat(1, 313, CV_32F, Scalar(2.606)));
//    
//    // extract L channel and subtract mean
//    Mat lab, L, input;
//    img.convertTo(img, CV_32F, 1.0/255);
//    cvtColor(img, lab, COLOR_BGR2Lab);
//    extractChannel(lab, L, 0);
//    resize(L, input, Size(W_in, H_in));
//    input -= 50;
//    
//    // run the L channel through the network
//    Mat inputBlob = blobFromImage(input);
//    net.setInput(inputBlob);
//    Mat result = net.forward();
//    
//    // retrieve the calculated a,b channels from the network output
//    Size siz(result.size[2], result.size[3]);
//    Mat a = Mat(siz, CV_32F, result.ptr(0,0));
//    Mat b = Mat(siz, CV_32F, result.ptr(0,1));
//    resize(a, a, img.size());
//    resize(b, b, img.size());
//    
//    // merge, and convert back to BGR
//    Mat color, chn[] = {L, a, b};
//    merge(chn, 3, lab);
//    cvtColor(lab, color, COLOR_Lab2BGR);
//
//    t = ((double)cv::getTickCount() - t)/cv::getTickFrequency();
//    cout << "Time taken : " << t << " secs" << endl;
//    
//    string str = imageFileName;
//    str.replace(str.end()-4, str.end(), "");
//    str = str+"_colorized.png";
//    
//    color = color*255;
//    color.convertTo(color, CV_8U);
//    imwrite(str, color);
//
//    cout << "Colorized image saved as " << str << endl;
//    
//    return 0;
//}

//#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//
//int main()
//{
//    cv::Mat gray = cv::imread("111.jpg", IMREAD_GRAYSCALE);
//    cv::namedWindow("Gray", 1);
//    cv::imshow("Gray", gray);
//
//    /// Initialize parameters
//    int histSize = 256;    // bin size
//    float range[] = { 0, 255 };
//    const float* ranges[] = { range };
//
//    /// Calculate histogram
//    cv::MatND hist;
//    cv::calcHist(&gray, 1, 0, cv::Mat(), hist, 1, &histSize, ranges, true, false);
//
//    /// Show the calculated histogram in command window
//    double total;
//    total = gray.rows * gray.cols;
//
//    for (int h = 0; h < histSize; h++)
//    {
//        float binVal = hist.at<float>(h);
//        std::cout << " " << binVal;
//    }
//
//    /// Plot the histogram
//    int hist_w = 512;
//    int hist_h = 400;
//    int bin_w = cvRound((double)hist_w / histSize);
//
//    cv::Mat histImage(hist_h, hist_w, CV_8UC1, cv::Scalar(0, 0, 0));
//    cv::normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, cv::Mat());
//
//    for (int i = 1; i < histSize; i++)
//    {
//        line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
//            cv::Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
//            cv::Scalar(255, 0, 0), 2, 8, 0);
//    }
//
//    cv::namedWindow("Result", 1);
//    cv::imshow("Result", histImage);
//
//    cv::waitKey(0);
//
//    return 0;
//}


//#include <opencv2/opencv.hpp>
//
//#include <stdlib.h>
//#include <stdio.h>
//
//using namespace std;
//using namespace cv;
//
///* @ function main */
//int main(int argc, char** argv)
//{
//    /// Load an image
//    cv::Mat image = cv::imread("111.jpg", 1);
//    cv::Mat image_gray;
//
//    /// Copy image
//    image.copyTo(image_gray);
//
//    int nRows = image.rows;
//    int nCols = image.cols;
//
//    /// Convert to gray
//    float fGray = 0.0f;
//    float chBlue, chGreen, chRed;
//
//    for (int j = 0; j < nRows; j++) {
//
//        for (int i = 0; i < nCols; i++) {
//
//            chBlue = (float)(image.at<cv::Vec3b>(j, i)[0]);
//            chGreen = (float)(image.at<cv::Vec3b>(j, i)[1]);
//            chRed = (float)(image.at<cv::Vec3b>(j, i)[2]);
//
//            fGray = 0.2126f * chRed + 0.7152f * chGreen + 0.0722f * chBlue;
//
//            if (fGray < 0.0) fGray = 0.0f;
//            if (fGray > 255.0) fGray = 255.0f;
//
//            image_gray.at<cv::Vec3b>(j, i)[0] = (int)fGray;
//            image_gray.at<cv::Vec3b>(j, i)[1] = (int)fGray;
//            image_gray.at<cv::Vec3b>(j, i)[2] = (int)fGray;
//
//        }
//
//    }
//
//    /// Creates window
//    cv::namedWindow("Image Original", CV_WINDOW_AUTOSIZE);
//    cv::namedWindow("Image Grayed", CV_WINDOW_AUTOSIZE);
//
//    /// Show stuff
//    cv::imshow("Image Original", image);
//    cv::imshow("Image Grayed", image_gray);
//
//    /// Wait until user press some key
//    cv::waitKey();
//
//    return 0;
//}


//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/highgui.hpp>
//
//#include <iostream>
//#include <stdio.h>
//
//using namespace cv;
//using namespace std;
//
//
//int main(int ac, char** av) {
//
//	Mat img = imread("111.jpg", 1); //�ڽ��� �����Ų �̹��� �̸��� �ԷµǾ�� ��, Ȯ���ڱ���
//
//	imshow("img", img);
//	waitKey(0);
//
//	return 0;
//}