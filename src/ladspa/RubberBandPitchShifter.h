/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */

/*
    Rubber Band
    An audio time-stretching and pitch-shifting library.
    Copyright 2007 Chris Cannam.
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.  See the file
    COPYING included with this distribution for more information.
*/

#ifndef _RUBBERBAND_PITCH_SHIFTER_H_
#define _RUBBERBAND_PITCH_SHIFTER_H_

#include <ladspa.h>

#include "RingBuffer.h"

namespace RubberBand {
class RubberBandStretcher;
}

class RubberBandPitchShifter
{
public:
    static const LADSPA_Descriptor *getDescriptor(unsigned long index);
    
protected:
    RubberBandPitchShifter(int sampleRate, size_t channels);
    ~RubberBandPitchShifter();

    enum {
        LatencyPort      = 0,
	OctavesPort      = 1,
	SemitonesPort    = 2,
	CentsPort        = 3,
        InputPort1       = 4,
        OutputPort1      = 5,
        PortCountMono    = 6,
        InputPort2       = 6,
        OutputPort2      = 7,
        PortCountStereo  = 8
    };

    static const char *const portNamesMono[PortCountMono];
    static const LADSPA_PortDescriptor portsMono[PortCountMono];
    static const LADSPA_PortRangeHint hintsMono[PortCountMono];

    static const char *const portNamesStereo[PortCountStereo];
    static const LADSPA_PortDescriptor portsStereo[PortCountStereo];
    static const LADSPA_PortRangeHint hintsStereo[PortCountStereo];

    static const LADSPA_Properties properties;

    static const LADSPA_Descriptor ladspaDescriptorMono;
    static const LADSPA_Descriptor ladspaDescriptorStereo;

    static LADSPA_Handle instantiate(const LADSPA_Descriptor *, unsigned long);
    static void connectPort(LADSPA_Handle, unsigned long, LADSPA_Data *);
    static void activate(LADSPA_Handle);
    static void run(LADSPA_Handle, unsigned long);
    static void deactivate(LADSPA_Handle);
    static void cleanup(LADSPA_Handle);

    void runImpl(unsigned long);
    void updateRatio();

    float *m_input[2];
    float *m_output[2];
    float *m_latency;
    float *m_cents;
    float *m_semitones;
    float *m_octaves;
    double m_ratio;
    double m_prevRatio;

    size_t m_extraLatency;

    RubberBand::RubberBandStretcher *m_stretcher;
    RubberBand::RingBuffer<float> *m_outputBuffer[2];
    float *m_scratch[2];

    int m_sampleRate;
    size_t m_channels;
};


#endif
