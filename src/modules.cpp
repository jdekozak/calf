/* Calf DSP Library
 * Example audio modules - parameters and LADSPA wrapper instantiation
 *
 * Copyright (C) 2001-2007 Krzysztof Foltman
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#include <assert.h>
#include <memory.h>
#if USE_JACK
#include <jack/jack.h>
#endif
#include <calf/giface.h>
#include <calf/modules.h>
#include <calf/modules_dev.h>

using namespace synth;

const char *copyright = "(C) 2001-2007 Krzysztof Foltman, license: LGPL";

const char *amp_audio_module::port_names[] = {"In L", "In R", "Out L", "Out R"};

parameter_properties amp_audio_module::param_props[] = {
    { 1, 0, 4, 1.1, PF_FLOAT | PF_SCALE_GAIN | PF_CTL_KNOB, NULL, "gain", "Gain" }
};

static synth::ladspa_info amp_info = { 0x847c, "Amp", "Calf Const Amp", "Krzysztof Foltman", copyright, "AmplifierPlugin" };

#if USE_LADSPA
static synth::ladspa_wrapper<amp_audio_module> amp(amp_info);
#endif

////////////////////////////////////////////////////////////////////////////

const char *flanger_audio_module::port_names[] = {"In L", "In R", "Out L", "Out R"};

parameter_properties flanger_audio_module::param_props[] = {
    { 0.1,      0.1, 10, 1.01, PF_FLOAT | PF_SCALE_LOG | PF_CTL_KNOB | PF_UNIT_MSEC, NULL, "min_delay", "Minimum delay" },
    { 0.5,      0.1, 10, 1.01, PF_FLOAT | PF_SCALE_LOG | PF_CTL_KNOB | PF_UNIT_MSEC, NULL, "mod_depth", "Modulation depth" },
    { 0.25,    0.01, 20, 1.01, PF_FLOAT | PF_SCALE_LOG | PF_CTL_KNOB | PF_UNIT_HZ, NULL, "mod_rate", "Modulation rate" },
    { 0.90,   -0.99, 0.99, 1.01, PF_FLOAT | PF_SCALE_PERC | PF_CTL_KNOB | PF_UNIT_COEF, NULL, "feedback", "Feedback" },
    { 1, 0, 2, 1.1, PF_FLOAT | PF_SCALE_GAIN | PF_CTL_KNOB | PF_UNIT_COEF, NULL, "amount", "Amount" },
};

static synth::ladspa_info flanger_info = { 0x847d, "Flanger", "Calf Flanger", "Krzysztof Foltman", copyright, "FlangerPlugin" };

#if USE_LADSPA
static synth::ladspa_wrapper<flanger_audio_module> flanger(flanger_info);
#endif

////////////////////////////////////////////////////////////////////////////

const char *reverb_audio_module::port_names[] = {"In L", "In R", "Out L", "Out R"};

parameter_properties reverb_audio_module::param_props[] = {
    { 1.5,      1.0,  4.0, 1.01, PF_FLOAT | PF_SCALE_LOG | PF_CTL_KNOB | PF_UNIT_SEC, NULL, "decay_time", "Decay time" },
    { 5000,    2000,20000, 1.01, PF_FLOAT | PF_SCALE_LOG | PF_CTL_KNOB | PF_UNIT_HZ, NULL, "hf_damp", "High Frq Damp" },
    { 0.25,       0,    2, 1.1, PF_FLOAT | PF_SCALE_GAIN | PF_CTL_KNOB | PF_UNIT_COEF, NULL, "amount", "Amount" },
};

static synth::ladspa_info reverb_info = { 0x847e, "Reverb", "Calf Reverb", "Krzysztof Foltman", copyright, "ReverbPlugin" };

#if USE_LADSPA
static synth::ladspa_wrapper<reverb_audio_module> reverb(reverb_info);
#endif

////////////////////////////////////////////////////////////////////////////

const char *filter_audio_module::port_names[] = {"In L", "In R", "Out L", "Out R"};

const char *filter_choices[] = {
    "12dB/oct Lowpass",
    "24dB/oct Lowpass",
    "36dB/oct Lowpass",
    "12dB/oct Highpass",
    "24dB/oct Highpass",
    "36dB/oct Highpass",
};

parameter_properties filter_audio_module::param_props[] = {
    { 2000,      10,20000, 1.01, PF_FLOAT | PF_SCALE_LOG | PF_CTL_KNOB | PF_UNIT_HZ, NULL, "freq", "Frequency" },
    { 0.707,  0.707,   20,  1.1, PF_FLOAT | PF_SCALE_GAIN | PF_CTL_KNOB | PF_UNIT_COEF, NULL, "res", "Resonance" },
    { 0,          0,    5,    1, PF_ENUM | PF_CTL_COMBO, filter_choices, "mode", "Mode" },
    { 20,         5,  100,    1, PF_INT | PF_SCALE_LOG | PF_CTL_KNOB | PF_UNIT_MSEC, NULL, "inertia", "Inertia"},
};

static synth::ladspa_info filter_info = { 0x847f, "Filter", "Calf Filter", "Krzysztof Foltman", copyright, "FilterPlugin" };

#if USE_LADSPA
static synth::ladspa_wrapper<filter_audio_module> filter(filter_info);
#endif

////////////////////////////////////////////////////////////////////////////
#ifdef ENABLE_EXPERIMENTAL
const char *organ_audio_module::port_names[] = {"Out L", "Out R"};

const char *organ_percussion_mode_names[] = { "Off", "Short", "Long" };
const char *organ_percussion_harmonic_names[] = { "2nd", "3rd" };
const char *organ_vibrato_speed_names[] = { "Off", "Swell", "Tremolo", "HoldPedal", "ModWheel" };

parameter_properties organ_audio_module::param_props[] = {
    { 0.3,       0,  1, 1.01, PF_FLOAT | PF_SCALE_QUAD | PF_CTL_FADER, NULL, "h1", "16'" },
    { 0.3,       0,  1, 1.01, PF_FLOAT | PF_SCALE_QUAD | PF_CTL_FADER, NULL, "h3", "5 1/3'" },
    { 0.3,       0,  1, 1.01, PF_FLOAT | PF_SCALE_QUAD | PF_CTL_FADER, NULL, "h2", "8'" },
    { 0,         0,  1, 1.01, PF_FLOAT | PF_SCALE_QUAD | PF_CTL_FADER, NULL, "h4", "4'" },
    { 0,         0,  1, 1.01, PF_FLOAT | PF_SCALE_QUAD | PF_CTL_FADER, NULL, "h6", "2 2/3'" },
    { 0,         0,  1, 1.01, PF_FLOAT | PF_SCALE_QUAD | PF_CTL_FADER, NULL, "h8", "2'" },
    { 0,         0,  1, 1.01, PF_FLOAT | PF_SCALE_QUAD | PF_CTL_FADER, NULL, "h10", "1 3/5'" },
    { 0,         0,  1, 1.01, PF_FLOAT | PF_SCALE_QUAD | PF_CTL_FADER, NULL, "h12", "1 1/3'" },
    { 0,         0,  1, 1.01, PF_FLOAT | PF_SCALE_QUAD | PF_CTL_FADER, NULL, "h16", "1'" },

    { 1,         0,  1, 1.01, PF_BOOL | PF_CTL_TOGGLE, NULL, "foldover", "Foldover" },
    { 1,         0,  2, 1.01, PF_ENUM | PF_CTL_COMBO, organ_percussion_mode_names, "perc mode", "Perc. mode" },
    { 3,         2,  3, 1.01, PF_ENUM | PF_CTL_COMBO, organ_percussion_harmonic_names, "perc_hrm", "Perc. harmonic" },
    { 1,         0,  4, 1.01, PF_ENUM | PF_CTL_COMBO, organ_vibrato_speed_names, "vib_speed", "Vibrato mode" },

    { 0.2,         0,  1, 1.01, PF_FLOAT | PF_SCALE_GAIN | PF_CTL_KNOB, NULL, "amount", "Amount" },
};

static synth::ladspa_info organ_info = { 0x8481, "Organ", "Calf Organ", "Krzysztof Foltman", copyright, "SynthesizerPlugin" };

#if USE_LADSPA
static synth::ladspa_wrapper<organ_audio_module> organ(organ_info);
#endif

#endif
////////////////////////////////////////////////////////////////////////////

const char *monosynth_audio_module::port_names[] = {
    "Out L", "Out R", 
};

const char *monosynth_waveform_names[] = { "Sawtooth", "Square", "Pulse", "Sine", "Triangle" };
const char *monosynth_mode_names[] = { "0 : 0", "0 : 180", "0 : 90", "90 : 90", "90 : 270", "Random" };
const char *monosynth_legato_names[] = { "Retrig", "Legato", "Fng Retrig", "Fng Legato" };

const char *monosynth_filter_choices[] = {
    "12dB/oct Lowpass",
    "24dB/oct Lowpass",
    "2x12dB/oct Lowpass",
    "12dB/oct Highpass",
    "Lowpass+Notch",
    "Highpass+Notch",
    "6dB/oct Bandpass",
    "2x6dB/oct Bandpass",
};

parameter_properties monosynth_audio_module::param_props[] = {
    { wave_saw,         0, wave_count - 1, 1, PF_ENUM | PF_CTL_COMBO, monosynth_waveform_names, "o1_wave", "Osc1 Wave" },
    { wave_sqr,         0, wave_count - 1, 1, PF_ENUM | PF_CTL_COMBO, monosynth_waveform_names, "o2_wave", "Osc2 Wave" },
    { 10,         0,  100, 1.01, PF_FLOAT | PF_SCALE_LINEAR | PF_CTL_KNOB | PF_UNIT_CENTS, NULL, "osc_detune", "O1<>2 Detune" },
    { 12,       -24,   24, 1.01, PF_INT | PF_SCALE_LINEAR | PF_CTL_KNOB | PF_UNIT_SEMITONES, NULL, "osc_xpose", "Osc transpose" },
    { 0,          0,    5, 1.01, PF_ENUM | PF_CTL_COMBO, monosynth_mode_names, "phase_mode", "Phase mode" },
    { 0.5,        0,    1, 1.01, PF_FLOAT | PF_SCALE_PERC, NULL, "o12_mix", "O1<>2 Mix" },
    { 1,          0,    7, 1.01, PF_ENUM | PF_CTL_COMBO, monosynth_filter_choices, "filter", "Filter" },
    { 33,        10,16000, 1.01, PF_FLOAT | PF_SCALE_LOG | PF_CTL_KNOB | PF_UNIT_HZ, NULL, "cutoff", "Cutoff" },
    { 2,        0.7,    8, 1.01, PF_FLOAT | PF_SCALE_LOG | PF_CTL_KNOB, NULL, "res", "Resonance" },
    { 0,      -2400, 2400, 1.01, PF_FLOAT | PF_SCALE_LINEAR | PF_CTL_KNOB | PF_UNIT_CENTS, NULL, "filter_sep", "Separation" },
    { 8000,  -10800,10800, 1.01, PF_FLOAT | PF_SCALE_LINEAR | PF_CTL_KNOB | PF_UNIT_CENTS, NULL, "e2cutoff", "Env->Cutoff" },
    { 1,          0,    1, 1.01, PF_FLOAT | PF_SCALE_PERC | PF_CTL_KNOB, NULL, "e2res", "Env->Res" },
    
    { 1,          1,20000, 1.01, PF_FLOAT | PF_SCALE_LOG | PF_CTL_KNOB | PF_UNIT_MSEC, NULL, "adsr_a", "Attack" },
    { 350,       10,20000, 1.01, PF_FLOAT | PF_SCALE_LOG | PF_CTL_KNOB | PF_UNIT_MSEC, NULL, "adsr_d", "Decay" },
    { 0.5,        0,    1, 1.01, PF_FLOAT | PF_SCALE_PERC, NULL, "adsr_s", "Sustain" },
    { 50,       10,20000, 1.01, PF_FLOAT | PF_SCALE_LOG | PF_CTL_KNOB | PF_UNIT_MSEC, NULL, "adsr_r", "Release" },
    
    { 0,          0,    1, 1.01, PF_BOOL | PF_CTL_TOGGLE, NULL, "key_follow", "Key Follow" },
    { 0,          0,    3, 1.01, PF_ENUM | PF_CTL_COMBO, monosynth_legato_names, "legato", "Legato Mode" },
    { 1,          1, 2000, 1.01, PF_FLOAT | PF_SCALE_LOG | PF_CTL_KNOB | PF_UNIT_MSEC, NULL, "portamento", "Portamento" },
    
    { 0,          0,    1,  0.1, PF_FLOAT | PF_SCALE_PERC | PF_CTL_KNOB, NULL, "vel2amp", "Vel->Amp" },
    { 0.5,        0,    1,  0.1, PF_FLOAT | PF_SCALE_PERC | PF_CTL_KNOB, NULL, "vel2flt", "Vel->Filter" },
};

static synth::ladspa_info monosynth_info = { 0x8480, "Monosynth", "Calf Monosynth", "Krzysztof Foltman", copyright, "SynthesizerPlugin" };

#if USE_LADSPA
static synth::ladspa_wrapper<monosynth_audio_module> monosynth(monosynth_info);
#endif

////////////////////////////////////////////////////////////////////////////

#if USE_LADSPA
extern "C" {

const LADSPA_Descriptor *ladspa_descriptor(unsigned long Index)
{
    switch (Index) {
        case 0: return &::filter.descriptor;
        case 1: return &::flanger.descriptor;
        case 2: return &::reverb.descriptor;
        default: return NULL;
    }
}

};

#if USE_DSSI
extern "C" {

const DSSI_Descriptor *dssi_descriptor(unsigned long Index)
{
    switch (Index) {
        case 0: return &::filter.dssi_descriptor;
        case 1: return &::flanger.dssi_descriptor;
        case 2: return &::reverb.dssi_descriptor;
        case 3: return &::monosynth.dssi_descriptor;
#ifdef ENABLE_EXPERIMENTAL
        case 4: return &::organ.dssi_descriptor;
#endif
        default: return NULL;
    }
}

};
#endif

std::string synth::get_builtin_modules_rdf()
{
    std::string rdf;
    
    rdf += ::flanger.generate_rdf();
    rdf += ::reverb.generate_rdf();
    rdf += ::filter.generate_rdf();
    rdf += ::monosynth.generate_rdf();
    
    return rdf;
}
#endif
