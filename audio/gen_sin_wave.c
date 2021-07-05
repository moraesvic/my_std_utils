/* Credits go to Ciro Santili
 * https://stackoverflow.com/questions/732699/how-is-audio-represented-with-numbers-in-computers 
 * 
 * I modified the code to simplify it slightly using little endian (native Linux
 * encoding) */

/* To listen to the generated audio-file:
   -----
 * Play out.raw directly:

sudo apt-get install ffmpeg
ffplay -autoexit -f u16be -ar 44100 -ac 1 out.raw
-> or use little endian: -f u16le
or convert to a more common audio format and then play with a more common audio player:

ffmpeg -f u16be -ar 44100 -ac 1 -i out.raw out.flac
-> or use little endian: -f u16le
vlc out.flac
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void) {
    FILE *f;
    const double PI2 = 2 * acos(-1.0);
    const double SAMPLE_FREQ = 44100;
    const unsigned int NSAMPLES = SAMPLE_FREQ;
    const double FUND_FREQ = 8.0;
    uint16_t ampl;
    unsigned int t;

    f = fopen("out.raw", "wb");
    for (t = 0; t < NSAMPLES; ++t) {
        ampl = UINT16_MAX * 0.5 * (1.0 + sin(PI2 * t * FUND_FREQ / SAMPLE_FREQ));
        fwrite(&ampl, 1, sizeof(uint16_t), f);
    }
    fclose(f);
    return EXIT_SUCCESS;
}