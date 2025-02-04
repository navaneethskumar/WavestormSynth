classdef oscillator_class<audioPlugin
    %OSCILLATOR_CLASS Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        Type = 'Sinusoidal'
        Fo = 1000
        Gain = 0.70
    end
    properties(Access = private)
        circularBuffer = zeros(192001,1)
        bufferIndex = 1
        modVal = -1
        modSquareVal = 1
      
    end
    properties (Constant)
        PluginInterface = audioPluginInterface(...
            audioPluginParameter('Type','Mapping', ...
            {'enum','Sinusoidal','Square','Triangle','Sawtooth'}),...
            audioPluginParameter('Fo','Mapping',{'lin',20,20000}),...
            audioPluginParameter('Gain','Mapping',{'lin',0.0,1.0}));
    end    

    methods
        function plugin = oscillator_class(buff_length)
            plugin.circularBuffer = zeros(buff_length,1);
        end

        function[out , plugin] = process(plugin)
            for i=1:length(plugin.circularBuffer)
                plugin = modulo_counter(plugin);
                switch plugin.Type
                    case 'Sinusoidal'
                        plugin.circularBuffer(i) = plugin.Gain * sin(2*pi*plugin.modVal);
                    case 'Sawtooth'
                        plugin.circularBuffer(i) = plugin.Gain * plugin.modVal;  
                    case 'Triangle'
                        plugin.circularBuffer(i) = plugin.Gain * (2 * abs(plugin.modVal)-1);
                    case 'Square'
                        plugin.circularBuffer(i) = plugin.Gain * (plugin.modSquareVal);
                    otherwise
                        plugin.circularBuffer(i) = plugin.Gain * sin(2*pi*plugin.modVal);
                        
                end    

            end   
            out = plugin.circularBuffer;
        end    
        function plugin = modulo_counter(plugin)
            inc = plugin.Fo/getSampleRate(plugin);
            plugin.modVal = plugin.modVal + inc;
            if plugin.modVal > 1
                plugin.modVal = plugin.modVal - 2;
                plugin.modSquareVal = plugin.modSquareVal * -1;
            end    
        end    
    end    
end   
