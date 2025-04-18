/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define trunc(x) ((Int)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class rnbomatic : public PatcherInterfaceImpl {
public:

class RNBOSubpatcher_149 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    class RNBOSubpatcher_145 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_149;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_145()
            {
            }
            
            ~RNBOSubpatcher_145()
            {
            }
            
            virtual RNBOSubpatcher_149* getPatcher() const {
                return static_cast<RNBOSubpatcher_149 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
                getEngine()->flushClockEvents(this, -871642103, false);
            }
            
            inline number linearinterp(number frac, number x, number y) {
                return x + (y - x) * frac;
            }
            
            number samplerate() const {
                return this->sr;
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                RNBO_UNUSED(numOutputs);
                RNBO_UNUSED(outputs);
                RNBO_UNUSED(numInputs);
                RNBO_UNUSED(inputs);
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->samplerate_01_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double samplerate) {
                this->samplerate_01_onSampleRateChanged(samplerate);
            }
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                RNBO_UNUSED(value);
                RNBO_UNUSED(hasValue);
                this->updateTime(time);
            
                switch (index) {
                case -871642103:
                    {
                    this->loadbang_01_startupbang_bang();
                    break;
                    }
                }
            }
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
                this->updateTime(time);
            
                switch (tag) {
                case TAG("startupbang"):
                    {
                    if (TAG("poly/freq-conversion[2]/loadbang_obj-21") == objectId)
                        this->loadbang_01_startupbang_bang();
            
                    break;
                    }
                }
            }
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
                case TAG("startupbang"):
                    {
                    return "startupbang";
                    }
                case TAG("poly/freq-conversion[2]/loadbang_obj-21"):
                    {
                    return "poly/freq-conversion[2]/loadbang_obj-21";
                    }
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                this->updateTime(time);
            
                if (index == 0) {
                    this->mtof_01_innerMtoF_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultMtofLookupTable256);
                }
            }
            
            void initialize() {
                this->assign_defaults();
                this->setState();
                this->mtof_01_innerMtoF_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultMtofLookupTable256);
            }
            
            protected:
            
            void eventinlet_01_out1_bang_bang() {
                this->expr_01_in1_bang();
            }
            
            void eventinlet_01_out1_list_set(const list& v) {
                {
                    if (v->length > 1)
                        this->expr_01_in2_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->expr_01_in1_set(converted);
                }
            }
            
            void loadbang_01_startupbang_bang() {
                this->loadbang_01_output_bang();
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 0;
            }
            
            Index getNumOutputChannels() const {
                return 0;
            }
            
            void initializeObjects() {
                this->mtof_01_innerScala_init();
                this->mtof_01_init();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
                this->getEngine()->scheduleClockEvent(this, -871642103, 0 + this->_currentTime);;
            }
            
            void allocateDataRefs() {
                this->mtof_01_innerMtoF_buffer->requestSize(65536, 1);
                this->mtof_01_innerMtoF_buffer->setSampleRate(this->sr);
                this->mtof_01_innerMtoF_buffer = this->mtof_01_innerMtoF_buffer->allocateIfNeeded();
            }
            
            void eventoutlet_01_in1_number_set(number v) {
                this->getPatcher()->updateTime(this->_currentTime);
                this->getPatcher()->p_01_out1_number_set(v);
            }
            
            void expr_03_out1_set(number v) {
                this->expr_03_out1 = v;
                this->eventoutlet_01_in1_number_set(this->expr_03_out1);
            }
            
            void expr_03_in1_set(number in1) {
                this->expr_03_in1 = in1;
            
                this->expr_03_out1_set(
                    (this->expr_03_in2 == 0 ? 0 : (this->expr_03_in2 == 0. ? 0. : this->expr_03_in1 / this->expr_03_in2))
                );//#map:freq-conversion[2]//_obj-91:1
            }
            
            void expr_03_in2_set(number v) {
                this->expr_03_in2 = v;
            }
            
            void mtof_01_out_set(const list& v) {
                {
                    if (v->length > 1)
                        this->expr_03_in2_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->expr_03_in1_set(converted);
                }
            }
            
            void mtof_01_midivalue_set(const list& v) {
                this->mtof_01_midivalue = jsCreateListCopy(v);
                list tmp = list();
            
                for (int i = 0; i < this->mtof_01_midivalue->length; i++) {
                    tmp->push(
                        this->mtof_01_innerMtoF_next(this->mtof_01_midivalue[(Index)i], this->mtof_01_base)
                    );
                }
            
                this->mtof_01_out_set(tmp);
            }
            
            void expr_02_out1_set(number v) {
                this->expr_02_out1 = v;
            
                {
                    list converted = {this->expr_02_out1};
                    this->mtof_01_midivalue_set(converted);
                }
            }
            
            void expr_02_in1_set(number in1) {
                this->expr_02_in1 = in1;
                this->expr_02_out1_set(this->expr_02_in1 + this->expr_02_in2);//#map:freq-conversion[2]/+_obj-94:1
            }
            
            void expr_01_out1_set(number v) {
                this->expr_01_out1 = v;
                this->expr_02_in1_set(this->expr_01_out1);
            }
            
            void expr_01_in1_set(number in1) {
                this->expr_01_in1 = in1;
                this->expr_01_out1_set(this->expr_01_in1 - this->expr_01_in2);//#map:freq-conversion[2]/-_obj-20:1
            }
            
            void eventinlet_01_out1_number_set(number v) {
                this->expr_01_in1_set(v);
            }
            
            void expr_01_in1_bang() {
                this->expr_01_out1_set(this->expr_01_in1 - this->expr_01_in2);//#map:freq-conversion[2]/-_obj-20:1
            }
            
            void expr_01_in2_set(number v) {
                this->expr_01_in2 = v;
            }
            
            void samplerate_01_samplerate_set(number v) {
                this->samplerate_01_samplerate = v;
                this->expr_03_in2_set(v);
            }
            
            void samplerate_01_input_bang() {
                this->samplerate_01_samplerate_set(this->samplerate());
            }
            
            void loadbang_01_output_bang() {
                this->samplerate_01_input_bang();
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            number mtof_01_innerMtoF_next(number midivalue, number tuning) {
                if (midivalue == this->mtof_01_innerMtoF_lastInValue && tuning == this->mtof_01_innerMtoF_lastTuning)
                    return this->mtof_01_innerMtoF_lastOutValue;
            
                this->mtof_01_innerMtoF_lastInValue = midivalue;
                this->mtof_01_innerMtoF_lastTuning = tuning;
                number result = 0;
            
                {
                    result = rnbo_exp(.057762265 * (midivalue - 69.0));
                }
            
                this->mtof_01_innerMtoF_lastOutValue = tuning * result;
                return this->mtof_01_innerMtoF_lastOutValue;
            }
            
            void mtof_01_innerMtoF_reset() {
                this->mtof_01_innerMtoF_lastInValue = 0;
                this->mtof_01_innerMtoF_lastOutValue = 0;
                this->mtof_01_innerMtoF_lastTuning = 0;
            }
            
            void mtof_01_innerScala_mid(int v) {
                this->mtof_01_innerScala_kbmMid = v;
                this->mtof_01_innerScala_updateRefFreq();
            }
            
            void mtof_01_innerScala_ref(int v) {
                this->mtof_01_innerScala_kbmRefNum = v;
                this->mtof_01_innerScala_updateRefFreq();
            }
            
            void mtof_01_innerScala_base(number v) {
                this->mtof_01_innerScala_kbmRefFreq = v;
                this->mtof_01_innerScala_updateRefFreq();
            }
            
            void mtof_01_innerScala_init() {
                list sclValid = {
                    12,
                    100,
                    0,
                    200,
                    0,
                    300,
                    0,
                    400,
                    0,
                    500,
                    0,
                    600,
                    0,
                    700,
                    0,
                    800,
                    0,
                    900,
                    0,
                    1000,
                    0,
                    1100,
                    0,
                    2,
                    1
                };
            
                this->mtof_01_innerScala_updateScale(sclValid);
            }
            
            void mtof_01_innerScala_update(list scale, list map) {
                if (scale->length > 0) {
                    this->mtof_01_innerScala_updateScale(scale);
                }
            
                if (map->length > 0) {
                    this->mtof_01_innerScala_updateMap(map);
                }
            }
            
            number mtof_01_innerScala_mtof(number note) {
                if ((bool)(this->mtof_01_innerScala_lastValid) && this->mtof_01_innerScala_lastNote == note) {
                    return this->mtof_01_innerScala_lastFreq;
                }
            
                array<int, 2> degoct = this->mtof_01_innerScala_applyKBM(note);
                number out = 0;
            
                if (degoct[1] > 0) {
                    out = this->mtof_01_innerScala_applySCL(degoct[0], fract(note), this->mtof_01_innerScala_refFreq);
                }
            
                this->mtof_01_innerScala_updateLast(note, out);
                return out;
            }
            
            number mtof_01_innerScala_ftom(number hz) {
                if (hz <= 0.0) {
                    return 0.0;
                }
            
                if ((bool)(this->mtof_01_innerScala_lastValid) && this->mtof_01_innerScala_lastFreq == hz) {
                    return this->mtof_01_innerScala_lastNote;
                }
            
                array<number, 2> df = this->mtof_01_innerScala_hztodeg(hz);
                int degree = (int)(df[0]);
                number frac = df[1];
                number out = 0;
            
                if (this->mtof_01_innerScala_kbmSize == 0) {
                    out = this->mtof_01_innerScala_kbmMid + degree;
                } else {
                    array<int, 2> octdeg = this->mtof_01_innerScala_octdegree(degree, this->mtof_01_innerScala_kbmOctaveDegree);
                    number oct = (number)(octdeg[0]);
                    int index = (int)(octdeg[1]);
                    Index entry = 0;
            
                    for (Index i = 0; i < this->mtof_01_innerScala_kbmMapSize; i++) {
                        if (index == this->mtof_01_innerScala_kbmValid[(Index)(i + this->mtof_01_innerScala_KBM_MAP_OFFSET)]) {
                            entry = i;
                            break;
                        }
                    }
            
                    out = oct * this->mtof_01_innerScala_kbmSize + entry + this->mtof_01_innerScala_kbmMid;
                }
            
                out = out + frac;
                this->mtof_01_innerScala_updateLast(out, hz);
                return this->mtof_01_innerScala_lastNote;
            }
            
            int mtof_01_innerScala_updateScale(list scl) {
                if (scl->length < 1) {
                    return 0;
                }
            
                number sclDataEntries = scl[0] * 2 + 1;
            
                if (sclDataEntries <= scl->length) {
                    this->mtof_01_innerScala_lastValid = false;
                    this->mtof_01_innerScala_sclExpMul = {};
                    number last = 1;
            
                    for (Index i = 1; i < sclDataEntries; i += 2) {
                        const number c = (const number)(scl[(Index)(i + 0)]);
                        const number d = (const number)(scl[(Index)(i + 1)]);
            
                        if (d <= 0) {
                            last = c / (number)1200;
                        } else {
                            last = rnbo_log2(c / d);
                        }
            
                        this->mtof_01_innerScala_sclExpMul->push(last);
                    }
            
                    this->mtof_01_innerScala_sclOctaveMul = last;
                    this->mtof_01_innerScala_sclEntryCount = (int)(this->mtof_01_innerScala_sclExpMul->length);
            
                    if (scl->length >= sclDataEntries + 3) {
                        this->mtof_01_innerScala_kbmMid = (int)(scl[(Index)(sclDataEntries + 2)]);
                        this->mtof_01_innerScala_kbmRefNum = (int)(scl[(Index)(sclDataEntries + 1)]);
                        this->mtof_01_innerScala_kbmRefFreq = scl[(Index)(sclDataEntries + 0)];
                        this->mtof_01_innerScala_kbmSize = (int)(0);
                    }
            
                    this->mtof_01_innerScala_updateRefFreq();
                    return 1;
                }
            
                return 0;
            }
            
            int mtof_01_innerScala_updateMap(list kbm) {
                if (kbm->length == 1 && kbm[0] == 0.0) {
                    kbm = {0.0, 0.0, 0.0, 60.0, 69.0, 440.0};
                }
            
                if (kbm->length >= 6 && kbm[0] >= 0.0) {
                    this->mtof_01_innerScala_lastValid = false;
                    Index size = (Index)(kbm[0]);
                    int octave = 12;
            
                    if (kbm->length > 6) {
                        octave = (int)(kbm[6]);
                    }
            
                    if (size > 0 && kbm->length < this->mtof_01_innerScala_KBM_MAP_OFFSET) {
                        return 0;
                    }
            
                    this->mtof_01_innerScala_kbmSize = (int)(size);
                    this->mtof_01_innerScala_kbmMin = (int)(kbm[1]);
                    this->mtof_01_innerScala_kbmMax = (int)(kbm[2]);
                    this->mtof_01_innerScala_kbmMid = (int)(kbm[3]);
                    this->mtof_01_innerScala_kbmRefNum = (int)(kbm[4]);
                    this->mtof_01_innerScala_kbmRefFreq = kbm[5];
                    this->mtof_01_innerScala_kbmOctaveDegree = octave;
                    this->mtof_01_innerScala_kbmValid = kbm;
                    this->mtof_01_innerScala_kbmMapSize = (kbm->length - this->mtof_01_innerScala_KBM_MAP_OFFSET > kbm->length ? kbm->length : (kbm->length - this->mtof_01_innerScala_KBM_MAP_OFFSET < 0 ? 0 : kbm->length - this->mtof_01_innerScala_KBM_MAP_OFFSET));
                    this->mtof_01_innerScala_updateRefFreq();
                    return 1;
                }
            
                return 0;
            }
            
            void mtof_01_innerScala_updateLast(number note, number freq) {
                this->mtof_01_innerScala_lastValid = true;
                this->mtof_01_innerScala_lastNote = note;
                this->mtof_01_innerScala_lastFreq = freq;
            }
            
            array<number, 2> mtof_01_innerScala_hztodeg(number hz) {
                number hza = rnbo_abs(hz);
            
                number octave = rnbo_floor(
                    rnbo_log2(hza / this->mtof_01_innerScala_refFreq) / this->mtof_01_innerScala_sclOctaveMul
                );
            
                int i = 0;
                number frac = 0;
                number n = 0;
            
                for (; i < this->mtof_01_innerScala_sclEntryCount; i++) {
                    number c = this->mtof_01_innerScala_applySCLOctIndex(octave, i + 0, 0.0, this->mtof_01_innerScala_refFreq);
                    n = this->mtof_01_innerScala_applySCLOctIndex(octave, i + 1, 0.0, this->mtof_01_innerScala_refFreq);
            
                    if (c <= hza && hza < n) {
                        if (c != hza) {
                            frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
                        }
            
                        break;
                    }
                }
            
                if (i == this->mtof_01_innerScala_sclEntryCount && n != hza) {
                    number c = n;
                    n = this->mtof_01_innerScala_applySCLOctIndex(octave + 1, 0, 0.0, this->mtof_01_innerScala_refFreq);
                    frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
                }
            
                number deg = i + octave * this->mtof_01_innerScala_sclEntryCount;
            
                {
                    deg = rnbo_fround((deg + frac) * 1 / (number)1) * 1;
                    frac = 0.0;
                }
            
                return {deg, frac};
            }
            
            array<int, 2> mtof_01_innerScala_octdegree(int degree, int count) {
                int octave = 0;
                int index = 0;
            
                if (degree < 0) {
                    octave = -(1 + (-1 - degree) / count);
                    index = -degree % count;
            
                    if (index > 0) {
                        index = count - index;
                    }
                } else {
                    octave = degree / count;
                    index = degree % count;
                }
            
                return {octave, index};
            }
            
            array<int, 2> mtof_01_innerScala_applyKBM(number note) {
                if ((this->mtof_01_innerScala_kbmMin == this->mtof_01_innerScala_kbmMax && this->mtof_01_innerScala_kbmMax == 0) || (note >= this->mtof_01_innerScala_kbmMin && note <= this->mtof_01_innerScala_kbmMax)) {
                    int degree = (int)(rnbo_floor(note - this->mtof_01_innerScala_kbmMid));
            
                    if (this->mtof_01_innerScala_kbmSize == 0) {
                        return {degree, 1};
                    }
            
                    array<int, 2> octdeg = this->mtof_01_innerScala_octdegree(degree, this->mtof_01_innerScala_kbmSize);
                    int octave = (int)(octdeg[0]);
                    Index index = (Index)(octdeg[1]);
            
                    if (this->mtof_01_innerScala_kbmMapSize > index) {
                        degree = (int)(this->mtof_01_innerScala_kbmValid[(Index)(this->mtof_01_innerScala_KBM_MAP_OFFSET + index)]);
            
                        if (degree >= 0) {
                            return {degree + octave * this->mtof_01_innerScala_kbmOctaveDegree, 1};
                        }
                    }
                }
            
                return {-1, 0};
            }
            
            number mtof_01_innerScala_applySCL(int degree, number frac, number refFreq) {
                array<int, 2> octdeg = this->mtof_01_innerScala_octdegree(degree, this->mtof_01_innerScala_sclEntryCount);
                return this->mtof_01_innerScala_applySCLOctIndex(octdeg[0], octdeg[1], frac, refFreq);
            }
            
            number mtof_01_innerScala_applySCLOctIndex(number octave, int index, number frac, number refFreq) {
                number p = 0;
            
                if (index > 0) {
                    p = this->mtof_01_innerScala_sclExpMul[(Index)(index - 1)];
                }
            
                if (frac > 0) {
                    p = this->linearinterp(frac, p, this->mtof_01_innerScala_sclExpMul[(Index)index]);
                } else if (frac < 0) {
                    p = this->linearinterp(-frac, this->mtof_01_innerScala_sclExpMul[(Index)index], p);
                }
            
                return refFreq * rnbo_pow(2, p + octave * this->mtof_01_innerScala_sclOctaveMul);
            }
            
            void mtof_01_innerScala_updateRefFreq() {
                this->mtof_01_innerScala_lastValid = false;
                int refOffset = (int)(this->mtof_01_innerScala_kbmRefNum - this->mtof_01_innerScala_kbmMid);
            
                if (refOffset == 0) {
                    this->mtof_01_innerScala_refFreq = this->mtof_01_innerScala_kbmRefFreq;
                } else {
                    int base = (int)(this->mtof_01_innerScala_kbmSize);
            
                    if (base < 1) {
                        base = this->mtof_01_innerScala_sclEntryCount;
                    }
            
                    array<int, 2> octdeg = this->mtof_01_innerScala_octdegree(refOffset, base);
                    number oct = (number)(octdeg[0]);
                    int index = (int)(octdeg[1]);
            
                    if (base > 0) {
                        oct = oct + rnbo_floor(index / base);
                        index = index % base;
                    }
            
                    if (index >= 0 && index < this->mtof_01_innerScala_kbmSize) {
                        if (index < this->mtof_01_innerScala_kbmMapSize) {
                            index = (int)(this->mtof_01_innerScala_kbmValid[(Index)((Index)(index) + this->mtof_01_innerScala_KBM_MAP_OFFSET)]);
                        } else {
                            index = -1;
                        }
                    }
            
                    if (index < 0 || index > this->mtof_01_innerScala_sclExpMul->length)
                        {} else {
                        number p = 0;
            
                        if (index > 0) {
                            p = this->mtof_01_innerScala_sclExpMul[(Index)(index - 1)];
                        }
            
                        this->mtof_01_innerScala_refFreq = this->mtof_01_innerScala_kbmRefFreq / rnbo_pow(2, p + oct * this->mtof_01_innerScala_sclOctaveMul);
                    }
                }
            }
            
            void mtof_01_innerScala_reset() {
                this->mtof_01_innerScala_lastValid = false;
                this->mtof_01_innerScala_lastNote = 0;
                this->mtof_01_innerScala_lastFreq = 0;
                this->mtof_01_innerScala_sclEntryCount = 0;
                this->mtof_01_innerScala_sclOctaveMul = 1;
                this->mtof_01_innerScala_sclExpMul = {};
                this->mtof_01_innerScala_kbmValid = {0, 0, 0, 60, 69, 440};
                this->mtof_01_innerScala_kbmMid = 60;
                this->mtof_01_innerScala_kbmRefNum = 69;
                this->mtof_01_innerScala_kbmRefFreq = 440;
                this->mtof_01_innerScala_kbmSize = 0;
                this->mtof_01_innerScala_kbmMin = 0;
                this->mtof_01_innerScala_kbmMax = 0;
                this->mtof_01_innerScala_kbmOctaveDegree = 12;
                this->mtof_01_innerScala_kbmMapSize = 0;
                this->mtof_01_innerScala_refFreq = 261.63;
            }
            
            void mtof_01_init() {
                this->mtof_01_innerScala_update(this->mtof_01_scale, this->mtof_01_map);
            }
            
            void samplerate_01_onSampleRateChanged(number samplerate) {
                if (this->samplerate_01_samplerate != samplerate) {
                    this->samplerate_01_samplerate_set(samplerate);
                }
            }
            
            void samplerate_01_dspsetup(bool force) {
                if ((bool)(this->samplerate_01_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->samplerate_01_onSampleRateChanged(this->samplerate());
                this->samplerate_01_setupDone = true;
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                expr_01_in1 = 0;
                expr_01_in2 = 4;
                expr_01_out1 = 0;
                expr_02_in1 = 0;
                expr_02_in2 = 72;
                expr_02_out1 = 0;
                expr_03_in1 = 0;
                expr_03_in2 = 0;
                expr_03_out1 = 0;
                mtof_01_base = 440;
                samplerate_01_samplerate = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                mtof_01_innerMtoF_lastInValue = 0;
                mtof_01_innerMtoF_lastOutValue = 0;
                mtof_01_innerMtoF_lastTuning = 0;
                mtof_01_innerScala_lastValid = false;
                mtof_01_innerScala_lastNote = 0;
                mtof_01_innerScala_lastFreq = 0;
                mtof_01_innerScala_sclEntryCount = 0;
                mtof_01_innerScala_sclOctaveMul = 1;
                mtof_01_innerScala_kbmValid = { 0, 0, 0, 60, 69, 440 };
                mtof_01_innerScala_kbmMid = 60;
                mtof_01_innerScala_kbmRefNum = 69;
                mtof_01_innerScala_kbmRefFreq = 440;
                mtof_01_innerScala_kbmSize = 0;
                mtof_01_innerScala_kbmMin = 0;
                mtof_01_innerScala_kbmMax = 0;
                mtof_01_innerScala_kbmOctaveDegree = 12;
                mtof_01_innerScala_kbmMapSize = 0;
                mtof_01_innerScala_refFreq = 261.63;
                samplerate_01_setupDone = false;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number expr_01_in1;
                number expr_01_in2;
                number expr_01_out1;
                number expr_02_in1;
                number expr_02_in2;
                number expr_02_out1;
                number expr_03_in1;
                number expr_03_in2;
                number expr_03_out1;
                list mtof_01_midivalue;
                list mtof_01_scale;
                list mtof_01_map;
                number mtof_01_base;
                number samplerate_01_samplerate;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number mtof_01_innerMtoF_lastInValue;
                number mtof_01_innerMtoF_lastOutValue;
                number mtof_01_innerMtoF_lastTuning;
                Float64BufferRef mtof_01_innerMtoF_buffer;
                const Index mtof_01_innerScala_KBM_MAP_OFFSET = 7;
                bool mtof_01_innerScala_lastValid;
                number mtof_01_innerScala_lastNote;
                number mtof_01_innerScala_lastFreq;
                int mtof_01_innerScala_sclEntryCount;
                number mtof_01_innerScala_sclOctaveMul;
                list mtof_01_innerScala_sclExpMul;
                list mtof_01_innerScala_kbmValid;
                int mtof_01_innerScala_kbmMid;
                int mtof_01_innerScala_kbmRefNum;
                number mtof_01_innerScala_kbmRefFreq;
                int mtof_01_innerScala_kbmSize;
                int mtof_01_innerScala_kbmMin;
                int mtof_01_innerScala_kbmMax;
                int mtof_01_innerScala_kbmOctaveDegree;
                Index mtof_01_innerScala_kbmMapSize;
                number mtof_01_innerScala_refFreq;
                bool samplerate_01_setupDone;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_146 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_149;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_146()
            {
            }
            
            ~RNBOSubpatcher_146()
            {
            }
            
            virtual RNBOSubpatcher_149* getPatcher() const {
                return static_cast<RNBOSubpatcher_149 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
                getEngine()->flushClockEvents(this, -871642103, false);
            }
            
            inline number linearinterp(number frac, number x, number y) {
                return x + (y - x) * frac;
            }
            
            number samplerate() const {
                return this->sr;
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                RNBO_UNUSED(numOutputs);
                RNBO_UNUSED(outputs);
                RNBO_UNUSED(numInputs);
                RNBO_UNUSED(inputs);
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->samplerate_02_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double samplerate) {
                this->samplerate_02_onSampleRateChanged(samplerate);
            }
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                RNBO_UNUSED(value);
                RNBO_UNUSED(hasValue);
                this->updateTime(time);
            
                switch (index) {
                case -871642103:
                    {
                    this->loadbang_02_startupbang_bang();
                    break;
                    }
                }
            }
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
                this->updateTime(time);
            
                switch (tag) {
                case TAG("startupbang"):
                    {
                    if (TAG("poly/freq-conversion[1]/loadbang_obj-21") == objectId)
                        this->loadbang_02_startupbang_bang();
            
                    break;
                    }
                }
            }
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
                case TAG("startupbang"):
                    {
                    return "startupbang";
                    }
                case TAG("poly/freq-conversion[1]/loadbang_obj-21"):
                    {
                    return "poly/freq-conversion[1]/loadbang_obj-21";
                    }
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                this->updateTime(time);
            
                if (index == 0) {
                    this->mtof_02_innerMtoF_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultMtofLookupTable256);
                }
            }
            
            void initialize() {
                this->assign_defaults();
                this->setState();
                this->mtof_02_innerMtoF_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultMtofLookupTable256);
            }
            
            protected:
            
            void eventinlet_02_out1_bang_bang() {
                this->expr_06_in1_bang();
            }
            
            void eventinlet_02_out1_list_set(const list& v) {
                {
                    if (v->length > 1)
                        this->expr_06_in2_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->expr_06_in1_set(converted);
                }
            }
            
            void loadbang_02_startupbang_bang() {
                this->loadbang_02_output_bang();
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 0;
            }
            
            Index getNumOutputChannels() const {
                return 0;
            }
            
            void initializeObjects() {
                this->mtof_02_innerScala_init();
                this->mtof_02_init();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
                this->getEngine()->scheduleClockEvent(this, -871642103, 0 + this->_currentTime);;
            }
            
            void allocateDataRefs() {
                this->mtof_02_innerMtoF_buffer->requestSize(65536, 1);
                this->mtof_02_innerMtoF_buffer->setSampleRate(this->sr);
                this->mtof_02_innerMtoF_buffer = this->mtof_02_innerMtoF_buffer->allocateIfNeeded();
            }
            
            void eventoutlet_02_in1_number_set(number v) {
                this->getPatcher()->updateTime(this->_currentTime);
                this->getPatcher()->p_02_out1_number_set(v);
            }
            
            void expr_05_out1_set(number v) {
                this->expr_05_out1 = v;
                this->eventoutlet_02_in1_number_set(this->expr_05_out1);
            }
            
            void expr_05_in1_set(number in1) {
                this->expr_05_in1 = in1;
            
                this->expr_05_out1_set(
                    (this->expr_05_in2 == 0 ? 0 : (this->expr_05_in2 == 0. ? 0. : this->expr_05_in1 / this->expr_05_in2))
                );//#map:freq-conversion[1]//_obj-91:1
            }
            
            void expr_05_in2_set(number v) {
                this->expr_05_in2 = v;
            }
            
            void mtof_02_out_set(const list& v) {
                {
                    if (v->length > 1)
                        this->expr_05_in2_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->expr_05_in1_set(converted);
                }
            }
            
            void mtof_02_midivalue_set(const list& v) {
                this->mtof_02_midivalue = jsCreateListCopy(v);
                list tmp = list();
            
                for (int i = 0; i < this->mtof_02_midivalue->length; i++) {
                    tmp->push(
                        this->mtof_02_innerMtoF_next(this->mtof_02_midivalue[(Index)i], this->mtof_02_base)
                    );
                }
            
                this->mtof_02_out_set(tmp);
            }
            
            void expr_04_out1_set(number v) {
                this->expr_04_out1 = v;
            
                {
                    list converted = {this->expr_04_out1};
                    this->mtof_02_midivalue_set(converted);
                }
            }
            
            void expr_04_in1_set(number in1) {
                this->expr_04_in1 = in1;
                this->expr_04_out1_set(this->expr_04_in1 + this->expr_04_in2);//#map:freq-conversion[1]/+_obj-94:1
            }
            
            void expr_06_out1_set(number v) {
                this->expr_06_out1 = v;
                this->expr_04_in1_set(this->expr_06_out1);
            }
            
            void expr_06_in1_set(number in1) {
                this->expr_06_in1 = in1;
                this->expr_06_out1_set(this->expr_06_in1 - this->expr_06_in2);//#map:freq-conversion[1]/-_obj-20:1
            }
            
            void eventinlet_02_out1_number_set(number v) {
                this->expr_06_in1_set(v);
            }
            
            void expr_06_in1_bang() {
                this->expr_06_out1_set(this->expr_06_in1 - this->expr_06_in2);//#map:freq-conversion[1]/-_obj-20:1
            }
            
            void expr_06_in2_set(number v) {
                this->expr_06_in2 = v;
            }
            
            void samplerate_02_samplerate_set(number v) {
                this->samplerate_02_samplerate = v;
                this->expr_05_in2_set(v);
            }
            
            void samplerate_02_input_bang() {
                this->samplerate_02_samplerate_set(this->samplerate());
            }
            
            void loadbang_02_output_bang() {
                this->samplerate_02_input_bang();
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            number mtof_02_innerMtoF_next(number midivalue, number tuning) {
                if (midivalue == this->mtof_02_innerMtoF_lastInValue && tuning == this->mtof_02_innerMtoF_lastTuning)
                    return this->mtof_02_innerMtoF_lastOutValue;
            
                this->mtof_02_innerMtoF_lastInValue = midivalue;
                this->mtof_02_innerMtoF_lastTuning = tuning;
                number result = 0;
            
                {
                    result = rnbo_exp(.057762265 * (midivalue - 69.0));
                }
            
                this->mtof_02_innerMtoF_lastOutValue = tuning * result;
                return this->mtof_02_innerMtoF_lastOutValue;
            }
            
            void mtof_02_innerMtoF_reset() {
                this->mtof_02_innerMtoF_lastInValue = 0;
                this->mtof_02_innerMtoF_lastOutValue = 0;
                this->mtof_02_innerMtoF_lastTuning = 0;
            }
            
            void mtof_02_innerScala_mid(int v) {
                this->mtof_02_innerScala_kbmMid = v;
                this->mtof_02_innerScala_updateRefFreq();
            }
            
            void mtof_02_innerScala_ref(int v) {
                this->mtof_02_innerScala_kbmRefNum = v;
                this->mtof_02_innerScala_updateRefFreq();
            }
            
            void mtof_02_innerScala_base(number v) {
                this->mtof_02_innerScala_kbmRefFreq = v;
                this->mtof_02_innerScala_updateRefFreq();
            }
            
            void mtof_02_innerScala_init() {
                list sclValid = {
                    12,
                    100,
                    0,
                    200,
                    0,
                    300,
                    0,
                    400,
                    0,
                    500,
                    0,
                    600,
                    0,
                    700,
                    0,
                    800,
                    0,
                    900,
                    0,
                    1000,
                    0,
                    1100,
                    0,
                    2,
                    1
                };
            
                this->mtof_02_innerScala_updateScale(sclValid);
            }
            
            void mtof_02_innerScala_update(list scale, list map) {
                if (scale->length > 0) {
                    this->mtof_02_innerScala_updateScale(scale);
                }
            
                if (map->length > 0) {
                    this->mtof_02_innerScala_updateMap(map);
                }
            }
            
            number mtof_02_innerScala_mtof(number note) {
                if ((bool)(this->mtof_02_innerScala_lastValid) && this->mtof_02_innerScala_lastNote == note) {
                    return this->mtof_02_innerScala_lastFreq;
                }
            
                array<int, 2> degoct = this->mtof_02_innerScala_applyKBM(note);
                number out = 0;
            
                if (degoct[1] > 0) {
                    out = this->mtof_02_innerScala_applySCL(degoct[0], fract(note), this->mtof_02_innerScala_refFreq);
                }
            
                this->mtof_02_innerScala_updateLast(note, out);
                return out;
            }
            
            number mtof_02_innerScala_ftom(number hz) {
                if (hz <= 0.0) {
                    return 0.0;
                }
            
                if ((bool)(this->mtof_02_innerScala_lastValid) && this->mtof_02_innerScala_lastFreq == hz) {
                    return this->mtof_02_innerScala_lastNote;
                }
            
                array<number, 2> df = this->mtof_02_innerScala_hztodeg(hz);
                int degree = (int)(df[0]);
                number frac = df[1];
                number out = 0;
            
                if (this->mtof_02_innerScala_kbmSize == 0) {
                    out = this->mtof_02_innerScala_kbmMid + degree;
                } else {
                    array<int, 2> octdeg = this->mtof_02_innerScala_octdegree(degree, this->mtof_02_innerScala_kbmOctaveDegree);
                    number oct = (number)(octdeg[0]);
                    int index = (int)(octdeg[1]);
                    Index entry = 0;
            
                    for (Index i = 0; i < this->mtof_02_innerScala_kbmMapSize; i++) {
                        if (index == this->mtof_02_innerScala_kbmValid[(Index)(i + this->mtof_02_innerScala_KBM_MAP_OFFSET)]) {
                            entry = i;
                            break;
                        }
                    }
            
                    out = oct * this->mtof_02_innerScala_kbmSize + entry + this->mtof_02_innerScala_kbmMid;
                }
            
                out = out + frac;
                this->mtof_02_innerScala_updateLast(out, hz);
                return this->mtof_02_innerScala_lastNote;
            }
            
            int mtof_02_innerScala_updateScale(list scl) {
                if (scl->length < 1) {
                    return 0;
                }
            
                number sclDataEntries = scl[0] * 2 + 1;
            
                if (sclDataEntries <= scl->length) {
                    this->mtof_02_innerScala_lastValid = false;
                    this->mtof_02_innerScala_sclExpMul = {};
                    number last = 1;
            
                    for (Index i = 1; i < sclDataEntries; i += 2) {
                        const number c = (const number)(scl[(Index)(i + 0)]);
                        const number d = (const number)(scl[(Index)(i + 1)]);
            
                        if (d <= 0) {
                            last = c / (number)1200;
                        } else {
                            last = rnbo_log2(c / d);
                        }
            
                        this->mtof_02_innerScala_sclExpMul->push(last);
                    }
            
                    this->mtof_02_innerScala_sclOctaveMul = last;
                    this->mtof_02_innerScala_sclEntryCount = (int)(this->mtof_02_innerScala_sclExpMul->length);
            
                    if (scl->length >= sclDataEntries + 3) {
                        this->mtof_02_innerScala_kbmMid = (int)(scl[(Index)(sclDataEntries + 2)]);
                        this->mtof_02_innerScala_kbmRefNum = (int)(scl[(Index)(sclDataEntries + 1)]);
                        this->mtof_02_innerScala_kbmRefFreq = scl[(Index)(sclDataEntries + 0)];
                        this->mtof_02_innerScala_kbmSize = (int)(0);
                    }
            
                    this->mtof_02_innerScala_updateRefFreq();
                    return 1;
                }
            
                return 0;
            }
            
            int mtof_02_innerScala_updateMap(list kbm) {
                if (kbm->length == 1 && kbm[0] == 0.0) {
                    kbm = {0.0, 0.0, 0.0, 60.0, 69.0, 440.0};
                }
            
                if (kbm->length >= 6 && kbm[0] >= 0.0) {
                    this->mtof_02_innerScala_lastValid = false;
                    Index size = (Index)(kbm[0]);
                    int octave = 12;
            
                    if (kbm->length > 6) {
                        octave = (int)(kbm[6]);
                    }
            
                    if (size > 0 && kbm->length < this->mtof_02_innerScala_KBM_MAP_OFFSET) {
                        return 0;
                    }
            
                    this->mtof_02_innerScala_kbmSize = (int)(size);
                    this->mtof_02_innerScala_kbmMin = (int)(kbm[1]);
                    this->mtof_02_innerScala_kbmMax = (int)(kbm[2]);
                    this->mtof_02_innerScala_kbmMid = (int)(kbm[3]);
                    this->mtof_02_innerScala_kbmRefNum = (int)(kbm[4]);
                    this->mtof_02_innerScala_kbmRefFreq = kbm[5];
                    this->mtof_02_innerScala_kbmOctaveDegree = octave;
                    this->mtof_02_innerScala_kbmValid = kbm;
                    this->mtof_02_innerScala_kbmMapSize = (kbm->length - this->mtof_02_innerScala_KBM_MAP_OFFSET > kbm->length ? kbm->length : (kbm->length - this->mtof_02_innerScala_KBM_MAP_OFFSET < 0 ? 0 : kbm->length - this->mtof_02_innerScala_KBM_MAP_OFFSET));
                    this->mtof_02_innerScala_updateRefFreq();
                    return 1;
                }
            
                return 0;
            }
            
            void mtof_02_innerScala_updateLast(number note, number freq) {
                this->mtof_02_innerScala_lastValid = true;
                this->mtof_02_innerScala_lastNote = note;
                this->mtof_02_innerScala_lastFreq = freq;
            }
            
            array<number, 2> mtof_02_innerScala_hztodeg(number hz) {
                number hza = rnbo_abs(hz);
            
                number octave = rnbo_floor(
                    rnbo_log2(hza / this->mtof_02_innerScala_refFreq) / this->mtof_02_innerScala_sclOctaveMul
                );
            
                int i = 0;
                number frac = 0;
                number n = 0;
            
                for (; i < this->mtof_02_innerScala_sclEntryCount; i++) {
                    number c = this->mtof_02_innerScala_applySCLOctIndex(octave, i + 0, 0.0, this->mtof_02_innerScala_refFreq);
                    n = this->mtof_02_innerScala_applySCLOctIndex(octave, i + 1, 0.0, this->mtof_02_innerScala_refFreq);
            
                    if (c <= hza && hza < n) {
                        if (c != hza) {
                            frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
                        }
            
                        break;
                    }
                }
            
                if (i == this->mtof_02_innerScala_sclEntryCount && n != hza) {
                    number c = n;
                    n = this->mtof_02_innerScala_applySCLOctIndex(octave + 1, 0, 0.0, this->mtof_02_innerScala_refFreq);
                    frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
                }
            
                number deg = i + octave * this->mtof_02_innerScala_sclEntryCount;
            
                {
                    deg = rnbo_fround((deg + frac) * 1 / (number)1) * 1;
                    frac = 0.0;
                }
            
                return {deg, frac};
            }
            
            array<int, 2> mtof_02_innerScala_octdegree(int degree, int count) {
                int octave = 0;
                int index = 0;
            
                if (degree < 0) {
                    octave = -(1 + (-1 - degree) / count);
                    index = -degree % count;
            
                    if (index > 0) {
                        index = count - index;
                    }
                } else {
                    octave = degree / count;
                    index = degree % count;
                }
            
                return {octave, index};
            }
            
            array<int, 2> mtof_02_innerScala_applyKBM(number note) {
                if ((this->mtof_02_innerScala_kbmMin == this->mtof_02_innerScala_kbmMax && this->mtof_02_innerScala_kbmMax == 0) || (note >= this->mtof_02_innerScala_kbmMin && note <= this->mtof_02_innerScala_kbmMax)) {
                    int degree = (int)(rnbo_floor(note - this->mtof_02_innerScala_kbmMid));
            
                    if (this->mtof_02_innerScala_kbmSize == 0) {
                        return {degree, 1};
                    }
            
                    array<int, 2> octdeg = this->mtof_02_innerScala_octdegree(degree, this->mtof_02_innerScala_kbmSize);
                    int octave = (int)(octdeg[0]);
                    Index index = (Index)(octdeg[1]);
            
                    if (this->mtof_02_innerScala_kbmMapSize > index) {
                        degree = (int)(this->mtof_02_innerScala_kbmValid[(Index)(this->mtof_02_innerScala_KBM_MAP_OFFSET + index)]);
            
                        if (degree >= 0) {
                            return {degree + octave * this->mtof_02_innerScala_kbmOctaveDegree, 1};
                        }
                    }
                }
            
                return {-1, 0};
            }
            
            number mtof_02_innerScala_applySCL(int degree, number frac, number refFreq) {
                array<int, 2> octdeg = this->mtof_02_innerScala_octdegree(degree, this->mtof_02_innerScala_sclEntryCount);
                return this->mtof_02_innerScala_applySCLOctIndex(octdeg[0], octdeg[1], frac, refFreq);
            }
            
            number mtof_02_innerScala_applySCLOctIndex(number octave, int index, number frac, number refFreq) {
                number p = 0;
            
                if (index > 0) {
                    p = this->mtof_02_innerScala_sclExpMul[(Index)(index - 1)];
                }
            
                if (frac > 0) {
                    p = this->linearinterp(frac, p, this->mtof_02_innerScala_sclExpMul[(Index)index]);
                } else if (frac < 0) {
                    p = this->linearinterp(-frac, this->mtof_02_innerScala_sclExpMul[(Index)index], p);
                }
            
                return refFreq * rnbo_pow(2, p + octave * this->mtof_02_innerScala_sclOctaveMul);
            }
            
            void mtof_02_innerScala_updateRefFreq() {
                this->mtof_02_innerScala_lastValid = false;
                int refOffset = (int)(this->mtof_02_innerScala_kbmRefNum - this->mtof_02_innerScala_kbmMid);
            
                if (refOffset == 0) {
                    this->mtof_02_innerScala_refFreq = this->mtof_02_innerScala_kbmRefFreq;
                } else {
                    int base = (int)(this->mtof_02_innerScala_kbmSize);
            
                    if (base < 1) {
                        base = this->mtof_02_innerScala_sclEntryCount;
                    }
            
                    array<int, 2> octdeg = this->mtof_02_innerScala_octdegree(refOffset, base);
                    number oct = (number)(octdeg[0]);
                    int index = (int)(octdeg[1]);
            
                    if (base > 0) {
                        oct = oct + rnbo_floor(index / base);
                        index = index % base;
                    }
            
                    if (index >= 0 && index < this->mtof_02_innerScala_kbmSize) {
                        if (index < this->mtof_02_innerScala_kbmMapSize) {
                            index = (int)(this->mtof_02_innerScala_kbmValid[(Index)((Index)(index) + this->mtof_02_innerScala_KBM_MAP_OFFSET)]);
                        } else {
                            index = -1;
                        }
                    }
            
                    if (index < 0 || index > this->mtof_02_innerScala_sclExpMul->length)
                        {} else {
                        number p = 0;
            
                        if (index > 0) {
                            p = this->mtof_02_innerScala_sclExpMul[(Index)(index - 1)];
                        }
            
                        this->mtof_02_innerScala_refFreq = this->mtof_02_innerScala_kbmRefFreq / rnbo_pow(2, p + oct * this->mtof_02_innerScala_sclOctaveMul);
                    }
                }
            }
            
            void mtof_02_innerScala_reset() {
                this->mtof_02_innerScala_lastValid = false;
                this->mtof_02_innerScala_lastNote = 0;
                this->mtof_02_innerScala_lastFreq = 0;
                this->mtof_02_innerScala_sclEntryCount = 0;
                this->mtof_02_innerScala_sclOctaveMul = 1;
                this->mtof_02_innerScala_sclExpMul = {};
                this->mtof_02_innerScala_kbmValid = {0, 0, 0, 60, 69, 440};
                this->mtof_02_innerScala_kbmMid = 60;
                this->mtof_02_innerScala_kbmRefNum = 69;
                this->mtof_02_innerScala_kbmRefFreq = 440;
                this->mtof_02_innerScala_kbmSize = 0;
                this->mtof_02_innerScala_kbmMin = 0;
                this->mtof_02_innerScala_kbmMax = 0;
                this->mtof_02_innerScala_kbmOctaveDegree = 12;
                this->mtof_02_innerScala_kbmMapSize = 0;
                this->mtof_02_innerScala_refFreq = 261.63;
            }
            
            void mtof_02_init() {
                this->mtof_02_innerScala_update(this->mtof_02_scale, this->mtof_02_map);
            }
            
            void samplerate_02_onSampleRateChanged(number samplerate) {
                if (this->samplerate_02_samplerate != samplerate) {
                    this->samplerate_02_samplerate_set(samplerate);
                }
            }
            
            void samplerate_02_dspsetup(bool force) {
                if ((bool)(this->samplerate_02_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->samplerate_02_onSampleRateChanged(this->samplerate());
                this->samplerate_02_setupDone = true;
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                expr_04_in1 = 0;
                expr_04_in2 = 72;
                expr_04_out1 = 0;
                expr_05_in1 = 0;
                expr_05_in2 = 0;
                expr_05_out1 = 0;
                mtof_02_base = 440;
                expr_06_in1 = 0;
                expr_06_in2 = 4;
                expr_06_out1 = 0;
                samplerate_02_samplerate = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                mtof_02_innerMtoF_lastInValue = 0;
                mtof_02_innerMtoF_lastOutValue = 0;
                mtof_02_innerMtoF_lastTuning = 0;
                mtof_02_innerScala_lastValid = false;
                mtof_02_innerScala_lastNote = 0;
                mtof_02_innerScala_lastFreq = 0;
                mtof_02_innerScala_sclEntryCount = 0;
                mtof_02_innerScala_sclOctaveMul = 1;
                mtof_02_innerScala_kbmValid = { 0, 0, 0, 60, 69, 440 };
                mtof_02_innerScala_kbmMid = 60;
                mtof_02_innerScala_kbmRefNum = 69;
                mtof_02_innerScala_kbmRefFreq = 440;
                mtof_02_innerScala_kbmSize = 0;
                mtof_02_innerScala_kbmMin = 0;
                mtof_02_innerScala_kbmMax = 0;
                mtof_02_innerScala_kbmOctaveDegree = 12;
                mtof_02_innerScala_kbmMapSize = 0;
                mtof_02_innerScala_refFreq = 261.63;
                samplerate_02_setupDone = false;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number expr_04_in1;
                number expr_04_in2;
                number expr_04_out1;
                number expr_05_in1;
                number expr_05_in2;
                number expr_05_out1;
                list mtof_02_midivalue;
                list mtof_02_scale;
                list mtof_02_map;
                number mtof_02_base;
                number expr_06_in1;
                number expr_06_in2;
                number expr_06_out1;
                number samplerate_02_samplerate;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number mtof_02_innerMtoF_lastInValue;
                number mtof_02_innerMtoF_lastOutValue;
                number mtof_02_innerMtoF_lastTuning;
                Float64BufferRef mtof_02_innerMtoF_buffer;
                const Index mtof_02_innerScala_KBM_MAP_OFFSET = 7;
                bool mtof_02_innerScala_lastValid;
                number mtof_02_innerScala_lastNote;
                number mtof_02_innerScala_lastFreq;
                int mtof_02_innerScala_sclEntryCount;
                number mtof_02_innerScala_sclOctaveMul;
                list mtof_02_innerScala_sclExpMul;
                list mtof_02_innerScala_kbmValid;
                int mtof_02_innerScala_kbmMid;
                int mtof_02_innerScala_kbmRefNum;
                number mtof_02_innerScala_kbmRefFreq;
                int mtof_02_innerScala_kbmSize;
                int mtof_02_innerScala_kbmMin;
                int mtof_02_innerScala_kbmMax;
                int mtof_02_innerScala_kbmOctaveDegree;
                Index mtof_02_innerScala_kbmMapSize;
                number mtof_02_innerScala_refFreq;
                bool samplerate_02_setupDone;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_147 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_149;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_147()
            {
            }
            
            ~RNBOSubpatcher_147()
            {
            }
            
            virtual RNBOSubpatcher_149* getPatcher() const {
                return static_cast<RNBOSubpatcher_149 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
                getEngine()->flushClockEvents(this, -871642103, false);
            }
            
            inline number linearinterp(number frac, number x, number y) {
                return x + (y - x) * frac;
            }
            
            number samplerate() const {
                return this->sr;
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                RNBO_UNUSED(numOutputs);
                RNBO_UNUSED(outputs);
                RNBO_UNUSED(numInputs);
                RNBO_UNUSED(inputs);
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                this->samplerate_03_dspsetup(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double samplerate) {
                this->samplerate_03_onSampleRateChanged(samplerate);
            }
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                RNBO_UNUSED(value);
                RNBO_UNUSED(hasValue);
                this->updateTime(time);
            
                switch (index) {
                case -871642103:
                    {
                    this->loadbang_03_startupbang_bang();
                    break;
                    }
                }
            }
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
                this->updateTime(time);
            
                switch (tag) {
                case TAG("startupbang"):
                    {
                    if (TAG("poly/freq-conversion/loadbang_obj-21") == objectId)
                        this->loadbang_03_startupbang_bang();
            
                    break;
                    }
                }
            }
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
                case TAG("startupbang"):
                    {
                    return "startupbang";
                    }
                case TAG("poly/freq-conversion/loadbang_obj-21"):
                    {
                    return "poly/freq-conversion/loadbang_obj-21";
                    }
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
                this->updateTime(time);
            
                if (index == 0) {
                    this->mtof_03_innerMtoF_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultMtofLookupTable256);
                }
            }
            
            void initialize() {
                this->assign_defaults();
                this->setState();
                this->mtof_03_innerMtoF_buffer = new Float64Buffer(this->getPatcher()->getPatcher()->RNBODefaultMtofLookupTable256);
            }
            
            protected:
            
            void eventinlet_03_out1_bang_bang() {
                this->expr_09_in1_bang();
            }
            
            void eventinlet_03_out1_list_set(const list& v) {
                {
                    if (v->length > 1)
                        this->expr_09_in2_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->expr_09_in1_set(converted);
                }
            }
            
            void loadbang_03_startupbang_bang() {
                this->loadbang_03_output_bang();
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 0;
            }
            
            Index getNumOutputChannels() const {
                return 0;
            }
            
            void initializeObjects() {
                this->mtof_03_innerScala_init();
                this->mtof_03_init();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
                this->getEngine()->scheduleClockEvent(this, -871642103, 0 + this->_currentTime);;
            }
            
            void allocateDataRefs() {
                this->mtof_03_innerMtoF_buffer->requestSize(65536, 1);
                this->mtof_03_innerMtoF_buffer->setSampleRate(this->sr);
                this->mtof_03_innerMtoF_buffer = this->mtof_03_innerMtoF_buffer->allocateIfNeeded();
            }
            
            void eventoutlet_03_in1_number_set(number v) {
                this->getPatcher()->updateTime(this->_currentTime);
                this->getPatcher()->p_03_out1_number_set(v);
            }
            
            void expr_08_out1_set(number v) {
                this->expr_08_out1 = v;
                this->eventoutlet_03_in1_number_set(this->expr_08_out1);
            }
            
            void expr_08_in1_set(number in1) {
                this->expr_08_in1 = in1;
            
                this->expr_08_out1_set(
                    (this->expr_08_in2 == 0 ? 0 : (this->expr_08_in2 == 0. ? 0. : this->expr_08_in1 / this->expr_08_in2))
                );//#map:freq-conversion//_obj-91:1
            }
            
            void expr_08_in2_set(number v) {
                this->expr_08_in2 = v;
            }
            
            void mtof_03_out_set(const list& v) {
                {
                    if (v->length > 1)
                        this->expr_08_in2_set(v[1]);
            
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->expr_08_in1_set(converted);
                }
            }
            
            void mtof_03_midivalue_set(const list& v) {
                this->mtof_03_midivalue = jsCreateListCopy(v);
                list tmp = list();
            
                for (int i = 0; i < this->mtof_03_midivalue->length; i++) {
                    tmp->push(
                        this->mtof_03_innerMtoF_next(this->mtof_03_midivalue[(Index)i], this->mtof_03_base)
                    );
                }
            
                this->mtof_03_out_set(tmp);
            }
            
            void expr_07_out1_set(number v) {
                this->expr_07_out1 = v;
            
                {
                    list converted = {this->expr_07_out1};
                    this->mtof_03_midivalue_set(converted);
                }
            }
            
            void expr_07_in1_set(number in1) {
                this->expr_07_in1 = in1;
                this->expr_07_out1_set(this->expr_07_in1 + this->expr_07_in2);//#map:freq-conversion/+_obj-94:1
            }
            
            void expr_09_out1_set(number v) {
                this->expr_09_out1 = v;
                this->expr_07_in1_set(this->expr_09_out1);
            }
            
            void expr_09_in1_set(number in1) {
                this->expr_09_in1 = in1;
                this->expr_09_out1_set(this->expr_09_in1 - this->expr_09_in2);//#map:freq-conversion/-_obj-20:1
            }
            
            void eventinlet_03_out1_number_set(number v) {
                this->expr_09_in1_set(v);
            }
            
            void expr_09_in1_bang() {
                this->expr_09_out1_set(this->expr_09_in1 - this->expr_09_in2);//#map:freq-conversion/-_obj-20:1
            }
            
            void expr_09_in2_set(number v) {
                this->expr_09_in2 = v;
            }
            
            void samplerate_03_samplerate_set(number v) {
                this->samplerate_03_samplerate = v;
                this->expr_08_in2_set(v);
            }
            
            void samplerate_03_input_bang() {
                this->samplerate_03_samplerate_set(this->samplerate());
            }
            
            void loadbang_03_output_bang() {
                this->samplerate_03_input_bang();
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            number mtof_03_innerMtoF_next(number midivalue, number tuning) {
                if (midivalue == this->mtof_03_innerMtoF_lastInValue && tuning == this->mtof_03_innerMtoF_lastTuning)
                    return this->mtof_03_innerMtoF_lastOutValue;
            
                this->mtof_03_innerMtoF_lastInValue = midivalue;
                this->mtof_03_innerMtoF_lastTuning = tuning;
                number result = 0;
            
                {
                    result = rnbo_exp(.057762265 * (midivalue - 69.0));
                }
            
                this->mtof_03_innerMtoF_lastOutValue = tuning * result;
                return this->mtof_03_innerMtoF_lastOutValue;
            }
            
            void mtof_03_innerMtoF_reset() {
                this->mtof_03_innerMtoF_lastInValue = 0;
                this->mtof_03_innerMtoF_lastOutValue = 0;
                this->mtof_03_innerMtoF_lastTuning = 0;
            }
            
            void mtof_03_innerScala_mid(int v) {
                this->mtof_03_innerScala_kbmMid = v;
                this->mtof_03_innerScala_updateRefFreq();
            }
            
            void mtof_03_innerScala_ref(int v) {
                this->mtof_03_innerScala_kbmRefNum = v;
                this->mtof_03_innerScala_updateRefFreq();
            }
            
            void mtof_03_innerScala_base(number v) {
                this->mtof_03_innerScala_kbmRefFreq = v;
                this->mtof_03_innerScala_updateRefFreq();
            }
            
            void mtof_03_innerScala_init() {
                list sclValid = {
                    12,
                    100,
                    0,
                    200,
                    0,
                    300,
                    0,
                    400,
                    0,
                    500,
                    0,
                    600,
                    0,
                    700,
                    0,
                    800,
                    0,
                    900,
                    0,
                    1000,
                    0,
                    1100,
                    0,
                    2,
                    1
                };
            
                this->mtof_03_innerScala_updateScale(sclValid);
            }
            
            void mtof_03_innerScala_update(list scale, list map) {
                if (scale->length > 0) {
                    this->mtof_03_innerScala_updateScale(scale);
                }
            
                if (map->length > 0) {
                    this->mtof_03_innerScala_updateMap(map);
                }
            }
            
            number mtof_03_innerScala_mtof(number note) {
                if ((bool)(this->mtof_03_innerScala_lastValid) && this->mtof_03_innerScala_lastNote == note) {
                    return this->mtof_03_innerScala_lastFreq;
                }
            
                array<int, 2> degoct = this->mtof_03_innerScala_applyKBM(note);
                number out = 0;
            
                if (degoct[1] > 0) {
                    out = this->mtof_03_innerScala_applySCL(degoct[0], fract(note), this->mtof_03_innerScala_refFreq);
                }
            
                this->mtof_03_innerScala_updateLast(note, out);
                return out;
            }
            
            number mtof_03_innerScala_ftom(number hz) {
                if (hz <= 0.0) {
                    return 0.0;
                }
            
                if ((bool)(this->mtof_03_innerScala_lastValid) && this->mtof_03_innerScala_lastFreq == hz) {
                    return this->mtof_03_innerScala_lastNote;
                }
            
                array<number, 2> df = this->mtof_03_innerScala_hztodeg(hz);
                int degree = (int)(df[0]);
                number frac = df[1];
                number out = 0;
            
                if (this->mtof_03_innerScala_kbmSize == 0) {
                    out = this->mtof_03_innerScala_kbmMid + degree;
                } else {
                    array<int, 2> octdeg = this->mtof_03_innerScala_octdegree(degree, this->mtof_03_innerScala_kbmOctaveDegree);
                    number oct = (number)(octdeg[0]);
                    int index = (int)(octdeg[1]);
                    Index entry = 0;
            
                    for (Index i = 0; i < this->mtof_03_innerScala_kbmMapSize; i++) {
                        if (index == this->mtof_03_innerScala_kbmValid[(Index)(i + this->mtof_03_innerScala_KBM_MAP_OFFSET)]) {
                            entry = i;
                            break;
                        }
                    }
            
                    out = oct * this->mtof_03_innerScala_kbmSize + entry + this->mtof_03_innerScala_kbmMid;
                }
            
                out = out + frac;
                this->mtof_03_innerScala_updateLast(out, hz);
                return this->mtof_03_innerScala_lastNote;
            }
            
            int mtof_03_innerScala_updateScale(list scl) {
                if (scl->length < 1) {
                    return 0;
                }
            
                number sclDataEntries = scl[0] * 2 + 1;
            
                if (sclDataEntries <= scl->length) {
                    this->mtof_03_innerScala_lastValid = false;
                    this->mtof_03_innerScala_sclExpMul = {};
                    number last = 1;
            
                    for (Index i = 1; i < sclDataEntries; i += 2) {
                        const number c = (const number)(scl[(Index)(i + 0)]);
                        const number d = (const number)(scl[(Index)(i + 1)]);
            
                        if (d <= 0) {
                            last = c / (number)1200;
                        } else {
                            last = rnbo_log2(c / d);
                        }
            
                        this->mtof_03_innerScala_sclExpMul->push(last);
                    }
            
                    this->mtof_03_innerScala_sclOctaveMul = last;
                    this->mtof_03_innerScala_sclEntryCount = (int)(this->mtof_03_innerScala_sclExpMul->length);
            
                    if (scl->length >= sclDataEntries + 3) {
                        this->mtof_03_innerScala_kbmMid = (int)(scl[(Index)(sclDataEntries + 2)]);
                        this->mtof_03_innerScala_kbmRefNum = (int)(scl[(Index)(sclDataEntries + 1)]);
                        this->mtof_03_innerScala_kbmRefFreq = scl[(Index)(sclDataEntries + 0)];
                        this->mtof_03_innerScala_kbmSize = (int)(0);
                    }
            
                    this->mtof_03_innerScala_updateRefFreq();
                    return 1;
                }
            
                return 0;
            }
            
            int mtof_03_innerScala_updateMap(list kbm) {
                if (kbm->length == 1 && kbm[0] == 0.0) {
                    kbm = {0.0, 0.0, 0.0, 60.0, 69.0, 440.0};
                }
            
                if (kbm->length >= 6 && kbm[0] >= 0.0) {
                    this->mtof_03_innerScala_lastValid = false;
                    Index size = (Index)(kbm[0]);
                    int octave = 12;
            
                    if (kbm->length > 6) {
                        octave = (int)(kbm[6]);
                    }
            
                    if (size > 0 && kbm->length < this->mtof_03_innerScala_KBM_MAP_OFFSET) {
                        return 0;
                    }
            
                    this->mtof_03_innerScala_kbmSize = (int)(size);
                    this->mtof_03_innerScala_kbmMin = (int)(kbm[1]);
                    this->mtof_03_innerScala_kbmMax = (int)(kbm[2]);
                    this->mtof_03_innerScala_kbmMid = (int)(kbm[3]);
                    this->mtof_03_innerScala_kbmRefNum = (int)(kbm[4]);
                    this->mtof_03_innerScala_kbmRefFreq = kbm[5];
                    this->mtof_03_innerScala_kbmOctaveDegree = octave;
                    this->mtof_03_innerScala_kbmValid = kbm;
                    this->mtof_03_innerScala_kbmMapSize = (kbm->length - this->mtof_03_innerScala_KBM_MAP_OFFSET > kbm->length ? kbm->length : (kbm->length - this->mtof_03_innerScala_KBM_MAP_OFFSET < 0 ? 0 : kbm->length - this->mtof_03_innerScala_KBM_MAP_OFFSET));
                    this->mtof_03_innerScala_updateRefFreq();
                    return 1;
                }
            
                return 0;
            }
            
            void mtof_03_innerScala_updateLast(number note, number freq) {
                this->mtof_03_innerScala_lastValid = true;
                this->mtof_03_innerScala_lastNote = note;
                this->mtof_03_innerScala_lastFreq = freq;
            }
            
            array<number, 2> mtof_03_innerScala_hztodeg(number hz) {
                number hza = rnbo_abs(hz);
            
                number octave = rnbo_floor(
                    rnbo_log2(hza / this->mtof_03_innerScala_refFreq) / this->mtof_03_innerScala_sclOctaveMul
                );
            
                int i = 0;
                number frac = 0;
                number n = 0;
            
                for (; i < this->mtof_03_innerScala_sclEntryCount; i++) {
                    number c = this->mtof_03_innerScala_applySCLOctIndex(octave, i + 0, 0.0, this->mtof_03_innerScala_refFreq);
                    n = this->mtof_03_innerScala_applySCLOctIndex(octave, i + 1, 0.0, this->mtof_03_innerScala_refFreq);
            
                    if (c <= hza && hza < n) {
                        if (c != hza) {
                            frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
                        }
            
                        break;
                    }
                }
            
                if (i == this->mtof_03_innerScala_sclEntryCount && n != hza) {
                    number c = n;
                    n = this->mtof_03_innerScala_applySCLOctIndex(octave + 1, 0, 0.0, this->mtof_03_innerScala_refFreq);
                    frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
                }
            
                number deg = i + octave * this->mtof_03_innerScala_sclEntryCount;
            
                {
                    deg = rnbo_fround((deg + frac) * 1 / (number)1) * 1;
                    frac = 0.0;
                }
            
                return {deg, frac};
            }
            
            array<int, 2> mtof_03_innerScala_octdegree(int degree, int count) {
                int octave = 0;
                int index = 0;
            
                if (degree < 0) {
                    octave = -(1 + (-1 - degree) / count);
                    index = -degree % count;
            
                    if (index > 0) {
                        index = count - index;
                    }
                } else {
                    octave = degree / count;
                    index = degree % count;
                }
            
                return {octave, index};
            }
            
            array<int, 2> mtof_03_innerScala_applyKBM(number note) {
                if ((this->mtof_03_innerScala_kbmMin == this->mtof_03_innerScala_kbmMax && this->mtof_03_innerScala_kbmMax == 0) || (note >= this->mtof_03_innerScala_kbmMin && note <= this->mtof_03_innerScala_kbmMax)) {
                    int degree = (int)(rnbo_floor(note - this->mtof_03_innerScala_kbmMid));
            
                    if (this->mtof_03_innerScala_kbmSize == 0) {
                        return {degree, 1};
                    }
            
                    array<int, 2> octdeg = this->mtof_03_innerScala_octdegree(degree, this->mtof_03_innerScala_kbmSize);
                    int octave = (int)(octdeg[0]);
                    Index index = (Index)(octdeg[1]);
            
                    if (this->mtof_03_innerScala_kbmMapSize > index) {
                        degree = (int)(this->mtof_03_innerScala_kbmValid[(Index)(this->mtof_03_innerScala_KBM_MAP_OFFSET + index)]);
            
                        if (degree >= 0) {
                            return {degree + octave * this->mtof_03_innerScala_kbmOctaveDegree, 1};
                        }
                    }
                }
            
                return {-1, 0};
            }
            
            number mtof_03_innerScala_applySCL(int degree, number frac, number refFreq) {
                array<int, 2> octdeg = this->mtof_03_innerScala_octdegree(degree, this->mtof_03_innerScala_sclEntryCount);
                return this->mtof_03_innerScala_applySCLOctIndex(octdeg[0], octdeg[1], frac, refFreq);
            }
            
            number mtof_03_innerScala_applySCLOctIndex(number octave, int index, number frac, number refFreq) {
                number p = 0;
            
                if (index > 0) {
                    p = this->mtof_03_innerScala_sclExpMul[(Index)(index - 1)];
                }
            
                if (frac > 0) {
                    p = this->linearinterp(frac, p, this->mtof_03_innerScala_sclExpMul[(Index)index]);
                } else if (frac < 0) {
                    p = this->linearinterp(-frac, this->mtof_03_innerScala_sclExpMul[(Index)index], p);
                }
            
                return refFreq * rnbo_pow(2, p + octave * this->mtof_03_innerScala_sclOctaveMul);
            }
            
            void mtof_03_innerScala_updateRefFreq() {
                this->mtof_03_innerScala_lastValid = false;
                int refOffset = (int)(this->mtof_03_innerScala_kbmRefNum - this->mtof_03_innerScala_kbmMid);
            
                if (refOffset == 0) {
                    this->mtof_03_innerScala_refFreq = this->mtof_03_innerScala_kbmRefFreq;
                } else {
                    int base = (int)(this->mtof_03_innerScala_kbmSize);
            
                    if (base < 1) {
                        base = this->mtof_03_innerScala_sclEntryCount;
                    }
            
                    array<int, 2> octdeg = this->mtof_03_innerScala_octdegree(refOffset, base);
                    number oct = (number)(octdeg[0]);
                    int index = (int)(octdeg[1]);
            
                    if (base > 0) {
                        oct = oct + rnbo_floor(index / base);
                        index = index % base;
                    }
            
                    if (index >= 0 && index < this->mtof_03_innerScala_kbmSize) {
                        if (index < this->mtof_03_innerScala_kbmMapSize) {
                            index = (int)(this->mtof_03_innerScala_kbmValid[(Index)((Index)(index) + this->mtof_03_innerScala_KBM_MAP_OFFSET)]);
                        } else {
                            index = -1;
                        }
                    }
            
                    if (index < 0 || index > this->mtof_03_innerScala_sclExpMul->length)
                        {} else {
                        number p = 0;
            
                        if (index > 0) {
                            p = this->mtof_03_innerScala_sclExpMul[(Index)(index - 1)];
                        }
            
                        this->mtof_03_innerScala_refFreq = this->mtof_03_innerScala_kbmRefFreq / rnbo_pow(2, p + oct * this->mtof_03_innerScala_sclOctaveMul);
                    }
                }
            }
            
            void mtof_03_innerScala_reset() {
                this->mtof_03_innerScala_lastValid = false;
                this->mtof_03_innerScala_lastNote = 0;
                this->mtof_03_innerScala_lastFreq = 0;
                this->mtof_03_innerScala_sclEntryCount = 0;
                this->mtof_03_innerScala_sclOctaveMul = 1;
                this->mtof_03_innerScala_sclExpMul = {};
                this->mtof_03_innerScala_kbmValid = {0, 0, 0, 60, 69, 440};
                this->mtof_03_innerScala_kbmMid = 60;
                this->mtof_03_innerScala_kbmRefNum = 69;
                this->mtof_03_innerScala_kbmRefFreq = 440;
                this->mtof_03_innerScala_kbmSize = 0;
                this->mtof_03_innerScala_kbmMin = 0;
                this->mtof_03_innerScala_kbmMax = 0;
                this->mtof_03_innerScala_kbmOctaveDegree = 12;
                this->mtof_03_innerScala_kbmMapSize = 0;
                this->mtof_03_innerScala_refFreq = 261.63;
            }
            
            void mtof_03_init() {
                this->mtof_03_innerScala_update(this->mtof_03_scale, this->mtof_03_map);
            }
            
            void samplerate_03_onSampleRateChanged(number samplerate) {
                if (this->samplerate_03_samplerate != samplerate) {
                    this->samplerate_03_samplerate_set(samplerate);
                }
            }
            
            void samplerate_03_dspsetup(bool force) {
                if ((bool)(this->samplerate_03_setupDone) && (bool)(!(bool)(force)))
                    return;
            
                this->samplerate_03_onSampleRateChanged(this->samplerate());
                this->samplerate_03_setupDone = true;
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                expr_07_in1 = 0;
                expr_07_in2 = 72;
                expr_07_out1 = 0;
                expr_08_in1 = 0;
                expr_08_in2 = 0;
                expr_08_out1 = 0;
                mtof_03_base = 440;
                expr_09_in1 = 0;
                expr_09_in2 = 4;
                expr_09_out1 = 0;
                samplerate_03_samplerate = 0;
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                mtof_03_innerMtoF_lastInValue = 0;
                mtof_03_innerMtoF_lastOutValue = 0;
                mtof_03_innerMtoF_lastTuning = 0;
                mtof_03_innerScala_lastValid = false;
                mtof_03_innerScala_lastNote = 0;
                mtof_03_innerScala_lastFreq = 0;
                mtof_03_innerScala_sclEntryCount = 0;
                mtof_03_innerScala_sclOctaveMul = 1;
                mtof_03_innerScala_kbmValid = { 0, 0, 0, 60, 69, 440 };
                mtof_03_innerScala_kbmMid = 60;
                mtof_03_innerScala_kbmRefNum = 69;
                mtof_03_innerScala_kbmRefFreq = 440;
                mtof_03_innerScala_kbmSize = 0;
                mtof_03_innerScala_kbmMin = 0;
                mtof_03_innerScala_kbmMax = 0;
                mtof_03_innerScala_kbmOctaveDegree = 12;
                mtof_03_innerScala_kbmMapSize = 0;
                mtof_03_innerScala_refFreq = 261.63;
                samplerate_03_setupDone = false;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number expr_07_in1;
                number expr_07_in2;
                number expr_07_out1;
                number expr_08_in1;
                number expr_08_in2;
                number expr_08_out1;
                list mtof_03_midivalue;
                list mtof_03_scale;
                list mtof_03_map;
                number mtof_03_base;
                number expr_09_in1;
                number expr_09_in2;
                number expr_09_out1;
                number samplerate_03_samplerate;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                number mtof_03_innerMtoF_lastInValue;
                number mtof_03_innerMtoF_lastOutValue;
                number mtof_03_innerMtoF_lastTuning;
                Float64BufferRef mtof_03_innerMtoF_buffer;
                const Index mtof_03_innerScala_KBM_MAP_OFFSET = 7;
                bool mtof_03_innerScala_lastValid;
                number mtof_03_innerScala_lastNote;
                number mtof_03_innerScala_lastFreq;
                int mtof_03_innerScala_sclEntryCount;
                number mtof_03_innerScala_sclOctaveMul;
                list mtof_03_innerScala_sclExpMul;
                list mtof_03_innerScala_kbmValid;
                int mtof_03_innerScala_kbmMid;
                int mtof_03_innerScala_kbmRefNum;
                number mtof_03_innerScala_kbmRefFreq;
                int mtof_03_innerScala_kbmSize;
                int mtof_03_innerScala_kbmMin;
                int mtof_03_innerScala_kbmMax;
                int mtof_03_innerScala_kbmOctaveDegree;
                Index mtof_03_innerScala_kbmMapSize;
                number mtof_03_innerScala_refFreq;
                bool samplerate_03_setupDone;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    class RNBOSubpatcher_148 : public PatcherInterfaceImpl {
            
            friend class RNBOSubpatcher_149;
            friend class rnbomatic;
            
            public:
            
            RNBOSubpatcher_148()
            {
            }
            
            ~RNBOSubpatcher_148()
            {
            }
            
            virtual RNBOSubpatcher_149* getPatcher() const {
                return static_cast<RNBOSubpatcher_149 *>(_parentPatcher);
            }
            
            rnbomatic* getTopLevelPatcher() {
                return this->getPatcher()->getTopLevelPatcher();
            }
            
            void cancelClockEvents()
            {
                getEngine()->flushClockEvents(this, 892732297, false);
                getEngine()->flushClockEvents(this, -834257525, false);
                getEngine()->flushClockEvents(this, 29237386, false);
            }
            
            Index getNumMidiInputPorts() const {
                return 0;
            }
            
            void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
            
            Index getNumMidiOutputPorts() const {
                return 0;
            }
            
            void process(
                const SampleValue * const* inputs,
                Index numInputs,
                SampleValue * const* outputs,
                Index numOutputs,
                Index n
            ) {
                RNBO_UNUSED(numOutputs);
                RNBO_UNUSED(outputs);
                RNBO_UNUSED(numInputs);
                RNBO_UNUSED(inputs);
                this->vs = n;
                this->updateTime(this->getEngine()->getCurrentTime());
                this->stackprotect_perform(n);
                this->audioProcessSampleCount += this->vs;
            }
            
            void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
                if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
                    this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
                    this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
                    this->didAllocateSignals = true;
                }
            
                const bool sampleRateChanged = sampleRate != this->sr;
                const bool maxvsChanged = maxBlockSize != this->maxvs;
                const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
            
                if (sampleRateChanged || maxvsChanged) {
                    this->vs = maxBlockSize;
                    this->maxvs = maxBlockSize;
                    this->sr = sampleRate;
                    this->invsr = 1 / sampleRate;
                }
            
                RNBO_UNUSED(forceDSPSetup);
            
                if (sampleRateChanged)
                    this->onSampleRateChanged(sampleRate);
            }
            
            void setProbingTarget(MessageTag id) {
                switch (id) {
                default:
                    {
                    this->setProbingIndex(-1);
                    break;
                    }
                }
            }
            
            void setProbingIndex(ProbingIndex ) {}
            
            Index getProbingChannels(MessageTag outletId) const {
                RNBO_UNUSED(outletId);
                return 0;
            }
            
            void setVoiceIndex(Index index)  {
                this->_voiceIndex = index;
            }
            
            void setNoteNumber(Int noteNumber)  {
                this->_noteNumber = noteNumber;
            }
            
            Index getIsMuted()  {
                return this->isMuted;
            }
            
            void setIsMuted(Index v)  {
                this->isMuted = v;
            }
            
            void onSampleRateChanged(double ) {}
            
            Index getPatcherSerial() const {
                return 0;
            }
            
            void getState(PatcherStateInterface& ) {}
            
            void setState() {}
            
            void getPreset(PatcherStateInterface& ) {}
            
            void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
            
            void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValue(index, value, time);
            }
            
            void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
                this->setParameterValue(index, this->getParameterValue(index), time);
            }
            
            void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
                this->setParameterValueNormalized(index, value, time);
            }
            
            ParameterValue getParameterValue(ParameterIndex index)  {
                switch (index) {
                default:
                    {
                    return 0;
                    }
                }
            }
            
            ParameterIndex getNumSignalInParameters() const {
                return 0;
            }
            
            ParameterIndex getNumSignalOutParameters() const {
                return 0;
            }
            
            ParameterIndex getNumParameters() const {
                return 0;
            }
            
            ConstCharPointer getParameterName(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            ConstCharPointer getParameterId(ParameterIndex index) const {
                switch (index) {
                default:
                    {
                    return "bogus";
                    }
                }
            }
            
            void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
            
            void sendParameter(ParameterIndex index, bool ignoreValue) {
                this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
            }
            
            void setParameterOffset(ParameterIndex offset) {
                this->parameterOffset = offset;
            }
            
            ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
                if (steps == 1) {
                    if (normalizedValue > 0) {
                        normalizedValue = 1.;
                    }
                } else {
                    ParameterValue oneStep = (number)1. / (steps - 1);
                    ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
                    normalizedValue = numberOfSteps * oneStep;
                }
            
                return normalizedValue;
            }
            
            ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
                switch (index) {
                default:
                    {
                    return value;
                    }
                }
            }
            
            void scheduleParamInit(ParameterIndex index, Index order) {
                this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
            }
            
            void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
                RNBO_UNUSED(value);
                RNBO_UNUSED(hasValue);
                this->updateTime(time);
            
                switch (index) {
                case 892732297:
                    {
                    this->loadmess_01_startupbang_bang();
                    break;
                    }
                case -834257525:
                    {
                    this->loadmess_02_startupbang_bang();
                    break;
                    }
                case 29237386:
                    {
                    this->loadmess_03_startupbang_bang();
                    break;
                    }
                }
            }
            
            void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
            
            void processOutletEvent(
                EngineLink* sender,
                OutletIndex index,
                ParameterValue value,
                MillisecondTime time
            ) {
                this->updateTime(time);
                this->processOutletAtCurrentTime(sender, index, value);
            }
            
            void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
                this->updateTime(time);
            
                switch (tag) {
                case TAG("valin"):
                    {
                    if (TAG("poly/old-magic-number-tuning-system/number_obj-39") == objectId)
                        this->numberobj_01_valin_set(payload);
            
                    if (TAG("poly/old-magic-number-tuning-system/number_obj-42") == objectId)
                        this->numberobj_02_valin_set(payload);
            
                    break;
                    }
                case TAG("format"):
                    {
                    if (TAG("poly/old-magic-number-tuning-system/number_obj-39") == objectId)
                        this->numberobj_01_format_set(payload);
            
                    if (TAG("poly/old-magic-number-tuning-system/number_obj-42") == objectId)
                        this->numberobj_02_format_set(payload);
            
                    break;
                    }
                }
            }
            
            void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
            
            void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
                this->updateTime(time);
            
                switch (tag) {
                case TAG("startupbang"):
                    {
                    if (TAG("poly/old-magic-number-tuning-system/loadmess_obj-7") == objectId)
                        this->loadmess_01_startupbang_bang();
            
                    if (TAG("poly/old-magic-number-tuning-system/loadmess_obj-44") == objectId)
                        this->loadmess_02_startupbang_bang();
            
                    if (TAG("poly/old-magic-number-tuning-system/loadmess_obj-45") == objectId)
                        this->loadmess_03_startupbang_bang();
            
                    break;
                    }
                }
            }
            
            MessageTagInfo resolveTag(MessageTag tag) const {
                switch (tag) {
                case TAG("valout"):
                    {
                    return "valout";
                    }
                case TAG("poly/old-magic-number-tuning-system/number_obj-39"):
                    {
                    return "poly/old-magic-number-tuning-system/number_obj-39";
                    }
                case TAG("setup"):
                    {
                    return "setup";
                    }
                case TAG("poly/old-magic-number-tuning-system/number_obj-42"):
                    {
                    return "poly/old-magic-number-tuning-system/number_obj-42";
                    }
                case TAG("startupbang"):
                    {
                    return "startupbang";
                    }
                case TAG("poly/old-magic-number-tuning-system/loadmess_obj-7"):
                    {
                    return "poly/old-magic-number-tuning-system/loadmess_obj-7";
                    }
                case TAG("poly/old-magic-number-tuning-system/loadmess_obj-44"):
                    {
                    return "poly/old-magic-number-tuning-system/loadmess_obj-44";
                    }
                case TAG("valin"):
                    {
                    return "valin";
                    }
                case TAG("format"):
                    {
                    return "format";
                    }
                case TAG("poly/old-magic-number-tuning-system/loadmess_obj-45"):
                    {
                    return "poly/old-magic-number-tuning-system/loadmess_obj-45";
                    }
                }
            
                return nullptr;
            }
            
            DataRef* getDataRef(DataRefIndex index)  {
                switch (index) {
                default:
                    {
                    return nullptr;
                    }
                }
            }
            
            DataRefIndex getNumDataRefs() const {
                return 0;
            }
            
            void fillDataRef(DataRefIndex , DataRef& ) {}
            
            void processDataViewUpdate(DataRefIndex , MillisecondTime ) {}
            
            void initialize() {
                this->assign_defaults();
                this->setState();
            }
            
            protected:
            
            void loadmess_01_startupbang_bang() {
                this->loadmess_01_message_bang();
            }
            
            void loadmess_02_startupbang_bang() {
                this->loadmess_02_message_bang();
            }
            
            void numberobj_01_valin_set(number v) {
                this->numberobj_01_value_set(v);
            }
            
            void numberobj_01_format_set(number v) {
                this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
            }
            
            void loadmess_03_startupbang_bang() {
                this->loadmess_03_message_bang();
            }
            
            void numberobj_02_valin_set(number v) {
                this->numberobj_02_value_set(v);
            }
            
            void numberobj_02_format_set(number v) {
                this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
            }
            
            number msToSamps(MillisecondTime ms, number sampleRate) {
                return ms * sampleRate * 0.001;
            }
            
            MillisecondTime sampsToMs(SampleIndex samps) {
                return samps * (this->invsr * 1000);
            }
            
            Index getMaxBlockSize() const {
                return this->maxvs;
            }
            
            number getSampleRate() const {
                return this->sr;
            }
            
            bool hasFixedVectorSize() const {
                return false;
            }
            
            Index getNumInputChannels() const {
                return 0;
            }
            
            Index getNumOutputChannels() const {
                return 0;
            }
            
            void initializeObjects() {
                this->numberobj_01_init();
                this->numberobj_02_init();
            }
            
            void sendOutlet(OutletIndex index, ParameterValue value) {
                this->getEngine()->sendOutlet(this, index, value);
            }
            
            void startup() {
                this->updateTime(this->getEngine()->getCurrentTime());
                this->getEngine()->scheduleClockEvent(this, 892732297, 0 + this->_currentTime);;
                this->getEngine()->scheduleClockEvent(this, -834257525, 0 + this->_currentTime);;
                this->getEngine()->scheduleClockEvent(this, 29237386, 0 + this->_currentTime);;
            }
            
            void allocateDataRefs() {}
            
            void loadmess_01_message_bang() {}
            
            void scale_03_outhigh_set(number v) {
                this->scale_03_outhigh = v;
            }
            
            void scale_02_outhigh_set(number v) {
                this->scale_02_outhigh = v;
            }
            
            void scale_01_outhigh_set(number v) {
                this->scale_01_outhigh = v;
            }
            
            void expr_14_out1_set(number v) {
                this->expr_14_out1 = v;
                this->scale_03_outhigh_set(this->expr_14_out1);
                this->scale_02_outhigh_set(this->expr_14_out1);
                this->scale_01_outhigh_set(this->expr_14_out1);
            }
            
            void expr_14_in1_set(number in1) {
                this->expr_14_in1 = in1;
                this->expr_14_out1_set(this->expr_14_in1 + this->expr_14_in2);//#map:old-magic-number-tuning-system/+_obj-40:1
            }
            
            void scale_03_outlow_set(number v) {
                this->scale_03_outlow = v;
            }
            
            void scale_02_outlow_set(number v) {
                this->scale_02_outlow = v;
            }
            
            void scale_01_outlow_set(number v) {
                this->scale_01_outlow = v;
            }
            
            void numberobj_01_output_set(number v) {
                this->expr_14_in1_set(v);
                this->scale_03_outlow_set(v);
                this->scale_02_outlow_set(v);
                this->scale_01_outlow_set(v);
            }
            
            void numberobj_01_value_set(number v) {
                this->numberobj_01_value_setter(v);
                v = this->numberobj_01_value;
                number localvalue = v;
            
                if (this->numberobj_01_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->getEngine()->sendNumMessage(
                    TAG("valout"),
                    TAG("poly/old-magic-number-tuning-system/number_obj-39"),
                    localvalue,
                    this->_currentTime
                );
            
                this->numberobj_01_output_set(localvalue);
            }
            
            void loadmess_02_message_bang() {
                list v = this->loadmess_02_message;
            
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->numberobj_01_value_set(converted);
                }
            }
            
            void expr_14_in2_set(number v) {
                this->expr_14_in2 = v;
            }
            
            void trigger_01_out2_set(number v) {
                this->expr_14_in2_set(v);
            }
            
            void expr_14_in1_bang() {
                this->expr_14_out1_set(this->expr_14_in1 + this->expr_14_in2);//#map:old-magic-number-tuning-system/+_obj-40:1
            }
            
            void trigger_01_out1_bang() {
                this->expr_14_in1_bang();
            }
            
            void trigger_01_input_number_set(number v) {
                this->trigger_01_out2_set(v);
                this->trigger_01_out1_bang();
            }
            
            void numberobj_02_output_set(number v) {
                this->trigger_01_input_number_set(v);
            }
            
            void numberobj_02_value_set(number v) {
                this->numberobj_02_value_setter(v);
                v = this->numberobj_02_value;
                number localvalue = v;
            
                if (this->numberobj_02_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->getEngine()->sendNumMessage(
                    TAG("valout"),
                    TAG("poly/old-magic-number-tuning-system/number_obj-42"),
                    localvalue,
                    this->_currentTime
                );
            
                this->numberobj_02_output_set(localvalue);
            }
            
            void loadmess_03_message_bang() {
                list v = this->loadmess_03_message;
            
                {
                    number converted = (v->length > 0 ? v[0] : 0);
                    this->numberobj_02_value_set(converted);
                }
            }
            
            void stackprotect_perform(Index n) {
                RNBO_UNUSED(n);
                auto __stackprotect_count = this->stackprotect_count;
                __stackprotect_count = 0;
                this->stackprotect_count = __stackprotect_count;
            }
            
            void numberobj_01_value_setter(number v) {
                number localvalue = v;
            
                if (this->numberobj_01_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->numberobj_01_value = localvalue;
            }
            
            void numberobj_02_value_setter(number v) {
                number localvalue = v;
            
                if (this->numberobj_02_currentFormat != 6) {
                    localvalue = trunc(localvalue);
                }
            
                this->numberobj_02_value = localvalue;
            }
            
            void numberobj_01_init() {
                this->numberobj_01_currentFormat = 6;
            
                this->getEngine()->sendNumMessage(
                    TAG("setup"),
                    TAG("poly/old-magic-number-tuning-system/number_obj-39"),
                    1,
                    this->_currentTime
                );
            }
            
            void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->numberobj_01_value;
            }
            
            void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->numberobj_01_value_set(preset["value"]);
            }
            
            void numberobj_02_init() {
                this->numberobj_02_currentFormat = 6;
            
                this->getEngine()->sendNumMessage(
                    TAG("setup"),
                    TAG("poly/old-magic-number-tuning-system/number_obj-42"),
                    1,
                    this->_currentTime
                );
            }
            
            void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
                preset["value"] = this->numberobj_02_value;
            }
            
            void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
                if ((bool)(stateIsEmpty(preset)))
                    return;
            
                this->numberobj_02_value_set(preset["value"]);
            }
            
            bool stackprotect_check() {
                this->stackprotect_count++;
            
                if (this->stackprotect_count > 128) {
                    console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
                    return true;
                }
            
                return false;
            }
            
            void updateTime(MillisecondTime time) {
                this->_currentTime = time;
                this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
            
                if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
                    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
            
                if (this->sampleOffsetIntoNextAudioBuffer < 0)
                    this->sampleOffsetIntoNextAudioBuffer = 0;
            }
            
            void assign_defaults()
            {
                expr_10_in1 = 0;
                expr_10_in2 = 8;
                expr_10_out1 = 0;
                scale_01_inlow = 0;
                scale_01_inhigh = 127;
                scale_01_outlow = 50.4;
                scale_01_outhigh = 51.4;
                scale_01_power = 1;
                expr_11_in1 = 0;
                expr_11_in2 = 24;
                expr_11_out1 = 0;
                scale_02_inlow = 0;
                scale_02_inhigh = 127;
                scale_02_outlow = 50.4;
                scale_02_outhigh = 51.4;
                scale_02_power = 1;
                expr_12_in1 = 0;
                expr_12_in2 = 26;
                expr_12_out1 = 0;
                expr_13_in1 = 0;
                expr_13_in2 = 48;
                expr_13_out1 = 0;
                scale_03_inlow = 0;
                scale_03_inhigh = 127;
                scale_03_outlow = 50.4;
                scale_03_outhigh = 51.4;
                scale_03_power = 1;
                loadmess_01_message = { 50.25 };
                loadmess_02_message = { 0 };
                expr_14_in1 = 0;
                expr_14_in2 = 1.1;
                expr_14_out1 = 0;
                numberobj_01_value = 0;
                numberobj_01_value_setter(numberobj_01_value);
                loadmess_03_message = { 1.5 };
                numberobj_02_value = 0;
                numberobj_02_value_setter(numberobj_02_value);
                _currentTime = 0;
                audioProcessSampleCount = 0;
                sampleOffsetIntoNextAudioBuffer = 0;
                zeroBuffer = nullptr;
                dummyBuffer = nullptr;
                didAllocateSignals = 0;
                vs = 0;
                maxvs = 0;
                sr = 44100;
                invsr = 0.00002267573696;
                numberobj_01_currentFormat = 6;
                numberobj_01_lastValue = 0;
                numberobj_02_currentFormat = 6;
                numberobj_02_lastValue = 0;
                stackprotect_count = 0;
                _voiceIndex = 0;
                _noteNumber = 0;
                isMuted = 1;
                parameterOffset = 0;
            }
            
            // member variables
            
                number expr_10_in1;
                number expr_10_in2;
                number expr_10_out1;
                list scale_01_input;
                number scale_01_inlow;
                number scale_01_inhigh;
                number scale_01_outlow;
                number scale_01_outhigh;
                number scale_01_power;
                list scale_01_out;
                number expr_11_in1;
                number expr_11_in2;
                number expr_11_out1;
                list scale_02_input;
                number scale_02_inlow;
                number scale_02_inhigh;
                number scale_02_outlow;
                number scale_02_outhigh;
                number scale_02_power;
                list scale_02_out;
                number expr_12_in1;
                number expr_12_in2;
                number expr_12_out1;
                number expr_13_in1;
                number expr_13_in2;
                number expr_13_out1;
                list scale_03_input;
                number scale_03_inlow;
                number scale_03_inhigh;
                number scale_03_outlow;
                number scale_03_outhigh;
                number scale_03_power;
                list scale_03_out;
                list loadmess_01_message;
                list loadmess_02_message;
                number expr_14_in1;
                number expr_14_in2;
                number expr_14_out1;
                number numberobj_01_value;
                list loadmess_03_message;
                number numberobj_02_value;
                MillisecondTime _currentTime;
                UInt64 audioProcessSampleCount;
                SampleIndex sampleOffsetIntoNextAudioBuffer;
                signal zeroBuffer;
                signal dummyBuffer;
                bool didAllocateSignals;
                Index vs;
                Index maxvs;
                number sr;
                number invsr;
                Int numberobj_01_currentFormat;
                number numberobj_01_lastValue;
                Int numberobj_02_currentFormat;
                number numberobj_02_lastValue;
                number stackprotect_count;
                Index _voiceIndex;
                Int _noteNumber;
                Index isMuted;
                ParameterIndex parameterOffset;
            
    };
    
    RNBOSubpatcher_149()
    {
    }
    
    ~RNBOSubpatcher_149()
    {
        delete this->p_01;
        delete this->p_02;
        delete this->p_03;
        delete this->p_04;
    }
    
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -1468824490, false);
    }
    
    Index voice() {
        return this->_voiceIndex;
    }
    
    number random(number low, number high) {
        number range = high - low;
        return globalrandom() * range + low;
    }
    
    Index vectorsize() const {
        return this->vs;
    }
    
    inline number safediv(number num, number denom) {
        return (denom == 0.0 ? 0.0 : num / denom);
    }
    
    number safepow(number base, number exponent) {
        return fixnan(rnbo_pow(base, exponent));
    }
    
    number scale(
        number x,
        number lowin,
        number hiin,
        number lowout,
        number highout,
        number pow
    ) {
        auto inscale = this->safediv(1., hiin - lowin);
        number outdiff = highout - lowout;
        number value = (x - lowin) * inscale;
    
        if (pow != 1) {
            if (value > 0)
                value = this->safepow(value, pow);
            else
                value = -this->safepow(-value, pow);
        }
    
        value = value * outdiff + lowout;
        return value;
    }
    
    number samplerate() const {
        return this->sr;
    }
    
    number maximum(number x, number y) {
        return (x < y ? y : x);
    }
    
    number minimum(number x, number y) {
        return (y < x ? y : x);
    }
    
    Index getNumMidiInputPorts() const {
        return 1;
    }
    
    void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
        this->updateTime(time);
        this->notein_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    }
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        RNBO_UNUSED(numInputs);
        RNBO_UNUSED(inputs);
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime());
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    
        if (this->getIsMuted())
            return;
    
        this->noise_tilde_01_perform(this->signals[0], n);
    
        this->adsr_01_perform(
            this->adsr_01_attack,
            this->adsr_01_decay,
            this->adsr_01_sustain,
            this->adsr_01_release,
            this->zeroBuffer,
            this->signals[1],
            n
        );
    
        this->dspexpr_02_perform(this->signals[0], this->signals[1], this->signals[2], n);
        this->dspexpr_01_perform(this->signals[2], this->dspexpr_01_in2, this->signals[1], n);
    
        this->gen_02_perform(
            this->signals[1],
            this->gen_02_in2,
            this->gen_02_in3,
            this->gen_02_in4,
            this->gen_02_in5,
            this->gen_02_id,
            this->gen_02_voices,
            this->signals[2],
            n
        );
    
        this->dspexpr_03_perform(this->signals[2], this->dspexpr_03_in2, this->signals[0], n);
    
        this->gen_03_perform(
            this->signals[1],
            this->gen_03_in2,
            this->gen_03_in3,
            this->gen_03_in4,
            this->gen_03_in5,
            this->gen_03_voices,
            this->gen_03_id,
            this->signals[2],
            n
        );
    
        this->dspexpr_04_perform(this->signals[2], this->dspexpr_04_in2, this->signals[3], n);
    
        this->gen_01_perform(
            this->signals[1],
            this->gen_01_in2,
            this->gen_01_in3,
            this->gen_01_in4,
            this->gen_01_in5,
            this->gen_01_id,
            this->gen_01_voices,
            this->signals[2],
            n
        );
    
        this->signaladder_01_perform(this->signals[3], this->signals[0], this->signals[2], this->signals[2], n);
        this->limi_01_perform(this->signals[2], this->signals[1], n);
        this->dcblock_tilde_01_perform(this->signals[1], this->dcblock_tilde_01_gain, this->signals[0], n);
        this->signaladder_02_perform(this->signals[0], out2, out2, n);
        this->signaladder_03_perform(this->signals[0], out1, out1, n);
        this->p_01_perform(n);
        this->p_02_perform(n);
        this->p_03_perform(n);
        this->p_04_perform(n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 4; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->adsr_01_triggerBuf = resizeSignal(this->adsr_01_triggerBuf, this->maxvs, maxBlockSize);
            this->adsr_01_triggerValueBuf = resizeSignal(this->adsr_01_triggerValueBuf, this->maxvs, maxBlockSize);
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->adsr_01_dspsetup(forceDSPSetup);
        this->limi_01_dspsetup(forceDSPSetup);
        this->dcblock_tilde_01_dspsetup(forceDSPSetup);
        this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_02->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_03->prepareToProcess(sampleRate, maxBlockSize, force);
        this->p_04->prepareToProcess(sampleRate, maxBlockSize, force);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    void setProbingTarget(MessageTag id) {
        switch (id) {
        default:
            {
            this->setProbingIndex(-1);
            break;
            }
        }
    }
    
    void setProbingIndex(ProbingIndex ) {}
    
    Index getProbingChannels(MessageTag outletId) const {
        RNBO_UNUSED(outletId);
        return 0;
    }
    
    void setVoiceIndex(Index index)  {
        this->_voiceIndex = index;
        this->p_01->setVoiceIndex(index);
        this->p_02->setVoiceIndex(index);
        this->p_03->setVoiceIndex(index);
        this->p_04->setVoiceIndex(index);
    }
    
    void setNoteNumber(Int noteNumber)  {
        this->_noteNumber = noteNumber;
        this->p_01->setNoteNumber(noteNumber);
        this->p_02->setNoteNumber(noteNumber);
        this->p_03->setNoteNumber(noteNumber);
        this->p_04->setNoteNumber(noteNumber);
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void getState(PatcherStateInterface& ) {}
    
    void setState() {
        this->p_01 = new RNBOSubpatcher_145();
        this->p_01->setEngineAndPatcher(this->getEngine(), this);
        this->p_01->initialize();
        this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
        this->p_02 = new RNBOSubpatcher_146();
        this->p_02->setEngineAndPatcher(this->getEngine(), this);
        this->p_02->initialize();
        this->p_02->setParameterOffset(this->getParameterOffset(this->p_02));
        this->p_03 = new RNBOSubpatcher_147();
        this->p_03->setEngineAndPatcher(this->getEngine(), this);
        this->p_03->initialize();
        this->p_03->setParameterOffset(this->getParameterOffset(this->p_03));
        this->p_04 = new RNBOSubpatcher_148();
        this->p_04->setEngineAndPatcher(this->getEngine(), this);
        this->p_04->initialize();
        this->p_04->setParameterOffset(this->getParameterOffset(this->p_04));
    }
    
    void getPreset(PatcherStateInterface& preset) {
        this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "freq-conversion[2]"));
        this->p_02->getPreset(getSubState(getSubState(preset, "__sps"), "freq-conversion[1]"));
        this->p_03->getPreset(getSubState(getSubState(preset, "__sps"), "freq-conversion"));
    
        this->p_04->getPreset(
            getSubState(getSubState(preset, "__sps"), "old-magic-number-tuning-system")
        );
    }
    
    void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
        this->updateTime(time);
    
        switch (index) {
        case 0:
            {
            this->param_01_value_set(v);
            break;
            }
        case 1:
            {
            this->param_02_value_set(v);
            break;
            }
        case 2:
            {
            this->param_03_value_set(v);
            break;
            }
        case 3:
            {
            this->param_04_value_set(v);
            break;
            }
        case 4:
            {
            this->param_05_value_set(v);
            break;
            }
        case 5:
            {
            this->param_06_value_set(v);
            break;
            }
        default:
            {
            index -= 6;
    
            if (index < this->p_01->getNumParameters())
                this->p_01->setParameterValue(index, v, time);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                this->p_02->setParameterValue(index, v, time);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                this->p_03->setParameterValue(index, v, time);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                this->p_04->setParameterValue(index, v, time);
    
            break;
            }
        }
    }
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        case 0:
            {
            return this->param_01_value;
            }
        case 1:
            {
            return this->param_02_value;
            }
        case 2:
            {
            return this->param_03_value;
            }
        case 3:
            {
            return this->param_04_value;
            }
        case 4:
            {
            return this->param_05_value;
            }
        case 5:
            {
            return this->param_06_value;
            }
        default:
            {
            index -= 6;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterValue(index);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterValue(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterValue(index);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->getParameterValue(index);
    
            return 0;
            }
        }
    }
    
    ParameterValue getPolyParameterValue(PatcherInterface** voices, ParameterIndex index)  {
        switch (index) {
        default:
            {
            return voices[0]->getParameterValue(index);
            }
        }
    }
    
    void setPolyParameterValue(
        PatcherInterface** voices,
        ParameterIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        switch (index) {
        default:
            {
            for (Index i = 0; i < 16; i++)
                voices[i]->setParameterValue(index, value, time);
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 6 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters() + this->p_04->getNumParameters();
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "attack";
            }
        case 1:
            {
            return "decay";
            }
        case 2:
            {
            return "sustain";
            }
        case 3:
            {
            return "release";
            }
        case 4:
            {
            return "secondPartialDecay";
            }
        case 5:
            {
            return "thirdPartialDecay";
            }
        default:
            {
            index -= 6;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterName(index);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterName(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterName(index);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->getParameterName(index);
    
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        case 0:
            {
            return "poly/attack";
            }
        case 1:
            {
            return "poly/decay";
            }
        case 2:
            {
            return "poly/sustain";
            }
        case 3:
            {
            return "poly/release";
            }
        case 4:
            {
            return "poly/secondPartialDecay";
            }
        case 5:
            {
            return "poly/thirdPartialDecay";
            }
        default:
            {
            index -= 6;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->getParameterId(index);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->getParameterId(index);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->getParameterId(index);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->getParameterId(index);
    
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
        {
            switch (index) {
            case 0:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 1;
                info->min = 1;
                info->max = 2000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 1:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 1;
                info->min = 0;
                info->max = 2000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 2:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 0;
                info->min = 0;
                info->max = 1;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 3:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 1;
                info->min = 0;
                info->max = 2000;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 4:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 3;
                info->min = 1;
                info->max = 10;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            case 5:
                {
                info->type = ParameterTypeNumber;
                info->initialValue = 6;
                info->min = 1;
                info->max = 10;
                info->exponent = 1;
                info->steps = 0;
                info->debug = false;
                info->saveable = true;
                info->transmittable = true;
                info->initialized = true;
                info->visible = false;
                info->displayName = "";
                info->unit = "";
                info->ioType = IOTypeUndefined;
                info->signalIndex = INVALID_INDEX;
                break;
                }
            default:
                {
                index -= 6;
    
                if (index < this->p_01->getNumParameters())
                    this->p_01->getParameterInfo(index, info);
    
                index -= this->p_01->getNumParameters();
    
                if (index < this->p_02->getNumParameters())
                    this->p_02->getParameterInfo(index, info);
    
                index -= this->p_02->getNumParameters();
    
                if (index < this->p_03->getNumParameters())
                    this->p_03->getParameterInfo(index, info);
    
                index -= this->p_03->getNumParameters();
    
                if (index < this->p_04->getNumParameters())
                    this->p_04->getParameterInfo(index, info);
    
                break;
                }
            }
        }
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        if (this->_voiceIndex == 1)
            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void sendPolyParameter(ParameterIndex index, Index voiceIndex, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset + voiceIndex - 1, ignoreValue);
    }
    
    ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
        if (subpatcher == this->p_01)
            return 6;
    
        if (subpatcher == this->p_02)
            return 6 + this->p_01->getNumParameters();
    
        if (subpatcher == this->p_03)
            return 6 + this->p_01->getNumParameters() + this->p_02->getNumParameters();
    
        if (subpatcher == this->p_04)
            return 6 + this->p_01->getNumParameters() + this->p_02->getNumParameters() + this->p_03->getNumParameters();
    
        return 0;
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 2:
            {
            {
                value = (value < 0 ? 0 : (value > 1 ? 1 : value));
                ParameterValue normalizedValue = (value - 0) / (1 - 0);
                return normalizedValue;
            }
            }
        case 1:
        case 3:
            {
            {
                value = (value < 0 ? 0 : (value > 2000 ? 2000 : value));
                ParameterValue normalizedValue = (value - 0) / (2000 - 0);
                return normalizedValue;
            }
            }
        case 4:
        case 5:
            {
            {
                value = (value < 1 ? 1 : (value > 10 ? 10 : value));
                ParameterValue normalizedValue = (value - 1) / (10 - 1);
                return normalizedValue;
            }
            }
        case 0:
            {
            {
                value = (value < 1 ? 1 : (value > 2000 ? 2000 : value));
                ParameterValue normalizedValue = (value - 1) / (2000 - 1);
                return normalizedValue;
            }
            }
        default:
            {
            index -= 6;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertToNormalizedParameterValue(index, value);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->convertToNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        case 2:
            {
            {
                {
                    return 0 + value * (1 - 0);
                }
            }
            }
        case 1:
        case 3:
            {
            {
                {
                    return 0 + value * (2000 - 0);
                }
            }
            }
        case 4:
        case 5:
            {
            {
                {
                    return 1 + value * (10 - 1);
                }
            }
            }
        case 0:
            {
            {
                {
                    return 1 + value * (2000 - 1);
                }
            }
            }
        default:
            {
            index -= 6;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->convertFromNormalizedParameterValue(index, value);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->convertFromNormalizedParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        case 0:
            {
            return this->param_01_value_constrain(value);
            }
        case 1:
            {
            return this->param_02_value_constrain(value);
            }
        case 2:
            {
            return this->param_03_value_constrain(value);
            }
        case 3:
            {
            return this->param_04_value_constrain(value);
            }
        case 4:
            {
            return this->param_05_value_constrain(value);
            }
        case 5:
            {
            return this->param_06_value_constrain(value);
            }
        default:
            {
            index -= 6;
    
            if (index < this->p_01->getNumParameters())
                return this->p_01->constrainParameterValue(index, value);
    
            index -= this->p_01->getNumParameters();
    
            if (index < this->p_02->getNumParameters())
                return this->p_02->constrainParameterValue(index, value);
    
            index -= this->p_02->getNumParameters();
    
            if (index < this->p_03->getNumParameters())
                return this->p_03->constrainParameterValue(index, value);
    
            index -= this->p_03->getNumParameters();
    
            if (index < this->p_04->getNumParameters())
                return this->p_04->constrainParameterValue(index, value);
    
            return value;
            }
        }
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time);
    
        switch (index) {
        case -1468824490:
            {
            this->adsr_01_mute_bang();
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("valin"):
            {
            if (TAG("poly/number_obj-68") == objectId)
                this->numberobj_03_valin_set(payload);
    
            if (TAG("poly/number_obj-69") == objectId)
                this->numberobj_04_valin_set(payload);
    
            if (TAG("poly/number_obj-70") == objectId)
                this->numberobj_05_valin_set(payload);
    
            if (TAG("poly/number_obj-71") == objectId)
                this->numberobj_06_valin_set(payload);
    
            if (TAG("poly/number_obj-51") == objectId)
                this->numberobj_07_valin_set(payload);
    
            if (TAG("poly/number_obj-52") == objectId)
                this->numberobj_08_valin_set(payload);
    
            if (TAG("poly/number_obj-76") == objectId)
                this->numberobj_09_valin_set(payload);
    
            if (TAG("poly/number_obj-77") == objectId)
                this->numberobj_10_valin_set(payload);
    
            break;
            }
        case TAG("format"):
            {
            if (TAG("poly/number_obj-68") == objectId)
                this->numberobj_03_format_set(payload);
    
            if (TAG("poly/number_obj-69") == objectId)
                this->numberobj_04_format_set(payload);
    
            if (TAG("poly/number_obj-70") == objectId)
                this->numberobj_05_format_set(payload);
    
            if (TAG("poly/number_obj-71") == objectId)
                this->numberobj_06_format_set(payload);
    
            if (TAG("poly/number_obj-51") == objectId)
                this->numberobj_07_format_set(payload);
    
            if (TAG("poly/number_obj-52") == objectId)
                this->numberobj_08_format_set(payload);
    
            if (TAG("poly/number_obj-76") == objectId)
                this->numberobj_09_format_set(payload);
    
            if (TAG("poly/number_obj-77") == objectId)
                this->numberobj_10_format_set(payload);
    
            break;
            }
        }
    
        this->p_01->processNumMessage(tag, objectId, time, payload);
        this->p_02->processNumMessage(tag, objectId, time, payload);
        this->p_03->processNumMessage(tag, objectId, time, payload);
        this->p_04->processNumMessage(tag, objectId, time, payload);
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        RNBO_UNUSED(objectId);
        this->updateTime(time);
        this->p_01->processListMessage(tag, objectId, time, payload);
        this->p_02->processListMessage(tag, objectId, time, payload);
        this->p_03->processListMessage(tag, objectId, time, payload);
        this->p_04->processListMessage(tag, objectId, time, payload);
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        this->updateTime(time);
    
        switch (tag) {
        case TAG("bangin"):
            {
            if (TAG("poly/button_obj-14") == objectId)
                this->button_01_bangin_bang();
    
            break;
            }
        }
    
        this->p_01->processBangMessage(tag, objectId, time);
        this->p_02->processBangMessage(tag, objectId, time);
        this->p_03->processBangMessage(tag, objectId, time);
        this->p_04->processBangMessage(tag, objectId, time);
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("valout"):
            {
            return "valout";
            }
        case TAG("poly/number_obj-68"):
            {
            return "poly/number_obj-68";
            }
        case TAG("setup"):
            {
            return "setup";
            }
        case TAG("poly/number_obj-69"):
            {
            return "poly/number_obj-69";
            }
        case TAG("poly/number_obj-70"):
            {
            return "poly/number_obj-70";
            }
        case TAG("poly/number_obj-71"):
            {
            return "poly/number_obj-71";
            }
        case TAG("bangout"):
            {
            return "bangout";
            }
        case TAG("poly/button_obj-14"):
            {
            return "poly/button_obj-14";
            }
        case TAG("poly/number_obj-51"):
            {
            return "poly/number_obj-51";
            }
        case TAG("poly/number_obj-52"):
            {
            return "poly/number_obj-52";
            }
        case TAG("poly/number_obj-76"):
            {
            return "poly/number_obj-76";
            }
        case TAG("poly/number_obj-77"):
            {
            return "poly/number_obj-77";
            }
        case TAG("valin"):
            {
            return "valin";
            }
        case TAG("format"):
            {
            return "format";
            }
        case TAG("bangin"):
            {
            return "bangin";
            }
        }
    
        auto subpatchResult_0 = this->p_01->resolveTag(tag);
    
        if (subpatchResult_0)
            return subpatchResult_0;
    
        auto subpatchResult_1 = this->p_02->resolveTag(tag);
    
        if (subpatchResult_1)
            return subpatchResult_1;
    
        auto subpatchResult_2 = this->p_03->resolveTag(tag);
    
        if (subpatchResult_2)
            return subpatchResult_2;
    
        auto subpatchResult_3 = this->p_04->resolveTag(tag);
    
        if (subpatchResult_3)
            return subpatchResult_3;
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->p_01->processDataViewUpdate(index, time);
        this->p_02->processDataViewUpdate(index, time);
        this->p_03->processDataViewUpdate(index, time);
        this->p_04->processDataViewUpdate(index, time);
    }
    
    void initialize() {
        this->assign_defaults();
        this->setState();
    }
    
    protected:
    
    void numberobj_03_valin_set(number v) {
        this->numberobj_03_value_set(v);
    }
    
    void numberobj_03_format_set(number v) {
        this->numberobj_03_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void param_01_value_set(number v) {
        v = this->param_01_value_constrain(v);
        this->param_01_value = v;
        this->sendParameter(0, false);
    
        if (this->param_01_value != this->param_01_lastValue) {
            this->getEngine()->presetTouched();
            this->param_01_lastValue = this->param_01_value;
        }
    
        this->adsr_01_attack_set(v);
    }
    
    void param_02_value_set(number v) {
        v = this->param_02_value_constrain(v);
        this->param_02_value = v;
        this->sendParameter(1, false);
    
        if (this->param_02_value != this->param_02_lastValue) {
            this->getEngine()->presetTouched();
            this->param_02_lastValue = this->param_02_value;
        }
    
        this->adsr_01_decay_set(v);
    }
    
    void numberobj_04_valin_set(number v) {
        this->numberobj_04_value_set(v);
    }
    
    void numberobj_04_format_set(number v) {
        this->numberobj_04_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_05_valin_set(number v) {
        this->numberobj_05_value_set(v);
    }
    
    void numberobj_05_format_set(number v) {
        this->numberobj_05_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void param_03_value_set(number v) {
        v = this->param_03_value_constrain(v);
        this->param_03_value = v;
        this->sendParameter(2, false);
    
        if (this->param_03_value != this->param_03_lastValue) {
            this->getEngine()->presetTouched();
            this->param_03_lastValue = this->param_03_value;
        }
    
        {
            list converted = {v};
            this->scale_04_input_set(converted);
        }
    
        this->adsr_01_sustain_set(v);
    }
    
    void numberobj_06_valin_set(number v) {
        this->numberobj_06_value_set(v);
    }
    
    void numberobj_06_format_set(number v) {
        this->numberobj_06_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void param_04_value_set(number v) {
        v = this->param_04_value_constrain(v);
        this->param_04_value = v;
        this->sendParameter(3, false);
    
        if (this->param_04_value != this->param_04_lastValue) {
            this->getEngine()->presetTouched();
            this->param_04_lastValue = this->param_04_value;
        }
    
        this->adsr_01_release_set(v);
    }
    
    void button_01_bangin_bang() {
        this->button_01_bangval_bang();
    }
    
    void numberobj_07_valin_set(number v) {
        this->numberobj_07_value_set(v);
    }
    
    void numberobj_07_format_set(number v) {
        this->numberobj_07_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_08_valin_set(number v) {
        this->numberobj_08_value_set(v);
    }
    
    void numberobj_08_format_set(number v) {
        this->numberobj_08_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void numberobj_09_valin_set(number v) {
        this->numberobj_09_value_set(v);
    }
    
    void numberobj_09_format_set(number v) {
        this->numberobj_09_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void param_05_value_set(number v) {
        v = this->param_05_value_constrain(v);
        this->param_05_value = v;
        this->sendParameter(4, false);
    
        if (this->param_05_value != this->param_05_lastValue) {
            this->getEngine()->presetTouched();
            this->param_05_lastValue = this->param_05_value;
        }
    
        this->expr_19_in2_set(v);
    }
    
    void numberobj_10_valin_set(number v) {
        this->numberobj_10_value_set(v);
    }
    
    void numberobj_10_format_set(number v) {
        this->numberobj_10_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
    }
    
    void param_06_value_set(number v) {
        v = this->param_06_value_constrain(v);
        this->param_06_value = v;
        this->sendParameter(5, false);
    
        if (this->param_06_value != this->param_06_lastValue) {
            this->getEngine()->presetTouched();
            this->param_06_lastValue = this->param_06_value;
        }
    
        this->expr_21_in2_set(v);
    }
    
    void adsr_01_mute_bang() {}
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    Index getNumInputChannels() const {
        return 0;
    }
    
    Index getNumOutputChannels() const {
        return 2;
    }
    
    void initializeObjects() {
        this->noise_tilde_01_init();
        this->numberobj_03_init();
        this->numberobj_04_init();
        this->numberobj_05_init();
        this->numberobj_06_init();
        this->gen_01_y2_init();
        this->gen_01_history_1_init();
        this->gen_01_history_2_init();
        this->gen_01_history_3_init();
        this->gen_01_y1_init();
        this->gen_02_y2_init();
        this->gen_02_history_1_init();
        this->gen_02_history_2_init();
        this->gen_02_history_3_init();
        this->gen_02_y1_init();
        this->gen_03_y2_init();
        this->gen_03_history_1_init();
        this->gen_03_history_2_init();
        this->gen_03_history_3_init();
        this->gen_03_y1_init();
        this->numberobj_07_init();
        this->numberobj_08_init();
        this->numberobj_09_init();
        this->numberobj_10_init();
        this->p_01->initializeObjects();
        this->p_02->initializeObjects();
        this->p_03->initializeObjects();
        this->p_04->initializeObjects();
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime());
        this->p_01->startup();
        this->p_02->startup();
        this->p_03->startup();
        this->p_04->startup();
    }
    
    void allocateDataRefs() {
        this->p_01->allocateDataRefs();
        this->p_02->allocateDataRefs();
        this->p_03->allocateDataRefs();
        this->p_04->allocateDataRefs();
    }
    
    void numberobj_03_output_set(number ) {}
    
    void numberobj_03_value_set(number v) {
        this->numberobj_03_value_setter(v);
        v = this->numberobj_03_value;
        number localvalue = v;
    
        if (this->numberobj_03_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("poly/number_obj-68"), localvalue, this->_currentTime);
        this->numberobj_03_output_set(localvalue);
    }
    
    number param_01_value_constrain(number v) const {
        v = (v > 2000 ? 2000 : (v < 1 ? 1 : v));
        return v;
    }
    
    void adsr_01_attack_set(number v) {
        this->adsr_01_attack = v;
    }
    
    number param_02_value_constrain(number v) const {
        v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
        return v;
    }
    
    void adsr_01_decay_set(number v) {
        this->adsr_01_decay = v;
    }
    
    void numberobj_04_output_set(number ) {}
    
    void numberobj_04_value_set(number v) {
        this->numberobj_04_value_setter(v);
        v = this->numberobj_04_value;
        number localvalue = v;
    
        if (this->numberobj_04_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("poly/number_obj-69"), localvalue, this->_currentTime);
        this->numberobj_04_output_set(localvalue);
    }
    
    void numberobj_05_output_set(number ) {}
    
    void numberobj_05_value_set(number v) {
        this->numberobj_05_value_setter(v);
        v = this->numberobj_05_value;
        number localvalue = v;
    
        if (this->numberobj_05_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("poly/number_obj-70"), localvalue, this->_currentTime);
        this->numberobj_05_output_set(localvalue);
    }
    
    number param_03_value_constrain(number v) const {
        v = (v > 1 ? 1 : (v < 0 ? 0 : v));
        return v;
    }
    
    void dspexpr_01_in2_set(number v) {
        this->dspexpr_01_in2 = v;
    }
    
    void scale_04_out_set(const list& v) {
        this->scale_04_out = jsCreateListCopy(v);
    
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->dspexpr_01_in2_set(converted);
        }
    }
    
    void scale_04_input_set(const list& v) {
        this->scale_04_input = jsCreateListCopy(v);
        list tmp = {};
    
        for (Index i = 0; i < v->length; i++) {
            tmp->push(this->scale(
                v[(Index)i],
                this->scale_04_inlow,
                this->scale_04_inhigh,
                this->scale_04_outlow,
                this->scale_04_outhigh,
                this->scale_04_power
            ));
        }
    
        this->scale_04_out_set(tmp);
    }
    
    void adsr_01_sustain_set(number v) {
        this->adsr_01_sustain = v;
    }
    
    void numberobj_06_output_set(number ) {}
    
    void numberobj_06_value_set(number v) {
        this->numberobj_06_value_setter(v);
        v = this->numberobj_06_value;
        number localvalue = v;
    
        if (this->numberobj_06_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("poly/number_obj-71"), localvalue, this->_currentTime);
        this->numberobj_06_output_set(localvalue);
    }
    
    number param_04_value_constrain(number v) const {
        v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
        return v;
    }
    
    void adsr_01_release_set(number v) {
        this->adsr_01_release = v;
    }
    
    void gen_01_id_set(number v) {
        this->gen_01_id = v;
    }
    
    void gen_01_voices_set(number v) {
        this->gen_01_voices = v;
    }
    
    void gen_01_reset_bang() {
        this->gen_01_id_set(0);
        this->gen_01_voices_set(1);
        this->gen_01_y2_init();
        this->gen_01_history_1_init();
        this->gen_01_history_2_init();
        this->gen_01_history_3_init();
        this->gen_01_y1_init();
    }
    
    void gen_03_voices_set(number v) {
        this->gen_03_voices = v;
    }
    
    void gen_03_id_set(number v) {
        this->gen_03_id = v;
    }
    
    void gen_03_reset_bang() {
        this->gen_03_voices_set(1);
        this->gen_03_id_set(0);
        this->gen_03_y2_init();
        this->gen_03_history_1_init();
        this->gen_03_history_2_init();
        this->gen_03_history_3_init();
        this->gen_03_y1_init();
    }
    
    void gen_02_id_set(number v) {
        this->gen_02_id = v;
    }
    
    void gen_02_voices_set(number v) {
        this->gen_02_voices = v;
    }
    
    void gen_02_reset_bang() {
        this->gen_02_id_set(0);
        this->gen_02_voices_set(1);
        this->gen_02_y2_init();
        this->gen_02_history_1_init();
        this->gen_02_history_2_init();
        this->gen_02_history_3_init();
        this->gen_02_y1_init();
    }
    
    void button_01_output_bang() {
        this->gen_01_reset_bang();
        this->gen_03_reset_bang();
        this->gen_02_reset_bang();
    }
    
    void button_01_bangval_bang() {
        this->getEngine()->sendBangMessage(TAG("bangout"), TAG("poly/button_obj-14"), this->_currentTime);;
        this->button_01_output_bang();
    }
    
    void gen_03_in4_set(number v) {
        this->gen_03_in4 = v;
    }
    
    void gen_02_in4_set(number v) {
        this->gen_02_in4 = v;
    }
    
    void gen_01_in4_set(number v) {
        this->gen_01_in4 = v;
    }
    
    void numberobj_07_output_set(number v) {
        this->gen_03_in4_set(v);
        this->gen_02_in4_set(v);
        this->gen_01_in4_set(v);
    }
    
    void numberobj_07_value_set(number v) {
        this->numberobj_07_value_setter(v);
        v = this->numberobj_07_value;
        number localvalue = v;
    
        if (this->numberobj_07_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("poly/number_obj-51"), localvalue, this->_currentTime);
        this->numberobj_07_output_set(localvalue);
    }
    
    void gen_03_in5_set(number v) {
        this->gen_03_in5 = v;
    }
    
    void expr_21_out1_set(number v) {
        this->expr_21_out1 = v;
        this->gen_03_in5_set(this->expr_21_out1);
    }
    
    void expr_21_in1_set(number in1) {
        this->expr_21_in1 = in1;
        this->expr_21_out1_set(this->expr_21_in1 * this->expr_21_in2);//#map:*_obj-41:1
    }
    
    void gen_02_in5_set(number v) {
        this->gen_02_in5 = v;
    }
    
    void expr_19_out1_set(number v) {
        this->expr_19_out1 = v;
        this->gen_02_in5_set(this->expr_19_out1);
    }
    
    void expr_19_in1_set(number in1) {
        this->expr_19_in1 = in1;
        this->expr_19_out1_set(this->expr_19_in1 * this->expr_19_in2);//#map:*_obj-11:1
    }
    
    void gen_01_in5_set(number v) {
        this->gen_01_in5 = v;
    }
    
    void numberobj_08_output_set(number v) {
        this->expr_21_in1_set(v);
        this->expr_19_in1_set(v);
        this->gen_01_in5_set(v);
    }
    
    void numberobj_08_value_set(number v) {
        this->numberobj_08_value_setter(v);
        v = this->numberobj_08_value;
        number localvalue = v;
    
        if (this->numberobj_08_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("poly/number_obj-52"), localvalue, this->_currentTime);
        this->numberobj_08_output_set(localvalue);
    }
    
    void numberobj_09_output_set(number ) {}
    
    void numberobj_09_value_set(number v) {
        this->numberobj_09_value_setter(v);
        v = this->numberobj_09_value;
        number localvalue = v;
    
        if (this->numberobj_09_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("poly/number_obj-76"), localvalue, this->_currentTime);
        this->numberobj_09_output_set(localvalue);
    }
    
    number param_05_value_constrain(number v) const {
        v = (v > 10 ? 10 : (v < 1 ? 1 : v));
        return v;
    }
    
    void expr_19_in2_set(number v) {
        this->expr_19_in2 = v;
    }
    
    void numberobj_10_output_set(number ) {}
    
    void numberobj_10_value_set(number v) {
        this->numberobj_10_value_setter(v);
        v = this->numberobj_10_value;
        number localvalue = v;
    
        if (this->numberobj_10_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->getEngine()->sendNumMessage(TAG("valout"), TAG("poly/number_obj-77"), localvalue, this->_currentTime);
        this->numberobj_10_output_set(localvalue);
    }
    
    number param_06_value_constrain(number v) const {
        v = (v > 10 ? 10 : (v < 1 ? 1 : v));
        return v;
    }
    
    void expr_21_in2_set(number v) {
        this->expr_21_in2 = v;
    }
    
    void notein_01_outchannel_set(number ) {}
    
    void notein_01_releasevelocity_set(number ) {}
    
    void split_02_out1_set(number ) {}
    
    void scale_06_out_set(const list& v) {
        this->scale_06_out = jsCreateListCopy(v);
    
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->numberobj_08_value_set(converted);
        }
    }
    
    void scale_06_input_set(const list& v) {
        this->scale_06_input = jsCreateListCopy(v);
        list tmp = {};
    
        for (Index i = 0; i < v->length; i++) {
            tmp->push(this->scale(
                v[(Index)i],
                this->scale_06_inlow,
                this->scale_06_inhigh,
                this->scale_06_outlow,
                this->scale_06_outhigh,
                this->scale_06_power
            ));
        }
    
        this->scale_06_out_set(tmp);
    }
    
    void expr_18_out1_set(number v) {
        this->expr_18_out1 = v;
        this->numberobj_07_value_set(this->expr_18_out1);
    }
    
    void expr_18_in1_set(number in1) {
        this->expr_18_in1 = in1;
        this->expr_18_out1_set(fixnan(rnbo_pow(this->expr_18_in1, this->expr_18_in2)));//#map:pow_obj-3:1
    }
    
    void expr_18_in2_set(number v) {
        this->expr_18_in2 = v;
    }
    
    void scale_05_out_set(const list& v) {
        this->scale_05_out = jsCreateListCopy(v);
    
        {
            if (v->length > 1)
                this->expr_18_in2_set(v[1]);
    
            number converted = (v->length > 0 ? v[0] : 0);
            this->expr_18_in1_set(converted);
        }
    }
    
    void scale_05_input_set(const list& v) {
        this->scale_05_input = jsCreateListCopy(v);
        list tmp = {};
    
        for (Index i = 0; i < v->length; i++) {
            tmp->push(this->scale(
                v[(Index)i],
                this->scale_05_inlow,
                this->scale_05_inhigh,
                this->scale_05_outlow,
                this->scale_05_outhigh,
                this->scale_05_power
            ));
        }
    
        this->scale_05_out_set(tmp);
    }
    
    void expr_20_out1_set(number v) {
        this->expr_20_out1 = v;
    
        {
            list converted = {this->expr_20_out1};
            this->scale_06_input_set(converted);
        }
    
        {
            list converted = {this->expr_20_out1};
            this->scale_05_input_set(converted);
        }
    }
    
    void expr_20_in1_set(number in1) {
        this->expr_20_in1 = in1;
    
        this->expr_20_out1_set(
            (this->expr_20_in1 > this->expr_20_in3 ? this->expr_20_in3 : (this->expr_20_in1 < this->expr_20_in2 ? this->expr_20_in2 : this->expr_20_in1))
        );//#map:clip_obj-25:1
    }
    
    void split_02_out2_set(number v) {
        this->expr_20_in1_set(v);
    }
    
    void split_02_input_set(number v) {
        this->split_02_input = v;
    
        if (v >= this->split_02_min && v <= this->split_02_max)
            this->split_02_out1_set(v);
        else
            this->split_02_out2_set(v);
    }
    
    void adsr_01_trigger_number_set(number v) {
        this->adsr_01_trigger_number = v;
    
        if (v != 0)
            this->adsr_01_triggerBuf[(Index)this->sampleOffsetIntoNextAudioBuffer] = 1;
    
        for (number i = this->sampleOffsetIntoNextAudioBuffer; i < this->vectorsize(); i++) {
            this->adsr_01_triggerValueBuf[(Index)i] = v;
        }
    }
    
    void notein_01_velocity_set(number v) {
        this->split_02_input_set(v);
        this->adsr_01_trigger_number_set(v);
    }
    
    void gen_03_in3_set(number v) {
        this->gen_03_in3 = v;
    }
    
    void p_03_out1_number_set(number v) {
        this->gen_03_in3_set(v);
    }
    
    void p_03_in1_number_set(number v) {
        this->p_03->updateTime(this->_currentTime);
        this->p_03->eventinlet_03_out1_number_set(v);
    }
    
    void expr_17_out1_set(number v) {
        this->expr_17_out1 = v;
        this->p_03_in1_number_set(this->expr_17_out1);
    }
    
    void expr_17_in1_set(number in1) {
        this->expr_17_in1 = in1;
        this->expr_17_out1_set(this->expr_17_in1 + this->expr_17_in2);//#map:+_obj-38:1
    }
    
    void gen_02_in3_set(number v) {
        this->gen_02_in3 = v;
    }
    
    void p_02_out1_number_set(number v) {
        this->gen_02_in3_set(v);
    }
    
    void p_02_in1_number_set(number v) {
        this->p_02->updateTime(this->_currentTime);
        this->p_02->eventinlet_02_out1_number_set(v);
    }
    
    void expr_16_out1_set(number v) {
        this->expr_16_out1 = v;
        this->p_02_in1_number_set(this->expr_16_out1);
    }
    
    void expr_16_in1_set(number in1) {
        this->expr_16_in1 = in1;
        this->expr_16_out1_set(this->expr_16_in1 + this->expr_16_in2);//#map:+_obj-33:1
    }
    
    void gen_01_in3_set(number v) {
        this->gen_01_in3 = v;
    }
    
    void p_01_out1_number_set(number v) {
        this->gen_01_in3_set(v);
    }
    
    void p_01_in1_number_set(number v) {
        this->p_01->updateTime(this->_currentTime);
        this->p_01->eventinlet_01_out1_number_set(v);
    }
    
    void expr_15_out1_set(number v) {
        this->expr_15_out1 = v;
        this->p_01_in1_number_set(this->expr_15_out1);
    }
    
    void expr_15_in1_set(number in1) {
        this->expr_15_in1 = in1;
        this->expr_15_out1_set(this->expr_15_in1 + this->expr_15_in2);//#map:+_obj-31:1
    }
    
    void split_01_out1_set(number v) {
        this->expr_17_in1_set(v);
        this->expr_16_in1_set(v);
        this->expr_15_in1_set(v);
    }
    
    void split_01_out2_set(number ) {}
    
    void split_01_input_set(number v) {
        this->split_01_input = v;
    
        if (v >= this->split_01_min && v <= this->split_01_max)
            this->split_01_out1_set(v);
        else
            this->split_01_out2_set(v);
    }
    
    void notein_01_notenumber_set(number v) {
        this->split_01_input_set(v);
    }
    
    void notein_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(length);
        RNBO_UNUSED(port);
    
        if (channel == this->notein_01_channel || this->notein_01_channel == 0) {
            if (status == 144 || status == 128) {
                this->notein_01_outchannel_set(channel);
    
                if (status == 128) {
                    this->notein_01_releasevelocity_set(data[2]);
                    this->notein_01_velocity_set(0);
                } else {
                    this->notein_01_releasevelocity_set(0);
                    this->notein_01_velocity_set(data[2]);
                }
    
                this->notein_01_notenumber_set(data[1]);
            }
        }
    }
    
    void midiouthelper_midiout_set(number ) {}
    
    void noise_tilde_01_perform(SampleValue * out1, Index n) {
        auto __noise_tilde_01_state = this->noise_tilde_01_state;
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = xoshiro_next(__noise_tilde_01_state);
        }
    }
    
    void adsr_01_perform(
        number attack,
        number decay,
        number sustain,
        number release,
        const SampleValue * trigger_signal,
        SampleValue * out,
        Index n
    ) {
        RNBO_UNUSED(trigger_signal);
        auto __adsr_01_trigger_number = this->adsr_01_trigger_number;
        auto __adsr_01_time = this->adsr_01_time;
        auto __adsr_01_amplitude = this->adsr_01_amplitude;
        auto __adsr_01_outval = this->adsr_01_outval;
        auto __adsr_01_startingpoint = this->adsr_01_startingpoint;
        auto __adsr_01_phase = this->adsr_01_phase;
        auto __adsr_01_legato = this->adsr_01_legato;
        auto __adsr_01_lastTriggerVal = this->adsr_01_lastTriggerVal;
        auto __adsr_01_maxsustain = this->adsr_01_maxsustain;
        auto __adsr_01_mspersamp = this->adsr_01_mspersamp;
        bool bangMute = false;
    
        for (Index i = 0; i < n; i++) {
            number clampedattack = (attack > __adsr_01_mspersamp ? attack : __adsr_01_mspersamp);
            number clampeddecay = (decay > __adsr_01_mspersamp ? decay : __adsr_01_mspersamp);
            number clampedsustain = (__adsr_01_maxsustain > __adsr_01_mspersamp ? __adsr_01_maxsustain : __adsr_01_mspersamp);
            number clampedrelease = (release > __adsr_01_mspersamp ? release : __adsr_01_mspersamp);
            number currentTriggerVal = this->adsr_01_triggerValueBuf[(Index)i];
    
            if ((__adsr_01_lastTriggerVal == 0.0 && currentTriggerVal != 0.0) || this->adsr_01_triggerBuf[(Index)i] == 1) {
                if ((bool)(__adsr_01_legato)) {
                    if (__adsr_01_phase != 0) {
                        __adsr_01_startingpoint = __adsr_01_outval;
                    } else {
                        __adsr_01_startingpoint = 0;
                    }
                } else {
                    __adsr_01_startingpoint = 0;
                }
    
                __adsr_01_amplitude = currentTriggerVal;
                __adsr_01_phase = 1;
                __adsr_01_time = 0.0;
                bangMute = false;
            } else if (__adsr_01_lastTriggerVal != 0.0 && currentTriggerVal == 0.0) {
                if (__adsr_01_phase != 4 && __adsr_01_phase != 0) {
                    __adsr_01_phase = 4;
                    __adsr_01_amplitude = __adsr_01_outval;
                    __adsr_01_time = 0.0;
                }
            }
    
            __adsr_01_time += __adsr_01_mspersamp;
    
            if (__adsr_01_phase == 0) {
                __adsr_01_outval = 0;
            } else if (__adsr_01_phase == 1) {
                if (__adsr_01_time > clampedattack) {
                    __adsr_01_time -= clampedattack;
                    __adsr_01_phase = 2;
                    __adsr_01_outval = __adsr_01_amplitude;
                } else {
                    __adsr_01_outval = (__adsr_01_amplitude - __adsr_01_startingpoint) * __adsr_01_time / clampedattack + __adsr_01_startingpoint;
                }
            } else if (__adsr_01_phase == 2) {
                if (__adsr_01_time > clampeddecay) {
                    __adsr_01_time -= clampeddecay;
                    __adsr_01_phase = 3;
                    __adsr_01_outval = __adsr_01_amplitude * sustain;
                } else {
                    __adsr_01_outval = __adsr_01_amplitude * sustain + (__adsr_01_amplitude - __adsr_01_amplitude * sustain) * (1. - __adsr_01_time / clampeddecay);
                }
            } else if (__adsr_01_phase == 3) {
                if (__adsr_01_time > clampedsustain && __adsr_01_maxsustain > -1) {
                    __adsr_01_time -= clampedsustain;
                    __adsr_01_phase = 4;
                    __adsr_01_amplitude = __adsr_01_outval;
                } else {
                    __adsr_01_outval = __adsr_01_amplitude * sustain;
                }
            } else if (__adsr_01_phase == 4) {
                if (__adsr_01_time > clampedrelease) {
                    __adsr_01_time = 0;
                    __adsr_01_phase = 0;
                    __adsr_01_outval = 0;
                    __adsr_01_amplitude = 0;
                    bangMute = true;
                } else {
                    __adsr_01_outval = __adsr_01_amplitude * (1.0 - __adsr_01_time / clampedrelease);
                }
            }
    
            out[(Index)i] = __adsr_01_outval;
            this->adsr_01_triggerBuf[(Index)i] = 0;
            this->adsr_01_triggerValueBuf[(Index)i] = __adsr_01_trigger_number;
            __adsr_01_lastTriggerVal = currentTriggerVal;
        }
    
        if ((bool)(bangMute)) {
            this->getEngine()->scheduleClockEventWithValue(
                this,
                -1468824490,
                this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                0
            );;
        }
    
        this->adsr_01_lastTriggerVal = __adsr_01_lastTriggerVal;
        this->adsr_01_phase = __adsr_01_phase;
        this->adsr_01_startingpoint = __adsr_01_startingpoint;
        this->adsr_01_outval = __adsr_01_outval;
        this->adsr_01_amplitude = __adsr_01_amplitude;
        this->adsr_01_time = __adsr_01_time;
    }
    
    void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_01_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
        }
    }
    
    void gen_02_perform(
        const Sample * in1,
        number in2,
        number in3,
        number in4,
        number in5,
        number id,
        number voices,
        SampleValue * out1,
        Index n
    ) {
        RNBO_UNUSED(voices);
        RNBO_UNUSED(id);
        RNBO_UNUSED(in2);
        auto __gen_02_y2_value = this->gen_02_y2_value;
        auto __gen_02_y1_value = this->gen_02_y1_value;
        auto __gen_02_history_3_value = this->gen_02_history_3_value;
        auto __gen_02_history_2_value = this->gen_02_history_2_value;
        auto __gen_02_history_1_value = this->gen_02_history_1_value;
        number eq_5_2 = 0 == 0;
        number lt_9_6 = 0 < 1;
        Index i;
    
        for (i = 0; i < n; i++) {
            number slide_4_1 = this->gen_02_slide_0_next(__gen_02_history_1_value, 200, 200);
            number switch_6_3 = ((bool)(eq_5_2) ? in4 : __gen_02_history_1_value);
            number switch_7_4 = ((bool)(eq_5_2) ? in3 : __gen_02_history_2_value);
            number switch_8_5 = ((bool)(eq_5_2) ? in5 : __gen_02_history_3_value);
            number slide_10_8 = this->gen_02_slide_7_next(lt_9_6, 200, 200);
            number mul_11_9 = in1[(Index)i] * slide_10_8;
            number cos_12_10 = rnbo_cos(__gen_02_history_2_value);
            number slide_13_12 = this->gen_02_slide_11_next(__gen_02_history_3_value, 200, 200);
            number mul_14_13 = slide_13_12 * -1;
            number exp_15_14 = rnbo_exp(mul_14_13);
            number mul_16_15 = exp_15_14 * -1;
            number mul_17_16 = slide_13_12 * 0.5;
            number exp_18_17 = rnbo_exp(mul_17_16);
            number mul_19_18 = cos_12_10 * exp_18_17;
            number mul_20_19 = mul_19_18 * 2;
            auto min_21_20 = this->minimum(mul_20_19, 1.9999);
            number mul_22_21 = __gen_02_y1_value * min_21_20;
            auto min_23_22 = this->minimum(mul_16_15 + mul_20_19, 1);
            number rsub_24_23 = 1 - min_23_22;
            number mul_25_24 = mul_11_9 * rsub_24_23;
            number sub_26_25 = min_23_22 - min_21_20;
            number mul_27_26 = __gen_02_y2_value * sub_26_25;
            number add_28_27 = mul_27_26 + mul_22_21 + mul_25_24 + 0;
            number mul_29_28 = slide_4_1 * add_28_27;
            out1[(Index)i] = mul_29_28;
            number y2_next_30_29 = fixdenorm(__gen_02_y1_value);
            number history_1_next_31_30 = fixdenorm(switch_6_3);
            number history_2_next_32_31 = fixdenorm(switch_7_4);
            number history_3_next_33_32 = fixdenorm(switch_8_5);
            number y1_next_34_33 = fixdenorm(add_28_27);
            __gen_02_y2_value = y2_next_30_29;
            __gen_02_y1_value = y1_next_34_33;
            __gen_02_history_3_value = history_3_next_33_32;
            __gen_02_history_2_value = history_2_next_32_31;
            __gen_02_history_1_value = history_1_next_31_30;
        }
    
        this->gen_02_history_1_value = __gen_02_history_1_value;
        this->gen_02_history_2_value = __gen_02_history_2_value;
        this->gen_02_history_3_value = __gen_02_history_3_value;
        this->gen_02_y1_value = __gen_02_y1_value;
        this->gen_02_y2_value = __gen_02_y2_value;
    }
    
    void dspexpr_03_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * 0.9;//#map:_###_obj_###_:1
        }
    }
    
    void gen_03_perform(
        const Sample * in1,
        number in2,
        number in3,
        number in4,
        number in5,
        number voices,
        number id,
        SampleValue * out1,
        Index n
    ) {
        RNBO_UNUSED(id);
        RNBO_UNUSED(voices);
        RNBO_UNUSED(in2);
        auto __gen_03_y2_value = this->gen_03_y2_value;
        auto __gen_03_y1_value = this->gen_03_y1_value;
        auto __gen_03_history_3_value = this->gen_03_history_3_value;
        auto __gen_03_history_2_value = this->gen_03_history_2_value;
        auto __gen_03_history_1_value = this->gen_03_history_1_value;
        number eq_5_2 = 0 == 0;
        number lt_9_6 = 0 < 1;
        Index i;
    
        for (i = 0; i < n; i++) {
            number slide_4_1 = this->gen_03_slide_0_next(__gen_03_history_1_value, 200, 200);
            number switch_6_3 = ((bool)(eq_5_2) ? in4 : __gen_03_history_1_value);
            number switch_7_4 = ((bool)(eq_5_2) ? in3 : __gen_03_history_2_value);
            number switch_8_5 = ((bool)(eq_5_2) ? in5 : __gen_03_history_3_value);
            number slide_10_8 = this->gen_03_slide_7_next(lt_9_6, 200, 200);
            number mul_11_9 = in1[(Index)i] * slide_10_8;
            number cos_12_10 = rnbo_cos(__gen_03_history_2_value);
            number slide_13_12 = this->gen_03_slide_11_next(__gen_03_history_3_value, 200, 200);
            number mul_14_13 = slide_13_12 * -1;
            number exp_15_14 = rnbo_exp(mul_14_13);
            number mul_16_15 = exp_15_14 * -1;
            number mul_17_16 = slide_13_12 * 0.5;
            number exp_18_17 = rnbo_exp(mul_17_16);
            number mul_19_18 = cos_12_10 * exp_18_17;
            number mul_20_19 = mul_19_18 * 2;
            auto min_21_20 = this->minimum(mul_20_19, 1.9999);
            number mul_22_21 = __gen_03_y1_value * min_21_20;
            auto min_23_22 = this->minimum(mul_20_19 + mul_16_15, 1);
            number sub_24_23 = min_23_22 - min_21_20;
            number mul_25_24 = __gen_03_y2_value * sub_24_23;
            number rsub_26_25 = 1 - min_23_22;
            number mul_27_26 = mul_11_9 * rsub_26_25;
            number add_28_27 = mul_27_26 + mul_22_21 + mul_25_24 + 0;
            number mul_29_28 = slide_4_1 * add_28_27;
            out1[(Index)i] = mul_29_28;
            number y2_next_30_29 = fixdenorm(__gen_03_y1_value);
            number history_1_next_31_30 = fixdenorm(switch_6_3);
            number history_2_next_32_31 = fixdenorm(switch_7_4);
            number history_3_next_33_32 = fixdenorm(switch_8_5);
            number y1_next_34_33 = fixdenorm(add_28_27);
            __gen_03_y2_value = y2_next_30_29;
            __gen_03_y1_value = y1_next_34_33;
            __gen_03_history_3_value = history_3_next_33_32;
            __gen_03_history_2_value = history_2_next_32_31;
            __gen_03_history_1_value = history_1_next_31_30;
        }
    
        this->gen_03_history_1_value = __gen_03_history_1_value;
        this->gen_03_history_2_value = __gen_03_history_2_value;
        this->gen_03_history_3_value = __gen_03_history_3_value;
        this->gen_03_y1_value = __gen_03_y1_value;
        this->gen_03_y2_value = __gen_03_y2_value;
    }
    
    void dspexpr_04_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < n; i++) {
            out1[(Index)i] = in1[(Index)i] * 0.8;//#map:_###_obj_###_:1
        }
    }
    
    void gen_01_perform(
        const Sample * in1,
        number in2,
        number in3,
        number in4,
        number in5,
        number id,
        number voices,
        SampleValue * out1,
        Index n
    ) {
        RNBO_UNUSED(voices);
        RNBO_UNUSED(id);
        RNBO_UNUSED(in2);
        auto __gen_01_y2_value = this->gen_01_y2_value;
        auto __gen_01_y1_value = this->gen_01_y1_value;
        auto __gen_01_history_3_value = this->gen_01_history_3_value;
        auto __gen_01_history_2_value = this->gen_01_history_2_value;
        auto __gen_01_history_1_value = this->gen_01_history_1_value;
        number eq_5_2 = 0 == 0;
        number lt_9_6 = 0 < 1;
        Index i;
    
        for (i = 0; i < n; i++) {
            number slide_4_1 = this->gen_01_slide_0_next(__gen_01_history_1_value, 200, 200);
            number switch_6_3 = ((bool)(eq_5_2) ? in4 : __gen_01_history_1_value);
            number switch_7_4 = ((bool)(eq_5_2) ? in3 : __gen_01_history_2_value);
            number switch_8_5 = ((bool)(eq_5_2) ? in5 : __gen_01_history_3_value);
            number slide_10_8 = this->gen_01_slide_7_next(lt_9_6, 200, 200);
            number mul_11_9 = in1[(Index)i] * slide_10_8;
            number cos_12_10 = rnbo_cos(__gen_01_history_2_value);
            number slide_13_12 = this->gen_01_slide_11_next(__gen_01_history_3_value, 200, 200);
            number mul_14_13 = slide_13_12 * -1;
            number exp_15_14 = rnbo_exp(mul_14_13);
            number mul_16_15 = exp_15_14 * -1;
            number mul_17_16 = slide_13_12 * 0.5;
            number exp_18_17 = rnbo_exp(mul_17_16);
            number mul_19_18 = cos_12_10 * exp_18_17;
            number mul_20_19 = mul_19_18 * 2;
            auto min_21_20 = this->minimum(mul_20_19, 1.9999);
            number mul_22_21 = __gen_01_y1_value * min_21_20;
            auto min_23_22 = this->minimum(mul_20_19 + mul_16_15, 1);
            number sub_24_23 = min_23_22 - min_21_20;
            number mul_25_24 = __gen_01_y2_value * sub_24_23;
            number rsub_26_25 = 1 - min_23_22;
            number mul_27_26 = mul_11_9 * rsub_26_25;
            number add_28_27 = mul_27_26 + mul_22_21 + mul_25_24 + 0;
            number mul_29_28 = slide_4_1 * add_28_27;
            out1[(Index)i] = mul_29_28;
            number y2_next_30_29 = fixdenorm(__gen_01_y1_value);
            number history_1_next_31_30 = fixdenorm(switch_6_3);
            number history_2_next_32_31 = fixdenorm(switch_7_4);
            number history_3_next_33_32 = fixdenorm(switch_8_5);
            number y1_next_34_33 = fixdenorm(add_28_27);
            __gen_01_y2_value = y2_next_30_29;
            __gen_01_y1_value = y1_next_34_33;
            __gen_01_history_3_value = history_3_next_33_32;
            __gen_01_history_2_value = history_2_next_32_31;
            __gen_01_history_1_value = history_1_next_31_30;
        }
    
        this->gen_01_history_1_value = __gen_01_history_1_value;
        this->gen_01_history_2_value = __gen_01_history_2_value;
        this->gen_01_history_3_value = __gen_01_history_3_value;
        this->gen_01_y1_value = __gen_01_y1_value;
        this->gen_01_y2_value = __gen_01_y2_value;
    }
    
    void signaladder_01_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        const SampleValue * in3,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i] + in3[(Index)i];
        }
    }
    
    void limi_01_perform(const SampleValue * input1, SampleValue * output1, Index n) {
        RNBO_UNUSED(output1);
        RNBO_UNUSED(input1);
        auto __limi_01_lookaheadInv = this->limi_01_lookaheadInv;
        auto __limi_01_threshold = this->limi_01_threshold;
        auto __limi_01_lookahead = this->limi_01_lookahead;
        auto __limi_01_recover = this->limi_01_recover;
        auto __limi_01_last = this->limi_01_last;
        auto __limi_01_postamp = this->limi_01_postamp;
        auto __limi_01_lookaheadIndex = this->limi_01_lookaheadIndex;
        auto __limi_01_preamp = this->limi_01_preamp;
        auto __limi_01_dcblock = this->limi_01_dcblock;
        auto __limi_01_bypass = this->limi_01_bypass;
        ConstSampleArray<1> input = {input1};
        SampleArray<1> output = {output1};
    
        if ((bool)(__limi_01_bypass)) {
            for (Index i = 0; i < n; i++) {
                for (Index j = 0; j < 1; j++) {
                    output[(Index)j][(Index)i] = input[(Index)j][(Index)i];
                }
            }
        } else {
            number v;
    
            for (Index i = 0; i < n; i++) {
                number hotSample = 0;
    
                for (Index j = 0; j < 1; j++) {
                    auto smps = input[(Index)j];
                    v = ((bool)(__limi_01_dcblock) ? this->limi_01_dc_next(j, smps[(Index)i], 0.9997) : smps[(Index)i]);
                    v *= __limi_01_preamp;
                    this->limi_01_lookaheadBuffers[(Index)j][__limi_01_lookaheadIndex] = v * __limi_01_postamp;
                    v = rnbo_fabs(v);
    
                    if (v > hotSample)
                        hotSample = v;
                }
    
                {
                    if (__limi_01_last > 0.01)
                        v = __limi_01_last + __limi_01_recover * __limi_01_last;
                    else
                        v = __limi_01_last + __limi_01_recover;
                }
    
                if (v > 1)
                    v = 1;
    
                this->limi_01_gainBuffer[__limi_01_lookaheadIndex] = v;
                int lookaheadPlayback = (int)(__limi_01_lookaheadIndex - (int)(__limi_01_lookahead));
    
                if (lookaheadPlayback < 0)
                    lookaheadPlayback += (int)(__limi_01_lookahead);
    
                if (hotSample * v > __limi_01_threshold) {
                    number newgain;
                    number curgain = __limi_01_threshold / hotSample;
                    number inc = __limi_01_threshold - curgain;
                    number acc = 0.0;
                    number flag = 0;
    
                    for (Index j = 0; flag == 0 && j < (Index)(__limi_01_lookahead); j++) {
                        int k = (int)(__limi_01_lookaheadIndex - (int)(j));
    
                        if (k < 0)
                            k += (int)(__limi_01_lookahead);
    
                        {
                            newgain = curgain + inc * (acc * acc);
                        }
    
                        if (newgain < this->limi_01_gainBuffer[(Index)k])
                            this->limi_01_gainBuffer[(Index)k] = newgain;
                        else
                            flag = 1;
    
                        acc = acc + __limi_01_lookaheadInv;
                    }
                }
    
                for (Index j = 0; j < 1; j++) {
                    output[(Index)j][(Index)i] = this->limi_01_lookaheadBuffers[(Index)j][(Index)lookaheadPlayback] * this->limi_01_gainBuffer[(Index)lookaheadPlayback];
                }
    
                __limi_01_last = this->limi_01_gainBuffer[__limi_01_lookaheadIndex];
                __limi_01_lookaheadIndex++;
    
                if (__limi_01_lookaheadIndex >= __limi_01_lookahead)
                    __limi_01_lookaheadIndex = 0;
            }
        }
    
        this->limi_01_lookaheadIndex = __limi_01_lookaheadIndex;
        this->limi_01_last = __limi_01_last;
    }
    
    void dcblock_tilde_01_perform(const Sample * x, number gain, SampleValue * out1, Index n) {
        RNBO_UNUSED(gain);
        auto __dcblock_tilde_01_ym1 = this->dcblock_tilde_01_ym1;
        auto __dcblock_tilde_01_xm1 = this->dcblock_tilde_01_xm1;
        Index i;
    
        for (i = 0; i < n; i++) {
            number y = x[(Index)i] - __dcblock_tilde_01_xm1 + __dcblock_tilde_01_ym1 * 0.9997;
            __dcblock_tilde_01_xm1 = x[(Index)i];
            __dcblock_tilde_01_ym1 = y;
            out1[(Index)i] = y;
        }
    
        this->dcblock_tilde_01_xm1 = __dcblock_tilde_01_xm1;
        this->dcblock_tilde_01_ym1 = __dcblock_tilde_01_ym1;
    }
    
    void signaladder_02_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void signaladder_03_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void p_01_perform(Index n) {
        // subpatcher: freq-conversion
        this->p_01->process(nullptr, 0, nullptr, 0, n);
    }
    
    void p_02_perform(Index n) {
        // subpatcher: freq-conversion
        this->p_02->process(nullptr, 0, nullptr, 0, n);
    }
    
    void p_03_perform(Index n) {
        // subpatcher: freq-conversion
        this->p_03->process(nullptr, 0, nullptr, 0, n);
    }
    
    void p_04_perform(Index n) {
        // subpatcher: old-magic-number-tuning-system
        this->p_04->process(nullptr, 0, nullptr, 0, n);
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void numberobj_03_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_03_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_03_value = localvalue;
    }
    
    void numberobj_04_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_04_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_04_value = localvalue;
    }
    
    void numberobj_05_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_05_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_05_value = localvalue;
    }
    
    void numberobj_06_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_06_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_06_value = localvalue;
    }
    
    void limi_01_lookahead_setter(number v) {
        this->limi_01_lookahead = (v > 512 ? 512 : (v < 0 ? 0 : v));
        this->limi_01_lookaheadInv = (number)1 / this->limi_01_lookahead;
    }
    
    void limi_01_preamp_setter(number v) {
        this->limi_01_preamp = rnbo_pow(10., v * 0.05);
    }
    
    void limi_01_postamp_setter(number v) {
        this->limi_01_postamp = rnbo_pow(10., v * 0.05);
    }
    
    void limi_01_threshold_setter(number v) {
        this->limi_01_threshold = rnbo_pow(10., v * 0.05);
    }
    
    void numberobj_07_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_07_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_07_value = localvalue;
    }
    
    void numberobj_08_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_08_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_08_value = localvalue;
    }
    
    void numberobj_09_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_09_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_09_value = localvalue;
    }
    
    void numberobj_10_value_setter(number v) {
        number localvalue = v;
    
        if (this->numberobj_10_currentFormat != 6) {
            localvalue = trunc(localvalue);
        }
    
        this->numberobj_10_value = localvalue;
    }
    
    void noise_tilde_01_init() {
        this->noise_tilde_01_reset();
    }
    
    void noise_tilde_01_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->noise_tilde_01_state
        );
    }
    
    void adsr_01_dspsetup(bool force) {
        if ((bool)(this->adsr_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->adsr_01_mspersamp = (number)1000 / this->sr;
        this->adsr_01_setupDone = true;
    }
    
    void numberobj_03_init() {
        this->numberobj_03_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("poly/number_obj-68"), 1, this->_currentTime);
    }
    
    void numberobj_03_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_03_value;
    }
    
    void numberobj_03_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_03_value_set(preset["value"]);
    }
    
    void param_01_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_01_value;
    }
    
    void param_01_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_01_value_set(preset["value"]);
    }
    
    void param_02_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_02_value;
    }
    
    void param_02_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_02_value_set(preset["value"]);
    }
    
    void numberobj_04_init() {
        this->numberobj_04_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("poly/number_obj-69"), 1, this->_currentTime);
    }
    
    void numberobj_04_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_04_value;
    }
    
    void numberobj_04_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_04_value_set(preset["value"]);
    }
    
    void numberobj_05_init() {
        this->numberobj_05_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("poly/number_obj-70"), 1, this->_currentTime);
    }
    
    void numberobj_05_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_05_value;
    }
    
    void numberobj_05_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_05_value_set(preset["value"]);
    }
    
    void param_03_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_03_value;
    }
    
    void param_03_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_03_value_set(preset["value"]);
    }
    
    void numberobj_06_init() {
        this->numberobj_06_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("poly/number_obj-71"), 1, this->_currentTime);
    }
    
    void numberobj_06_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_06_value;
    }
    
    void numberobj_06_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_06_value_set(preset["value"]);
    }
    
    void param_04_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_04_value;
    }
    
    void param_04_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_04_value_set(preset["value"]);
    }
    
    void dcblock_tilde_01_reset() {
        this->dcblock_tilde_01_xm1 = 0;
        this->dcblock_tilde_01_ym1 = 0;
    }
    
    void dcblock_tilde_01_dspsetup(bool force) {
        if ((bool)(this->dcblock_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->dcblock_tilde_01_reset();
        this->dcblock_tilde_01_setupDone = true;
    }
    
    number limi_01_dc1_next(number x, number gain) {
        number y = x - this->limi_01_dc1_xm1 + this->limi_01_dc1_ym1 * gain;
        this->limi_01_dc1_xm1 = x;
        this->limi_01_dc1_ym1 = y;
        return y;
    }
    
    void limi_01_dc1_reset() {
        this->limi_01_dc1_xm1 = 0;
        this->limi_01_dc1_ym1 = 0;
    }
    
    void limi_01_dc1_dspsetup() {
        this->limi_01_dc1_reset();
    }
    
    number limi_01_dc_next(Index i, number x, number gain) {
        switch ((int)i) {
        default:
            {
            return this->limi_01_dc1_next(x, gain);
            }
        }
    
        return 0;
    }
    
    void limi_01_dc_reset(Index i) {
        switch ((int)i) {
        default:
            {
            return this->limi_01_dc1_reset();
            }
        }
    }
    
    void limi_01_dc_dspsetup(Index i) {
        switch ((int)i) {
        default:
            {
            return this->limi_01_dc1_dspsetup();
            }
        }
    }
    
    void limi_01_reset() {
        this->limi_01_recover = (number)1000 / (this->limi_01_release * this->samplerate());
    
        {
            this->limi_01_recover *= 0.707;
        }
    }
    
    void limi_01_dspsetup(bool force) {
        if ((bool)(this->limi_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->limi_01_reset();
        this->limi_01_setupDone = true;
        this->limi_01_dc1_dspsetup();
    }
    
    number gen_01_y2_getvalue() {
        return this->gen_01_y2_value;
    }
    
    void gen_01_y2_setvalue(number val) {
        this->gen_01_y2_value = val;
    }
    
    void gen_01_y2_reset() {
        this->gen_01_y2_value = 0;
    }
    
    void gen_01_y2_init() {
        this->gen_01_y2_value = 0;
    }
    
    number gen_01_history_1_getvalue() {
        return this->gen_01_history_1_value;
    }
    
    void gen_01_history_1_setvalue(number val) {
        this->gen_01_history_1_value = val;
    }
    
    void gen_01_history_1_reset() {
        this->gen_01_history_1_value = 0;
    }
    
    void gen_01_history_1_init() {
        this->gen_01_history_1_value = 0;
    }
    
    number gen_01_history_2_getvalue() {
        return this->gen_01_history_2_value;
    }
    
    void gen_01_history_2_setvalue(number val) {
        this->gen_01_history_2_value = val;
    }
    
    void gen_01_history_2_reset() {
        this->gen_01_history_2_value = 0;
    }
    
    void gen_01_history_2_init() {
        this->gen_01_history_2_value = 0;
    }
    
    number gen_01_history_3_getvalue() {
        return this->gen_01_history_3_value;
    }
    
    void gen_01_history_3_setvalue(number val) {
        this->gen_01_history_3_value = val;
    }
    
    void gen_01_history_3_reset() {
        this->gen_01_history_3_value = 0;
    }
    
    void gen_01_history_3_init() {
        this->gen_01_history_3_value = 0;
    }
    
    number gen_01_y1_getvalue() {
        return this->gen_01_y1_value;
    }
    
    void gen_01_y1_setvalue(number val) {
        this->gen_01_y1_value = val;
    }
    
    void gen_01_y1_reset() {
        this->gen_01_y1_value = 0;
    }
    
    void gen_01_y1_init() {
        this->gen_01_y1_value = 0;
    }
    
    number gen_01_slide_0_next(number x, number up, number down) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        number temp = x - this->gen_01_slide_0_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        this->gen_01_slide_0_prev = this->gen_01_slide_0_prev + ((x > this->gen_01_slide_0_prev ? iup : idown)) * temp;
        return this->gen_01_slide_0_prev;
    }
    
    void gen_01_slide_0_reset() {
        this->gen_01_slide_0_prev = 0;
    }
    
    number gen_01_slide_7_next(number x, number up, number down) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        number temp = x - this->gen_01_slide_7_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        this->gen_01_slide_7_prev = this->gen_01_slide_7_prev + ((x > this->gen_01_slide_7_prev ? iup : idown)) * temp;
        return this->gen_01_slide_7_prev;
    }
    
    void gen_01_slide_7_reset() {
        this->gen_01_slide_7_prev = 0;
    }
    
    number gen_01_slide_11_next(number x, number up, number down) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        number temp = x - this->gen_01_slide_11_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        this->gen_01_slide_11_prev = this->gen_01_slide_11_prev + ((x > this->gen_01_slide_11_prev ? iup : idown)) * temp;
        return this->gen_01_slide_11_prev;
    }
    
    void gen_01_slide_11_reset() {
        this->gen_01_slide_11_prev = 0;
    }
    
    number gen_02_y2_getvalue() {
        return this->gen_02_y2_value;
    }
    
    void gen_02_y2_setvalue(number val) {
        this->gen_02_y2_value = val;
    }
    
    void gen_02_y2_reset() {
        this->gen_02_y2_value = 0;
    }
    
    void gen_02_y2_init() {
        this->gen_02_y2_value = 0;
    }
    
    number gen_02_history_1_getvalue() {
        return this->gen_02_history_1_value;
    }
    
    void gen_02_history_1_setvalue(number val) {
        this->gen_02_history_1_value = val;
    }
    
    void gen_02_history_1_reset() {
        this->gen_02_history_1_value = 0;
    }
    
    void gen_02_history_1_init() {
        this->gen_02_history_1_value = 0;
    }
    
    number gen_02_history_2_getvalue() {
        return this->gen_02_history_2_value;
    }
    
    void gen_02_history_2_setvalue(number val) {
        this->gen_02_history_2_value = val;
    }
    
    void gen_02_history_2_reset() {
        this->gen_02_history_2_value = 0;
    }
    
    void gen_02_history_2_init() {
        this->gen_02_history_2_value = 0;
    }
    
    number gen_02_history_3_getvalue() {
        return this->gen_02_history_3_value;
    }
    
    void gen_02_history_3_setvalue(number val) {
        this->gen_02_history_3_value = val;
    }
    
    void gen_02_history_3_reset() {
        this->gen_02_history_3_value = 0;
    }
    
    void gen_02_history_3_init() {
        this->gen_02_history_3_value = 0;
    }
    
    number gen_02_y1_getvalue() {
        return this->gen_02_y1_value;
    }
    
    void gen_02_y1_setvalue(number val) {
        this->gen_02_y1_value = val;
    }
    
    void gen_02_y1_reset() {
        this->gen_02_y1_value = 0;
    }
    
    void gen_02_y1_init() {
        this->gen_02_y1_value = 0;
    }
    
    number gen_02_slide_0_next(number x, number up, number down) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        number temp = x - this->gen_02_slide_0_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        this->gen_02_slide_0_prev = this->gen_02_slide_0_prev + ((x > this->gen_02_slide_0_prev ? iup : idown)) * temp;
        return this->gen_02_slide_0_prev;
    }
    
    void gen_02_slide_0_reset() {
        this->gen_02_slide_0_prev = 0;
    }
    
    number gen_02_slide_7_next(number x, number up, number down) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        number temp = x - this->gen_02_slide_7_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        this->gen_02_slide_7_prev = this->gen_02_slide_7_prev + ((x > this->gen_02_slide_7_prev ? iup : idown)) * temp;
        return this->gen_02_slide_7_prev;
    }
    
    void gen_02_slide_7_reset() {
        this->gen_02_slide_7_prev = 0;
    }
    
    number gen_02_slide_11_next(number x, number up, number down) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        number temp = x - this->gen_02_slide_11_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        this->gen_02_slide_11_prev = this->gen_02_slide_11_prev + ((x > this->gen_02_slide_11_prev ? iup : idown)) * temp;
        return this->gen_02_slide_11_prev;
    }
    
    void gen_02_slide_11_reset() {
        this->gen_02_slide_11_prev = 0;
    }
    
    number gen_03_y2_getvalue() {
        return this->gen_03_y2_value;
    }
    
    void gen_03_y2_setvalue(number val) {
        this->gen_03_y2_value = val;
    }
    
    void gen_03_y2_reset() {
        this->gen_03_y2_value = 0;
    }
    
    void gen_03_y2_init() {
        this->gen_03_y2_value = 0;
    }
    
    number gen_03_history_1_getvalue() {
        return this->gen_03_history_1_value;
    }
    
    void gen_03_history_1_setvalue(number val) {
        this->gen_03_history_1_value = val;
    }
    
    void gen_03_history_1_reset() {
        this->gen_03_history_1_value = 0;
    }
    
    void gen_03_history_1_init() {
        this->gen_03_history_1_value = 0;
    }
    
    number gen_03_history_2_getvalue() {
        return this->gen_03_history_2_value;
    }
    
    void gen_03_history_2_setvalue(number val) {
        this->gen_03_history_2_value = val;
    }
    
    void gen_03_history_2_reset() {
        this->gen_03_history_2_value = 0;
    }
    
    void gen_03_history_2_init() {
        this->gen_03_history_2_value = 0;
    }
    
    number gen_03_history_3_getvalue() {
        return this->gen_03_history_3_value;
    }
    
    void gen_03_history_3_setvalue(number val) {
        this->gen_03_history_3_value = val;
    }
    
    void gen_03_history_3_reset() {
        this->gen_03_history_3_value = 0;
    }
    
    void gen_03_history_3_init() {
        this->gen_03_history_3_value = 0;
    }
    
    number gen_03_y1_getvalue() {
        return this->gen_03_y1_value;
    }
    
    void gen_03_y1_setvalue(number val) {
        this->gen_03_y1_value = val;
    }
    
    void gen_03_y1_reset() {
        this->gen_03_y1_value = 0;
    }
    
    void gen_03_y1_init() {
        this->gen_03_y1_value = 0;
    }
    
    number gen_03_slide_0_next(number x, number up, number down) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        number temp = x - this->gen_03_slide_0_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        this->gen_03_slide_0_prev = this->gen_03_slide_0_prev + ((x > this->gen_03_slide_0_prev ? iup : idown)) * temp;
        return this->gen_03_slide_0_prev;
    }
    
    void gen_03_slide_0_reset() {
        this->gen_03_slide_0_prev = 0;
    }
    
    number gen_03_slide_7_next(number x, number up, number down) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        number temp = x - this->gen_03_slide_7_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        this->gen_03_slide_7_prev = this->gen_03_slide_7_prev + ((x > this->gen_03_slide_7_prev ? iup : idown)) * temp;
        return this->gen_03_slide_7_prev;
    }
    
    void gen_03_slide_7_reset() {
        this->gen_03_slide_7_prev = 0;
    }
    
    number gen_03_slide_11_next(number x, number up, number down) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        number temp = x - this->gen_03_slide_11_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(200)));
        this->gen_03_slide_11_prev = this->gen_03_slide_11_prev + ((x > this->gen_03_slide_11_prev ? iup : idown)) * temp;
        return this->gen_03_slide_11_prev;
    }
    
    void gen_03_slide_11_reset() {
        this->gen_03_slide_11_prev = 0;
    }
    
    void numberobj_07_init() {
        this->numberobj_07_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("poly/number_obj-51"), 1, this->_currentTime);
    }
    
    void numberobj_07_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_07_value;
    }
    
    void numberobj_07_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_07_value_set(preset["value"]);
    }
    
    void numberobj_08_init() {
        this->numberobj_08_currentFormat = 6;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("poly/number_obj-52"), 1, this->_currentTime);
    }
    
    void numberobj_08_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_08_value;
    }
    
    void numberobj_08_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_08_value_set(preset["value"]);
    }
    
    void numberobj_09_init() {
        this->numberobj_09_currentFormat = 0;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("poly/number_obj-76"), 1, this->_currentTime);
    }
    
    void numberobj_09_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_09_value;
    }
    
    void numberobj_09_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_09_value_set(preset["value"]);
    }
    
    void param_05_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_05_value;
    }
    
    void param_05_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_05_value_set(preset["value"]);
    }
    
    void numberobj_10_init() {
        this->numberobj_10_currentFormat = 0;
        this->getEngine()->sendNumMessage(TAG("setup"), TAG("poly/number_obj-77"), 1, this->_currentTime);
    }
    
    void numberobj_10_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->numberobj_10_value;
    }
    
    void numberobj_10_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->numberobj_10_value_set(preset["value"]);
    }
    
    void param_06_getPresetValue(PatcherStateInterface& preset) {
        preset["value"] = this->param_06_value;
    }
    
    void param_06_setPresetValue(PatcherStateInterface& preset) {
        if ((bool)(stateIsEmpty(preset)))
            return;
    
        this->param_06_value_set(preset["value"]);
    }
    
    void midiouthelper_sendMidi(number v) {
        this->midiouthelper_midiout_set(v);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    void updateTime(MillisecondTime time) {
        this->_currentTime = time;
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));
    
        if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
            this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;
    
        if (this->sampleOffsetIntoNextAudioBuffer < 0)
            this->sampleOffsetIntoNextAudioBuffer = 0;
    }
    
    void assign_defaults()
    {
        dspexpr_01_in1 = 0;
        dspexpr_01_in2 = 0.1;
        dspexpr_02_in1 = 0;
        dspexpr_02_in2 = 0;
        adsr_01_trigger_number = 0;
        adsr_01_attack = 0.1;
        adsr_01_decay = 0.1;
        adsr_01_sustain = 0;
        adsr_01_release = 0.1;
        adsr_01_legato = 0;
        adsr_01_maxsustain = -1;
        numberobj_03_value = 0;
        numberobj_03_value_setter(numberobj_03_value);
        param_01_value = 1;
        param_02_value = 1;
        numberobj_04_value = 0;
        numberobj_04_value_setter(numberobj_04_value);
        numberobj_05_value = 0;
        numberobj_05_value_setter(numberobj_05_value);
        param_03_value = 0;
        scale_04_inlow = 0;
        scale_04_inhigh = 1;
        scale_04_outlow = 0.1;
        scale_04_outhigh = 0.01;
        scale_04_power = 1;
        numberobj_06_value = 0;
        numberobj_06_value_setter(numberobj_06_value);
        param_04_value = 1;
        expr_15_in1 = 0;
        expr_15_in2 = 0;
        expr_15_out1 = 0;
        p_01_target = 0;
        notein_01_channel = 0;
        split_01_input = 0;
        split_01_min = 20;
        split_01_max = 77;
        dcblock_tilde_01_x = 0;
        dcblock_tilde_01_gain = 0.9997;
        limi_01_bypass = 0;
        limi_01_dcblock = 0;
        limi_01_lookahead = 100;
        limi_01_lookahead_setter(limi_01_lookahead);
        limi_01_preamp = 0;
        limi_01_preamp_setter(limi_01_preamp);
        limi_01_postamp = 0;
        limi_01_postamp_setter(limi_01_postamp);
        limi_01_threshold = 0;
        limi_01_threshold_setter(limi_01_threshold);
        limi_01_release = 1000;
        gen_01_in1 = 0;
        gen_01_in2 = 0;
        gen_01_in3 = 0;
        gen_01_in4 = 0;
        gen_01_in5 = 0;
        gen_01_id = 0;
        gen_01_voices = 1;
        expr_16_in1 = 0;
        expr_16_in2 = 12;
        expr_16_out1 = 0;
        p_02_target = 0;
        dspexpr_03_in1 = 0;
        dspexpr_03_in2 = 0.9;
        gen_02_in1 = 0;
        gen_02_in2 = 0;
        gen_02_in3 = 0;
        gen_02_in4 = 0;
        gen_02_in5 = 0;
        gen_02_id = 0;
        gen_02_voices = 1;
        expr_17_in1 = 0;
        expr_17_in2 = 24;
        expr_17_out1 = 0;
        p_03_target = 0;
        dspexpr_04_in1 = 0;
        dspexpr_04_in2 = 0.8;
        gen_03_in1 = 0;
        gen_03_in2 = 0;
        gen_03_in3 = 0;
        gen_03_in4 = 0;
        gen_03_in5 = 0;
        gen_03_voices = 1;
        gen_03_id = 0;
        expr_18_in1 = 0;
        expr_18_in2 = 2;
        expr_18_out1 = 0;
        scale_05_inlow = 0;
        scale_05_inhigh = 127;
        scale_05_outlow = 0.3;
        scale_05_outhigh = 1;
        scale_05_power = 1;
        numberobj_07_value = 0;
        numberobj_07_value_setter(numberobj_07_value);
        split_02_input = 0;
        split_02_min = -1;
        split_02_max = 0;
        expr_19_in1 = 0;
        expr_19_in2 = 3;
        expr_19_out1 = 0;
        expr_20_in1 = 0;
        expr_20_in2 = 0;
        expr_20_in3 = 127;
        expr_20_out1 = 0;
        scale_06_inlow = 0;
        scale_06_inhigh = 127;
        scale_06_outlow = 0.002;
        scale_06_outhigh = 0.00005;
        scale_06_power = 1;
        numberobj_08_value = 0;
        numberobj_08_value_setter(numberobj_08_value);
        numberobj_09_value = 0;
        numberobj_09_value_setter(numberobj_09_value);
        param_05_value = 3;
        expr_21_in1 = 0;
        expr_21_in2 = 6;
        expr_21_out1 = 0;
        numberobj_10_value = 0;
        numberobj_10_value_setter(numberobj_10_value);
        param_06_value = 6;
        p_04_target = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.00002267573696;
        adsr_01_phase = 3;
        adsr_01_mspersamp = 0;
        adsr_01_time = 0;
        adsr_01_lastTriggerVal = 0;
        adsr_01_amplitude = 0;
        adsr_01_outval = 0;
        adsr_01_startingpoint = 0;
        adsr_01_triggerBuf = nullptr;
        adsr_01_triggerValueBuf = nullptr;
        adsr_01_setupDone = false;
        numberobj_03_currentFormat = 6;
        numberobj_03_lastValue = 0;
        param_01_lastValue = 0;
        param_02_lastValue = 0;
        numberobj_04_currentFormat = 6;
        numberobj_04_lastValue = 0;
        numberobj_05_currentFormat = 6;
        numberobj_05_lastValue = 0;
        param_03_lastValue = 0;
        numberobj_06_currentFormat = 6;
        numberobj_06_lastValue = 0;
        param_04_lastValue = 0;
        notein_01_status = 0;
        notein_01_byte1 = -1;
        notein_01_inchan = 0;
        dcblock_tilde_01_xm1 = 0;
        dcblock_tilde_01_ym1 = 0;
        dcblock_tilde_01_setupDone = false;
        limi_01_last = 0;
        limi_01_lookaheadIndex = 0;
        limi_01_recover = 0;
        limi_01_lookaheadInv = 0;
        limi_01_dc1_xm1 = 0;
        limi_01_dc1_ym1 = 0;
        limi_01_setupDone = false;
        gen_01_y2_value = 0;
        gen_01_history_1_value = 0;
        gen_01_history_2_value = 0;
        gen_01_history_3_value = 0;
        gen_01_y1_value = 0;
        gen_01_slide_0_prev = 0;
        gen_01_slide_7_prev = 0;
        gen_01_slide_11_prev = 0;
        gen_02_y2_value = 0;
        gen_02_history_1_value = 0;
        gen_02_history_2_value = 0;
        gen_02_history_3_value = 0;
        gen_02_y1_value = 0;
        gen_02_slide_0_prev = 0;
        gen_02_slide_7_prev = 0;
        gen_02_slide_11_prev = 0;
        gen_03_y2_value = 0;
        gen_03_history_1_value = 0;
        gen_03_history_2_value = 0;
        gen_03_history_3_value = 0;
        gen_03_y1_value = 0;
        gen_03_slide_0_prev = 0;
        gen_03_slide_7_prev = 0;
        gen_03_slide_11_prev = 0;
        numberobj_07_currentFormat = 6;
        numberobj_07_lastValue = 0;
        numberobj_08_currentFormat = 6;
        numberobj_08_lastValue = 0;
        numberobj_09_currentFormat = 6;
        numberobj_09_lastValue = 0;
        param_05_lastValue = 0;
        numberobj_10_currentFormat = 6;
        numberobj_10_lastValue = 0;
        param_06_lastValue = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number dspexpr_01_in1;
        number dspexpr_01_in2;
        number dspexpr_02_in1;
        number dspexpr_02_in2;
        number adsr_01_trigger_number;
        number adsr_01_attack;
        number adsr_01_decay;
        number adsr_01_sustain;
        number adsr_01_release;
        number adsr_01_legato;
        number adsr_01_maxsustain;
        number numberobj_03_value;
        number param_01_value;
        number param_02_value;
        number numberobj_04_value;
        number numberobj_05_value;
        number param_03_value;
        list scale_04_input;
        number scale_04_inlow;
        number scale_04_inhigh;
        number scale_04_outlow;
        number scale_04_outhigh;
        number scale_04_power;
        list scale_04_out;
        number numberobj_06_value;
        number param_04_value;
        number expr_15_in1;
        number expr_15_in2;
        number expr_15_out1;
        number p_01_target;
        number notein_01_channel;
        number split_01_input;
        number split_01_min;
        number split_01_max;
        number dcblock_tilde_01_x;
        number dcblock_tilde_01_gain;
        number limi_01_bypass;
        number limi_01_dcblock;
        number limi_01_lookahead;
        number limi_01_preamp;
        number limi_01_postamp;
        number limi_01_threshold;
        number limi_01_release;
        number gen_01_in1;
        number gen_01_in2;
        number gen_01_in3;
        number gen_01_in4;
        number gen_01_in5;
        number gen_01_id;
        number gen_01_voices;
        number expr_16_in1;
        number expr_16_in2;
        number expr_16_out1;
        number p_02_target;
        number dspexpr_03_in1;
        number dspexpr_03_in2;
        number gen_02_in1;
        number gen_02_in2;
        number gen_02_in3;
        number gen_02_in4;
        number gen_02_in5;
        number gen_02_id;
        number gen_02_voices;
        number expr_17_in1;
        number expr_17_in2;
        number expr_17_out1;
        number p_03_target;
        number dspexpr_04_in1;
        number dspexpr_04_in2;
        number gen_03_in1;
        number gen_03_in2;
        number gen_03_in3;
        number gen_03_in4;
        number gen_03_in5;
        number gen_03_voices;
        number gen_03_id;
        number expr_18_in1;
        number expr_18_in2;
        number expr_18_out1;
        list scale_05_input;
        number scale_05_inlow;
        number scale_05_inhigh;
        number scale_05_outlow;
        number scale_05_outhigh;
        number scale_05_power;
        list scale_05_out;
        number numberobj_07_value;
        number split_02_input;
        number split_02_min;
        number split_02_max;
        number expr_19_in1;
        number expr_19_in2;
        number expr_19_out1;
        number expr_20_in1;
        number expr_20_in2;
        number expr_20_in3;
        number expr_20_out1;
        list scale_06_input;
        number scale_06_inlow;
        number scale_06_inhigh;
        number scale_06_outlow;
        number scale_06_outhigh;
        number scale_06_power;
        list scale_06_out;
        number numberobj_08_value;
        number numberobj_09_value;
        number param_05_value;
        number expr_21_in1;
        number expr_21_in2;
        number expr_21_out1;
        number numberobj_10_value;
        number param_06_value;
        number p_04_target;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        SampleIndex sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[4];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        UInt noise_tilde_01_state[4] = { };
        Int adsr_01_phase;
        number adsr_01_mspersamp;
        number adsr_01_time;
        number adsr_01_lastTriggerVal;
        number adsr_01_amplitude;
        number adsr_01_outval;
        number adsr_01_startingpoint;
        signal adsr_01_triggerBuf;
        signal adsr_01_triggerValueBuf;
        bool adsr_01_setupDone;
        Int numberobj_03_currentFormat;
        number numberobj_03_lastValue;
        number param_01_lastValue;
        number param_02_lastValue;
        Int numberobj_04_currentFormat;
        number numberobj_04_lastValue;
        Int numberobj_05_currentFormat;
        number numberobj_05_lastValue;
        number param_03_lastValue;
        Int numberobj_06_currentFormat;
        number numberobj_06_lastValue;
        number param_04_lastValue;
        int notein_01_status;
        int notein_01_byte1;
        int notein_01_inchan;
        number dcblock_tilde_01_xm1;
        number dcblock_tilde_01_ym1;
        bool dcblock_tilde_01_setupDone;
        SampleValue limi_01_lookaheadBuffers[1][512] = { };
        SampleValue limi_01_gainBuffer[512] = { };
        number limi_01_last;
        int limi_01_lookaheadIndex;
        number limi_01_recover;
        number limi_01_lookaheadInv;
        number limi_01_dc1_xm1;
        number limi_01_dc1_ym1;
        bool limi_01_setupDone;
        number gen_01_y2_value;
        number gen_01_history_1_value;
        number gen_01_history_2_value;
        number gen_01_history_3_value;
        number gen_01_y1_value;
        number gen_01_slide_0_prev;
        number gen_01_slide_7_prev;
        number gen_01_slide_11_prev;
        number gen_02_y2_value;
        number gen_02_history_1_value;
        number gen_02_history_2_value;
        number gen_02_history_3_value;
        number gen_02_y1_value;
        number gen_02_slide_0_prev;
        number gen_02_slide_7_prev;
        number gen_02_slide_11_prev;
        number gen_03_y2_value;
        number gen_03_history_1_value;
        number gen_03_history_2_value;
        number gen_03_history_3_value;
        number gen_03_y1_value;
        number gen_03_slide_0_prev;
        number gen_03_slide_7_prev;
        number gen_03_slide_11_prev;
        Int numberobj_07_currentFormat;
        number numberobj_07_lastValue;
        Int numberobj_08_currentFormat;
        number numberobj_08_lastValue;
        Int numberobj_09_currentFormat;
        number numberobj_09_lastValue;
        number param_05_lastValue;
        Int numberobj_10_currentFormat;
        number numberobj_10_lastValue;
        number param_06_lastValue;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        RNBOSubpatcher_145* p_01;
        RNBOSubpatcher_146* p_02;
        RNBOSubpatcher_147* p_03;
        RNBOSubpatcher_148* p_04;
    
};

rnbomatic()
{
}

~rnbomatic()
{
    for (int i = 0; i < 16; i++) {
        delete poly[i];
    }
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
}

template <typename T> void listquicksort(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template <typename T> Int listpartition(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template <typename T> void listswapelements(T& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

MillisecondTime currenttime() {
    return this->_currentTime;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

Index getNumMidiInputPorts() const {
    return 1;
}

void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
    this->updateTime(time);
    this->midiin_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
}

Index getNumMidiOutputPorts() const {
    return 1;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    RNBO_UNUSED(numInputs);
    RNBO_UNUSED(inputs);
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    this->poly_perform(out1, out2, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->globaltransport_dspsetup(forceDSPSetup);

    for (Index i = 0; i < 16; i++) {
        this->poly[i]->prepareToProcess(sampleRate, maxBlockSize, force);
    }

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        {
        this->setProbingIndex(-1);
        break;
        }
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->RNBODefaultMtofLookupTable256);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 1;
}

void fillRNBODefaultMtofLookupTable256(DataRef& ref) {
    Float64BufferRef buffer;
    buffer = new Float64Buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        number midivalue = -256. + (number)512. / (bufsize - 1) * i;
        buffer[i] = rnbo_exp(.057762265 * (midivalue - 69.0));
    }
}

void fillDataRef(DataRefIndex index, DataRef& ref) {
    switch (index) {
    case 0:
        {
        this->fillRNBODefaultMtofLookupTable256(ref);
        break;
        }
    }
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    for (Index i = 0; i < 16; i++) {
        this->poly[i]->processDataViewUpdate(index, time);
    }
}

void initialize() {
    this->RNBODefaultMtofLookupTable256 = initDataRef("RNBODefaultMtofLookupTable256", true, nullptr, "buffer~");
    this->assign_defaults();
    this->setState();
    this->RNBODefaultMtofLookupTable256->setIndex(0);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double ) {}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {
    for (Index i = 0; i < 16; i++) {
        this->poly[(Index)i] = new RNBOSubpatcher_149();
        this->poly[(Index)i]->setEngineAndPatcher(this->getEngine(), this);
        this->poly[(Index)i]->initialize();
        this->poly[(Index)i]->setParameterOffset(this->getParameterOffset(this->poly[0]));
        this->poly[(Index)i]->setVoiceIndex(i + 1);
    }
}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
    this->param_07_getPresetValue(getSubState(preset, "attack"));
    this->param_08_getPresetValue(getSubState(preset, "decay"));
    this->param_09_getPresetValue(getSubState(preset, "sustain"));
    this->param_10_getPresetValue(getSubState(preset, "release"));
    this->param_11_getPresetValue(getSubState(preset, "secondPartialDecay"));
    this->param_12_getPresetValue(getSubState(preset, "thirdPartialDecay"));

    for (Index i = 0; i < 16; i++)
        this->poly[i]->getPreset(getSubStateAt(getSubState(preset, "__sps"), "poly", i));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time);
    this->param_07_setPresetValue(getSubState(preset, "attack"));
    this->param_08_setPresetValue(getSubState(preset, "decay"));
    this->param_09_setPresetValue(getSubState(preset, "sustain"));
    this->param_10_setPresetValue(getSubState(preset, "release"));
    this->param_11_setPresetValue(getSubState(preset, "secondPartialDecay"));
    this->param_12_setPresetValue(getSubState(preset, "thirdPartialDecay"));
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time);

    switch (index) {
    case 0:
        {
        this->param_07_value_set(v);
        break;
        }
    case 1:
        {
        this->param_08_value_set(v);
        break;
        }
    case 2:
        {
        this->param_09_value_set(v);
        break;
        }
    case 3:
        {
        this->param_10_value_set(v);
        break;
        }
    case 4:
        {
        this->param_11_value_set(v);
        break;
        }
    case 5:
        {
        this->param_12_value_set(v);
        break;
        }
    default:
        {
        index -= 6;

        if (index < this->poly[0]->getNumParameters())
            this->poly[0]->setPolyParameterValue((PatcherInterface**)this->poly, index, v, time);

        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_07_value;
        }
    case 1:
        {
        return this->param_08_value;
        }
    case 2:
        {
        return this->param_09_value;
        }
    case 3:
        {
        return this->param_10_value;
        }
    case 4:
        {
        return this->param_11_value;
        }
    case 5:
        {
        return this->param_12_value;
        }
    default:
        {
        index -= 6;

        if (index < this->poly[0]->getNumParameters())
            return this->poly[0]->getPolyParameterValue((PatcherInterface**)this->poly, index);

        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 6 + this->poly[0]->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "attack";
        }
    case 1:
        {
        return "decay";
        }
    case 2:
        {
        return "sustain";
        }
    case 3:
        {
        return "release";
        }
    case 4:
        {
        return "secondPartialDecay";
        }
    case 5:
        {
        return "thirdPartialDecay";
        }
    default:
        {
        index -= 6;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->getParameterName(index);
            }
        }

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "attack";
        }
    case 1:
        {
        return "decay";
        }
    case 2:
        {
        return "sustain";
        }
    case 3:
        {
        return "release";
        }
    case 4:
        {
        return "secondPartialDecay";
        }
    case 5:
        {
        return "thirdPartialDecay";
        }
    default:
        {
        index -= 6;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->getParameterId(index);
            }
        }

        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 1;
            info->max = 2000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 2000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 2000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 3;
            info->min = 1;
            info->max = 10;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 6;
            info->min = 1;
            info->max = 10;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        default:
            {
            index -= 6;

            if (index < this->poly[0]->getNumParameters()) {
                for (Index i = 0; i < 16; i++) {
                    this->poly[i]->getParameterInfo(index, info);
                }
            }

            break;
            }
        }
    }
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterIndex getParameterOffset(BaseInterface* subpatcher) const {
    if (subpatcher == this->poly[0])
        return 6;

    return 0;
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 2:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 1:
    case 3:
        {
        {
            value = (value < 0 ? 0 : (value > 2000 ? 2000 : value));
            ParameterValue normalizedValue = (value - 0) / (2000 - 0);
            return normalizedValue;
        }
        }
    case 4:
    case 5:
        {
        {
            value = (value < 1 ? 1 : (value > 10 ? 10 : value));
            ParameterValue normalizedValue = (value - 1) / (10 - 1);
            return normalizedValue;
        }
        }
    case 0:
        {
        {
            value = (value < 1 ? 1 : (value > 2000 ? 2000 : value));
            ParameterValue normalizedValue = (value - 1) / (2000 - 1);
            return normalizedValue;
        }
        }
    default:
        {
        index -= 6;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->convertToNormalizedParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 2:
        {
        {
            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 1:
    case 3:
        {
        {
            {
                return 0 + value * (2000 - 0);
            }
        }
        }
    case 4:
    case 5:
        {
        {
            {
                return 1 + value * (10 - 1);
            }
        }
        }
    case 0:
        {
        {
            {
                return 1 + value * (2000 - 1);
            }
        }
        }
    default:
        {
        index -= 6;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->convertFromNormalizedParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_07_value_constrain(value);
        }
    case 1:
        {
        return this->param_08_value_constrain(value);
        }
    case 2:
        {
        return this->param_09_value_constrain(value);
        }
    case 3:
        {
        return this->param_10_value_constrain(value);
        }
    case 4:
        {
        return this->param_11_value_constrain(value);
        }
    case 5:
        {
        return this->param_12_value_constrain(value);
        }
    default:
        {
        index -= 6;

        if (index < this->poly[0]->getNumParameters()) {
            {
                return this->poly[0]->constrainParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time);
    this->processOutletAtCurrentTime(sender, index, value);
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);

    for (Index i = 0; i < 16; i++) {
        this->poly[i]->processNumMessage(tag, objectId, time, payload);
    }
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);

    for (Index i = 0; i < 16; i++) {
        this->poly[i]->processListMessage(tag, objectId, time, payload);
    }
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time);

    for (Index i = 0; i < 16; i++) {
        this->poly[i]->processBangMessage(tag, objectId, time);
    }
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {

    }

    auto subpatchResult_0 = this->poly[0]->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
}

protected:

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(0, false);

    if (this->param_07_value != this->param_07_lastValue) {
        this->getEngine()->presetTouched();
        this->param_07_lastValue = this->param_07_value;
    }

    this->poly_attack_set(v);
}

void param_08_value_set(number v) {
    v = this->param_08_value_constrain(v);
    this->param_08_value = v;
    this->sendParameter(1, false);

    if (this->param_08_value != this->param_08_lastValue) {
        this->getEngine()->presetTouched();
        this->param_08_lastValue = this->param_08_value;
    }

    this->poly_decay_set(v);
}

void param_09_value_set(number v) {
    v = this->param_09_value_constrain(v);
    this->param_09_value = v;
    this->sendParameter(2, false);

    if (this->param_09_value != this->param_09_lastValue) {
        this->getEngine()->presetTouched();
        this->param_09_lastValue = this->param_09_value;
    }

    this->poly_sustain_set(v);
}

void param_10_value_set(number v) {
    v = this->param_10_value_constrain(v);
    this->param_10_value = v;
    this->sendParameter(3, false);

    if (this->param_10_value != this->param_10_lastValue) {
        this->getEngine()->presetTouched();
        this->param_10_lastValue = this->param_10_value;
    }

    this->poly_release_set(v);
}

void param_11_value_set(number v) {
    v = this->param_11_value_constrain(v);
    this->param_11_value = v;
    this->sendParameter(4, false);

    if (this->param_11_value != this->param_11_lastValue) {
        this->getEngine()->presetTouched();
        this->param_11_lastValue = this->param_11_value;
    }

    this->poly_secondPartialDecay_set(v);
}

void param_12_value_set(number v) {
    v = this->param_12_value_constrain(v);
    this->param_12_value = v;
    this->sendParameter(5, false);

    if (this->param_12_value != this->param_12_lastValue) {
        this->getEngine()->presetTouched();
        this->param_12_lastValue = this->param_12_value;
    }

    this->poly_thirdPartialDecay_set(v);
}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

Index getNumInputChannels() const {
    return 0;
}

Index getNumOutputChannels() const {
    return 2;
}

void allocateDataRefs() {
    for (Index i = 0; i < 16; i++) {
        this->poly[i]->allocateDataRefs();
    }

    if (this->RNBODefaultMtofLookupTable256->hasRequestedSize()) {
        if (this->RNBODefaultMtofLookupTable256->wantsFill())
            this->fillRNBODefaultMtofLookupTable256(this->RNBODefaultMtofLookupTable256);

        this->getEngine()->sendDataRefUpdated(0);
    }
}

void initializeObjects() {
    this->midinotecontroller_01_init();

    for (Index i = 0; i < 16; i++) {
        this->poly[i]->initializeObjects();
    }
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());

    for (Index i = 0; i < 16; i++) {
        this->poly[i]->startup();
    }

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 0);
    }

    {
        this->scheduleParamInit(3, 0);
    }

    {
        this->scheduleParamInit(4, 0);
    }

    {
        this->scheduleParamInit(5, 0);
    }

    this->processParamInitEvents();
}

number param_07_value_constrain(number v) const {
    v = (v > 2000 ? 2000 : (v < 1 ? 1 : v));
    return v;
}

void poly_attack_set(number v) {
    for (number i = 0; i < 16; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(0, v, this->_currentTime);
        }
    }
}

number param_08_value_constrain(number v) const {
    v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
    return v;
}

void poly_decay_set(number v) {
    for (number i = 0; i < 16; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(1, v, this->_currentTime);
        }
    }
}

number param_09_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void poly_sustain_set(number v) {
    for (number i = 0; i < 16; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(2, v, this->_currentTime);
        }
    }
}

number param_10_value_constrain(number v) const {
    v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
    return v;
}

void poly_release_set(number v) {
    for (number i = 0; i < 16; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(3, v, this->_currentTime);
        }
    }
}

number param_11_value_constrain(number v) const {
    v = (v > 10 ? 10 : (v < 1 ? 1 : v));
    return v;
}

void poly_secondPartialDecay_set(number v) {
    for (number i = 0; i < 16; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(4, v, this->_currentTime);
        }
    }
}

number param_12_value_constrain(number v) const {
    v = (v > 10 ? 10 : (v < 1 ? 1 : v));
    return v;
}

void poly_thirdPartialDecay_set(number v) {
    for (number i = 0; i < 16; i++) {
        if (i + 1 == this->poly_target || 0 == this->poly_target) {
            this->poly[(Index)i]->setParameterValue(5, v, this->_currentTime);
        }
    }
}

void midinotecontroller_01_currenttarget_set(number v) {
    this->midinotecontroller_01_currenttarget = v;
}

void poly_target_set(number v) {
    this->poly_target = v;
    this->midinotecontroller_01_currenttarget_set(v);
}

void midinotecontroller_01_target_set(number v) {
    this->poly_target_set(v);
}

void poly_midiininternal_set(number v) {
    Index sendlen = 0;
    this->poly_currentStatus = parseMidi(this->poly_currentStatus, (int)(v), this->poly_mididata[0]);

    switch ((int)this->poly_currentStatus) {
    case MIDI_StatusByteReceived:
        {
        this->poly_mididata[0] = (uint8_t)(v);
        this->poly_mididata[1] = 0;
        break;
        }
    case MIDI_SecondByteReceived:
    case MIDI_ProgramChange:
    case MIDI_ChannelPressure:
        {
        this->poly_mididata[1] = (uint8_t)(v);

        if (this->poly_currentStatus == MIDI_ProgramChange || this->poly_currentStatus == MIDI_ChannelPressure) {
            sendlen = 2;
        }

        break;
        }
    case MIDI_NoteOff:
    case MIDI_NoteOn:
    case MIDI_Aftertouch:
    case MIDI_CC:
    case MIDI_PitchBend:
    default:
        {
        this->poly_mididata[2] = (uint8_t)(v);
        sendlen = 3;
        break;
        }
    }

    if (sendlen > 0) {
        number i;

        if (this->poly_target > 0 && this->poly_target <= 16) {
            i = this->poly_target - 1;
            this->poly[(Index)i]->processMidiEvent(_currentTime, 0, this->poly_mididata, sendlen);
        } else if (this->poly_target == 0) {
            for (i = 0; i < 16; i++) {
                this->poly[(Index)i]->processMidiEvent(_currentTime, 0, this->poly_mididata, sendlen);
            }
        }
    }
}

void midinotecontroller_01_midiout_set(number v) {
    this->poly_midiininternal_set(v);
}

void poly_noteNumber_set(number v) {
    if (this->poly_target > 0) {
        this->poly[(Index)(this->poly_target - 1)]->setNoteNumber((int)(v));
    }
}

void midinotecontroller_01_noteNumber_set(number v) {
    this->poly_noteNumber_set(v);
}

void midinotecontroller_01_voicestatus_set(const list& v) {
    if (v[1] == 1) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(v[0]);
        this->midinotecontroller_01_noteNumber_set(0);
        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void poly_voicestatus_set(const list& v) {
    this->midinotecontroller_01_voicestatus_set(v);
}

void poly_activevoices_set(number ) {}

void poly_mute_set(const list& v) {
    Index voiceNumber = (Index)(v[0]);
    Index muteState = (Index)(v[1]);

    if (voiceNumber == 0) {
        for (Index i = 0; i < 16; i++) {
            this->poly[(Index)i]->setIsMuted(muteState);
        }
    } else {
        Index subpatcherIndex = voiceNumber - 1;

        if (subpatcherIndex >= 0 && subpatcherIndex < 16) {
            this->poly[(Index)subpatcherIndex]->setIsMuted(muteState);
        }
    }

    list tmp = {v[0], v[1]};
    this->poly_voicestatus_set(tmp);
    this->poly_activevoices_set(this->poly_calcActiveVoices());
}

void midinotecontroller_01_mute_set(const list& v) {
    this->poly_mute_set(v);
}

void midinotecontroller_01_midiin_set(number v) {
    this->midinotecontroller_01_midiin = v;
    int val = (int)(v);

    this->midinotecontroller_01_currentStatus = parseMidi(
        this->midinotecontroller_01_currentStatus,
        (int)(v),
        this->midinotecontroller_01_status
    );

    switch ((int)this->midinotecontroller_01_currentStatus) {
    case MIDI_StatusByteReceived:
        {
        {
            this->midinotecontroller_01_status = val;
            this->midinotecontroller_01_byte1 = -1;
            break;
        }
        }
    case MIDI_SecondByteReceived:
        {
        this->midinotecontroller_01_byte1 = val;
        break;
        }
    case MIDI_NoteOn:
        {
        {
            bool sendnoteoff = true;
            number target = 1;
            MillisecondTime oldest = (MillisecondTime)(this->midinotecontroller_01_voice_lastontime[0]);
            number target_state = this->midinotecontroller_01_voice_state[0];

            for (Index i = 0; i < 16; i++) {
                number candidate_state = this->midinotecontroller_01_voice_state[(Index)i];

                if (this->midinotecontroller_01_voice_notenumber[(Index)i] == this->midinotecontroller_01_byte1 && candidate_state == MIDI_NoteState_On) {
                    sendnoteoff = false;
                    target = i + 1;
                    break;
                }

                if (i > 0) {
                    if (candidate_state != MIDI_NoteState_On || target_state == MIDI_NoteState_On) {
                        MillisecondTime candidate_ontime = (MillisecondTime)(this->midinotecontroller_01_voice_lastontime[(Index)i]);

                        if (candidate_ontime < oldest || (target_state == MIDI_NoteState_On && candidate_state != MIDI_NoteState_On)) {
                            target = i + 1;
                            oldest = candidate_ontime;
                            target_state = candidate_state;
                        }
                    }
                }
            }

            if ((bool)(sendnoteoff))
                this->midinotecontroller_01_sendnoteoff((int)(target));

            int i = (int)(target - 1);
            this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_On;
            this->midinotecontroller_01_voice_lastontime[(Index)i] = this->currenttime();
            this->midinotecontroller_01_voice_notenumber[(Index)i] = this->midinotecontroller_01_byte1;
            this->midinotecontroller_01_voice_channel[(Index)i] = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (Index j = 0; j < 128; j++) {
                if (this->midinotecontroller_01_notesdown[(Index)j] == 0) {
                    this->midinotecontroller_01_notesdown[(Index)j] = this->midinotecontroller_01_voice_notenumber[(Index)i];
                    break;
                }
            }

            this->midinotecontroller_01_note_lastvelocity[(Index)this->midinotecontroller_01_voice_notenumber[(Index)i]] = val;
            this->midinotecontroller_01_sendpitchbend((int)(i));
            this->midinotecontroller_01_sendpressure((int)(i));
            this->midinotecontroller_01_sendtimbre((int)(i));
            this->midinotecontroller_01_muteval[0] = target;
            this->midinotecontroller_01_muteval[1] = 0;
            this->midinotecontroller_01_mute_set(this->midinotecontroller_01_muteval);
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(target);
            this->midinotecontroller_01_noteNumber_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);

            this->midinotecontroller_01_midiout_set(
                (BinOpInt)((BinOpInt)MIDI_NoteOnMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)i])
            );

            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
            this->midinotecontroller_01_midiout_set(val);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_NoteOff:
        {
        {
            number target = 0;
            number notenumber = this->midinotecontroller_01_byte1;
            number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (Index i = 0; i < 16; i++) {
                if (this->midinotecontroller_01_voice_notenumber[(Index)i] == notenumber && this->midinotecontroller_01_voice_channel[(Index)i] == channel && this->midinotecontroller_01_voice_state[(Index)i] == MIDI_NoteState_On) {
                    target = i + 1;
                    break;
                }
            }

            if (target > 0) {
                int i = (int)(target - 1);
                Index j = (Index)(channel);
                bool ignoresustainchannel = true;

                if ((bool)(this->midinotecontroller_01_channel_sustain[((bool)(ignoresustainchannel) ? 0 : j)])) {
                    this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Sustained;
                } else {
                    number currentTarget = this->midinotecontroller_01_currenttarget;
                    this->midinotecontroller_01_target_set(target);
                    this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
                    this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
                    this->midinotecontroller_01_midiout_set(v);
                    this->midinotecontroller_01_target_set(currentTarget);

                    if (this->midinotecontroller_01_currentStatus == MIDI_NoteOff) {
                        this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
                    }
                }
            } else
                {}

            bool found = false;

            for (Index i = 0; i < 128; i++) {
                if (this->midinotecontroller_01_notesdown[(Index)i] == 0) {
                    break;
                } else if (this->midinotecontroller_01_notesdown[(Index)i] == notenumber) {
                    found = true;
                }

                if ((bool)(found)) {
                    this->midinotecontroller_01_notesdown[(Index)i] = this->midinotecontroller_01_notesdown[(Index)(i + 1)];
                }
            }

            break;
        }
        }
    case MIDI_Aftertouch:
        {
        {
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(0);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
            this->midinotecontroller_01_midiout_set(v);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_CC:
        {
        {
            bool sendToAllVoices = true;

            switch ((int)this->midinotecontroller_01_byte1) {
            case MIDI_CC_Sustain:
                {
                {
                    bool pedaldown = (bool)((val >= 64 ? true : false));
                    number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);
                    Index j = (Index)(channel);
                    bool ignoresustainchannel = true;
                    this->midinotecontroller_01_channel_sustain[((bool)(ignoresustainchannel) ? 0 : j)] = pedaldown;

                    if ((bool)(!(bool)(pedaldown))) {
                        for (Index i = 0; i < 16; i++) {
                            if (((bool)(ignoresustainchannel) || this->midinotecontroller_01_voice_channel[(Index)i] == channel) && this->midinotecontroller_01_voice_state[(Index)i] == MIDI_NoteState_Sustained) {
                                number currentTarget = this->midinotecontroller_01_currenttarget;
                                this->midinotecontroller_01_target_set(i + 1);
                                this->midinotecontroller_01_midiout_set((BinOpInt)((BinOpInt)MIDI_NoteOffMask | (BinOpInt)j));
                                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
                                this->midinotecontroller_01_midiout_set(64);
                                this->midinotecontroller_01_target_set(currentTarget);
                                this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
                            }
                        }
                    }

                    break;
                }
                }
            case MIDI_CC_TimbreMSB:
                {
                {
                    number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);
                    int k = (int)(v);
                    number timbre = (BinOpInt)(((BinOpInt)((BinOpInt)k & (BinOpInt)0x7F)) << imod_nocast((UBinOpInt)7, 32));
                    this->midinotecontroller_01_channel_timbre[(Index)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F)] = timbre;

                    for (Index i = 0; i < 16; i++) {
                        if (this->midinotecontroller_01_voice_channel[(Index)i] == channel && this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off) {
                            this->midinotecontroller_01_sendtimbre(i);
                        }
                    }

                    sendToAllVoices = false;
                    break;
                }
                }
            case MIDI_CC_TimbreLSB:
                {
                {
                    break;
                }
                }
            case MIDI_CC_AllNotesOff:
                {
                {
                    this->midinotecontroller_01_sendallnotesoff();
                    break;
                }
                }
            }

            if ((bool)(sendToAllVoices)) {
                number currentTarget = this->midinotecontroller_01_currenttarget;
                this->midinotecontroller_01_target_set(0);
                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
                this->midinotecontroller_01_midiout_set(v);
                this->midinotecontroller_01_target_set(currentTarget);
            }

            break;
        }
        }
    case MIDI_ProgramChange:
        {
        {
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(0);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_ChannelPressure:
        {
        {
            number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (number i = 0; i < 16; i++) {
                if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off && this->midinotecontroller_01_voice_channel[(Index)i] == channel) {
                    int k = (int)(channel);
                    this->midinotecontroller_01_channel_pressure[(Index)k] = v;
                    this->midinotecontroller_01_sendpressure(i);
                }
            }

            break;
        }
        }
    case MIDI_PitchBend:
        {
        {
            number bendamount = (BinOpInt)((BinOpInt)this->midinotecontroller_01_byte1 | (BinOpInt)((BinOpInt)val << imod_nocast((UBinOpInt)7, 32)));
            int channel = (int)((BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F));
            this->midinotecontroller_01_channel_pitchbend[(Index)channel] = bendamount;

            for (Index i = 0; i < 16; i++) {
                if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off && this->midinotecontroller_01_voice_channel[(Index)i] == channel) {
                    this->midinotecontroller_01_sendpitchbend(i);
                }
            }

            break;
        }
        }
    }
}

void poly_midiin_set(number v) {
    this->poly_midiin = v;
    this->midinotecontroller_01_midiin_set(v);
}

void midiin_midiout_set(number v) {
    this->poly_midiin_set(v);
}

void midiin_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(port);
    RNBO_UNUSED(channel);
    RNBO_UNUSED(status);
    Index i;

    for (i = 0; i < length; i++) {
        this->midiin_midiout_set(data[i]);
    }
}

void poly_perform(SampleValue * out1, SampleValue * out2, Index n) {
    SampleArray<2> outs = {out1, out2};

    for (number chan = 0; chan < 2; chan++)
        zeroSignal(outs[(Index)chan], n);

    for (Index i = 0; i < 16; i++)
        this->poly[(Index)i]->process(nullptr, 0, outs, 2, n);
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void param_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_07_value;
}

void param_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_07_value_set(preset["value"]);
}

void param_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_08_value;
}

void param_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_08_value_set(preset["value"]);
}

void param_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_09_value;
}

void param_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_09_value_set(preset["value"]);
}

void param_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_10_value;
}

void param_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_10_value_set(preset["value"]);
}

void param_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_11_value;
}

void param_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_11_value_set(preset["value"]);
}

void param_12_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_12_value;
}

void param_12_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_12_value_set(preset["value"]);
}

number poly_calcActiveVoices() {
    {
        number activeVoices = 0;

        for (Index i = 0; i < 16; i++) {
            if ((bool)(!(bool)(this->poly[(Index)i]->getIsMuted())))
                activeVoices++;
        }

        return activeVoices;
    }
}

void midinotecontroller_01_init() {
    for (Index i = 0; i < 16; i++) {
        this->midinotecontroller_01_channel_pitchbend[(Index)i] = 0x2000;
    }

    for (Index i = 0; i < 16; i++) {
        this->midinotecontroller_01_voice_lastontime[(Index)i] = -1;
    }
}

void midinotecontroller_01_sendnoteoff(int target) {
    int i = (int)(target - 1);

    if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(target);

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)MIDI_NoteOffMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)i])
        );

        this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
        this->midinotecontroller_01_midiout_set(64);
        this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void midinotecontroller_01_sendpitchbend(int v) {
    if (v >= 0 && v < 16) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(v + 1);
        int totalbendamount = (int)(this->midinotecontroller_01_channel_pitchbend[(Index)this->midinotecontroller_01_voice_channel[(Index)v]]);

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)MIDI_PitchBendMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
        );

        this->midinotecontroller_01_midiout_set((BinOpInt)((BinOpInt)totalbendamount & (BinOpInt)0x7F));

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)((BinOpInt)totalbendamount >> imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)7, 32), 32)) & (BinOpInt)0x7F)
        );

        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void midinotecontroller_01_sendpressure(int v) {
    number currentTarget = this->midinotecontroller_01_currenttarget;
    this->midinotecontroller_01_target_set(v + 1);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_ChannelPressureMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(
        this->midinotecontroller_01_channel_pressure[(Index)this->midinotecontroller_01_voice_channel[(Index)v]]
    );

    this->midinotecontroller_01_target_set(currentTarget);
}

void midinotecontroller_01_sendtimbre(int v) {
    number currentTarget = this->midinotecontroller_01_currenttarget;
    this->midinotecontroller_01_target_set(v + 1);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_CCMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(MIDI_CC_TimbreLSB);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)this->midinotecontroller_01_channel_timbre[(Index)this->midinotecontroller_01_voice_channel[(Index)v]] & (BinOpInt)0x7F)
    );

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_CCMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(MIDI_CC_TimbreMSB);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)((BinOpInt)this->midinotecontroller_01_channel_timbre[(Index)this->midinotecontroller_01_voice_channel[(Index)v]] >> imod_nocast((UBinOpInt)7, 32)) & (BinOpInt)0x7F)
    );

    this->midinotecontroller_01_target_set(currentTarget);
}

void midinotecontroller_01_sendallnotesoff() {
    for (Index i = 1; i <= 16; i++) {
        this->midinotecontroller_01_sendnoteoff(i);
    }
}

void globaltransport_advance() {}

void globaltransport_dspsetup(bool ) {}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

void updateTime(MillisecondTime time) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    midiin_port = 0;
    midiout_port = 0;
    param_07_value = 1;
    param_08_value = 1;
    param_09_value = 0;
    param_10_value = 1;
    param_11_value = 3;
    param_12_value = 6;
    poly_target = 0;
    poly_midiin = 0;
    midinotecontroller_01_currenttarget = 0;
    midinotecontroller_01_midiin = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    midiout_currentStatus = -1;
    midiout_status = -1;
    midiout_byte1 = -1;
    param_07_lastValue = 0;
    param_08_lastValue = 0;
    param_09_lastValue = 0;
    param_10_lastValue = 0;
    param_11_lastValue = 0;
    param_12_lastValue = 0;
    poly_currentStatus = -1;
    poly_mididata[0] = 0;
    poly_mididata[1] = 0;
    poly_mididata[2] = 0;
    midinotecontroller_01_currentStatus = -1;
    midinotecontroller_01_status = -1;
    midinotecontroller_01_byte1 = -1;
    midinotecontroller_01_zone_masterchannel = 1;
    midinotecontroller_01_zone_numnotechannels = 15;
    midinotecontroller_01_zone_masterpitchbendrange = 2;
    midinotecontroller_01_zone_pernotepitchbendrange = 48;
    midinotecontroller_01_muteval = { 0, 0 };
    globaltransport_tempo = nullptr;
    globaltransport_state = nullptr;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number midiin_port;
    number midiout_port;
    number param_07_value;
    number param_08_value;
    number param_09_value;
    number param_10_value;
    number param_11_value;
    number param_12_value;
    number poly_target;
    number poly_midiin;
    number midinotecontroller_01_currenttarget;
    number midinotecontroller_01_midiin;
    MillisecondTime _currentTime;
    UInt64 audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    int midiout_currentStatus;
    int midiout_status;
    int midiout_byte1;
    list midiout_sysex;
    number param_07_lastValue;
    number param_08_lastValue;
    number param_09_lastValue;
    number param_10_lastValue;
    number param_11_lastValue;
    number param_12_lastValue;
    int poly_currentStatus;
    uint8_t poly_mididata[3];
    int midinotecontroller_01_currentStatus;
    int midinotecontroller_01_status;
    int midinotecontroller_01_byte1;
    int midinotecontroller_01_zone_masterchannel;
    int midinotecontroller_01_zone_numnotechannels;
    int midinotecontroller_01_zone_masterpitchbendrange;
    int midinotecontroller_01_zone_pernotepitchbendrange;
    number midinotecontroller_01_channel_pitchbend[16] = { };
    number midinotecontroller_01_channel_pressure[16] = { };
    number midinotecontroller_01_channel_timbre[16] = { };
    Int midinotecontroller_01_channel_sustain[16] = { };
    MillisecondTime midinotecontroller_01_voice_lastontime[16] = { };
    number midinotecontroller_01_voice_notenumber[16] = { };
    number midinotecontroller_01_voice_channel[16] = { };
    number midinotecontroller_01_voice_state[16] = { };
    number midinotecontroller_01_notesdown[129] = { };
    number midinotecontroller_01_note_lastvelocity[128] = { };
    list midinotecontroller_01_muteval;
    signal globaltransport_tempo;
    signal globaltransport_state;
    number stackprotect_count;
    DataRef RNBODefaultMtofLookupTable256;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_149* poly[16];

};

PatcherInterface* creaternbomatic()
{
    return new rnbomatic();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return creaternbomatic;
}

} // end RNBO namespace

