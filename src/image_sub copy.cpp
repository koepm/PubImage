/*
#include "pubsubimg/image_sub.hpp"
#include "opencv2/highgui/highgui.hpp"

ImageSubscriber::ImageSubscriber()
: Node("image_subscriber")
{
    subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
        "image", 10,
        std::bind(&ImageSubscriber::image_callback, this, std::placeholders::_1)
    );
}

void ImageSubscriber::image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
{
    cv_bridge::CvImagePtr cv_ptr;

    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        //cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");

    }
    catch(cv_bridge::Exception &e)
    {
        RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        return;
    }

    cv::Mat gray_image;
    cv::cvtColor(cv_ptr->image, cv_ptr->image, cv::COLOR_BGR2GRAY);
    cv::imshow("gray", gray_image);
    cv::waitKey(1);
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImageSubscriber>());
    rclcpp::shutdown();
    return 0;
}

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>

class ImageSubscriber : public rclcpp::Node
{
public:
  ImageSubscriber()
    : Node("image_subscriber")
  {
    // Subscriber 생성
    subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
      "image_topic", 10, std::bind(&ImageSubscriber::imageCallback, this, std::placeholders::_1));
  }

private:
  void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
  {
    // 이미지 데이터를 OpenCV 형식으로 변환
    cv::Mat image(msg->height, msg->width, CV_8UC3, const_cast<unsigned char*>(msg->data.data()), msg->step);

    // 이미지 표시
    cv::imshow("Image", image);
    cv::waitKey(1);
  }

  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ImageSubscriber>());
  rclcpp::shutdown();
  return 0;
}
*/

#include "pubsubimg/image_sub.hpp"

ImageSubscriber::ImageSubscriber()
:Node("image_subscriber")
{
  // Subscriber 생성
  subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
    "image", 10, std::bind(&ImageSubscriber::imageCallback, this, std::placeholders::_1));
}

void ImageSubscriber::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
{
  // 이미지 데이터를 OpenCV 형식으로 변환
  cv::Mat image(msg->height, msg->width, CV_8UC3, const_cast<unsigned char*>(msg->data.data()), msg->step);

  // 이미지 표시
  cv::imshow("Image", image);
  cv::waitKey(1);
}

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ImageSubscriber>());
  rclcpp::shutdown();
  return 0;
}