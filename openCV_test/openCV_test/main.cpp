#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;


int main(int ac, char** av) {

	Mat img = imread("hanriver.jpg"); //�ڽ��� �����Ų �̹��� �̸��� �ԷµǾ�� ��, Ȯ���ڱ���

	imshow("img", img);
	waitKey(0);

	return 0;
}