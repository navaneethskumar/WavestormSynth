classdef parametricEQ
    %PARAMETRICEQ Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
          a0
        a1
        a2
        b1
        b2
        d0
        w0
        
        %delays
        a1_delay
        a2_delay
        b1_delay
        b2_delay
    end
    
    methods
        function obj = parametricEQ(f_center,Q,gain,fs)
            obj=resetDelays(obj);
            obj=updateDryWetRatio(obj,0.5);
            obj=updateCoefficients(obj, f_center,Q,gain,fs);
        end
  function obj = updateCoefficients(obj,f_center,Q,gain,fs)
            theta=2*pi*f_center/fs;
            U = 10^(gain/20);
            E= 4/(1+U);
            B=0.5*(1 - (E*tan(theta/2*Q)))/(1 + (E*tan(theta/2*Q)));
             G=(0.5+B)*cos(theta);

        obj.a0=0.5-B;
        obj.a1 = 0;
        obj.a2 = -(0.5-B);
        obj.b1 = -2*G;
        obj.b2 = 2*B;


            obj.w0 = U-1.0;
            obj.d0= 1;
         
        end
        function[out_buffer]=processAudio(obj,EQ_Fcenter,EQ_Q,EQ_gain,fs,input_buffer)
            obj=obj.updateCoefficients(EQ_Fcenter,EQ_Q,EQ_gain,fs);
           
            z = zeros(length(input_buffer),1);
            x=input_buffer;

            for n = 1:length(x)
                
                z(n) =  (x(n)*obj.a0 + ...
                    obj.a1*obj.a1_delay + obj.a2*obj.a2_delay - obj.b1*obj.b1_delay - obj.b2*obj.b2_delay);
                obj.a2_delay = obj.a1_delay;
                obj.b2_delay = obj.b1_delay;
                obj. a1_delay = x(n);
                obj.b1_delay = z(n);
            end

            out_buffer = obj.d0*x + obj.w0*z;
            
            
        end
        function obj=resetDelays(obj)
            obj.a1_delay=0;
            obj.a2_delay=0;
            obj.b1_delay=0;
            obj.b2_delay=0;

        end
        function obj= updateDryWetRatio(obj,ratio)
            obj.d0=ratio;
            obj.w0=1.0-ratio;

        end
    end
end

