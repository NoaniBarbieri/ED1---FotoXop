/*
 * DCE05968 - Estruturas de Dados I
 * Funções responsaveis pelos filtros que podem ser aplicados na imagem.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Imagem.h"  /* Tipos e protótipos de funções que manipulam imagens */
#include "Filtros.h" /* Protótipo das funções responsáveis pelos filtros das imagens */

/* Função responsável por escurecer uma imagem
 * A função recebe um ponteiro para um struct Imagem e altera/escurece
 * cada um de seus pixels em cada canal de cor (RGB).
 *
 * Analise essa função com bastante atenção. Ela irá te auxiliar no entendimento
 * do TAD Imagem e como outros filtros podem ser implementados.
 *
 * Você não precisa modificar essa função
 */
void escurecerImagem(Imagem *img){
    int v;
    printf("Digite o fator de escurecimento: ");
    scanf("%d", &v);
    /* Cada canal de cor (RGB) de cada pixel é reduzido 'v' do valor.
     * Note que devemos garantir que o valor esteja entre 0 e 255.
     * Como estamos subtraindo, verificamos apenas se o valor é >= 0
     * Note também a utilização de expressão ternária e o cast (conversão)
     * entre os valores Byte (unsigned int) e int. Esse cast evita erros nas
     * operações matemáticas.
     */
    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            //Obtém o pixel da posição (h, w) da imagem
            Pixel pixel = obtemPixel(img, h, w);
            //Modifica cada canal de cor do pixel
            pixel.cor[RED]   = (((int)pixel.cor[RED] - v) >= 0 ? ((int)pixel.cor[RED] - v) : 0);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] - v) >= 0 ? ((int)pixel.cor[GREEN] - v) : 0);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE] - v) >= 0 ? ((int)pixel.cor[BLUE] - v) : 0);
            //Grava o novo pixel na posição (h, w) da imagem
            recolorePixel(img, h, w, pixel);
        }
    }
}

/* Função responsável por clarear uma imagem
 * A função recebe um ponteiro para um struct Imagem e altera/clareia
 * cada um de seus pixels em cada canal de cor (RGB).
 */
void clarearImagem(Imagem *img){
    int v;
    printf("Digite o fator de clareamento: ");
    scanf("%d", &v);

     for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            //Obtém o pixel da posição (h, w) da imagem
            Pixel pixel = obtemPixel(img, h, w);
            //Modifica cada canal de cor do pixel
            pixel.cor[RED]   = (((int)pixel.cor[RED] + v) <= 255 ? ((int)pixel.cor[RED] + v) : 255);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] + v) <= 255 ? ((int)pixel.cor[GREEN] + v) : 255);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE] + v) <= 255 ? ((int)pixel.cor[BLUE] + v) : 255);
            //Grava o novo pixel na posição (h, w) da imagem
            recolorePixel(img, h, w, pixel);
        }
    }
}

/* Função responsável por converter uma imagem colorida em escala de cinza
 * A função recebe um ponteiro para um struct Imagem e converte
 * cada um de seus pixels em cada canal de cor (RGB) em uma tonalidade de cinza.
 *
 * No pdf de descrição do EP existem duas estretégias para a implementação
 * desse filtro. Você deve implementar uma delas ou pesquisar por outras alternativas.
 */
void escalaDeCinzaImagem(Imagem *img){
    //utilizado a mudanca por cinza a partir da media das cores
    int cinza;
    for (int h = 0; h < obtemAltura(img); h++){
        for (int w = 0; w < obtemLargura(img); w++){
            Pixel pixel = obtemPixel(img, h, w);
            cinza = (((int)pixel.cor[RED] + (int)pixel.cor[GREEN] + (int)pixel.cor[BLUE])/3);
            pixel.cor[RED] = (Byte)cinza;
            pixel.cor[GREEN] = (Byte)cinza;
            pixel.cor[BLUE] = (Byte)cinza;
            recolorePixel(img, h, w, pixel);
        }
     }
}

/* Função responsável por aplicar o filtro de Sobel na imagem.
 * Leia o pdf do EP para obter mais informações de como o filtro é implementado.
 */
void filtroSobel(Imagem *img){

    int yR = 0,yG = 0,yB = 0, xR = 0,xG = 0,xB = 0;
    int  mR, mG,mB, h, w;
    Imagem *copiaS = copiaImagem(img);

    //realiza o calculo na matriz GX e GY
    for (h = 1; h < obtemAltura(copiaS) - 1; h++){
        for (w = 1; w < obtemLargura(copiaS) - 1; w++){
            //matriz em GX
            Pixel pixel = obtemPixel(copiaS, h-1, w-1);
            xR = 1 * (int)pixel.cor[RED];
            xG = 1 * (int)pixel.cor[GREEN];
            xB = 1 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaS, h-1, w);
            xR += 0 * (int)pixel.cor[RED];
            xG += 0 * (int)pixel.cor[GREEN];
            xB += 0 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaS, h-1, w +1);
            xR += -1 * (int)pixel.cor[RED];
            xG += -1 * (int)pixel.cor[GREEN];
            xB += -1 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaS, h, w - 1);
            xR += 2 * (int)pixel.cor[RED];
            xG += 2 * (int)pixel.cor[GREEN];
            xB += 2 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaS, h, w);
            xR += 0 * (int)pixel.cor[RED];
            xG += 0 * (int)pixel.cor[GREEN];
            xB += 0 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaS, h, w - 1);
            xR += -2 * (int)pixel.cor[RED];
            xG += -2 * (int)pixel.cor[GREEN];
            xB += -2 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaS, h+1, w-1);
            xR += 1 * (int)pixel.cor[RED];
            xG += 1 * (int)pixel.cor[GREEN];
            xB += 1 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaS, h+1, w);
            xR += 0 * (int)pixel.cor[RED];
            xG += 0 * (int)pixel.cor[GREEN];
            xB += 0 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaS, h+1, w +1);
            xR += -1 * (int)pixel.cor[RED];
            xG += -1 * (int)pixel.cor[GREEN];
            xB += -1 * (int)pixel.cor[BLUE];

            //matriz em GY
            pixel = obtemPixel(copiaS, h-1, w-1);
            yR = 1 * (int)pixel.cor[RED];
            yG = 1 * (int)pixel.cor[GREEN];
            yB = 1 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaS, h-1, w);
            yR += 2 * (int)pixel.cor[RED];
            yG += 2 * (int)pixel.cor[GREEN];
            yB += 2 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaS, h-1, w +1);
            yR += 1 * (int)pixel.cor[RED];
            yG += 1 * (int)pixel.cor[GREEN];
            yB += 1 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaS, h, w - 1);
            yR += 0 * (int)pixel.cor[RED];
            yG += 0 * (int)pixel.cor[GREEN];
            yB += 0 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaS, h, w);
            yR += 0 * (int)pixel.cor[RED];
            yG += 0 * (int)pixel.cor[GREEN];
            yB += 0 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaS, h, w - 1);
            yR += 0 * (int)pixel.cor[RED];
            yG += 0 * (int)pixel.cor[GREEN];
            yB += 0 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaS, h+1, w-1);
            yR += -1 * (int)pixel.cor[RED];
            yG += -1 * (int)pixel.cor[GREEN];
            yB += -1 * (int)pixel.cor[BLUE];


            pixel = obtemPixel(copiaS, h+1, w);
            yR += -2 * (int)pixel.cor[RED];
            yG += -2 * (int)pixel.cor[GREEN];
            yB += -2 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaS, h+1, w +1);
            yR += -1 * (int)pixel.cor[RED];
            yG += -1 * (int)pixel.cor[GREEN];
            yB += -1 * (int)pixel.cor[BLUE];

            mR = sqrt(pow(xR,2)+ pow(yR,2));
            mG = sqrt(pow(xG,2)+ pow(yG,2));
            mB = sqrt(pow(xB,2)+ pow(yB,2));

            //verifica a cor vermelha
            if(mR > 255){
                pixel.cor[RED] = 255;
            }
            else{
                if(mR < 0){
                    pixel.cor[RED] = 0;
                }
                else{
                    pixel.cor[RED] = mR;
                }
            }
            //verifica a cor verde
            if(mG > 255){
                pixel.cor[GREEN] = 255;
            }
            else{
                if(mG < 0){
                    pixel.cor[GREEN] = 0;
                }
                else{
                    pixel.cor[GREEN] = mG;
                }
            }
            //verifica a cor azul
            if(mB > 255){
                pixel.cor[BLUE] = 255;
            }
            else{
                if(mB < 0){
                    pixel.cor[BLUE] = 0;
                }
                else{
                    pixel.cor[BLUE] = mB;
                }
            }

            recolorePixel(img, h , w , pixel);
        }
    }

    liberaImagem(copiaS);


    /* Dicas:
     * 1) Se quiser, pode ignorar as bordas das imagens
     * 2) Para o pixel na posição (h, w), obtenha os outros 8 pixels vizinhos e aplique a matriz gx e gy
     *    em cada banda de cor do pixel. Combine o valor obtido por gx e gy e modifique o pixel de img.
     *    Lembre-se que a obtenção dos pixels deve ser a partir de uma cópia da imagem.
     * 3) Verifique se o novo valor obtido para a banda de cor é um valor válido (entre 0 e 255).
    */
}

/* Função responsável por aplicar a detecçõa de bordas de Laplace na imagem.
 * Leia o pdf do EP para obter mais informações de como o filtro é implementado.
 */
void deteccaoBordasLaplace(Imagem *img) {
    int xR = 0,xG = 0,xB = 0;
    int  mR, mG,mB, h, w;
    Imagem *copiaBL = copiaImagem(img); // definindo ponteiro do tipo imagem

    for (h = 1; h < obtemAltura(copiaBL) - 1; h++){
        for (w = 1; w < obtemLargura(copiaBL) - 1; w++){
            Pixel pixel = obtemPixel(copiaBL, h-1, w-1);
            xR = 0 * (int)pixel.cor[RED];
            xG = 0 * (int)pixel.cor[GREEN];
            xB = 0 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaBL, h-1, w);
            xR += -1 * (int)pixel.cor[RED];
            xG += -1 * (int)pixel.cor[GREEN];
            xB += -1 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaBL, h-1, w +1);
            xR += 0 * (int)pixel.cor[RED];
            xG += 0 * (int)pixel.cor[GREEN];
            xB += 0 * (int)pixel.cor[BLUE];


            pixel = obtemPixel(copiaBL, h, w - 1);
            xR += -1 * (int)pixel.cor[RED];
            xG += -1 * (int)pixel.cor[GREEN];
            xB += -1 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaBL, h, w);
            xR += 4 * (int)pixel.cor[RED];
            xG += 4 * (int)pixel.cor[GREEN];
            xB += 4 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaBL, h, w - 1);
            xR += -1 * (int)pixel.cor[RED];
            xG += -1 * (int)pixel.cor[GREEN];
            xB += -1 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaBL, h+1, w-1);
            xR += 0 * (int)pixel.cor[RED];
            xG += 0 * (int)pixel.cor[GREEN];
            xB += 0 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaBL, h+1, w);
            xR += -1 * (int)pixel.cor[RED];
            xG += -1 * (int)pixel.cor[GREEN];
            xB += -1 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaBL, h+1, w +1);
            xR += 0 * (int)pixel.cor[RED];
            xG += 0 * (int)pixel.cor[GREEN];
            xB += 0 * (int)pixel.cor[BLUE];

            //verifica a cor vermelha
            if(xR > 255){
                pixel.cor[RED] = 255;
            }
            else{
                if(xR < 0){
                    pixel.cor[RED] = 0;
                }
                else{
                    pixel.cor[RED] = xR;
                }
            }
            //verifica a cor verde
            if(xG > 255){
                pixel.cor[GREEN] = 255;
            }
            else{
                if(xG < 0){
                    pixel.cor[GREEN] = 0;
                }
                else{
                    pixel.cor[GREEN] = xG;
                }
            }
            //verifica a cor azul
            if(xB > 255){
                pixel.cor[BLUE] = 255;
            }
            else{
                if(xB < 0){
                    pixel.cor[BLUE] = 0;
                }
                else{
                    pixel.cor[BLUE] = xB;
                }
            }

            recolorePixel(img, h , w , pixel);
        }
    }

    liberaImagem(copiaBL);
    /* Siga as mesmas dicas do filtro de Sobel */
}

/* Função responsável por aplicar na imagem o filtro definido por você. Seja criativo!
 * Filtros que apenas fazem algumas modificações simples em cada pixel
 * (por exemplo, negativo, espelhar a imagem) não serão considerados.
 */


void meuFiltro(Imagem *img){
    Imagem *copiaM = copiaImagem(img);
    int xR = 0,xG = 0,xB = 0;
    int  mR, mG,mB, h, w;

    for (h = 1; h < obtemAltura(copiaM) - 1; h++){
        for (w = 1; w < obtemLargura(copiaM) - 1; w++){
            Pixel pixel = obtemPixel(copiaM, h-1, w-1);
            xR = 0 * (int)pixel.cor[RED];
            xG = 0* (int)pixel.cor[GREEN];
            xB = 0* (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaM, h-1, w);
            xR += -1 * (int)pixel.cor[RED];
            xG += -1 * (int)pixel.cor[GREEN];
            xB += -1 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaM, h-1, w +1);
            xR += 0 * (int)pixel.cor[RED];
            xG += 0 * (int)pixel.cor[GREEN];
            xB += 0 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaM, h, w - 1);
            xR += -1 * (int)pixel.cor[RED];
            xG += -1 * (int)pixel.cor[GREEN];
            xB += -1 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaM, h, w);
            xR += 5 * (int)pixel.cor[RED];
            xG += 5 * (int)pixel.cor[GREEN];
            xB += 5 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaM, h, w - 1);
            xR += -1 * (int)pixel.cor[RED];
            xG += -1 * (int)pixel.cor[GREEN];
            xB += -1 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaM, h+1, w-1);
            xR += 0 * (int)pixel.cor[RED];
            xG += 0 * (int)pixel.cor[GREEN];
            xB += 0 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaM, h+1, w);
            xR += -1 * (int)pixel.cor[RED];
            xG += -1 * (int)pixel.cor[GREEN];
            xB += -1 * (int)pixel.cor[BLUE];

            pixel = obtemPixel(copiaM, h+1, w +1);
            xR += 0 * (int)pixel.cor[RED];
            xG += 0 * (int)pixel.cor[GREEN];
            xB += 0 * (int)pixel.cor[BLUE];
            //verifica a cor vermelha
            if(xR > 255){
                pixel.cor[RED] = 255;
            }
            else{
                if(xR < 0){
                    pixel.cor[RED] = 0;
                }
                else{
                    pixel.cor[RED] = xR;
                }
            }
            //verifica a cor verde
            if(xG > 255){
                pixel.cor[GREEN] = 255;
            }
            else{
                if(xG < 0){
                    pixel.cor[GREEN] = 0;
                }
                else{
                    pixel.cor[GREEN] = xG;
                }
            }
            //verifica a cor azul
            if(xB > 255){
                pixel.cor[BLUE] = 255;
            }
            else{
                if(xB < 0){
                    pixel.cor[BLUE] = 0;
                }
                else{
                    pixel.cor[BLUE] = xB;
                }
            }

            recolorePixel(img, h , w , pixel);
        }
    }

    liberaImagem(copiaM);
}
