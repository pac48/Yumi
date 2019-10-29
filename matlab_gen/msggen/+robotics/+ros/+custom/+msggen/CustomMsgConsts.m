classdef CustomMsgConsts
    %CustomMsgConsts This class stores all message types
    %   The message types are constant properties, which in turn resolve
    %   to the strings of the actual types.
    
    %   Copyright 2014-2019 The MathWorks, Inc.
    
    properties (Constant)
        dynamics_getC = 'dynamics/getC'
        dynamics_getCRequest = 'dynamics/getCRequest'
        dynamics_getCResponse = 'dynamics/getCResponse'
        dynamics_getG = 'dynamics/getG'
        dynamics_getGRequest = 'dynamics/getGRequest'
        dynamics_getGResponse = 'dynamics/getGResponse'
        dynamics_getJ = 'dynamics/getJ'
        dynamics_getJRequest = 'dynamics/getJRequest'
        dynamics_getJResponse = 'dynamics/getJResponse'
        dynamics_getM = 'dynamics/getM'
        dynamics_getMRequest = 'dynamics/getMRequest'
        dynamics_getMResponse = 'dynamics/getMResponse'
        dynamics_getStaticTorques = 'dynamics/getStaticTorques'
        dynamics_getStaticTorquesRequest = 'dynamics/getStaticTorquesRequest'
        dynamics_getStaticTorquesResponse = 'dynamics/getStaticTorquesResponse'
        dynamics_getT = 'dynamics/getT'
        dynamics_getTRequest = 'dynamics/getTRequest'
        dynamics_getTResponse = 'dynamics/getTResponse'
        dynamics_getTrajTorques = 'dynamics/getTrajTorques'
        dynamics_getTrajTorquesRequest = 'dynamics/getTrajTorquesRequest'
        dynamics_getTrajTorquesResponse = 'dynamics/getTrajTorquesResponse'
        dynamics_setTorques = 'dynamics/setTorques'
        dynamics_setTorquesRequest = 'dynamics/setTorquesRequest'
        dynamics_setTorquesResponse = 'dynamics/setTorquesResponse'
    end
    
    methods (Static, Hidden)
        function messageList = getMessageList
            %getMessageList Generate a cell array with all message types.
            %   The list will be sorted alphabetically.
            
            persistent msgList
            if isempty(msgList)
                msgList = cell(16, 1);
                msgList{1} = 'dynamics/getCRequest';
                msgList{2} = 'dynamics/getCResponse';
                msgList{3} = 'dynamics/getGRequest';
                msgList{4} = 'dynamics/getGResponse';
                msgList{5} = 'dynamics/getJRequest';
                msgList{6} = 'dynamics/getJResponse';
                msgList{7} = 'dynamics/getMRequest';
                msgList{8} = 'dynamics/getMResponse';
                msgList{9} = 'dynamics/getStaticTorquesRequest';
                msgList{10} = 'dynamics/getStaticTorquesResponse';
                msgList{11} = 'dynamics/getTRequest';
                msgList{12} = 'dynamics/getTResponse';
                msgList{13} = 'dynamics/getTrajTorquesRequest';
                msgList{14} = 'dynamics/getTrajTorquesResponse';
                msgList{15} = 'dynamics/setTorquesRequest';
                msgList{16} = 'dynamics/setTorquesResponse';
            end
            
            messageList = msgList;
        end
        
        function serviceList = getServiceList
            %getServiceList Generate a cell array with all service types.
            %   The list will be sorted alphabetically.
            
            persistent svcList
            if isempty(svcList)
                svcList = cell(8, 1);
                svcList{1} = 'dynamics/getC';
                svcList{2} = 'dynamics/getG';
                svcList{3} = 'dynamics/getJ';
                svcList{4} = 'dynamics/getM';
                svcList{5} = 'dynamics/getStaticTorques';
                svcList{6} = 'dynamics/getT';
                svcList{7} = 'dynamics/getTrajTorques';
                svcList{8} = 'dynamics/setTorques';
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
