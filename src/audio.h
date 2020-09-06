#ifndef AUDIO
#define AUDIO

#define SAMPLE_RATE 48000
#define SAMPLES 4096
#define FREQUENCY 220

void setup_audio();
void audio_callback();
void play_tone();
void stop_audio();
#endif