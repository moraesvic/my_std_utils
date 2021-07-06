/*
https://rosettacode.org/wiki/Fast_Fourier_transform#C
gcc -o rosetta rosetta.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <complex.h>
 
double PI = atan2(1, 1) * 4;
typedef double complex cplx;
 
void _fft(cplx buf[], cplx out[], int n, int step)
{
	if (step < n) {
		_fft(out, buf, n, step * 2);
		_fft(out + step, buf + step, n, step * 2);
 
		for (int i = 0; i < n; i += 2 * step) {
			cplx t = cexp(-I * PI * i / n) * out[i + step];
			buf[i / 2]     = out[i] + t;
			buf[(i + n)/2] = out[i] - t;
		}
	}
}
 
void fft(cplx buf[], int n)
{
	cplx out[n];
	for (int i = 0; i < n; i++) out[i] = buf[i];
 
	_fft(buf, out, n, 1);
}
 
 
void show(const char * s, cplx buf[], unsigned n) {
	printf("%s", s);
	for (int i = 0; i < n; i++)
		if (!cimag(buf[i]))
			printf("%g ", creal(buf[i]));
		else
			printf("(%g, %g) ", creal(buf[i]), cimag(buf[i]));
}

cplx* pad_if_needed(cplx *buf, unsigned * sz)
{
    unsigned msb, i, oldsz;
    cplx *newbuf;
    if (*sz & (*sz - 1) != 0) {
        oldsz = *sz;
        for (i = 0; i < 8 * sizeof(unsigned); i++)
            if ( (1 << i) & *sz )
                msb = i;
        *sz = 1 << (msb + 1);
        newbuf = malloc(*sz * sizeof(cplx));
        for (i = 0; i < oldsz; i++)
            newbuf[i] = buf[i];
        for (i = oldsz; i < *sz; i++)
            newbuf[i] = 0;
        free(buf);
        return newbuf;
    }
    return buf;
}

unsigned get_file_size(FILE * fp)
{
    unsigned filesz;
    fseek(fp, 0, SEEK_END);
    filesz = ftell(fp);
    rewind(fp);
    return filesz;
}
 
int main()
{
    cplx *buf;
    FILE * fp;
    unsigned i, filesz, sz;
    uint16_t tmp;

    fp = fopen("out2.raw", "rb");
    filesz = get_file_size(fp);
    sz = filesz / sizeof(uint16_t);
    printf("File size is %u, will read %u samples\n",
    filesz, sz);
    buf = calloc(sz, sizeof(cplx));
    for (i = 0; i < sz; i++) {
        if (!fread(&tmp, sizeof(uint16_t), 1, fp)) {
            fprintf(stderr, "Error reading file!\n");
            return -1;
        }
        buf[i] = tmp - 0x7fff;
    }
    
    buf = pad_if_needed(buf, &sz);
    printf("sz = %u\n", sz);
	show("Data: ", buf, sz);
	fft(buf, sz);
	show("\nFFT : ", buf, sz);
    printf("\n");
 
	return 0;
}
 