/* DFT = Discrete Fourier Transform */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PI 3.1415926535897932384626433
#define PI_TIMES_2 6.283185307179586

/* I know C-99 can do complex numbers, but I never really
 * learned to used this library, so I will keep myself to one
 * thing at a time and just do complex numbers "by hand" */

/* Theoretical references:
https://www.youtube.com/watch?v=mkGsMWi_j4Q
https://en.wikipedia.org/wiki/Discrete_Fourier_transform
*/

struct Complex {
    double real;
    double imag;
};

struct Complex* dft(double *input, unsigned n)
{
    /* Receives a vector with the samples,
     * outputs a complex vector containing the 
     * Fast Fourier Transform */
    int i, j;
    double angle;
    struct Complex *cpx = malloc((n/2) * sizeof(struct Complex));
    
    /* we only get the first n/2 harmonics (Nyquist limit) */
    /* That's also the reason we multiply everything by 2 */
    for (i = 0; i < n/2; i++) {
        cpx[i].real = 0;
        cpx[i].imag = 0;
        for (j = 0; j < n; j++) {
            angle = PI_TIMES_2 * i * j / n;
            cpx[i].real += input[j] * cos(angle);
            cpx[i].imag -= input[j] * sin(angle);
        }
        /* averaging over number of samples */
        cpx[i].real /= n;
        cpx[i].imag /= n;
    }
    return cpx;
}

unsigned get_file_size(FILE * fp)
{
    unsigned filesz;
    fseek(fp, 0, SEEK_END);
    filesz = ftell(fp);
    rewind(fp);
    return filesz;
}

inline double mod_cpx(struct Complex cpx)
{
    return sqrt(cpx.real * cpx.real + cpx.imag * cpx.imag);
}

void print_cpx(struct Complex cpx, unsigned harm)
{
    printf("[%4d] (%.4f ", harm, cpx.real);
    if (cpx.imag < 0)
        printf("%.4f", cpx.imag);
    else
        printf("+%.4f", cpx.imag);
    printf(" i -> ampl: %.4f)\n", mod_cpx(cpx));
}

/* 
Probably the best idea is using a well-tested and fast implementation
https://www.fftw.org/
*/

int main()
{
    FILE * fp;
    unsigned i, filesz, samplesz;
    uint16_t tmp;
    complex double *buf;

    fp = fopen("out2.raw", "rb");
    filesz = get_file_size(fp);
    samplesz = filesz / sizeof(uint16_t);
    printf("File size is %u, will read %u samples\n",
    filesz, samplesz);
    buf = calloc(samplesz, sizeof(complex double));
    for (i = 0; i < samplesz; i++) {
        if (!fread(&tmp, sizeof(uint16_t), 1, fp)) {
            fprintf(stderr, "Error reading file!\n");
            return -1;
        }
        buf[i] = tmp - 0x7fff;
    }

    dft(buf, samplesz);

    free(buf);
    return 0;
}