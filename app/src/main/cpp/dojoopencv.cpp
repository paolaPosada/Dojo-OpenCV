
#include <jni.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/objdetect.hpp>
#include <vector>
#include <string>

using namespace cv;

extern "C" {
JNIEXPORT void JNICALL
Java_co_edu_udea_compumovil_gr0120221_dojoopencv_MainActivity_FindFeatures(JNIEnv *jniEnv, jobject,
                                                                           jlong imGray,
                                                                           jlong imRGB) {
    Mat *mGray = (Mat *) imGray;
    Mat *mRGB = (Mat *) imRGB;

    std::vector<Point2f> corners;
    goodFeaturesToTrack(*mGray, corners, 25, 0.01, 10, Mat(), 3, false);

    for (int i = 0; i < corners.size(); i++) {
        circle(*mRGB, corners[i], 10, Scalar(0, 255, 0), 2);
    }
}

CascadeClassifier face_cascade;

JNIEXPORT void JNICALL
Java_co_edu_udea_compumovil_gr0120221_dojoopencv_MainActivity_InitDetector(JNIEnv *jniEnv, jobject,
                                                                           jstring jFilePath) {
    const char *jnamestr = jniEnv->GetStringUTFChars(jFilePath, NULL);
    std::string filePath(jnamestr);
    face_cascade.load(filePath);
}
JNIEXPORT void JNICALL
Java_co_edu_udea_compumovil_gr0120221_dojoopencv_MainActivity_DetectFaces(JNIEnv *jniEnv, jobject,
                                                                          jlong imGray,
                                                                          jlong imRGB) {
    Mat *mGray = (Mat *) imGray;
    Mat *mRGB = (Mat *) imRGB;

    std::vector<Rect> faces;
    face_cascade.detectMultiScale(*mGray, faces);

    for (int i = 0; i < faces.size(); i++) {
        rectangle(*mRGB, Point(faces[i].x, faces[i].y),
                  Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height),
                  Scalar(0, 255, 0), 2);
    }

}

}

