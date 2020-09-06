#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <SDL_audio.h>
#include "audio.h"

bool is_playing_audio = false;
unsigned int phase_position = 0;
SDL_AudioDeviceID audio_device;

void setup_audio() {
    SDL_AudioSpec wanted;
    wanted.freq = SAMPLE_RATE;
    wanted.format = AUDIO_S8;
    wanted.channels = 1;
    wanted.samples = SAMPLES;
    wanted.callback = audio_callback;
    wanted.userdata = NULL;

    SDL_AudioSpec obtained;
    // open audio device
    audio_device = SDL_OpenAudioDevice(NULL, 0, &wanted, NULL, 0);
    if (audio_device < 0) {
        fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
    }
}

void audio_callback(void *unused, Uint8 *stream, int length) {
    for (int i = 0; i < length; i++) {
        double t = FREQUENCY * (M_PI * 2) * phase_position / SAMPLE_RATE;
        int value = (128/4) * sin(t);
        stream[i] = value;
        phase_position++;
        phase_position %= (SAMPLE_RATE / FREQUENCY);
    }
}

void play_tone() {
    if (is_playing_audio == true)
        return;
    SDL_PauseAudioDevice(audio_device, 0);
    is_playing_audio = true;
}

void stop_audio() {
    if (is_playing_audio == false)
        return;
    SDL_PauseAudioDevice(audio_device, 1);
    is_playing_audio = false;
}
