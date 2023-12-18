/*
  ==============================================================================

    parametricEQ.cpp
    Created: 16 Sep 2023 1:28:22pm
    Author:  Navaneeth Suresh Kumar

  ==============================================================================
*/

#include "parametricEQ.h"


parametricEQ::parametricEQ() {
    a0 = 0.f;
    a1 = 0.f;
    a2 = 0.f;
    b1 = 0.f;
    b2 = 0.f;
    d0 = 0.f;
    w0 = 1.f;

    int numInputs = 2;
    for (int i = 0; i < numInputs; i++) {
        a1_delay.add(0.f);
        a2_delay.add(0.f);
        b1_delay.add(0.f);
        b2_delay.add(0.f);
    }

}
parametricEQ::~parametricEQ() {}

void parametricEQ::updateCoefficients(int f_center, float Q, float gain, double fs) {
    float Pi = juce::MathConstants<float>::pi;
    float theta = 2.f * Pi * f_center / fs;
    float U = powf(10.f, (gain / 20.f));
    float E = 4.f / (1.f + U);
    float B = 0.5f * (1.f - (E * tan(theta / 2.f * Q))) / (1.f + (E * tan(theta / 2.f * Q)));
    float G = (0.5f + B) * cos(theta);

    a0 = 0.5f - B;
    a1 = 0.f;
    a2 = -(0.5f - B);
    b1 = -2.f * G;
    b2 = 2.f * B;
    w0 = U - 1.f;
    d0 = 1.f;


}
void parametricEQ::processAudio(juce::AudioBuffer<float>& buffer) {
    float z = 0.f;
    auto totalNumInputChannels = buffer.getNumChannels();
    for (int i = 0; i < totalNumInputChannels; i++) {
        auto* channelData = buffer.getWritePointer(i);
        for (int n = 0; n < buffer.getNumSamples(); n++) {
            z = (*channelData) * a0 + a1 * a1_delay[i] + a2 * a2_delay[i] - b1 * b1_delay[i] - b2 * b2_delay[i];
            a2_delay.set(i, a1_delay[i]);
            b2_delay.set(i, b1_delay[i]);
            a1_delay.set(i, *channelData);;
            b1_delay.set(i, z);
            *channelData = d0 * (*channelData) + w0 * z;
            channelData++;
        }
    }

}

void parametricEQ::resetDelay(int numInputs){
    
    
    for (int i = 0; i<numInputs; i++){
        a1_delay.set(i, 0.f);
        a2_delay.set(i, 0.f);
        b1_delay.set(i, 0.f);
        b2_delay.set(i, 0.f);
    }
    
}
void parametricEQ::updateDryWetRatio(float ratio){
    d0 = ratio;
    w0 = 1.f - ratio;
    
}
