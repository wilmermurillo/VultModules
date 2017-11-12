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

struct Spank : Module
{
   enum ParamIds
   {
      ATTACK_PARAM,
      HOLD_PARAM,
      RELEASE_PARAM,
      ATTACK_AMT_PARAM,
      HOLD_AMT_PARAM,
      RELEASE_AMT_PARAM,
      MODE_PARAM,
      NUM_PARAMS
   };
   enum InputIds
   {
      GATE_INPUT,
      ATTACK_INPUT,
      HOLD_INPUT,
      RELEASE_INPUT,
      AUDIO_INPUT,
      NUM_INPUTS
   };
   enum OutputIds
   {
      AUDIO_OUTPUT,
      ENV_OUTPUT,
      NUM_OUTPUTS
   };

   VultEngine_spank_type processor;

   Spank();
   void step() override;
};

Spank::Spank() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS)
{
   params.resize(NUM_PARAMS);
   inputs.resize(NUM_INPUTS);
   outputs.resize(NUM_OUTPUTS);
   VultEngine_spank_init(processor);
}

void Spank::step()
{

   float audio = inputs[AUDIO_INPUT].value / 5.0;
   float gate = inputs[GATE_INPUT].value / 5.0;

   float attack_knob = params[ATTACK_PARAM].value;
   float attack_cv = inputs[ATTACK_INPUT].value / 5.0;
   float attack_amt = params[ATTACK_AMT_PARAM].value;
   float attack = attack_knob + attack_amt * attack_cv;

   float hold_knob = params[HOLD_PARAM].value;
   float hold_cv = inputs[HOLD_INPUT].value / 5.0;
   float hold_amt = params[HOLD_AMT_PARAM].value;
   float hold = hold_knob + hold_amt * hold_cv;

   float release_knob = params[RELEASE_PARAM].value;
   float release_cv = inputs[RELEASE_INPUT].value / 5.0;
   float release_amt = params[RELEASE_AMT_PARAM].value;
   float release = release_knob + release_amt * release_cv;

   float mode = params[MODE_PARAM].value;
   _tuple___real_real__ out;

   VultEngine_spank(processor, gate, audio, attack, hold, release, mode, out);

   outputs[ENV_OUTPUT].value = out.field_0 * 5.0;
   outputs[AUDIO_OUTPUT].value = out.field_1 * 5.0;
}

SpankWidget::SpankWidget()
{
   Spank *module = new Spank();
   setModule(module);
   box.size = Vec(15 * 10, 380);

   {
      SVGPanel *panel = new SVGPanel();
      panel->box.size = box.size;
      panel->setBackground(SVG::load(assetPlugin(plugin, "res/Spank.svg")));
      addChild(panel);
   }
   addChild(createScrew<VultScrew>(Vec(16, 0)));
   addChild(createScrew<VultScrew>(Vec(box.size.x - 29, 0)));
   addChild(createScrew<VultScrew>(Vec(16, 365)));
   addChild(createScrew<VultScrew>(Vec(box.size.x - 29, 365)));

   addParam(createParam<VultKnob>(Vec(30, 67), module, Spank::ATTACK_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<VultKnob>(Vec(30, 134), module, Spank::HOLD_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<VultKnob>(Vec(30, 200), module, Spank::RELEASE_PARAM, 0.0, 1.0, 0.0));

   addParam(createParam<VultKnobSmall>(Vec(104, 67), module, Spank::ATTACK_AMT_PARAM, -1.0, 1.0, 0.0));
   addParam(createParam<VultKnobSmall>(Vec(104, 134), module, Spank::HOLD_AMT_PARAM, -1.0, 1.0, 0.0));
   addParam(createParam<VultKnobSmall>(Vec(104, 200), module, Spank::RELEASE_AMT_PARAM, -1.0, 1.0, 0.0));

   addParam(createParam<VultSelector3>(Vec(18, 265), module, Spank::MODE_PARAM, 0.0, 2.0, 0.0));

   addInput(createInput<VultJack>(Vec(100, 93), module, Spank::ATTACK_INPUT));
   addInput(createInput<VultJack>(Vec(100, 160), module, Spank::HOLD_INPUT));
   addInput(createInput<VultJack>(Vec(100, 227), module, Spank::RELEASE_INPUT));

   addInput(createInput<VultJack>(Vec(65, 274), module, Spank::AUDIO_INPUT));
   addOutput(createOutput<VultJack>(Vec(101, 274), module, Spank::AUDIO_OUTPUT));

   addInput(createInput<VultJack>(Vec(31, 322), module, Spank::GATE_INPUT));
   addOutput(createOutput<VultJack>(Vec(102, 322), module, Spank::ENV_OUTPUT));
}
