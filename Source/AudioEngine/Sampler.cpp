/*
  ==============================================================================

    Sampler.cpp
    Created: 17 Apr 2018 1:12:15pm
    Author:  Matthias Pueski

  ==============================================================================
*/

#include "Sampler.h"
#include "Project.h"


Sampler::Sampler(float sampleRate, int bufferSize) {
    this->sampleRate = sampleRate;
    this->bufferSize = bufferSize;
    this->manager = Project::getInstance()->getFormatManager();
}

Sampler::~Sampler() {
    if(sampleBuffer != nullptr) {
        delete sampleBuffer;
    }
}

void Sampler::nextSample() {
    if (sampleLength > 0)
        currentSample = (currentSample + 1) % sampleLength;
}

void Sampler::play() {
}

void Sampler::stop() {
}

float Sampler::getCurrentSample(int channel){
    if (sampleBuffer != nullptr && sampleLength > 0)
        return sampleBuffer->getSample(channel, currentSample) * volume;
    
    return 0;
}

float Sampler::getSampleAt(int channel, long pos){
    return sampleBuffer->getSample(channel, pos) * volume;
}

void Sampler::loadSample(File file) {
    AudioFormatReader* reader = manager->createReaderFor(file);
    ScopedPointer<AudioFormatReaderSource> afr = new AudioFormatReaderSource(reader, true);
    sampleBuffer = new AudioSampleBuffer(2, reader->lengthInSamples);
    reader->read(sampleBuffer, 0, reader->lengthInSamples, 0, true, true);
    sampleLength = reader->lengthInSamples;
    endPosition = sampleLength;
    startPosition = 0;
    loaded = true;
}

void Sampler::loadSample(InputStream* input) {
    AudioFormatReader* reader = manager->createReaderFor(input);
    ScopedPointer<AudioFormatReaderSource> afr = new AudioFormatReaderSource(reader, true);
    sampleBuffer = new AudioSampleBuffer(2, reader->lengthInSamples);
    reader->read(sampleBuffer, 0, reader->lengthInSamples, 0, true, true);
    sampleLength = reader->lengthInSamples;
    endPosition = sampleLength;
    startPosition = 0;
    loaded = true;
}


void Sampler::setStartPosition(long start) {
    this->startPosition = start;
}

long Sampler::getStartPosition() {
    return startPosition;
}

void Sampler::setEndPosition(long end) {
    this->endPosition = end;
}

long Sampler::getEndPosition() {
    return this->endPosition;
}

void Sampler::setSampleLength(long length) {
    this->sampleLength = length;
}

long Sampler::getSampleLength(){
    return this->sampleLength;
}

void Sampler::setLoop(bool loop) {
    this->loop = loop;
}

bool Sampler::isLoop() {
    return this->loop;
}

void Sampler::setVolume(float volume) {
    this->volume = volume;
}

AudioSampleBuffer* Sampler::getSampleBuffer(){
    return sampleBuffer;
}
bool Sampler::hasSample() {
    return loaded;
}
