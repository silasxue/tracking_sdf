#include "sdf_3d_reconstruction/camera_tracking.h"
CameraTracking::CameraTracking(){
  
}
CameraTracking::~CameraTracking(){
  
}

void CameraTracking::camera_info_cb(const sensor_msgs::CameraInfoConstPtr &rgbd_camera_info)
{
	this->K(0,0) = rgbd_camera_info->K[0];
	this->K(0,1) = rgbd_camera_info->K[1];
	this->K(0,2) = rgbd_camera_info->K[2];
	this->K(1,0) = rgbd_camera_info->K[3];
	this->K(1,1) = rgbd_camera_info->K[4];
	this->K(1,2) = rgbd_camera_info->K[5];
	this->K(2,0) = rgbd_camera_info->K[6];
	this->K(2,1) = rgbd_camera_info->K[7];
	this->K(2,2) = rgbd_camera_info->K[8];
	this->isKFilled = true;
	cout<<"read Camera Matrix"<<endl;
	this->cam_info.shutdown();
}
//todo: validate!
void CameraTracking::projectCamera3DPointToImagePlane(Vector3i& camera_point, Vector2i& image_point){
	//Eq. 2
	Vector2i ij;
	float fx = this->K(0,0);
	float fy = this->K(1,1);
	float cx = this->K(0,2);
	float cy = this->K(1,2);
	image_point(0) = fx*(camera_point(0)/camera_point(2)) + cx;
	image_point(1) = fy*(camera_point(1)/camera_point(2)) + cy;
}