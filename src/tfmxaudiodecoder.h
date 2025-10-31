/* C language wrapper library for TFMX & FC audio decoder library
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef TFMXAUDIODECODER_H
#define TFMXAUDIODECODER_H

#ifdef __cplusplus
extern "C" {
#endif

    #include <stdint.h>
    
    /* Return ptr to new decoder object. */
    void* tfmxdec_new();

    /* Delete decoder object. */
    void tfmxdec_delete(void* decoder);

    void tfmxdec_set_path(void* decoder, const char*);
    
    /* Initialize decoder with input data from a memory buffer.
       Input buffer may be freed as buffer contents get copied.
       Song numbers start at 0.
       Returns: boolean integer 1 = success, 0 = failure */
    int tfmxdec_init(void* decoder, void* buffer, uint32_t length, int songNumber);

    /* With an already initialized decoder, this can be called
       to init a different song or reinit the current song.
       Song numbers start at 0. Current is < 0.
       Returns: boolean integer 1 = success, 0 = failure */
    int tfmxdec_reinit(void* decoder, int songNumber);

    /* Initialize decoder's audio sample mixer.
       frequency : output sample frequency
       precision : bits per sample
       channels : 1=mono, 2=stereo
       zero : value of silent output sample
              (e.g. 0x80 for unsigned 8-bit, 0x0000 for signed 16-bit)
       panning : 100 to 0, default = 75
                 100=full stereo, 50=middle, 0=mirrored full stereo */
    void tfmxdec_mixer_init(void* decoder, int frequency, int precision,
                            int channels, int zero, int panning);

    /* Return 1 (true) if song end has been reached, else 0 (false). */
    int tfmxdec_song_end(void* decoder);

    /* Only to be called after initialization.
       Return number of songs. */
    int tfmxdec_songs(void* decoder);
    
    /* Return duration of initialized song in milli-seconds [ms]. */
    uint32_t tfmxdec_duration(void* decoder);

    /* Set an initialized decoder's play position in milli-seconds [ms]. */
    void tfmxdec_seek(void* decoder, int32_t ms);

    /* Return short C-string identifying the detected input data format. */
    const char* tfmxdec_format_id(void* decoder);
    
    /* Return C-string describing the detected input data format. */
    const char* tfmxdec_format_name(void* decoder);

    /* Fill output sample buffer. */
    void tfmxdec_buffer_fill(void* decoder, void* buffer, uint32_t length);

    /* Whether to end short tracks/subsongs immediately,
       if they are shorter than N seconds.
       Default: false */
    void tfmxdec_end_shorts(void* decoder, int flag, int secs);

    /* Optional!
       Apply input format header check to a memory buffer containing
       at least 0xb80 bytes (= HippelDecoder::TFMX_PROBE_SIZE).
       With a minimum of 5 bytes it can detect only some raw modules with
       a tag at the very beginning. And full init may reject such data
       later, if taking a closer look.
       Returns: boolean integer 1 = recognized data, 0 = unknown data */
    int tfmxdec_detect(void* decoder, void* buffer, uint32_t length);
    
    /* Not that useful, but some TFMX-MOD files provide content for them. */
    const char* tfmxdec_get_artist(void* decoder);
    const char* tfmxdec_get_title(void* decoder);
    const char* tfmxdec_get_game(void* decoder);

    /* Only to be called after initialization.
       Return number of voices. */
    int tfmxdec_voices(void* decoder);
    
    /* With the number of voices retrieved via tfmxdec_get_voices,
       use this to mute/unmute individual voices. */
    void tfmxdec_mute_voice(void* decoder, bool mute, unsigned int voice);

    /* Returns: 0 to 100 */
    unsigned short int tfmxdec_get_voice_volume(void* decoder, unsigned int voice);
    
#ifdef __cplusplus
}
#endif

#endif  /* TFMXAUDIODECODER_H */
