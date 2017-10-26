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

struct Trummor2 : Module
{
   enum ParamIds
   {
      LEVEL1_PARAM,
      LEVEL2_PARAM,
      ENV1_A_PARAM,
      ENV1_H_PARAM,
      ENV1_R_PARAM,
      ENV2_A_PARAM,
      ENV2_H_PARAM,
      ENV2_R_PARAM,
      PITCH_PARAM,
      BEND_PARAM,
      DRIVE_PARAM,
      TONE_PARAM,
      OSC_BLEND_PARAM,
      NOISE_BLEND_PARAM,
      SEL_ENV1_PARAM,
      SEL_ENV2_PARAM,
      DECIMATE_PARAM,
      OSC_MOD_PARAM,
      NOISE_MOD_PARAM,
      OSC_SEL_PARAM,
      NOISE_SEL_PARAM,
      RING_SEL_PARAM,
      BEND_TIME_PARAM,
      SUB_PARAM,
      CHEBY_PARAM,
      CUTOFF_PARAM,
      RESONANCE_PARAM,
      NUM_PARAMS
   };
   enum InputIds
   {
      GATE_INPUT,
      OSC_INPUT,
      NOISE_INPUT,
      OSC_MOD_INPUT,
      NOISE_MOD_INPUT,
      NUM_INPUTS
   };
   enum OutputIds
   {
      AUDIO_OUTPUT,
      PITCH_OUTPUT,
      ENV1_OUTPUT,
      ENV2_OUTPUT,
      NUM_OUTPUTS
   };

   Trummor2_do_type processor;

   Trummor2();
   void step();
};

Trummor2::Trummor2() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS)
{
   params.resize(NUM_PARAMS);
   inputs.resize(NUM_INPUTS);
   outputs.resize(NUM_OUTPUTS);
   Trummor2_do_init(processor);
}

void Trummor2::step()
{

   Trummor2_setLevel1(processor, params[LEVEL1_PARAM].value);
   Trummor2_setLevel2(processor, params[LEVEL2_PARAM].value);

   Trummor2_setEnv1A(processor, params[ENV1_A_PARAM].value);
   Trummor2_setEnv1H(processor, params[ENV1_H_PARAM].value);
   Trummor2_setEnv1R(processor, params[ENV1_R_PARAM].value);

   Trummor2_setEnv2A(processor, params[ENV2_A_PARAM].value);
   Trummor2_setEnv2H(processor, params[ENV2_H_PARAM].value);
   Trummor2_setEnv2R(processor, params[ENV2_R_PARAM].value);

   Trummor2_setPitch(processor, params[PITCH_PARAM].value);
   Trummor2_setBend(processor, params[BEND_PARAM].value);
   Trummor2_setDrive(processor, params[DRIVE_PARAM].value);

   Trummor2_setTone(processor, params[TONE_PARAM].value);

   Trummor2_setOscBlend(processor, params[OSC_BLEND_PARAM].value);
   Trummor2_setNoiseBlend(processor, params[NOISE_BLEND_PARAM].value);

   Trummor2_setEnv1Scale(processor, params[SEL_ENV1_PARAM].value);
   Trummor2_setEnv2Scale(processor, params[SEL_ENV2_PARAM].value);

   Trummor2_setDecimate(processor, params[DECIMATE_PARAM].value);

   Trummor2_setRingSel(processor, params[RING_SEL_PARAM].value);

   Trummor2_setBendTime(processor, params[BEND_TIME_PARAM].value);

   Trummor2_setSub(processor, params[SUB_PARAM].value);

   Trummor2_setCheby(processor, params[CHEBY_PARAM].value);

   Trummor2_setCutoff(processor, params[CUTOFF_PARAM].value);
   Trummor2_setResonance(processor, params[RESONANCE_PARAM].value);

   int osc_sel = round(params[OSC_SEL_PARAM].value);
   float osc_mod = params[OSC_MOD_PARAM].value * inputs[OSC_MOD_INPUT].value / 5.0;
   switch (osc_sel)
   {
   case 0:
      Trummor2_setPitch(processor, osc_mod / 2.0f + params[PITCH_PARAM].value);
      break;
   case 1:
      Trummor2_setBend(processor, (osc_mod + params[BEND_PARAM].value));
      break;
   case 2:
      Trummor2_setDrive(processor, (osc_mod + params[DRIVE_PARAM].value));
      break;
   case 3:
      Trummor2_setEnv1A(processor, (osc_mod + params[ENV1_A_PARAM].value));
      break;
   case 4:
      Trummor2_setEnv1H(processor, (osc_mod + params[ENV1_H_PARAM].value));
      break;
   case 5:
      Trummor2_setEnv1R(processor, (osc_mod + params[ENV1_R_PARAM].value));
      break;
   case 6:
      Trummor2_setEnv1Scale(processor, (osc_mod + params[SEL_ENV1_PARAM].value));
      break;
   case 7:
      Trummor2_setOscBlend(processor, (osc_mod + params[OSC_BLEND_PARAM].value));
      break;
   case 8:
      Trummor2_setLevel1(processor, (osc_mod + params[LEVEL1_PARAM].value));
      break;
   }

   int noise_sel = round(params[NOISE_SEL_PARAM].value);
   float noise_mod = params[NOISE_MOD_PARAM].value * inputs[NOISE_MOD_INPUT].value / 5.0;

   switch (noise_sel)
   {
   case 0:
      Trummor2_setTone(processor, (noise_mod + params[TONE_PARAM].value));
      break;
   case 1:
      Trummor2_setDecimate(processor, (noise_mod + params[DECIMATE_PARAM].value));
      break;
   case 2:
      Trummor2_setEnv2A(processor, (noise_mod + params[ENV2_A_PARAM].value));
      break;
   case 3:
      Trummor2_setEnv2H(processor, (noise_mod + params[ENV2_H_PARAM].value));
      break;
   case 4:
      Trummor2_setEnv2R(processor, (noise_mod + params[ENV2_R_PARAM].value));
      break;
   case 5:
      Trummor2_setEnv2Scale(processor, (noise_mod + params[SEL_ENV2_PARAM].value));
      break;
   case 6:
      Trummor2_setNoiseBlend(processor, (noise_mod + params[NOISE_BLEND_PARAM].value));
      break;
   case 7:
      Trummor2_setLevel2(processor, (noise_mod + params[LEVEL2_PARAM].value));
      break;
   }

   _tuple___real_real_real_real__ out;
   Trummor2_do(processor, inputs[GATE_INPUT].value / 10.0f, inputs[OSC_INPUT].value / 10.0f, inputs[NOISE_INPUT].value / 10.0f, out);

   outputs[AUDIO_OUTPUT].value = out.field_0 * 10.0f;
   outputs[PITCH_OUTPUT].value = (out.field_1 - 0.3f) * 10.0f;
   outputs[ENV1_OUTPUT].value = out.field_2 * 10.0f;
   outputs[ENV2_OUTPUT].value = out.field_3 * 10.0f;
}

Trummor2Widget::Trummor2Widget()
{
   Trummor2 *module = new Trummor2();
   setModule(module);
   box.size = Vec(300, 380);

   {
      SVGPanel *panel = new SVGPanel();
      panel->box.size = box.size;
      panel->setBackground(SVG::load(assetPlugin(plugin, "res/Trummor2.svg")));
      addChild(panel);
   }
   addChild(createScrew<VultScrew>(Vec(16, 0)));
   addChild(createScrew<VultScrew>(Vec(box.size.x - 29, 0)));
   addChild(createScrew<VultScrew>(Vec(16, 365)));
   addChild(createScrew<VultScrew>(Vec(box.size.x - 29, 365)));

   addParam(createParam<VultKnob>(Vec(101, 201), module, Trummor2::LEVEL1_PARAM, 0.0, 1.0, 0.7));
   addParam(createParam<VultKnob>(Vec(244, 201), module, Trummor2::LEVEL2_PARAM, 0.0, 1.0, 0.1));

   addParam(createParam<VultKnobAlt>(Vec(17, 153), module, Trummor2::ENV1_A_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<VultKnobAlt>(Vec(63, 153), module, Trummor2::ENV1_H_PARAM, 0.0, 1.0, 0.2));
   addParam(createParam<VultKnobAlt>(Vec(110, 153), module, Trummor2::ENV1_R_PARAM, 0.0, 1.0, 0.2));

   addParam(createParam<VultKnobAlt>(Vec(160, 153), module, Trummor2::ENV2_A_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<VultKnobAlt>(Vec(206, 153), module, Trummor2::ENV2_H_PARAM, 0.0, 1.0, 0.05));
   addParam(createParam<VultKnobAlt>(Vec(252, 153), module, Trummor2::ENV2_R_PARAM, 0.0, 1.0, 0.05));

   addParam(createParam<VultKnobAlt>(Vec(17, 59), module, Trummor2::PITCH_PARAM, -0.1, 0.3, 0.0));
   addParam(createParam<VultKnobAlt>(Vec(63, 59), module, Trummor2::BEND_PARAM, -1.0, 1.0, 0.5));
   addParam(createParam<VultKnobAlt>(Vec(110, 59), module, Trummor2::DRIVE_PARAM, 0.0, 4.0, 0.0));

   addParam(createParam<VultKnobAlt>(Vec(160, 59), module, Trummor2::TONE_PARAM, -1.0, 1.0, -0.7));

   addParam(createParam<VultKnobAlt>(Vec(53, 207), module, Trummor2::OSC_BLEND_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<VultKnobAlt>(Vec(195, 207), module, Trummor2::NOISE_BLEND_PARAM, 0.0, 1.0, 0.0));

   addParam(createParam<VultSelector2>(Vec(12, 203), module, Trummor2::SEL_ENV1_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<VultSelector2>(Vec(155, 203), module, Trummor2::SEL_ENV2_PARAM, 0.0, 1.0, 0.0));

   addInput(createInput<VultJack>(Vec(77, 350), module, Trummor2::GATE_INPUT));

   addInput(createInput<VultJack>(Vec(14, 312), module, Trummor2::OSC_INPUT));
   addInput(createInput<VultJack>(Vec(157, 312), module, Trummor2::NOISE_INPUT));

   addOutput(createOutput<VultJack>(Vec(197, 350), module, Trummor2::AUDIO_OUTPUT));

   addOutput(createOutput<VultJack>(Vec(117, 312), module, Trummor2::PITCH_OUTPUT));

   addOutput(createOutput<VultJack>(Vec(66, 312), module, Trummor2::ENV1_OUTPUT));
   addOutput(createOutput<VultJack>(Vec(212, 312), module, Trummor2::ENV2_OUTPUT));

   addInput(createInput<VultJack>(Vec(13, 256), module, Trummor2::OSC_MOD_INPUT));
   addInput(createInput<VultJack>(Vec(156, 256), module, Trummor2::NOISE_MOD_INPUT));

   addParam(createParam<VultKnobSmall>(Vec(50, 259), module, Trummor2::OSC_MOD_PARAM, -1.0, 1.0, 0.0));
   addParam(createParam<VultKnobSmall>(Vec(193, 259), module, Trummor2::NOISE_MOD_PARAM, -1.0, 1.0, 0.0));

   addParam(createParam<TrummodNoiseSelector>(Vec(218, 261), module, Trummor2::NOISE_SEL_PARAM, 0.0, 7.0, 0.0));
   addParam(createParam<TrummodOscSelector>(Vec(75, 261), module, Trummor2::OSC_SEL_PARAM, 0.0, 8.0, 0.0));

   addParam(createParam<VultKnobAlt>(Vec(208, 59), module, Trummor2::DECIMATE_PARAM, 0.0, 1.0, 0.0));

   // Ring modulator
   addParam(createParam<VultSelector2>(Vec(254, 62), module, Trummor2::RING_SEL_PARAM, 0.0, 1.0, 0.0));

   // Bend time
   addParam(createParam<VultKnobAlt>(Vec(63, 106), module, Trummor2::BEND_TIME_PARAM, 0.0, 1.0, 0.0));

   // Sub-oscillator
   addParam(createParam<VultKnobAlt>(Vec(17, 106), module, Trummor2::SUB_PARAM, 0.0, 1.0, 0.0));
   // Cheby
   addParam(createParam<VultKnobAlt>(Vec(110, 106), module, Trummor2::CHEBY_PARAM, 0.0, 1.0, 0.0));

   // Filter
   addParam(createParam<VultKnobAlt>(Vec(160, 106), module, Trummor2::CUTOFF_PARAM, 0.0, 0.7, 0.5));
   addParam(createParam<VultKnobAlt>(Vec(208, 106), module, Trummor2::RESONANCE_PARAM, 0.0, 1.0, 0.0));
}
