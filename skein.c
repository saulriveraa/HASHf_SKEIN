#include <string.h>
#include <stdio.h>
#include "skein.h"
#include "threefish.h"

void init(context *ctx) {
    memset(ctx->M, 0x00, 1024);
    memset(ctx->buff, 0x00, 32);
    ctx->byt = 0;
}

void update(unsigned char *a, int len, context *ctx) {

    int aux2, aux3, aux4;

    memcpy(ctx->ch_val, C_I, 32);
    update_M(ctx, a, len);

    aux2 = (len + ctx->byt) / 32;
    aux3 = (len + ctx->byt) % 32;
    if(aux3 > 0){ aux4 = aux2 + 1; }
    else{ aux4 = aux2; }

    ctx->byt = 0;

    for(int o = 0; o < aux4; o++)
    {

        ctx->byt += bytes_operating(aux4, aux3, o);

        tweak(ctx->byt, ctx->t, aux4, o);

        for(int i = 0; i < 32; i++) ctx->buff[i] = ctx->M[32*o + i];

        threefish(ctx->ch_val, ctx->buff, ctx->ch_val, ctx->t);

        for(int i = 0; i < 32; i++) ctx->ch_val[i] ^= ctx->buff[i];

    }
}

void finalize(unsigned char *a, context *ctx) {

    unsigned char t_aux[16] = {0x00};
    unsigned char p_aux[32] = {0x00};

    tweak(8,t_aux, 1, 0);
    t_aux[15] = 0xff;

    threefish(a, p_aux, ctx->ch_val, t_aux);

}
