template<typename dataT,typename msgConstPointerT>
class Messenger{
public:
    dataT data;
    void callback(msgConstPointerT& msg){ //const std_msgs::Float32MultiArray::ConstPtr&
        data = msg->data;
    }
};