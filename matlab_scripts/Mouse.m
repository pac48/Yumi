classdef Mouse < handle
    %UNTITLED2 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        xpos=0
        ypos=0
        oldx=0;
        oldy=0;
        xvel=0
        yvel=0
        t=0;
        scale
    end
    
    methods
        function obj = Mouse(scale)
            obj.scale=scale;
            tic
        end
        
        function mouseMove (obj)%,object, eventdata)
            dt= toc-obj.t;
            obj.t = toc;
            figure(1)
            f= gcf;
            f.WindowButtonDownFcn();
            %C = get(gca, 'CurrentPoint');
            res=[2560,1440];
            C = get(0, 'PointerLocation');
            C=(C)./res;
            obj.oldx=(obj.xpos);
            obj.oldy=(obj.ypos);
            obj.xpos=(C(1)-.5)*obj.scale;
            obj.ypos=(C(2)-.5)*obj.scale;
            obj.xvel=.0*obj.xvel+1*(obj.xpos-obj.oldx)/dt;
            obj.yvel=.0*obj.yvel+1*(obj.ypos-obj.oldy)/dt;
        end
    end
end

