/*
  ==============================================================================

    delayEffect.cpp
    Created: 16 Sep 2023 1:29:07pm
    Author:  Navaneeth Suresh Kumar

  ==============================================================================
*/

#include "delayEffect.h"
delayEffect::delayEffect() {
    //

    readIndexL = 0;
    readIndexR = 0;
    writeIndexL = 0;
    writeIndexR = 0;
    delayBufferSize = 0;
    bufferSize = 0;
    totalNumInputChannels = 0;

    //
}
delayEffect::~delayEffect() {

    //
}
void delayEffect::prepareToPlay(float sampleRate, int samplesPrerBlock, int numInputChannels)
{

    bufferSize = sampleRate * 2;
    this->totalNumInputChannels = numInputChannels;
    delayBufferLeft.resize(bufferSize, 0.0f);
    delayBufferRight.resize(bufferSize, 0.0f);


}

void delayEffect::circularBuffer(juce::AudioBuffer<float>& buffer, float delayLength, float feedback, float dryWet) {

    /*auto delayLength = sampleRate * 1.0;*/
//auto delayBufferSize = delayLength + buffer.getNumSamples();
    //delayBufferSize = delayBufferSize * totalNumInputChannels;
    //delayBuffer.resize(delayBufferSize, 0.f);
    readIndexL = writeIndexL - delayLength ;
    if (readIndexL < 0)
        readIndexL = bufferSize + readIndexL;
    readIndexR = writeIndexR - delayLength ;
    if (readIndexR < 0)
        readIndexR = bufferSize + readIndexR;
    for (int n = 0; n < buffer.getNumSamples(); n++) {


        int index1 = static_cast<int>(readIndexL);
        int index2 = (index1 + 1) % static_cast<int>(bufferSize);
               float fraction = readIndexL - index1;
               float delayedSampleL = delayBufferLeft[index1] + fraction * (delayBufferLeft[index2] - delayBufferLeft[index1]);

               // Update the delay buffer
               delayBufferLeft[writeIndexL] = buffer.getSample(0, n) + delayedSampleL * (feedback / 100.0f);

               // Apply dry/wet mix
               buffer.getWritePointer(0)[n] = buffer.getSample(0, n) * (1 - dryWet / 100.0f) + delayedSampleL * dryWet / 100.0f;

               // Smoothly update the read and write indices (parameter ramping)
               readIndexL += 1.0f;
               if (readIndexL >= bufferSize)
                   readIndexL -= bufferSize;

               writeIndexL += 1.0f;
               if (writeIndexL >= bufferSize)
                   writeIndexL -= bufferSize;

    }
    
    
    
    
                for (int n = 0; n < buffer.getNumSamples(); n++) {

                    int index1 = static_cast<int>(readIndexR);
                    int index2 = (index1 + 1) % static_cast<int>(bufferSize);
                           float fraction = readIndexR - index1;
                           float delayedSampleR = delayBufferRight[index1] + fraction * (delayBufferRight[index2] - delayBufferRight[index1]);

                           // Update the delay buffer
                    delayBufferRight[writeIndexR] = buffer.getSample(1, n) + delayedSampleR * (feedback / 100.0f);

                           // Apply dry/wet mix
                           buffer.getWritePointer(1)[n] = buffer.getSample(1, n) * (1 - dryWet / 100.0f) + delayedSampleR * dryWet / 100.0f;

                           // Smoothly update the read and write indices (parameter ramping)
                           readIndexR += 1.0f;
                           if (readIndexR >= bufferSize)
                               readIndexR -= bufferSize;

                           writeIndexR += 1.0f;
                           if (writeIndexR >= bufferSize)
                               writeIndexR -= bufferSize;
                }


    
    
                
    

//    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
//    {
//
//
//
//            for (int n = 0; n < buffer.getNumSamples(); n++) {
//
//
//                delayBufferLeft[writeIndexL] = buffer.getSample(channel, n) + delayBufferLeft[readIndexL] * (feedback/100);
//                buffer.getWritePointer(channel)[n] = buffer.getSample(channel, n) * (1 - dryWet/100) + delayBufferLeft[writeIndexL] * dryWet/100;
//                //readIndexL += 1;
//                //writeIndexL += 1;
//                readIndexL = (readIndexL + 1) % delayBufferLeft.size();
//                writeIndexL = (writeIndexL + 1) % delayBufferLeft.size();
//
//
//            }
//
//            for (int n = 0; n < buffer.getNumSamples(); n++) {
//
//                delayBufferRight[writeIndexR] = buffer.getSample(channel, n) + delayBufferRight[readIndexR] * (feedback/100);
//                buffer.getWritePointer(channel)[n] = buffer.getSample(channel, n) * (1 - dryWet/100) + delayBufferRight[writeIndexR] * dryWet/100;
//                    writeIndexR = (writeIndexR + 1 )% delayBufferRight.size();
//
//
//                    readIndexR = ( readIndexR + 1 )% delayBufferRight.size();
//
//            }
//
//
//    }



};
