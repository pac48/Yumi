%% linear movment
rosshutdown
rosinit('192.168.1.5');
pub = rospublisher('/yumi/ikSloverVel_controller/command');
msg = rosmessage('std_msgs/Float64MultiArray');
%msg.Data = -[.008 0.008 0.008 .008 0.008 0.008];
msg.Data = -[.1 0 0.1 .1 0 0.1];
%msg.Data = [.008 0 0.00 .008 0 0.0];
%msg.Data = [.00 0 0.008 .00 0 0.008];
send(pub,msg);
pause(1)
msg.Data = [0 0 0 0 0 0];
send(pub,msg);
%% 
rosshutdown
rosinit('192.168.1.5');
pub = rospublisher('/yumi/ikSloverVel_controller/command');
sub = rossubscriber('/yumi/ikSloverVel_controller/ee_cart_position');
msg = rosmessage('std_msgs/Float64MultiArray');
V = zeros(3,1);
pause(.5)
tic
% X = 1-cos(tk)
offset = sub.LatestMessage.Data(1:3);
while 1
   k=2;
   A=.05;
   X = offset+[A*(1-cos(toc*k)); 0; A*(1+sin(toc*k))]; 
   V = 100*(X-sub.LatestMessage.Data(1:3));
   msg.Data = [V'./1000 0 0 0];
   send(pub,msg);
   pause(0.01);
end
%% mouse follow
rosshutdown
rosinit('192.168.1.5');
pub = rospublisher('/yumi/ikSloverVel_controller/command');
sub = rossubscriber('/yumi/ikSloverVel_controller/ee_cart_position');
msg = rosmessage('std_msgs/Float64MultiArray');
V = zeros(3,1);
pause(.5)
tic
% X = 1-cos(tk)
offset = sub.LatestMessage.Data(4:6);
mouse=Mouse;
set (gcf, 'WindowButtonMotionFcn', @mouse.mouseMove);
pause(3)
V = zeros(3,1);
while 1
    tic
   k=2;
   A=.05;
   X = offset+.2*[-mouse.ypos; mouse.xpos; 0]; 
   Vn = 5*(X-sub.LatestMessage.Data(4:6));
   V = (.2*V+.8*Vn)
   msg.Data = [0 0 0 V'];
   send(pub,msg);
   pause(0.001);
   mouse
   toc
end
%% linear movment
rosshutdown
rosinit('192.168.1.5');
pub = rospublisher('/operational_velocity_command');
msg = rosmessage('std_msgs/Float32MultiArray');
% msg.Data = -[.1 0 0.1 0 0 0 0 0 0 0 0 0];
msg.Data = [0 0 0 .1 0 0 0 0 0 0 0 0];
send(pub,msg);
pause(.2)

msg.Data = [0 0 0 0 0 0 0 0 0 0 0 0];
send(pub,msg);
%% mouse follow vel
rosshutdown
rosinit('192.168.1.5');
pub = rospublisher('/operational_velocity_command');
msg = rosmessage('std_msgs/Float32MultiArray');
msg.Data = [0 0 0 0 0 0 0 0 0 0 0 0];
V = zeros(3,1);
pause(.5)

tic
mouse=Mouse;
set (gcf, 'WindowButtonMotionFcn', @mouse.mouseMove);
pause(3)
V = zeros(3,1);
while 1
    tic
   msg.Data(1:3) = [-mouse.ypos; mouse.xpos; 0]*2;
   send(pub,msg);
   pause(0.00001);
   mouse
   toc
end
%% mouse follow
rosshutdown
rosinit('192.168.1.5');
pub = rospublisher('/operational_velocity_command');
msg = rosmessage('std_msgs/Float32MultiArray');
msg.Data = [0 0 0 0 0 0 0 0 0 0 0 0];
V = zeros(3,1);
pause(.5)
sub = rossubscriber('/operational_position_R');
scale=.15;
mouse=Mouse(scale);
%set (gcf, 'WindowButtonDownFcn',@mouse.mouseMove)
%f= gcf;
pause(3)
V = zeros(3,1);
mouseV = zeros(3,1);
offset=sub.LatestMessage.Data(1:3);
while 1
    cur = sub.LatestMessage.Data(1:3)-offset;
    mouseV(2) = 1*mouse.xvel;
    mouseV(1) = -1*mouse.yvel;
    msg.Data(1:3) = mouseV+(2*([-mouse.ypos mouse.xpos 0]'-cur));
%     [-mouse.ypos mouse.xpos 0]'-cur
%     mouseV+(.1*[-mouse.ypos mouse.xpos 0]'-cur)
    mouseV;
mouseV+(3*([-mouse.ypos mouse.xpos 0]'-cur))
   send(pub,msg);
   pause(0.01);
   mouseV;
 mouse.mouseMove;
   %f.WindowButtonMotionFcn();
   
   %f.WindowButtonDownFcn();
end
% get(0, 'PointerLocation')
%% sin follow
rosshutdown
rosinit('192.168.1.5');
pub = rospublisher('/operational_velocity_command');
msg = rosmessage('std_msgs/Float32MultiArray');
msg.Data = [0 0 0 0 0 0 0 0 0 0 0 0];
V = zeros(3,1);
pause(.5)
sub = rossubscriber('/operational_position_R');
f= gcf;
pause(1)
V = zeros(3,1);
mouseV = zeros(3,1);
offset=sub.LatestMessage.Data(1:3);
tic
while 1
    cur = sub.LatestMessage.Data(1:3)-offset;
    mouseV(1) = .1*cos(toc);
    mouseV(2) = 0
    .1*sin(toc)
    msg.Data(1:3) = mouseV+(3*([.1*sin(toc) 0 0]'-cur));
%     [-mouse.ypos mouse.xpos 0]'-cur
%     mouseV+(.1*[-mouse.ypos mouse.xpos 0]'-cur)
      send(pub,msg);
   pause(0.01);
   mouseV;
   f.WindowButtonDownFcn();
end
%%
rosshutdown
rosinit('192.168.1.5');
testclient = rossvcclient('/gazebo/apply_joint_effort')
testreq = rosmessage(testclient);
testreq.JointName='yumi_joint_3_r';
testreq.Effort=15;
testreq.Duration.Sec=2;
testresp = call(testclient,testreq,'Timeout',3)
testreq.JointName='yumi_joint_2_r';
testreq.Effort=15;
testreq.Duration.Sec=2;
testresp = call(testclient,testreq,'Timeout',3)

