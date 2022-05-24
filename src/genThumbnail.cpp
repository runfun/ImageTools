#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <opencv2/opencv.hpp>

void getImages(const std::string);

int main(int argc, char const *argv[])
{
    const std::string path = "/home/runfun/Pictures/MyLibrary";
    getImages(path);
    
    return 0;
}

cv::Mat* generateThumbnail(const std::string path){
    cv::Mat src = cv::imread(path);
    const size_t width = 300;
    size_t height = src.size().height/(src.size().width/width);

    cv::Mat* dst = new cv::Mat(cv::Size(width,height),src.type());

    // cv::resize(src,*dst,dst->size(),cv::InterpolationFlags::INTER_CUBIC);
    // cv::resize(src,*dst,dst->size(),cv::InterpolationFlags::INTER_LANCZOS4);
    cv::resize(src,*dst,dst->size(),cv::InterpolationFlags::INTER_AREA);
    return dst;
}

void getImages(const std::string srcPath){
    if(!std::filesystem::is_directory(srcPath)){
        generateThumbnail(srcPath);
        return;
    }
    const std::string dstPath = srcPath + "-Thumbnails";
    std::filesystem::create_directory(dstPath);

    for (auto & iter : std::filesystem::recursive_directory_iterator(srcPath)){
        const std::string iterPath = iter.path().string();
        const std::string dst = dstPath+iterPath.substr(srcPath.size(), iterPath.size());
        if(std::filesystem::is_directory(iter)){
            std::filesystem::create_directory(dst);
            std::cout << "create directory: " << dst << std::endl;
        }else{
            auto thumbnail = generateThumbnail(iter.path().string());
            cv::imwrite(dst,*thumbnail);
            delete thumbnail;
            thumbnail = nullptr;
            std::cout << "generate thumbnail: " << dst << std::endl;
        }
    }
}