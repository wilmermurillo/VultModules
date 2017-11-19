/*
Copyright (c) 2017 Leonardo Laguna Ruiz (modlfo@gmail.com), All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1.- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2.- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
3.- Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
4.- Commercial use requires explicit permission of the author.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <math.h>
#include "VultModules.hpp"

float getSampleRate()
{
   return engineGetSampleRate();
}

Plugin *plugin;

void init(rack::Plugin *p)
{
   plugin = p;
   p->slug = "VultModules";
#ifdef VERSION
   p->version = TOSTRING(VERSION);
#endif
   p->addModel(createModel<DebriatusWidget>("Vult", "Debriatus", "Debriatus", DISTORTION_TAG, WAVESHAPER_TAG, EFFECT_TAG));
   p->addModel(createModel<LateralusWidget>("Vult", "Lateralus", "Lateralus", FILTER_TAG, OSCILLATOR_TAG));
   p->addModel(createModel<RescombWidget>("Vult", "Rescomb", "Rescomb", FILTER_TAG, EFFECT_TAG));
   p->addModel(createModel<SpankWidget>("Vult", "Spank", "Spank", ENVELOPE_GENERATOR_TAG, AMPLIFIER_TAG));
   p->addModel(createModel<SplieWidget>("Vult", "Splie", "Splie", UTILITY_TAG));
   p->addModel(createModel<StabileWidget>("Vult", "Stabile", "Stabile", FILTER_TAG));
   p->addModel(createModel<TangentsWidget>("Vult", "Tangents", "Tangents", FILTER_TAG, OSCILLATOR_TAG));
   p->addModel(createModel<ToheWidget>("Vult", "Tohe", "Tohe", FILTER_TAG, EQUALIZER_TAG));
   p->addModel(createModel<TrummorWidget>("Vult", "Trummor", "Trummor", DRUM_TAG, ENVELOPE_GENERATOR_TAG, NOISE_TAG));
   p->addModel(createModel<Trummor2Widget>("Vult", "Trummor2", "Trummor 2", DRUM_TAG, ENVELOPE_GENERATOR_TAG, NOISE_TAG));
   p->addModel(createModel<UnstabileWidget>("Vult", "Unstabile", "Unstabile", FILTER_TAG));
}
