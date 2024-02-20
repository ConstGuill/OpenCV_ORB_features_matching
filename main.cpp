#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

#define TESTING_PATH "testing.png"
#define TRAINING_PATH "training.png"

using namespace cv;
using namespace std;

Mat rotateImg(Mat src, double angle);

int main()
{
    Mat img_match;
    Mat img_goodmatch;
    Mat testing_img = imread(TESTING_PATH, IMREAD_COLOR);
    Mat training_img = imread(TRAINING_PATH, IMREAD_COLOR);
    double min_dist = 10000, max_dist = 0;

    if (testing_img.empty())
    {
        cout << "Test Image File Not Found" << endl;
        return -1;
    }
    else if (training_img.empty())
    {
        cout << "Train Image File Not Found" << endl;
        return -1;
    }

    rotate(testing_img, testing_img, ROTATE_90_CLOCKWISE);
    rotate(training_img, training_img, ROTATE_90_CLOCKWISE);

    vector<KeyPoint> keypoints_1, keypoints_2;
    Mat descriptors_1, descriptors_2;
    Ptr<FeatureDetector> detector = ORB::create();
    Ptr<DescriptorExtractor> descriptor = ORB::create();
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");

    detector->detect(testing_img, keypoints_1);
    detector->detect(training_img, keypoints_2);
    descriptor->compute(testing_img, keypoints_1, descriptors_1);
    descriptor->compute(training_img, keypoints_2, descriptors_2);

    vector<DMatch> matches;
    matcher->match(descriptors_1, descriptors_2, matches);

    for (int i = 0; i < descriptors_1.rows; i++)
    {
        double dist = matches[i].distance;
        if (dist < min_dist)
            min_dist = dist;
        if (dist > max_dist)
            max_dist = dist;
    }

    printf("-- Distance maximale : %f \n", max_dist);
    printf("-- Distance minimale : %f \n", min_dist);

    vector<DMatch> good_matches;
    for (int i = 0; i < descriptors_1.rows; i++)
    {
        if (matches[i].distance <= max(2 * min_dist, 30.0))
        {
            good_matches.push_back(matches[i]);
        }
    }

    drawMatches(testing_img, keypoints_1, training_img, keypoints_2, good_matches, img_goodmatch);
    rotate(img_goodmatch, img_goodmatch, ROTATE_90_COUNTERCLOCKWISE);
    imwrite("goodmatch_image.png", img_goodmatch);
    return 0;
}