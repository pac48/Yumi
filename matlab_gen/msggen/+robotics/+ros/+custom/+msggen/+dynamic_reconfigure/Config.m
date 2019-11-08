classdef Config < robotics.ros.Message
    %Config MATLAB implementation of dynamic_reconfigure/Config
    %   This class was automatically generated by
    %   robotics.ros.msg.internal.gen.MessageClassGenerator.
    
    %   Copyright 2014-2019 The MathWorks, Inc.
    
    %#ok<*INUSD>
    
    properties (Constant)
        MessageType = 'dynamic_reconfigure/Config' % The ROS message type
    end
    
    properties (Constant, Hidden)
        MD5Checksum = '958f16a05573709014982821e6822580' % The MD5 Checksum of the message definition
    end
    
    properties (Access = protected)
        JavaMessage % The Java message object
    end
    
    properties (Constant, Access = protected)
        DynamicReconfigureBoolParameterClass = robotics.ros.msg.internal.MessageFactory.getClassForType('dynamic_reconfigure/BoolParameter') % Dispatch to MATLAB class for message type dynamic_reconfigure/BoolParameter
        DynamicReconfigureDoubleParameterClass = robotics.ros.msg.internal.MessageFactory.getClassForType('dynamic_reconfigure/DoubleParameter') % Dispatch to MATLAB class for message type dynamic_reconfigure/DoubleParameter
        DynamicReconfigureGroupStateClass = robotics.ros.msg.internal.MessageFactory.getClassForType('dynamic_reconfigure/GroupState') % Dispatch to MATLAB class for message type dynamic_reconfigure/GroupState
        DynamicReconfigureIntParameterClass = robotics.ros.msg.internal.MessageFactory.getClassForType('dynamic_reconfigure/IntParameter') % Dispatch to MATLAB class for message type dynamic_reconfigure/IntParameter
        DynamicReconfigureStrParameterClass = robotics.ros.msg.internal.MessageFactory.getClassForType('dynamic_reconfigure/StrParameter') % Dispatch to MATLAB class for message type dynamic_reconfigure/StrParameter
    end
    
    properties (Dependent)
        Bools
        Ints
        Strs
        Doubles
        Groups
    end
    
    properties (Access = protected)
        Cache = struct('Bools', [], 'Ints', [], 'Strs', [], 'Doubles', [], 'Groups', []) % The cache for fast data access
    end
    
    properties (Constant, Hidden)
        PropertyList = {'Bools', 'Doubles', 'Groups', 'Ints', 'Strs'} % List of non-constant message properties
        ROSPropertyList = {'bools', 'doubles', 'groups', 'ints', 'strs'} % List of non-constant ROS message properties
    end
    
    methods
        function obj = Config(msg)
            %Config Construct the message object Config
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
        
        function bools = get.Bools(obj)
            %get.Bools Get the value for property Bools
            if isempty(obj.Cache.Bools)
                javaArray = obj.JavaMessage.getBools;
                array = obj.readJavaArray(javaArray, obj.DynamicReconfigureBoolParameterClass);
                obj.Cache.Bools = feval(obj.DynamicReconfigureBoolParameterClass, array);
            end
            bools = obj.Cache.Bools;
        end
        
        function set.Bools(obj, bools)
            %set.Bools Set the value for property Bools
            if ~isvector(bools) && isempty(bools)
                % Allow empty [] input
                bools = feval([obj.DynamicReconfigureBoolParameterClass '.empty'], 0, 1);
            end
            
            validateattributes(bools, {obj.DynamicReconfigureBoolParameterClass}, {'vector'}, 'Config', 'Bools');
            
            javaArray = obj.JavaMessage.getBools;
            array = obj.writeJavaArray(bools, javaArray, obj.DynamicReconfigureBoolParameterClass);
            obj.JavaMessage.setBools(array);
            
            % Update cache if necessary
            if ~isempty(obj.Cache.Bools)
                obj.Cache.Bools = [];
                obj.Cache.Bools = obj.Bools;
            end
        end
        
        function ints = get.Ints(obj)
            %get.Ints Get the value for property Ints
            if isempty(obj.Cache.Ints)
                javaArray = obj.JavaMessage.getInts;
                array = obj.readJavaArray(javaArray, obj.DynamicReconfigureIntParameterClass);
                obj.Cache.Ints = feval(obj.DynamicReconfigureIntParameterClass, array);
            end
            ints = obj.Cache.Ints;
        end
        
        function set.Ints(obj, ints)
            %set.Ints Set the value for property Ints
            if ~isvector(ints) && isempty(ints)
                % Allow empty [] input
                ints = feval([obj.DynamicReconfigureIntParameterClass '.empty'], 0, 1);
            end
            
            validateattributes(ints, {obj.DynamicReconfigureIntParameterClass}, {'vector'}, 'Config', 'Ints');
            
            javaArray = obj.JavaMessage.getInts;
            array = obj.writeJavaArray(ints, javaArray, obj.DynamicReconfigureIntParameterClass);
            obj.JavaMessage.setInts(array);
            
            % Update cache if necessary
            if ~isempty(obj.Cache.Ints)
                obj.Cache.Ints = [];
                obj.Cache.Ints = obj.Ints;
            end
        end
        
        function strs = get.Strs(obj)
            %get.Strs Get the value for property Strs
            if isempty(obj.Cache.Strs)
                javaArray = obj.JavaMessage.getStrs;
                array = obj.readJavaArray(javaArray, obj.DynamicReconfigureStrParameterClass);
                obj.Cache.Strs = feval(obj.DynamicReconfigureStrParameterClass, array);
            end
            strs = obj.Cache.Strs;
        end
        
        function set.Strs(obj, strs)
            %set.Strs Set the value for property Strs
            if ~isvector(strs) && isempty(strs)
                % Allow empty [] input
                strs = feval([obj.DynamicReconfigureStrParameterClass '.empty'], 0, 1);
            end
            
            validateattributes(strs, {obj.DynamicReconfigureStrParameterClass}, {'vector'}, 'Config', 'Strs');
            
            javaArray = obj.JavaMessage.getStrs;
            array = obj.writeJavaArray(strs, javaArray, obj.DynamicReconfigureStrParameterClass);
            obj.JavaMessage.setStrs(array);
            
            % Update cache if necessary
            if ~isempty(obj.Cache.Strs)
                obj.Cache.Strs = [];
                obj.Cache.Strs = obj.Strs;
            end
        end
        
        function doubles = get.Doubles(obj)
            %get.Doubles Get the value for property Doubles
            if isempty(obj.Cache.Doubles)
                javaArray = obj.JavaMessage.getDoubles;
                array = obj.readJavaArray(javaArray, obj.DynamicReconfigureDoubleParameterClass);
                obj.Cache.Doubles = feval(obj.DynamicReconfigureDoubleParameterClass, array);
            end
            doubles = obj.Cache.Doubles;
        end
        
        function set.Doubles(obj, doubles)
            %set.Doubles Set the value for property Doubles
            if ~isvector(doubles) && isempty(doubles)
                % Allow empty [] input
                doubles = feval([obj.DynamicReconfigureDoubleParameterClass '.empty'], 0, 1);
            end
            
            validateattributes(doubles, {obj.DynamicReconfigureDoubleParameterClass}, {'vector'}, 'Config', 'Doubles');
            
            javaArray = obj.JavaMessage.getDoubles;
            array = obj.writeJavaArray(doubles, javaArray, obj.DynamicReconfigureDoubleParameterClass);
            obj.JavaMessage.setDoubles(array);
            
            % Update cache if necessary
            if ~isempty(obj.Cache.Doubles)
                obj.Cache.Doubles = [];
                obj.Cache.Doubles = obj.Doubles;
            end
        end
        
        function groups = get.Groups(obj)
            %get.Groups Get the value for property Groups
            if isempty(obj.Cache.Groups)
                javaArray = obj.JavaMessage.getGroups;
                array = obj.readJavaArray(javaArray, obj.DynamicReconfigureGroupStateClass);
                obj.Cache.Groups = feval(obj.DynamicReconfigureGroupStateClass, array);
            end
            groups = obj.Cache.Groups;
        end
        
        function set.Groups(obj, groups)
            %set.Groups Set the value for property Groups
            if ~isvector(groups) && isempty(groups)
                % Allow empty [] input
                groups = feval([obj.DynamicReconfigureGroupStateClass '.empty'], 0, 1);
            end
            
            validateattributes(groups, {obj.DynamicReconfigureGroupStateClass}, {'vector'}, 'Config', 'Groups');
            
            javaArray = obj.JavaMessage.getGroups;
            array = obj.writeJavaArray(groups, javaArray, obj.DynamicReconfigureGroupStateClass);
            obj.JavaMessage.setGroups(array);
            
            % Update cache if necessary
            if ~isempty(obj.Cache.Groups)
                obj.Cache.Groups = [];
                obj.Cache.Groups = obj.Groups;
            end
        end
    end
    
    methods (Access = protected)
        function resetCache(obj)
            %resetCache Resets any cached properties
            obj.Cache.Bools = [];
            obj.Cache.Ints = [];
            obj.Cache.Strs = [];
            obj.Cache.Doubles = [];
            obj.Cache.Groups = [];
        end
        
        function cpObj = copyElement(obj)
            %copyElement Implements deep copy behavior for message
            
            % Call default copy method for shallow copy
            cpObj = copyElement@robotics.ros.Message(obj);
            
            % Clear any existing cached properties
            cpObj.resetCache;
            
            % Create a new Java message object
            cpObj.JavaMessage = obj.createNewJavaMessage;
            
            % Recursively copy compound properties
            cpObj.Bools = copy(obj.Bools);
            cpObj.Ints = copy(obj.Ints);
            cpObj.Strs = copy(obj.Strs);
            cpObj.Doubles = copy(obj.Doubles);
            cpObj.Groups = copy(obj.Groups);
        end
        
        function reload(obj, strObj)
            %reload Called by loadobj to assign properties
            BoolsCell = arrayfun(@(x) feval([obj.DynamicReconfigureBoolParameterClass '.loadobj'], x), strObj.Bools, 'UniformOutput', false);
            obj.Bools = vertcat(BoolsCell{:});
            IntsCell = arrayfun(@(x) feval([obj.DynamicReconfigureIntParameterClass '.loadobj'], x), strObj.Ints, 'UniformOutput', false);
            obj.Ints = vertcat(IntsCell{:});
            StrsCell = arrayfun(@(x) feval([obj.DynamicReconfigureStrParameterClass '.loadobj'], x), strObj.Strs, 'UniformOutput', false);
            obj.Strs = vertcat(StrsCell{:});
            DoublesCell = arrayfun(@(x) feval([obj.DynamicReconfigureDoubleParameterClass '.loadobj'], x), strObj.Doubles, 'UniformOutput', false);
            obj.Doubles = vertcat(DoublesCell{:});
            GroupsCell = arrayfun(@(x) feval([obj.DynamicReconfigureGroupStateClass '.loadobj'], x), strObj.Groups, 'UniformOutput', false);
            obj.Groups = vertcat(GroupsCell{:});
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
            
            strObj.Bools = arrayfun(@(x) saveobj(x), obj.Bools);
            strObj.Ints = arrayfun(@(x) saveobj(x), obj.Ints);
            strObj.Strs = arrayfun(@(x) saveobj(x), obj.Strs);
            strObj.Doubles = arrayfun(@(x) saveobj(x), obj.Doubles);
            strObj.Groups = arrayfun(@(x) saveobj(x), obj.Groups);
        end
    end
    
    methods (Static, Access = {?matlab.unittest.TestCase, ?robotics.ros.Message})
        function obj = loadobj(strObj)
            %loadobj Implements loading of message from MAT file
            
            % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = robotics.ros.custom.msggen.dynamic_reconfigure.Config.empty(0,1);
                return
            end
            
            % Create an empty message object
            obj = robotics.ros.custom.msggen.dynamic_reconfigure.Config;
            obj.reload(strObj);
        end
    end
end
