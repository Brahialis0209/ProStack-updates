#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

class Param_line 
{
public:

	bool param_parser(int argc, const char** argv) {
		int k1, k2;
		int sigma;
		double edgeThresh1;
		double edgeThresh2;
		if (argc == 0) return false;
		k1 = stoi(argv[2]);
		k2 = stoi(argv[3]);
		sigma = stoi(argv[4]);
		edgeThresh1 = stod(argv[5]);
		edgeThresh2 = stod(argv[6]);
		this->k1 = k1;
		this->k2 = k2;
		this->sigma = sigma;
		this->edgeThresh1 = edgeThresh1;
		this->edgeThresh2 = edgeThresh2;
		return true;
	}
	int k1, k2;
	int sigma;
	double edgeThresh1;
	double edgeThresh2;
};


string file_name_parser(const string &str) {
	string newStr;
	char a = '\'';
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] != a)
			newStr.append(1, str[i]);
	return newStr;
}


Mat canny_work(Mat & image, Param_line & canny_params) {
	Mat cedge, gray, blur_gaus, gray_res;
	cedge.create(image.size(), image.type());
	GaussianBlur(image, blur_gaus, Size(canny_params.k1,canny_params.k2), canny_params.sigma);
	Canny(blur_gaus, cedge, canny_params.edgeThresh1, canny_params.edgeThresh2);
	return cedge;
}


int main(int argc, const char** argv)
{
	string file_name_params[2];
	vector<Mat> mats;
	vector<Mat> canny_mats;
	Param_line canny_params;
	Mat image;
	string filename;
	string out_name;
	Mat result_mat;
	file_name_params[0] = argv[argc - 2];
	file_name_params[1] = argv[argc - 1];
	filename = file_name_parser(file_name_params[0]);
	out_name = file_name_parser(file_name_params[1]);
	if (!canny_params.param_parser(argc, argv)) {
		printf("Incorrect input parameters\n");
		return -1;
	}
	bool res = imreadmulti(filename,mats);
	if (!res)
	{
		printf("Cannot read image file: %s\n", filename.c_str());
		return -1;
	}
	for (Mat part : mats) {
		//imshow("display window", part);
		//int k = waitKey(0);
		result_mat = canny_work(part, canny_params);
		//imshow("display window", result_mat);
		//k = waitKey(0);
		canny_mats.push_back(result_mat);
	}
	imwritemulti(out_name, canny_mats);
	return 0;
}