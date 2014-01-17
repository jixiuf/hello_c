#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
// http://docs.opencv.org/doc/tutorials/core/discrete_fourier_transform/discrete_fourier_transform.html#discretfouriertransform
// 傅立叶变换 ，
// 这块代码非常不懂，  ， 留待以后再看
using namespace cv;
using namespace std;

static void help(char* progName)
{
    cout << endl
        <<  "This program demonstrated the use of the discrete Fourier transform (DFT). " << endl
        <<  "The dft of an image is taken and it's power spectrum is displayed."          << endl
        <<  "Usage:"                                                                      << endl
        << progName << " [image_name -- default lena.jpg] "                       << endl << endl;
}

int main(int argc, char ** argv)
{
    help(argv[0]);

    const char* filename = argc >=2 ? argv[1] : "in_color.png";

    Mat I = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
    if( I.empty())
        return -1;

    //he performance of a DFT is dependent of the image size. It tends to be the
    //fastest for image sizes that are multiple of the numbers two, three and
    //five. Therefore, to achieve maximal performance it is generally a good
    //idea to pad border values to the image to get a size with such traits. The
    //getOptimalDFTSize() returns this optimal size and we can use the
    //copyMakeBorder() function to expand the borders of an image:
    // 当图片的太小符合某一比例时 ，  进行 傅立叶变换 性能会好很多
    // 所以getOptimalDFTSize 适当的将 图片的宽高加长，
    // 然后再应用
    Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( I.rows );
    int n = getOptimalDFTSize( I.cols ); // on the border add zero values
    std::cout << I.rows<<" "<<I.cols<<" "<<m <<" "<<n << std::endl;
    // 把图片 I copy 到padded中 ， 不足的区域用0补齐
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

    cv::namedWindow("optimalsized");
    cv::imshow("optimalsized" ,padded);

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    dft(complexI, complexI);            // this way the result may fit in the source matrix

    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];

    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
                                            // viewable image form (float between values 0 and 1).

    imshow("Input Image"       , I   );    // Show the result
    imshow("spectrum magnitude", magI);
    waitKey();

    return 0;
}
