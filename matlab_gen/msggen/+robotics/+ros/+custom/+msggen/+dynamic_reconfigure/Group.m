classdef Group < robotics.ros.Message
    %Group MATLAB implementation of dynamic_reconfigure/Group
    %   This class was automatically generated by
    %   robotics.ros.msg.internal.gen.MessageClassGenerator.
    
    %   Copyright 2014-2019 The MathWorks, Inc.
    
    %#ok<*INUSD>
    
    properties (Constant)
        MessageType = 'dynamic_reconfigure/Group' % The ROS message type
    end
    
    properties (Constant, Hidden)
        MD5Checksum = '9e8cd9e9423c94823db3614dd8b1cf7a' % The MD5 Checksum of the message definition
    end
    
    properties (Access = protected)
        JavaMessage % The Java message object
    end
    
    properties (Constant, Access = protected)
        DynamicReconfigureParamDescriptionClass = robotics.ros.msg.internal.MessageFactory.getClassForType('dynamic_reconfigure/ParamDescription') % Dispatch to MATLAB class for message type dynamic_reconfigure/ParamDescription
    end
    
    properties (Dependent)
        Name
        Type
        Parent
        Id
        Parameters
    end
    
    properties (Access = protected)
        Cache = struct('Parameters', []) % The cache for fast data access
    end
    
    properties (Constant, Hidden)
        PropertyList = {'Id', 'Name', 'Parameters', 'Parent', 'Type'} % List of non-constant message properties
        ROSPropertyList = {'id', 'name', 'parameters', 'parent', 'type'} % List of non-constant ROS message properties
    end
    
    methods
        function obj = Group(msg)
            %Group Construct the message object Group
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
        
        function name = get.Name(obj)
            %get.Name Get the value for property Name
            name = char(obj.JavaMessage.getName);
        end
        
        function set.Name(obj, name)
            %set.Name Set the value for property Name
            name = convertStringsToChars(name);
            
            validateattributes(name, {'char', 'string'}, {}, 'Group', 'Name');
            
            obj.JavaMessage.setName(name);
        end
        
        function type = get.Type(obj)
            %get.Type Get the value for property Type
            type = char(obj.JavaMessage.getType);
        end
        
        function set.Type(obj, type)
            %set.Type Set the value for property Type
            type = convertStringsToChars(type);
            
            validateattributes(type, {'char', 'string'}, {}, 'Group', 'Type');
            
            obj.JavaMessage.setType(type);
        end
        
        function parent = get.Parent(obj)
            %get.Parent Get the value for property Parent
            parent = int32(obj.JavaMessage.getParent);
        end
        
        function set.Parent(obj, parent)
            %set.Parent Set the value for property Parent
            validateattributes(parent, {'numeric'}, {'nonempty', 'scalar'}, 'Group', 'Parent');
            
            obj.JavaMessage.setParent(parent);
        end
        
        function id = get.Id(obj)
            %get.Id Get the value for property Id
            id = int32(obj.JavaMessage.getId);
        end
        
        function set.Id(obj, id)
            %set.Id Set the value for property Id
            validateattributes(id, {'numeric'}, {'nonempty', 'scalar'}, 'Group', 'Id');
            
            obj.JavaMessage.setId(id);
        end
        
        function parameters = get.Parameters(obj)
            %get.Parameters Get the value for property Parameters
            if isempty(obj.Cache.Parameters)
                javaArray = obj.JavaMessage.getParameters;
                array = obj.readJavaArray(javaArray, obj.DynamicReconfigureParamDescriptionClass);
                obj.Cache.Parameters = feval(obj.DynamicReconfigureParamDescriptionClass, array);
            end
            parameters = obj.Cache.Parameters;
        end
        
        function set.Parameters(obj, parameters)
            %set.Parameters Set the value for property Parameters
            if ~isvector(parameters) && isempty(parameters)
                % Allow empty [] input
                parameters = feval([obj.DynamicReconfigureParamDescriptionClass '.empty'], 0, 1);
            end
            
            validateattributes(parameters, {obj.DynamicReconfigureParamDescriptionClass}, {'vector'}, 'Group', 'Parameters');
            
            javaArray = obj.JavaMessage.getParameters;
            array = obj.writeJavaArray(parameters, javaArray, obj.DynamicReconfigureParamDescriptionClass);
            obj.JavaMessage.setParameters(array);
            
            % Update cache if necessary
            if ~isempty(obj.Cache.Parameters)
                obj.Cache.Parameters = [];
                obj.Cache.Parameters = obj.Parameters;
            end
        end
    end
    
    methods (Access = protected)
        function resetCache(obj)
            %resetCache Resets any cached properties
            obj.Cache.Parameters = [];
        end
        
        function cpObj = copyElement(obj)
            %copyElement Implements deep copy behavior for message
            
            % Call default copy method for shallow copy
            cpObj = copyElement@robotics.ros.Message(obj);
            
            % Clear any existing cached properties
            cpObj.resetCache;
            
            % Create a new Java message object
            cpObj.JavaMessage = obj.createNewJavaMessage;
            
            % Iterate over all primitive properties
            cpObj.Name = obj.Name;
            cpObj.Type = obj.Type;
            cpObj.Parent = obj.Parent;
            cpObj.Id = obj.Id;
            
            % Recursively copy compound properties
            cpObj.Parameters = copy(obj.Parameters);
        end
        
        function reload(obj, strObj)
            %reload Called by loadobj to assign properties
            obj.Name = strObj.Name;
            obj.Type = strObj.Type;
            obj.Parent = strObj.Parent;
            obj.Id = strObj.Id;
            ParametersCell = arrayfun(@(x) feval([obj.DynamicReconfigureParamDescriptionClass '.loadobj'], x), strObj.Parameters, 'UniformOutput', false);
            obj.Parameters = vertcat(ParametersCell{:});
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
            
            strObj.Name = obj.Name;
            strObj.Type = obj.Type;
            strObj.Parent = obj.Parent;
            strObj.Id = obj.Id;
            strObj.Parameters = arrayfun(@(x) saveobj(x), obj.Parameters);
        end
    end
    
    methods (Static, Access = {?matlab.unittest.TestCase, ?robotics.ros.Message})
        function obj = loadobj(strObj)
            %loadobj Implements loading of message from MAT file
            
            % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = robotics.ros.custom.msggen.dynamic_reconfigure.Group.empty(0,1);
                return
            end
            
            % Create an empty message object
            obj = robotics.ros.custom.msggen.dynamic_reconfigure.Group;
            obj.reload(strObj);
        end
    end
end
