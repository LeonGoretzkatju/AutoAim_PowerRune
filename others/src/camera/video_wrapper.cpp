//
// Created by xixiliadorabarry on 1/24/19.
//

#include "camera/video_wrapper.h"


VideoWrapper::VideoWrapper() {
    video.set(CV_CAP_PROP_BUFFERSIZE,3);
    video.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    video.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    video.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
    video.set(CV_CAP_PROP_AUTO_EXPOSURE,0.25);
    video.set(CV_CAP_PROP_EXPOSURE, 0.005);
    video.open(0);

}

VideoWrapper::~VideoWrapper() = default;


bool VideoWrapper::init() {
    video.set(CV_CAP_PROP_BUFFERSIZE,3);
    video.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    video.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    video.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
    video.set(CV_CAP_PROP_AUTO_EXPOSURE,0.25);
    video.set(CV_CAP_PROP_EXPOSURE, 0.05);
    return video.open(0);
}

bool VideoWrapper::read(cv::Mat &src) {
    return video.read(src);
}
