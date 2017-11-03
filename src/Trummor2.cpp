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
#include <string.h>

struct Trummor2 : Module
{
   enum ParamIds
   {
      // Oscillator
      TUNE_PARAM,
      BEND_PARAM,
      TIME_PARAM,
      SUB_PARAM,
      WAVE_PARAM,
      SHAPER_PARAM,
      ENV1_A_PARAM,
      ENV1_H_PARAM,
      ENV1_R_PARAM,
      ENV1_SPEED_PARAM,
      OSC_BLEND_PARAM,
      LEVEL1_PARAM,

      // Noise
      PITCH_PARAM,
      RESCOMB_PARAM,
      TONE_PARAM,
      CUTOFF_PARAM,
      RESONANCE_PARAM,
      FILTER_PARAM,
      ENV2_A_PARAM,
      ENV2_H_PARAM,
      ENV2_R_PARAM,
      ENV2_SPEED_PARAM,
      NOISE_BLEND_PARAM,
      LEVEL2_PARAM,

      LAST_MOD_PARAM,
      // Modulation
      MODA_AMT_PARAM,
      MODB_AMT_PARAM,
      MODC_AMT_PARAM,
      MODD_AMT_PARAM,
      MODA_BUTTON_PARAM,
      MODB_BUTTON_PARAM,
      MODC_BUTTON_PARAM,
      MODD_BUTTON_PARAM,
      NUM_PARAMS
   };
   enum InputIds
   {
      GATE_INPUT,
      OSC_INPUT,
      NOISE_INPUT,
      MODA_INPUT,
      MODB_INPUT,
      MODC_INPUT,
      MODD_INPUT,
      OSC_GATE_INPUT,
      NOISE_GATE_INPUT,
      NUM_INPUTS
   };
   enum OutputIds
   {
      AUDIO_OUTPUT,
      PITCH_OUTPUT,
      ENV1_OUTPUT,
      ENV2_OUTPUT,
      OSC_OUTPUT,
      NOISE_OUTPUT,
      NUM_OUTPUTS
   };
   enum States
   {
      LEARN_A,
      LEARN_B,
      LEARN_C,
      LEARN_D,
      NORMAL
   };

   Trummor2_do_type processor;

   int mod[5];
   int pre_mod[5];

   States state;

   float previous[64];
   float current[64];

   Trummor2();
   void step() override;
   void randomize() override
   {

      for (int i = 0; i < 5; i++)
         mod[i] = rand() % LAST_MOD_PARAM;
   };
   void setParam(ParamIds p, float value)
   {
      current[p] = value;
      switch (p)
      {
      case LEVEL1_PARAM:
         Trummor2_setLevel1(processor, value);
         break;
      case LEVEL2_PARAM:
         Trummor2_setLevel2(processor, value);
         break;
      case ENV1_A_PARAM:
         Trummor2_setEnv1A(processor, value);
         break;
      case ENV1_H_PARAM:
         Trummor2_setEnv1H(processor, value);
         break;
      case ENV1_R_PARAM:
         Trummor2_setEnv1R(processor, value);
         break;
      case ENV2_A_PARAM:
         Trummor2_setEnv2A(processor, value);
         break;
      case ENV2_H_PARAM:
         Trummor2_setEnv2H(processor, value);
         break;
      case ENV2_R_PARAM:
         Trummor2_setEnv2R(processor, value);
         break;
      case TUNE_PARAM:
         Trummor2_setPitch(processor, value);
         break;
      case BEND_PARAM:
         Trummor2_setBend(processor, value);
         break;
      case SHAPER_PARAM:
         Trummor2_setShaper(processor, value);
         break;
      case WAVE_PARAM:
         Trummor2_setWave(processor, value);
         break;
      case PITCH_PARAM:
         Trummor2_setNoiseTune(processor, value);
         break;
      case RESCOMB_PARAM:
         Trummor2_setRescomb(processor, value);
         break;
      case TONE_PARAM:
         Trummor2_setTone(processor, value);
         break;
      case OSC_BLEND_PARAM:
         Trummor2_setOscBlend(processor, value);
         break;
      case NOISE_BLEND_PARAM:
         Trummor2_setNoiseBlend(processor, value);
         break;
      case ENV1_SPEED_PARAM:
         Trummor2_setEnv1Scale(processor, value);
         break;
      case ENV2_SPEED_PARAM:
         Trummor2_setEnv2Scale(processor, value);
         break;
      case TIME_PARAM:
         Trummor2_setBendTime(processor, value);
         break;
      case SUB_PARAM:
         Trummor2_setSub(processor, value);
         break;
      case CUTOFF_PARAM:
         Trummor2_setCutoff(processor, value);
         break;
      case RESONANCE_PARAM:
         Trummor2_setResonance(processor, value);
         break;
      case FILTER_PARAM:
         Trummor2_setFilter(processor, value);
         break;
      case LAST_MOD_PARAM:
      case MODA_AMT_PARAM:
      case MODB_AMT_PARAM:
      case MODC_AMT_PARAM:
      case MODD_AMT_PARAM:
      case MODA_BUTTON_PARAM:
      case MODB_BUTTON_PARAM:
      case MODC_BUTTON_PARAM:
      case MODD_BUTTON_PARAM:
      case NUM_PARAMS:
         break;
      }
   }
   json_t *toJson() override
   {
      json_t *rootJ = json_object();

      json_object_set_new(rootJ, "mod_a", json_integer(mod[LEARN_A]));
      json_object_set_new(rootJ, "mod_b", json_integer(mod[LEARN_B]));
      json_object_set_new(rootJ, "mod_c", json_integer(mod[LEARN_C]));
      json_object_set_new(rootJ, "mod_d", json_integer(mod[LEARN_D]));

      return rootJ;
   }

   void fromJson(json_t *rootJ) override
   {
      json_t *jmod_a = json_object_get(rootJ, "mod_a");
      if (jmod_a)
      {
         mod[LEARN_A] = json_integer_value(jmod_a);
         pre_mod[LEARN_A] = mod[LEARN_A];
      }

      json_t *jmod_b = json_object_get(rootJ, "mod_b");
      {
         mod[LEARN_B] = json_integer_value(jmod_b);
         pre_mod[LEARN_B] = mod[LEARN_B];
      }

      json_t *jmod_c = json_object_get(rootJ, "mod_c");
      {
         mod[LEARN_C] = json_integer_value(jmod_c);
         pre_mod[LEARN_C] = mod[LEARN_C];
      }

      json_t *jmod_d = json_object_get(rootJ, "mod_d");
      {
         mod[LEARN_D] = json_integer_value(jmod_d);
         pre_mod[LEARN_D] = mod[LEARN_D];
      }
   }
};

Trummor2::Trummor2() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS)
{
   params.resize(NUM_PARAMS);
   inputs.resize(NUM_INPUTS);
   outputs.resize(NUM_OUTPUTS);
   Trummor2_do_init(processor);
   state = NORMAL;
   for (int i = 0; i < 5; i++)
   {
      mod[i] = 0;
      pre_mod[i] = 0;
   }
   for (int i = 0; i < 64; i++)
   {
      previous[i] = 0;
      current[i] = 0;
   }
}

void Trummor2::step()
{

   if (previous[MODA_BUTTON_PARAM] != params[MODA_BUTTON_PARAM].value && params[MODA_BUTTON_PARAM].value >= 1.0)
   {
      state = LEARN_A;
   }
   else if (previous[MODB_BUTTON_PARAM] != params[MODB_BUTTON_PARAM].value && params[MODB_BUTTON_PARAM].value >= 1.0)
   {
      state = LEARN_B;
   }
   else if (previous[MODC_BUTTON_PARAM] != params[MODC_BUTTON_PARAM].value && params[MODC_BUTTON_PARAM].value >= 1.0)
   {
      state = LEARN_C;
   }
   else if (previous[MODD_BUTTON_PARAM] != params[MODD_BUTTON_PARAM].value && params[MODD_BUTTON_PARAM].value >= 1.0)
   {
      state = LEARN_D;
   }

   ParamIds last_changed = NUM_PARAMS;
   for (int p = 0; p < NUM_PARAMS; p++)
   {
      current[p] = params[p].value;
      setParam((ParamIds)p, current[p]);
      if (p < LAST_MOD_PARAM && previous[p] != current[p])
         last_changed = (ParamIds)p;

      previous[p] = current[p];
   }
   if (last_changed != NUM_PARAMS && state != NORMAL)
   {
      mod[state] = last_changed;
      state = NORMAL;
   }

   float mod_a_value = params[MODA_AMT_PARAM].value * inputs[MODA_INPUT].value / 10.0;
   setParam((ParamIds)mod[LEARN_A], current[mod[LEARN_A]] + mod_a_value);

   float mod_b_value = params[MODB_AMT_PARAM].value * inputs[MODB_INPUT].value / 10.0;
   setParam((ParamIds)mod[LEARN_B], current[mod[LEARN_B]] + mod_b_value);

   float mod_c_value = params[MODC_AMT_PARAM].value * inputs[MODC_INPUT].value / 10.0;
   setParam((ParamIds)mod[LEARN_C], current[mod[LEARN_C]] + mod_c_value);

   float mod_d_value = params[MODD_AMT_PARAM].value * inputs[MODD_INPUT].value / 10.0;
   setParam((ParamIds)mod[LEARN_D], current[mod[LEARN_D]] + mod_d_value);

   _tuple___real_real_real_real_real_real__ out;
   Trummor2_do(processor, inputs[GATE_INPUT].value / 10.0f, inputs[OSC_INPUT].value / 10.0f, inputs[NOISE_INPUT].value / 10.0f, inputs[OSC_GATE_INPUT].value / 10.0, inputs[NOISE_GATE_INPUT].value / 10.0, out);

   outputs[AUDIO_OUTPUT].value = out.field_0 * 10.0f;
   outputs[PITCH_OUTPUT].value = (out.field_1 - 0.3f) * 10.0f;
   outputs[ENV1_OUTPUT].value = out.field_2 * 10.0f;
   outputs[ENV2_OUTPUT].value = out.field_3 * 10.0f;
   outputs[OSC_OUTPUT].value = out.field_4 * 10.0f;
   outputs[NOISE_OUTPUT].value = out.field_5 * 10.0f;
}

static const char *parameters[] = {
    "O-TUNE",
    "O-BEND",
    "O-TIME",
    "O-SUB",
    "O-WAVE",
    "O-SHAPE",
    "O-ATTACK",
    "O-HOLD",
    "O-RELEAS",
    "O-SPEED",
    "O-SOURCE",
    "O-LEVEL",
    "N-PITCH",
    "N-RESCOM",
    "N-TONE",
    "N-CUTOFF",
    "N-RES",
    "N-FILTER",
    "N-ATTACK",
    "N-HOLD",
    "N-RELEAS",
    "N-SPEED",
    "N-SOURCE",
    "N-LEVEL",
    "    ",
};

struct Trummor2Display : TransparentWidget
{
   Trummor2 *module;
   std::shared_ptr<Font> font;

   Trummor2Display()
   {
      font = Font::load(assetPlugin(plugin, "res/01 Digit.ttf"));
   }

   void draw(NVGcontext *vg) override
   {
      nvgFontSize(vg, 6);
      nvgFontFaceId(vg, font->handle);
      nvgTextLetterSpacing(vg, 2.5);

      NVGcolor textColor = nvgRGB(0xFF, 0xFF, 0xFF);
      nvgFillColor(vg, textColor);

      if (module->state == Trummor2::NORMAL)
      {
         Vec moda = Vec(2, 12);
         nvgText(vg, moda.x, moda.y, parameters[module->mod[Trummor2::LEARN_A]], NULL);

         Vec modb = Vec(112 - strlen(parameters[module->mod[Trummor2::LEARN_B]]) * 6, 12);
         nvgText(vg, modb.x, modb.y, parameters[module->mod[Trummor2::LEARN_B]], NULL);

         Vec modc = Vec(2, 24);
         nvgText(vg, modc.x, modc.y, parameters[module->mod[Trummor2::LEARN_C]], NULL);

         Vec modd = Vec(112 - strlen(parameters[module->mod[Trummor2::LEARN_D]]) * 6, 24);
         nvgText(vg, modd.x, modd.y, parameters[module->mod[Trummor2::LEARN_D]], NULL);
      }
      else
      {
         Vec row1 = Vec(18, 12);
         nvgText(vg, row1.x, row1.y, "MOVE A CONTROL", NULL);
         Vec row2 = Vec(24, 24);
         nvgText(vg, row2.x, row2.y, "TO ASSIGN IT", NULL);
      }
   }
};

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
   {
      Trummor2Display *display = new Trummor2Display();
      display->box.pos = Vec(92, 302);
      display->box.size = Vec(110, 30);
      display->module = module;
      addChild(display);
   }
   addChild(createScrew<VultScrew>(Vec(16, 0)));
   addChild(createScrew<VultScrew>(Vec(box.size.x - 29, 0)));
   addChild(createScrew<VultScrew>(Vec(16, 365)));
   addChild(createScrew<VultScrew>(Vec(box.size.x - 29, 365)));

   /* Oscillator section */
   addParam(createParam<VultKnobAlt>(Vec(17, 59), module, Trummor2::TUNE_PARAM, -0.1, 0.3, 0.0));
   addParam(createParam<VultKnobAlt>(Vec(63, 59), module, Trummor2::BEND_PARAM, -1.0, 1.0, 0.5));
   addParam(createParam<VultKnobAlt>(Vec(110, 59), module, Trummor2::TIME_PARAM, 0.0, 1.0, 0.0));

   addParam(createParam<VultKnobAlt>(Vec(110, 106), module, Trummor2::SHAPER_PARAM, -1.0, 1.0, 0.0));
   addParam(createParam<VultKnobAlt>(Vec(17, 106), module, Trummor2::SUB_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<VultKnobAlt>(Vec(63, 106), module, Trummor2::WAVE_PARAM, 0.0, 1.0, 0.0));

   addParam(createParam<VultKnobAlt>(Vec(17, 153), module, Trummor2::ENV1_A_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<VultKnobAlt>(Vec(63, 153), module, Trummor2::ENV1_H_PARAM, 0.0, 1.0, 0.2));
   addParam(createParam<VultKnobAlt>(Vec(110, 153), module, Trummor2::ENV1_R_PARAM, 0.0, 1.0, 0.4));

   addParam(createParam<VultSelector3>(Vec(12, 203), module, Trummor2::ENV1_SPEED_PARAM, 0.0, 2.0, 0.0));

   addParam(createParam<VultKnobAlt>(Vec(53, 207), module, Trummor2::OSC_BLEND_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<VultKnob>(Vec(101, 201), module, Trummor2::LEVEL1_PARAM, 0.0, 1.0, 0.7));

   /* Noise section */
   addParam(createParam<VultKnob>(Vec(244, 201), module, Trummor2::LEVEL2_PARAM, 0.0, 1.0, 0.1));

   addParam(createParam<VultKnobAlt>(Vec(208, 59), module, Trummor2::PITCH_PARAM, -0.1, 0.9, -0.1));
   addParam(createParam<VultKnobAlt>(Vec(160, 59), module, Trummor2::TONE_PARAM, -1.0, 1.0, 0.0));
   addParam(createParam<VultKnobAlt>(Vec(252, 59), module, Trummor2::RESCOMB_PARAM, -1.0, 1.0, 0.0));
   addParam(createParam<VultKnobAlt>(Vec(160, 106), module, Trummor2::CUTOFF_PARAM, 0.0, 0.95, 0.95));
   addParam(createParam<VultKnobAlt>(Vec(208, 106), module, Trummor2::RESONANCE_PARAM, 0.0, 1.0, 0.0));

   addParam(createParam<VultKnobAlt>(Vec(160, 153), module, Trummor2::ENV2_A_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<VultKnobAlt>(Vec(206, 153), module, Trummor2::ENV2_H_PARAM, 0.0, 1.0, 0.05));
   addParam(createParam<VultKnobAlt>(Vec(252, 153), module, Trummor2::ENV2_R_PARAM, 0.0, 1.0, 0.05));

   addParam(createParam<VultSelector3>(Vec(254, 102), module, Trummor2::FILTER_PARAM, 0.0, 2.0, 0.0));

   addParam(createParam<VultKnobAlt>(Vec(195, 207), module, Trummor2::NOISE_BLEND_PARAM, 0.0, 1.0, 0.0));

   addParam(createParam<VultSelector3>(Vec(155, 203), module, Trummor2::ENV2_SPEED_PARAM, 0.0, 2.0, 0.0));

   /* Oscillator jacks */
   addInput(createInput<VultJack>(Vec(9, 254), module, Trummor2::OSC_INPUT));
   addInput(createInput<VultJack>(Vec(37, 254), module, Trummor2::OSC_GATE_INPUT));
   addOutput(createOutput<VultJack>(Vec(94, 254), module, Trummor2::ENV1_OUTPUT));
   addOutput(createOutput<VultJack>(Vec(66, 254), module, Trummor2::PITCH_OUTPUT));
   addOutput(createOutput<VultJack>(Vec(121, 254), module, Trummor2::OSC_OUTPUT));

   /* Noise jacks */
   addInput(createInput<VultJack>(Vec(152, 254), module, Trummor2::NOISE_INPUT));
   addInput(createInput<VultJack>(Vec(180, 254), module, Trummor2::NOISE_GATE_INPUT));
   addOutput(createOutput<VultJack>(Vec(236, 254), module, Trummor2::ENV2_OUTPUT));
   addOutput(createOutput<VultJack>(Vec(264, 254), module, Trummor2::NOISE_OUTPUT));

   /* Modulation */
   addInput(createInput<VultJack>(Vec(14, 292), module, Trummor2::MODA_INPUT));
   addInput(createInput<VultJack>(Vec(263, 292), module, Trummor2::MODB_INPUT));
   addInput(createInput<VultJack>(Vec(14, 320), module, Trummor2::MODC_INPUT));
   addInput(createInput<VultJack>(Vec(263, 320), module, Trummor2::MODD_INPUT));

   addParam(createParam<VultKnobSmall>(Vec(47, 295), module, Trummor2::MODA_AMT_PARAM, -1.0, 1.0, 0.0));
   addParam(createParam<VultKnobSmall>(Vec(236, 295), module, Trummor2::MODB_AMT_PARAM, -1.0, 1.0, 0.0));
   addParam(createParam<VultKnobSmall>(Vec(47, 323), module, Trummor2::MODC_AMT_PARAM, -1.0, 1.0, 0.0));
   addParam(createParam<VultKnobSmall>(Vec(236, 323), module, Trummor2::MODD_AMT_PARAM, -1.0, 1.0, 0.0));

   addParam(createParam<ButtonA>(Vec(74, 302), module, Trummor2::MODA_BUTTON_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<ButtonB>(Vec(212, 302), module, Trummor2::MODB_BUTTON_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<ButtonC>(Vec(74, 318), module, Trummor2::MODC_BUTTON_PARAM, 0.0, 1.0, 0.0));
   addParam(createParam<ButtonD>(Vec(212, 318), module, Trummor2::MODD_BUTTON_PARAM, 0.0, 1.0, 0.0));

   /* Main jacks */
   addInput(createInput<VultJack>(Vec(77, 350), module, Trummor2::GATE_INPUT));
   addOutput(createOutput<VultJack>(Vec(197, 350), module, Trummor2::AUDIO_OUTPUT));
}
