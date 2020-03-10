%% coords
%clear all

points = load('calibration.mat');

robot_points = points.calibration{1, 1};
camera_points = points.calibration{1, 2};

% P1_cam = [1,-2,3,1];
% P1_rob = [4,5,6];
% 
% P2_cam = [2,4,6,1];
% P2_rob = [7,8,9];
% 
% P3_cam = [3,5,7,1];
% P3_rob = [9,10,11];
% 
% P4_cam = [7,9,13,1];
% P4_rob = [12,14,15];

%% optimize
robot_array = reshape(robot_points',size(robot_points,1)*size(robot_points,2),1);
camera_matrix = zeros(length(camera_points)*3, 12);
%camera_matrix = zeros(12,12);
for i = 1:3*length(camera_points) 
    offset = (mod(i-1,3))*4;
    camera_matrix(i,(1:4)+offset) = camera_points(floor((i-1)/3)+1,:);
end

% camera_matrix(1,1:4) = P1_cam;
% camera_matrix(2,5:8) = P1_cam;
% camera_matrix(3,9:12) = P1_cam;
% 
% camera_matrix(4,1:4) = P2_cam;
% camera_matrix(5,5:8) = P2_cam;
% camera_matrix(6,9:12) = P2_cam;
% 
% camera_matrix(7,1:4) = P3_cam;
% camera_matrix(8,5:8) = P3_cam;
% camera_matrix(9,9:12) = P3_cam;
% 
% camera_matrix(10,1:4) = P4_cam;
% camera_matrix(11,5:8) = P4_cam;
% camera_matrix(12,9:12) = P4_cam;

%robot_array = [P1_rob,P2_rob,P3_rob,P4_rob]';

fun = @(x) sum((camera_matrix*x-robot_array).^2);
nonlcon = @(x)constraints(x);
opt = optimoptions("fmincon", 'MaxFunctionEvaluations', 30000);
initial = eye(4);
initial_new = reshape(initial(1:3,1:4)', [12,1]);
b = fmincon(fun,initial_new,[],[],[],[],[],[],nonlcon,opt);

transformation_matrix = [b(1:4)';b(5:8)';b(9:12)';[0,0,0,1]];
%%
rosshutdown()
rosinit("192.168.1.27")
msg = rosmessage('std_msgs/Float32MultiArray');
%rot = eul2rotm([0,0,0])*transformation_matrix(1:3,1:3)*eul2rotm([pi/2,0,0]);%*eul2rotm([0,pi/2,0]);
%quat = rotm2quat(rot);
tmp = [b;0;0;0;1];%[quat';transformation_matrix(1:3,4)];
msg.Data = tmp;
transformation_pub = rospublisher("/transfrom");

send(transformation_pub,msg)

