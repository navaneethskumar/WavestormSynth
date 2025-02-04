classdef outputGain
    %OUTPUTGAIN Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        GainDB
    end
    
    methods
        function obj = outputGain()
            %OUTPUTGAIN Construct an instance of this class
            %   Detailed explanation goes here
            obj.GainDB = 2.0;
        end
        
        function obj = setGain(obj,gainInDecibels)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            obj.GainDB = gainInDecibels;
        end
        function output = processAudio(obj,input)
            
            
                output =  10^(obj.GainDB/20.0) * input;
               
      
        end    

    end
end

