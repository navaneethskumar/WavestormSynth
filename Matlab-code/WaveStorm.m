classdef WaveStorm < audioPlugin
    properties
        Delay = 0.4 % Default delay time in seconds
        DryWet = 20 % Default Dry/Wet mix
        fb = 20        
        fs % Sample rate (initialize it in the constructor)
        EQ_Fcenter = 1000 % Default center frequency for the EQ
        EQ_Q = 0.5 % Default Q factor for the EQ
        EQ_gain = 2 % Default output gain in dB
        outGain=0
    end
    
    properties (Constant)
        PluginInterface = audioPluginInterface(...
            audioPluginParameter('Delay', ...
                'DisplayName', 'Delay Time', ...
                'Label', 's', ...
                'Mapping', { 'lin', 0.001, 2 }), ... % Adjust the range as needed
            audioPluginParameter('DryWet', ...
                'DisplayName', 'Dry/Wet Mix', ...
                'Label', '%', ...
                'Mapping', { 'lin', 0, 100 }), ...
            audioPluginParameter('fb', ...
                'DisplayName', 'Feedback', ...
                'Label', '%', ...
                'Mapping', { 'lin', 0, 100 }), ...
            audioPluginParameter('EQ_Fcenter', ...
                'DisplayName', 'EQ Center Frequency', ...
                'Label', 'Hz', ...
                'Mapping', { 'log', 20, 20000 }), ...
            audioPluginParameter('EQ_Q', ...
                'DisplayName', 'EQ Q Factor', ...
                'Label', '', ...
                'Mapping', { 'lin', 0.1, 2 }),...
            audioPluginParameter('EQ_gain', ...
                'DisplayName', 'EQ Gain', ...
                'Label', 'dB', ...
                'Mapping', { 'lin', -10, 10 }), ...
            audioPluginParameter('outGain', ...
                'DisplayName', 'Output Gain', ...
                'Label', 'dB', ...
                'Mapping', { 'lin', -20.0, 20.0 }));
             
    end
    
    properties (Access = private)
        delayBuffer
        readIndex
        writeIndex
        buff_length
        EQ
        %GainControl

        %GainControl
    end
    
    methods
        function plugin = WaveStorm()
            % Constructor
            plugin.fs = 44100; % Default sample rate
            plugin.Delay=0.5;
            plugin.fb = 50; % Default feedback
            plugin.outGain = 0.5; % Default output gain
            plugin.buff_length = 480; % Adjust buffer size as needed
            plugin.delayBuffer = zeros(1, plugin.fs*2 + plugin.buff_length );
            plugin.readIndex = 1;
            plugin.writeIndex = round(plugin.Delay * plugin.fs) + 1; % Default delay lengt          
            % Create an instance of the Parametric EQ
            plugin.EQ = parametricEQ(plugin.EQ_Fcenter, plugin.EQ_Q, plugin.EQ_gain, plugin.fs);
            % Create an instance of the gainControl
            %plugin.GainControl = outputGain();
        end
        
        % function reset(plugin)
        %     % Reset the delay buffer and indices
        %     bufferLength = plugin.fs * 2; % Adjust buffer size as needed
        %     plugin.delayBuffer = zeros(1, bufferLength);
        %     plugin.readIndex = 1;
        %     plugin.writeIndex = round(plugin.Delay * plugin.fs) + 1; % Reset delay length
        % end
        % 
        function [output,plugin] = process(plugin, input)
%             Process audio input through the Long Delay effect
            
            output = zeros(size(input));
            
            % Process each sample in the input
            for n = 1:length(input)
%                 plugin.delayBuffer(plugin.writeIndex)=input(n);
%                 
%                 output(n)= plugin.delayBuffer(plugin.writeIndex)* (1 - plugin.DryWet/100)+(plugin.fb/100)*(plugin.delayBuffer(plugin.readIndex))* (plugin.DryWet/100);          
%                 
                delayed_signal=plugin.delayBuffer(plugin.readIndex);
                plugin.delayBuffer(plugin.writeIndex)=input(n)+delayed_signal*plugin.fb/100;
                output(n)= input(n)* (1 - plugin.DryWet/100)+delayed_signal* (plugin.DryWet/100);
                % Update read and write indices, with wrap-around
                plugin.readIndex = plugin.readIndex + 1;
                plugin.writeIndex = plugin.writeIndex + 1;
                if plugin.writeIndex >length(plugin.delayBuffer)
                      plugin.writeIndex = mod(plugin.writeIndex,length(plugin.delayBuffer));
                end
            
                 if plugin.readIndex >length(plugin.delayBuffer)
                        plugin.readIndex = mod(plugin.readIndex,length(plugin.delayBuffer));
                 end
                 
            end

            %
            
            %process audio through the EQ

           output = plugin.EQ.processAudio(plugin.EQ_Fcenter, plugin.EQ_Q, plugin.EQ_gain, plugin.fs,output);

            % Apply output gain to the buffer (convert dB to linear)
           output = 10^(plugin.outGain / 20) * output;

           %plugin.GainControl = plugin.GainControl.setGain(plugin.outGain);
           %output = plugin.GainControl.processAudio(output);

        end
    end
end
