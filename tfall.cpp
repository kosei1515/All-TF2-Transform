#include <tf/transform_broadcaster.h>
#include <tf2/buffer_core.h>
#include <tf2/utils.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2_ros/transform_listener.h>

int main() {
  tf2::Transform input_transform;
  tf2::Vector3 input_vector;
  tf2::Quaternion input_q{};
  input_q.setRPY(0, 0, 0);
  input_vector.setValue(0.0, 1.0, 2.0);
  input_transform.setOrigin(input_vector);
  input_transform.setRotation(input_q);

  tf2::Transform input2_transform;
  tf2::Vector3 input2_vector;
  // tf2::Quaternion input_q{};
  input_q.setRPY(0, 0, std::acos(-1) / 4);
  input2_vector.setValue(1.0, 4.0, 5.0);
  input2_transform.setOrigin(input2_vector);
  input2_transform.setRotation(input_q);
  // input

  auto diff = input_transform.inverse() * input2_transform;
  auto diff_msg = tf2::toMsg(diff);

  tf2::Transform input3_transform;
  tf2::Vector3 input3_vector;
  input3_vector.setValue(0.0, 0.0, 0.0);
  input_q.setRPY(0, 0, 0);
  input3_transform.setOrigin(input3_vector);
  input3_transform.setRotation(input_q);

  auto diff2 = tf2::toMsg(input3_transform * diff);
  auto diff3 = tf2::toMsg(input3_transform * diff.inverse());
  auto diff4 = tf2::toMsg(diff.inverse() * input3_transform);

  //   tf2::toMsg(diff2);

  // auto rot = input3_transform * diff.inverse();

  double roll, pitch, yaw;
  tf2::getEulerYPR(diff3.rotation, yaw, pitch, roll);
  std::cout << "diff " << diff_msg.translation.x << diff_msg.translation.y
            << diff_msg.translation.z << std::endl;
  std::cout << "diff2 " << diff2.translation.x << diff2.translation.y
            << diff2.translation.z << std::endl;
  std::cout << "diff3 " << diff3.translation.x << diff3.translation.y
            << diff3.translation.z << "yaw" << yaw << std::endl;

  tf2::getEulerYPR(diff4.rotation, yaw, pitch, roll);
  std::cout << "diff4 " << diff4.translation.x << diff4.translation.y
            << diff4.translation.z << "yaw" << yaw << std::endl;

  return 0;
}
