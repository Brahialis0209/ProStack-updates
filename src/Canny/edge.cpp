#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <stdio.h>

using namespace cv;
using namespace std;

int edgeThresh = 1;
int edgeThreshScharr=1;

Mat image, gray, gray_res, blurImage, edge1, edge2, cedge;
string filename;
string out_name;

const char* window_name1 = "Edge map : Canny default (Sobel gradient)";
const char* window_name2 = "Edge map : Canny with custom gradient (Scharr)";

// define a trackbar callback
static void onTrackbar(int, void*)
{
    blur(gray, blurImage, Size(3,3));

    // Run the edge detector on grayscale
    Canny(blurImage, edge1, edgeThresh, edgeThresh*3, 3);
    cedge = Scalar::all(0);

    image.copyTo(cedge, edge1);
    //imshow(window_name1, cedge);

    /// Canny detector with scharr
    Mat dx,dy;
    Scharr(blurImage,dx,CV_16S,1,0);
    Scharr(blurImage,dy,CV_16S,0,1);
    Canny( dx,dy, edge2, edgeThreshScharr, edgeThreshScharr*3 );
    /// Using Canny's output as a mask, we display our result
    cedge = Scalar::all(0);
    image.copyTo(cedge, edge2);
    //imshow(window_name2, cedge);
	cvtColor(cedge, gray_res, COLOR_BGR2GRAY);
	imwrite(out_name, gray_res);
}

static void help()
{
    printf("\nThis sample demonstrates Canny edge detection\n"
           "Call:\n"
           "    /.edge [image_name -- Default is ../data/fruits.jpg]\n\n");
}

const char* keys =
{
    "{help h||}{@image |../data/fruits.jpg|input image name}"
};


string without_cov(const string &str) {
	string newStr;
	char a = '\'';
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] != a)
			newStr.append(1, str[i]);
	return newStr;
}


int main( int argc, const char** argv )
{
	/*
    CommandLineParser parser(argc, argv, keys);
    if (parser.has("help"))
    {
        help();
        return 0;
    }
    string filename = parser.get<string>(0);
	*/
	string need_params[2];
	need_params[0] = argv[argc - 2];
	need_params[1] = argv[argc - 1];
	filename = without_cov(need_params[0]);
	out_name = without_cov(need_params[1]);

    image = imread(filename, 1);
    if(image.empty())
    {
        printf("Cannot read image file: %s\n", filename.c_str());
        help();
        return -1;
    }
    cedge.create(image.size(), image.type());
    cvtColor(image, gray, COLOR_BGR2GRAY);

    // Create a window
    namedWindow(window_name1, 1);
    namedWindow(window_name2, 1);

    // create a toolbar
    createTrackbar("Canny threshold default", window_name1, &edgeThresh, 100, onTrackbar);
    createTrackbar("Canny threshold Scharr", window_name2, &edgeThreshScharr, 400, onTrackbar);

    // Show the image
    onTrackbar(0, 0);

    // Wait for a key stroke; the same function arranges events processing
    //waitKey(0);

    return 0;
}
