clear all
rosshutdown()
rosinit("192.168.1.27")

desired_points = 100;

rob_points = zeros(desired_points,3);
camera_points = ones(desired_points,4);

rob_sub = rossubscriber("/operational_position_R");
camera_sub = rossubscriber("/camera_coords");

i = 1;


while i <= desired_points
    msg1 = receive(rob_sub);
    msg2 = receive(camera_sub);
    rob_point = msg1.Data(1:3);
    camera_point = msg2.Data;
    rob_points(i,1:3) = rob_point;
    camera_points(i,1:3) = camera_point;   
    pause(0.05)
    i = i+1
end
calibration = {rob_points,camera_points};
save("calibration" ,"calibration")