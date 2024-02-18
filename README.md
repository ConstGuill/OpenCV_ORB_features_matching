# OpenCV_ORB_features_matching
## Image Matching using ORB Features

This C++ program demonstrates image matching using the OpenCV library with ORB (Oriented FAST and Rotated BRIEF) features. The code reads two images, namely a testing image and a training image, and performs the following steps:

1. **Image Loading and Rotation:** Loads the testing and training images, and rotates them 90 degrees clockwise to account for potential orientation differences.

2. **Feature Detection and Description:** Utilizes the ORB feature detector to find keypoints and computes descriptors for both images.

3. **Descriptor Matching:** Matches descriptors between the testing and training images using the BruteForce-Hamming descriptor matcher.

4. **Filtering Good Matches:** Filters matches based on distance criteria and draws only the good matches.

5. **Output Image:** Saves the resulting image with good matches as "goodmatch_image.png."

## Dependencies
- **OpenCV:** Ensure that OpenCV is installed on your system.

## Usage
1. Place the test image at the specified path (`TESTING_PATH`).
2. Place the training image at the specified path (`TRAINING_PATH`).
3. Compile and run the program.

```bash
g++ -o image_matching image_matching.cpp `pkg-config opencv --cflags --libs`
./image_matching
```

## Note
- The program uses ORB features and the BruteForce-Hamming matcher for simplicity. Adjust the parameters and algorithms based on your specific use case.
- Ensure OpenCV is installed and configured correctly in your build environment.
- The resulting image with good matches is saved as "goodmatch_image.png."

Feel free to modify the code to suit your requirements or integrate additional functionalities.