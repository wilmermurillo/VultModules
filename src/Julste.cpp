/*
Copyright (c) 2017 Leonardo Laguna Ruiz (modlfo@gmail.com), All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1.- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2.- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
3.- Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
4.- Commercial use requires explicit permission of the author.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "VultModules.hpp"
#include "math.hpp"
#include "VultEngine.h"

struct Julste : Module
{
   enum ParamIds
   {
      OFFSET_PARAM,
      RESONANCE_PARAM,
      OFFSET_AMT_PARAM,
      RESONANCE_AMT_PARAM,
      SHARPNESS_PARAM,
      SHARPNESS_AMT_PARAM,
      MODE_PARAM,
      NUM_PARAMS
   };
   enum InputIds
   {
      GATE_INPUT,
      AUDIO_INPUT,
      OFFSET_INPUT,
      RESONANCE_INPUT,
      SHARPNESS_INPUT,
      NUM_INPUTS
   };
   enum OutputIds
   {
      AUDIO_OUTPUT,
      NUM_OUTPUTS
   };

   Julste_julste_type processor;

   Julste();
   void step() override;
};

Julste::Julste() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS)
{
   params.resize(NUM_PARAMS);
   inputs.resize(NUM_INPUTS);
   outputs.resize(NUM_OUTPUTS);
   Julste_julste_init(processor);
}

void Julste::step()
{

   float audio = inputs[AUDIO_INPUT].value / 5.0;
   float gate = inputs[GATE_INPUT].value / 5.0;

   float offset_knob = params[OFFSET_PARAM].value;
   float offset_cv = inputs[OFFSET_INPUT].value / 5.0;
   float offset_amt = params[OFFSET_AMT_PARAM].value;
   float offset = offset_knob + offset_amt * offset_cv;

   float resonance_knob = params[RESONANCE_PARAM].value;
   float resonance_cv = inputs[RESONANCE_INPUT].value / 5.0;
   float resonance_amt = params[RESONANCE_AMT_PARAM].value;
   float resonance = resonance_knob + resonance_amt * resonance_cv;

   float sharpness_knob = params[SHARPNESS_PARAM].value;
   float sharpness_cv = inputs[SHARPNESS_INPUT].value / 5.0;
   float sharpness_amt = params[SHARPNESS_AMT_PARAM].value;
   float sharpness = sharpness_knob + sharpness_amt * sharpness_cv;

   float out = Julste_julste(processor, gate, audio, offset, resonance, sharpness, params[MODE_PARAM].value, 1.0);

   outputs[AUDIO_OUTPUT].value = out * 5.0;

}

JulsteWidget::JulsteWidget()
{
   Julste *module = new Julste();
   setModule(module);
   box.size = Vec(15 * 10, 380);

   {
      SVGPanel *panel = new SVGPanel();
      panel->box.size = box.size;
      panel->setBackground(SVG::load(assetPlugin(plugin, "res/Julste.svg")));
      addChild(panel);
   }

   addChild(createScrew<VultScrew>(Vec(16, 0)));
   addChild(createScrew<VultScrew>(Vec(box.size.x - 29, 0)));
   addChild(createScrew<VultScrew>(Vec(16, 365)));
   addChild(createScrew<VultScrew>(Vec(box.size.x - 29, 365)));

   addParam(createParam<VultKnob>(Vec(34, 66), module, Julste::OFFSET_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<VultKnobSmall>(Vec(108, 66), module, Julste::OFFSET_AMT_PARAM, -1.0, 1.0, 0.0));
   addInput(createInput<VultJack>(Vec(105, 91), module, Julste::OFFSET_INPUT));

   addParam(createParam<VultKnob>(Vec(34, 131), module, Julste::RESONANCE_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<VultKnobSmall>(Vec(108, 131), module, Julste::RESONANCE_AMT_PARAM, -1.0, 1.0, 0.0));
   addInput(createInput<VultJack>(Vec(105, 156), module, Julste::RESONANCE_INPUT));

   addParam(createParam<VultKnob>(Vec(34, 196), module, Julste::SHARPNESS_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<VultKnobSmall>(Vec(108, 198), module, Julste::SHARPNESS_AMT_PARAM, -1.0, 1.0, 0.0));
   addInput(createInput<VultJack>(Vec(105, 223), module, Julste::SHARPNESS_INPUT));

   addParam(createParam<VultSelector2>(Vec(29, 270), module, Julste::MODE_PARAM, 0.0, 1.0, 0.0));

   addInput(createInput<VultJack>(Vec(14, 318), module, Julste::GATE_INPUT));
   addInput(createInput<VultJack>(Vec(63, 318), module, Julste::AUDIO_INPUT));
   addOutput(createOutput<VultJack>(Vec(111, 318), module, Julste::AUDIO_OUTPUT));
}
