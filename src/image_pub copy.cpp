/*
#include "pubsubimg/image_pub.hpp"
#include "cv_bridge/cv_bridge.h"

ImagePublisher::ImagePublisher()
: Node("image_publisher"), count_(0)
{
    publisher_ = this->create_publisher<sensor_msgs::msg::Image>("image", 10);
    timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&ImagePublisher::timer_callback, this));

    image_ = cv::imread("test.png", cv::IMREAD_COLOR);

}

void ImagePublisher::timer_callback()
{
    std_msgs::msg::Header header;
    header.stamp = this->now();  // 현재 시간으로 설정합니다.
    header.frame_id = "image";  // frame_id를 원하는 값으로 설정합니다.
    auto msg = cv_bridge::CvImage(header, "bgr8", image_).toImageMsg();
    publisher_ ->publish(*msg);
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImagePublisher>());
    rclcpp::shutdown();
    return 0;
}



#include "pubsubimg/image_pub.hpp"
#include "cv_bridge/cv_bridge.h"

ImagePublisher::ImagePublisher()
  : Node("image_publisher"), count_(0)
{
  publisher_ = this->create_publisher<sensor_msgs::msg::Image>("image", 10);
  timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&ImagePublisher::timer_callback, this));



  // Load image
  image_ = cv::imread("test.jpg", cv::IMREAD_COLOR);
}

void ImagePublisher::timer_callback()
{
  if (!image_.empty())
  {
    std_msgs::msg::Header header;
    header.stamp = this->now();  // 현재 시간으로 설정합니다.
    header.frame_id = "image";  // frame_id를 원하는 값으로 설정합니다.
    auto img_msg = cv_bridge::CvImage(header, "bgr8", image_).toImageMsg();
    RCLCPP_INFO(this->get_logger(), "Publishing image");
    publisher_->publish(*img_msg);
  }
  else
  {
    RCLCPP_ERROR(this->get_logger(), "Failed to load image");
  }
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImagePublisher>());
    rclcpp::shutdown();
    return 0;
}

#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>

using namespace std::chrono_literals;

class ImagePublisher : public rclcpp::Node
{
public:
  ImagePublisher()
    : Node("image_publisher")
  {
    // 이미지 파일 경로 설정
    std::string image_file_path = "test.png"; // 실제 파일 경로로 변경해야 합니다.

    // 이미지 메시지 초기화
    auto image_msg = std::make_shared<sensor_msgs::msg::Image>();

    // 이미지 파일 읽기
    cv::Mat image = cv::imread(image_file_path, cv::IMREAD_COLOR);
    if (image.empty()) {
      RCLCPP_ERROR(this->get_logger(), "Failed to load image file");
      return;
    }

    // 이미지 메시지에 데이터 설정
    image_msg->width = image.cols;
    image_msg->height = image.rows;
    image_msg->encoding = "bgr8";
    image_msg->step = static_cast<sensor_msgs::msg::Image::_step_type>(image.step);
    size_t image_size = image.step * image.rows;
    image_msg->data.resize(image_size);
    memcpy(&image_msg->data[0], image.data, image_size);

    // Publisher 생성 및 이미지 메시지 publish
    publisher_ = this->create_publisher<sensor_msgs::msg::Image>("image", 10);
    timer_ = this->create_wall_timer(1s, [this, image_msg]() {
      publisher_->publish(*image_msg);
    });
  }

private:
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ImagePublisher>());
  rclcpp::shutdown();
  return 0;
}
*/

#include "pubsubimg/image_pub.hpp"

ImagePublisher::ImagePublisher()
  : Node("image_publisher")
{
  // 이미지 파일 경로 설정
  std::string image_file_path = "/home/g1-ubuntu/ws/src/pubsubimg/src/test.png"; // 실제 파일 경로로 변경해야 합니다.

  // 이미지 메시지 초기화
  auto image_msg = std::make_shared<sensor_msgs::msg::Image>();

  // 이미지 파일 읽기
  cv::Mat image = cv::imread(image_file_path, cv::IMREAD_COLOR);
  if (image.empty()) {
    RCLCPP_ERROR(this->get_logger(), "Failed to load image file");
    return;
  }

  // 이미지 메시지에 데이터 설정
  image_msg->width = image.cols;
  image_msg->height = image.rows;
  image_msg->encoding = "bgr8";
  image_msg->step = static_cast<sensor_msgs::msg::Image::_step_type>(image.step);
  size_t image_size = image.step * image.rows;
  image_msg->data.resize(image_size);
  memcpy(&image_msg->data[0], image.data, image_size);

  // Publisher 생성 및 이미지 메시지 publish
  publisher_ = this->create_publisher<sensor_msgs::msg::Image>("image", 10);
  timer_ = this->create_wall_timer(1s, [this, image_msg]() {
    publisher_->publish(*image_msg);
  });
}

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ImagePublisher>());
  rclcpp::shutdown();
  return 0;
}


