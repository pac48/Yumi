classdef CustomMsgConsts
    %CustomMsgConsts This class stores all message types
    %   The message types are constant properties, which in turn resolve
    %   to the strings of the actual types.
    
    %   Copyright 2014-2019 The MathWorks, Inc.
    
    properties (Constant)
        dynamic_reconfigure_BoolParameter = 'dynamic_reconfigure/BoolParameter'
        dynamic_reconfigure_Config = 'dynamic_reconfigure/Config'
        dynamic_reconfigure_ConfigDescription = 'dynamic_reconfigure/ConfigDescription'
        dynamic_reconfigure_DoubleParameter = 'dynamic_reconfigure/DoubleParameter'
        dynamic_reconfigure_Group = 'dynamic_reconfigure/Group'
        dynamic_reconfigure_GroupState = 'dynamic_reconfigure/GroupState'
        dynamic_reconfigure_IntParameter = 'dynamic_reconfigure/IntParameter'
        dynamic_reconfigure_ParamDescription = 'dynamic_reconfigure/ParamDescription'
        dynamic_reconfigure_Reconfigure = 'dynamic_reconfigure/Reconfigure'
        dynamic_reconfigure_ReconfigureRequest = 'dynamic_reconfigure/ReconfigureRequest'
        dynamic_reconfigure_ReconfigureResponse = 'dynamic_reconfigure/ReconfigureResponse'
        dynamic_reconfigure_SensorLevels = 'dynamic_reconfigure/SensorLevels'
        dynamic_reconfigure_StrParameter = 'dynamic_reconfigure/StrParameter'
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
                msgList = cell(28, 1);
                msgList{1} = 'dynamic_reconfigure/BoolParameter';
                msgList{2} = 'dynamic_reconfigure/Config';
                msgList{3} = 'dynamic_reconfigure/ConfigDescription';
                msgList{4} = 'dynamic_reconfigure/DoubleParameter';
                msgList{5} = 'dynamic_reconfigure/Group';
                msgList{6} = 'dynamic_reconfigure/GroupState';
                msgList{7} = 'dynamic_reconfigure/IntParameter';
                msgList{8} = 'dynamic_reconfigure/ParamDescription';
                msgList{9} = 'dynamic_reconfigure/ReconfigureRequest';
                msgList{10} = 'dynamic_reconfigure/ReconfigureResponse';
                msgList{11} = 'dynamic_reconfigure/SensorLevels';
                msgList{12} = 'dynamic_reconfigure/StrParameter';
                msgList{13} = 'dynamics/getCRequest';
                msgList{14} = 'dynamics/getCResponse';
                msgList{15} = 'dynamics/getGRequest';
                msgList{16} = 'dynamics/getGResponse';
                msgList{17} = 'dynamics/getJRequest';
                msgList{18} = 'dynamics/getJResponse';
                msgList{19} = 'dynamics/getMRequest';
                msgList{20} = 'dynamics/getMResponse';
                msgList{21} = 'dynamics/getStaticTorquesRequest';
                msgList{22} = 'dynamics/getStaticTorquesResponse';
                msgList{23} = 'dynamics/getTRequest';
                msgList{24} = 'dynamics/getTResponse';
                msgList{25} = 'dynamics/getTrajTorquesRequest';
                msgList{26} = 'dynamics/getTrajTorquesResponse';
                msgList{27} = 'dynamics/setTorquesRequest';
                msgList{28} = 'dynamics/setTorquesResponse';
            end
            
            messageList = msgList;
        end
        
        function serviceList = getServiceList
            %getServiceList Generate a cell array with all service types.
            %   The list will be sorted alphabetically.
            
            persistent svcList
            if isempty(svcList)
                svcList = cell(9, 1);
                svcList{1} = 'dynamic_reconfigure/Reconfigure';
                svcList{2} = 'dynamics/getC';
                svcList{3} = 'dynamics/getG';
                svcList{4} = 'dynamics/getJ';
                svcList{5} = 'dynamics/getM';
                svcList{6} = 'dynamics/getStaticTorques';
                svcList{7} = 'dynamics/getT';
                svcList{8} = 'dynamics/getTrajTorques';
                svcList{9} = 'dynamics/setTorques';
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
