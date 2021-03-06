classdef getTrajTorquesRequest < robotics.ros.Message
    %getTrajTorquesRequest MATLAB implementation of dynamics/getTrajTorquesRequest
    %   This class was automatically generated by
    %   robotics.ros.msg.internal.gen.MessageClassGenerator.
    
    %   Copyright 2014-2019 The MathWorks, Inc.
    
    %#ok<*INUSD>
    
    properties (Constant)
        MessageType = 'dynamics/getTrajTorquesRequest' % The ROS message type
    end
    
    properties (Constant, Hidden)
        MD5Checksum = '3f47c7f52170cf888db2e2e44df8f0fb' % The MD5 Checksum of the message definition
    end
    
    properties (Access = protected)
        JavaMessage % The Java message object
    end
    
    properties (Dependent)
        Q
        Qd
        Qdd
        Fext
    end
    
    properties (Constant, Hidden)
        PropertyList = {'Fext', 'Q', 'Qd', 'Qdd'} % List of non-constant message properties
        ROSPropertyList = {'Fext', 'q', 'qd', 'qdd'} % List of non-constant ROS message properties
    end
    
    methods
        function obj = getTrajTorquesRequest(msg)
            %getTrajTorquesRequest Construct the message object getTrajTorquesRequest
            import com.mathworks.toolbox.robotics.ros.message.MessageInfo;
            
            % Support default constructor
            if nargin == 0
                obj.JavaMessage = obj.createNewJavaMessage;
                return;
            end
            
            % Construct appropriate empty array
            if isempty(msg)
                obj = obj.empty(0,1);
                return;
            end
            
            % Make scalar construction fast
            if isscalar(msg)
                % Check for correct input class
                if ~MessageInfo.compareTypes(msg(1), obj.MessageType)
                    error(message('robotics:ros:message:NoTypeMatch', obj.MessageType, ...
                        char(MessageInfo.getType(msg(1))) ));
                end
                obj.JavaMessage = msg(1);
                return;
            end
            
            % Check that this is a vector of scalar messages. Since this
            % is an object array, use arrayfun to verify.
            if ~all(arrayfun(@isscalar, msg))
                error(message('robotics:ros:message:MessageArraySizeError'));
            end
            
            % Check that all messages in the array have the correct type
            if ~all(arrayfun(@(x) MessageInfo.compareTypes(x, obj.MessageType), msg))
                error(message('robotics:ros:message:NoTypeMatchArray', obj.MessageType));
            end
            
            % Construct array of objects if necessary
            objType = class(obj);
            for i = 1:length(msg)
                obj(i,1) = feval(objType, msg(i)); %#ok<AGROW>
            end
        end
        
        function q = get.Q(obj)
            %get.Q Get the value for property Q
            javaArray = obj.JavaMessage.getQ;
            array = obj.readJavaArray(javaArray, 'double');
            q = double(array);
        end
        
        function set.Q(obj, q)
            %set.Q Set the value for property Q
            if ~isvector(q) && isempty(q)
                % Allow empty [] input
                q = double.empty(0,1);
            end
            
            validateattributes(q, {'numeric'}, {'vector'}, 'getTrajTorquesRequest', 'Q');
            
            javaArray = obj.JavaMessage.getQ;
            array = obj.writeJavaArray(q, javaArray, 'double');
            obj.JavaMessage.setQ(array);
        end
        
        function qd = get.Qd(obj)
            %get.Qd Get the value for property Qd
            javaArray = obj.JavaMessage.getQd;
            array = obj.readJavaArray(javaArray, 'double');
            qd = double(array);
        end
        
        function set.Qd(obj, qd)
            %set.Qd Set the value for property Qd
            if ~isvector(qd) && isempty(qd)
                % Allow empty [] input
                qd = double.empty(0,1);
            end
            
            validateattributes(qd, {'numeric'}, {'vector'}, 'getTrajTorquesRequest', 'Qd');
            
            javaArray = obj.JavaMessage.getQd;
            array = obj.writeJavaArray(qd, javaArray, 'double');
            obj.JavaMessage.setQd(array);
        end
        
        function qdd = get.Qdd(obj)
            %get.Qdd Get the value for property Qdd
            javaArray = obj.JavaMessage.getQdd;
            array = obj.readJavaArray(javaArray, 'double');
            qdd = double(array);
        end
        
        function set.Qdd(obj, qdd)
            %set.Qdd Set the value for property Qdd
            if ~isvector(qdd) && isempty(qdd)
                % Allow empty [] input
                qdd = double.empty(0,1);
            end
            
            validateattributes(qdd, {'numeric'}, {'vector'}, 'getTrajTorquesRequest', 'Qdd');
            
            javaArray = obj.JavaMessage.getQdd;
            array = obj.writeJavaArray(qdd, javaArray, 'double');
            obj.JavaMessage.setQdd(array);
        end
        
        function fext = get.Fext(obj)
            %get.Fext Get the value for property Fext
            javaArray = obj.JavaMessage.getFext;
            array = obj.readJavaArray(javaArray, 'double');
            fext = double(array);
        end
        
        function set.Fext(obj, fext)
            %set.Fext Set the value for property Fext
            if ~isvector(fext) && isempty(fext)
                % Allow empty [] input
                fext = double.empty(0,1);
            end
            
            validateattributes(fext, {'numeric'}, {'vector'}, 'getTrajTorquesRequest', 'Fext');
            
            javaArray = obj.JavaMessage.getFext;
            array = obj.writeJavaArray(fext, javaArray, 'double');
            obj.JavaMessage.setFext(array);
        end
    end
    
    methods (Access = protected)
        function cpObj = copyElement(obj)
            %copyElement Implements deep copy behavior for message
            
            % Call default copy method for shallow copy
            cpObj = copyElement@robotics.ros.Message(obj);
            
            % Create a new Java message object
            cpObj.JavaMessage = obj.createNewJavaMessage;
            
            % Iterate over all primitive properties
            cpObj.Q = obj.Q;
            cpObj.Qd = obj.Qd;
            cpObj.Qdd = obj.Qdd;
            cpObj.Fext = obj.Fext;
        end
        
        function reload(obj, strObj)
            %reload Called by loadobj to assign properties
            obj.Q = strObj.Q;
            obj.Qd = strObj.Qd;
            obj.Qdd = strObj.Qdd;
            obj.Fext = strObj.Fext;
        end
    end
    
    methods (Access = ?robotics.ros.Message)
        function strObj = saveobj(obj)
            %saveobj Implements saving of message to MAT file
            
            % Return an empty element if object array is empty
            if isempty(obj)
                strObj = struct.empty;
                return
            end
            
            strObj.Q = obj.Q;
            strObj.Qd = obj.Qd;
            strObj.Qdd = obj.Qdd;
            strObj.Fext = obj.Fext;
        end
    end
    
    methods (Static, Access = {?matlab.unittest.TestCase, ?robotics.ros.Message})
        function obj = loadobj(strObj)
            %loadobj Implements loading of message from MAT file
            
            % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = robotics.ros.custom.msggen.dynamics.getTrajTorquesRequest.empty(0,1);
                return
            end
            
            % Create an empty message object
            obj = robotics.ros.custom.msggen.dynamics.getTrajTorquesRequest;
            obj.reload(strObj);
        end
    end
end
