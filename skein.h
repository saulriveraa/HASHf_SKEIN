#include <math.h>

/* This is your hash instance context, i.e., hash state.
 * You could put the following stuff inside here:
 * - buffered message bytes
 * - current offset within said buffer
 * - chaining value
 * - tweak
 * - leprechaun gold
 * - next week's correct lotto numbers
 */
typedef struct {
    unsigned char ch_val[32];
    unsigned char buff[32];
    unsigned char t[16];
    int byt;
    unsigned char M[1024];
} context;

static unsigned char C_I[32] = {
                            0x49, 0xb4, 0x48, 0xd0, 0x60, 0xa8, 0x9d, 0xfc,
                            0x33, 0xd8, 0xa7, 0x9f, 0x47, 0x66, 0xca, 0x2f,
                            0x0f, 0x84, 0x56, 0x66, 0x89, 0xc3, 0x3b, 0xb3,
                            0x69, 0xda, 0xe8, 0xfd, 0x20, 0xe9, 0x54, 0x6a};

static inline int bytes_operating(int aux4, int aux3, int o)
{
    int res = 0;
    if(o == (aux4 - 1))
        {
            if(aux3 != 0) { res = aux3;}
            else {res = 32;}
        }
    else{
        res = 32;
        }
    return res;
}

static inline void update_M(context *ctx, unsigned char *a, int len)
{
    for(int o = 0; o < len; o++)
        ctx->M[o + ctx->byt] = a[o];
}

static inline void tweak(int byt, unsigned char *t_aux, int aux4, int o)
{
    for(int i = 0; i < 15; i++)
        t_aux[i] = fmod(floor(byt/pow(256, i)), 256);


    if(aux4 == 1)
    {
        t_aux[15] = 0xf0;
    }
    else
    {
        if(aux4 == 2)
        {
            if(o == 0) t_aux[15] = 0x70;
            else t_aux[15] = 0xb0;
        }
        else
        {
            if (o == 0) t_aux[15] = 0x70;
            else if((o + 1) < aux4) t_aux[15] = 0x30;
            else t_aux[15] = 0xb0;
        }
    }


}

/* Implement the following API.
 * You can add your own functions above, but don't modify below this line.
 */

/* Initialize fresh context ctx */
void init(context *ctx);

/* Under context ctx, incrementally process len bytes at a */
void update(unsigned char *a, int len, context *ctx);

/* Under context ctx, finalize the hash and place the digest at a */
void finalize(unsigned char *a, context *ctx);

