classdef CustomMsgConsts
    %CustomMsgConsts This class stores all message types
    %   The message types are constant properties, which in turn resolve
    %   to the strings of the actual types.
    
    %   Copyright 2014-2019 The MathWorks, Inc.
    
    properties (Constant)
        dynamics_getStaticTorques = 'dynamics/getStaticTorques'
        dynamics_getStaticTorquesRequest = 'dynamics/getStaticTorquesRequest'
        dynamics_getStaticTorquesResponse = 'dynamics/getStaticTorquesResponse'
        dynamics_setTorques = 'dynamics/setTorques'
        dynamics_setTorquesRequest = 'dynamics/setTorquesRequest'
        dynamics_setTorquesResponse = 'dynamics/setTorquesResponse'
        simulator_getStaticTorques = 'simulator/getStaticTorques'
        simulator_getStaticTorquesRequest = 'simulator/getStaticTorquesRequest'
        simulator_getStaticTorquesResponse = 'simulator/getStaticTorquesResponse'
    end
    
    methods (Static, Hidden)
        function messageList = getMessageList
            %getMessageList Generate a cell array with all message types.
            %   The list will be sorted alphabetically.
            
            persistent msgList
            if isempty(msgList)
                msgList = cell(6, 1);
                msgList{1} = 'dynamics/getStaticTorquesRequest';
                msgList{2} = 'dynamics/getStaticTorquesResponse';
                msgList{3} = 'dynamics/setTorquesRequest';
                msgList{4} = 'dynamics/setTorquesResponse';
                msgList{5} = 'simulator/getStaticTorquesRequest';
                msgList{6} = 'simulator/getStaticTorquesResponse';
            end
            
            messageList = msgList;
        end
        
        function serviceList = getServiceList
            %getServiceList Generate a cell array with all service types.
            %   The list will be sorted alphabetically.
            
            persistent svcList
            if isempty(svcList)
                svcList = cell(3, 1);
                svcList{1} = 'dynamics/getStaticTorques';
                svcList{2} = 'dynamics/setTorques';
                svcList{3} = 'simulator/getStaticTorques';
            end
            
            % The message list was already sorted, so don't need to sort
            % again.
            serviceList = svcList;
        end
        
        function actionList = getActionList
            %getActionList Generate a cell array with all action types.
            %   The list will be sorted alphabetically.
            
            persistent actList
            if isempty(actList)
                actList = cell(0, 1);
            end
            
            % The message list was already sorted, so don't need to sort
            % again.
            actionList = actList;
        end
    end
end
