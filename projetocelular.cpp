#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"
#include "ranking.h"

main()
{
    /*
    MAPA DAS TELAS:
    1 - PRINCIPAL
    2 - MENU
    3 - INICIO
    4 - TECLADO
    5 - START
    6 - PERDEU
    7 - GANHOU
    8 - RANKING
    9 - WINNER
    10 - SAIR DO JOGO
    */

    int tela=1, mapa=0, aux=0, fase = 0, idCor = 0, sequencia = 0;
    int tamanhoNome = 0;
    int corSorteada[15], somaCliques = 0, totalGeral = 0;
    int i,x = 0;
    fila f1, f2;
    listaRanking L;
    jogada j;
    j.record=0;
    memoria jogo[8] = {1,"vermelho.jpg",
                       2,"azul.jpg",
                       3,"amarelo.jpg",
                       4,"marrom.jpg",
                       5,"cinza.jpg",
                       6,"ciano.jpg",
                       7,"magenta.jpg",
                       8,"verde.jpg"};

    char nomeJogador[11] = {"\0"}, pontos[10] = {"0"};
    initwindow (400,700,"Programando um Jogo",500,0);

    readimagefile("principal.jpg",0,0,400,700);

    criarFila(&f1);
    criarFila(&f2);
    criarLista(&L);

    srand(time(NULL));
    for (i = 0;i<15;i++)
        {
            x = rand()%8;
            corSorteada[i] = jogo[x].id;
            inserirNaFila(&f1,corSorteada[i]);
            //printf("%d\n",corSorteada[i]);
            //printf("==============");

        }
        //imprimirFila(f1);

    do
    {
        //printf("\nx - %d  y - %d", mousex(), mousey());
        Sleep(200);

        //PEGA CLIQUE DO BOTÃO PARA ACESSAR O MENU
        if(tela==1 && mousex() > 180 && mousex() < 220 && mousey() > 545 && mousey() < 580 && ismouseclick(WM_LBUTTONDOWN))
        {
            readimagefile("menu.jpg", 0, 0, 400, 700);
            tela=2;
            clearmouseclick(WM_LBUTTONDOWN);
        }
        else if(mousex() > 180 && mousex() < 220 && mousey() > 610 && mousey() < 630 && ismouseclick(WM_LBUTTONDOWN))
        {
            readimagefile("principal.jpg", 0, 0, 400, 700);
            tela=1;
            clearmouseclick(WM_LBUTTONDOWN);
        }
        else if(tela==2 && mousex() > 155 && mousex() < 248 && mousey() > 410 && mousey() < 468 && ismouseclick(WM_LBUTTONDOWN))
        {
            readimagefile("inicio.jpg", 0, 0, 400, 700);
            tela=3;
            clearmouseclick(WM_LBUTTONDOWN);
        }
        else if(tela==3 && mousex() > 60 && mousex() < 340 && mousey() > 355 && mousey() < 420 && ismouseclick(WM_LBUTTONDOWN))
        {
            readimagefile("teclado.jpg", 0, 0, 400, 700);
            tela=4;
            strcpy(nomeJogador,"\0");
            clearmouseclick(WM_LBUTTONDOWN);
        }
        //PROGRAMANDO A FASE 1
        else if(tela==3 && mousex() > 108 && mousex() < 290 && mousey() > 461 && mousey() < 530 && ismouseclick(WM_LBUTTONDOWN))
        {
            readimagefile("mapa1.jpg", 0, 0, 400, 700);
            tela = 11;
            mapa=1;
            clearmouseclick(WM_LBUTTONDOWN);

            if(strcmpi(nomeJogador,"\0")==0){
                strcpy(nomeJogador,"Anônimo");
            }


        }
        if(tela==11 && mousex() > 270 && mousex() < 295 && mousey() > 233 && mousey() < 254 && ismouseclick(WM_LBUTTONDOWN))
        {
            //BOTAO DA PRIMEIRA FASE
            readimagefile("start.jpg", 0, 0, 400, 700);
            fase=1;
            tela=19; mapa=0;
            clearmouseclick(WM_LBUTTONDOWN);
        }
        if(fase==1 && mousex() > 156 && mousex() < 237 && mousey() > 266 && mousey() < 345 && ismouseclick(WM_LBUTTONDOWN))
        {
            fase=0; tela=0; //OPÇÃO DE PARADA DO SORTEIO
            sequencia=1;
            for (i = 0;i<5;i++)
            {
                idCor = corSorteada[i]-1;
                readimagefile(jogo[idCor].nome, 0, 0, 400, 700);
                Sleep(1000);
                readimagefile("telajogo.jpg", 0, 0, 400, 700);
                setbkcolor(15);
                setcolor(0);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                outtextxy(110,510,"1");
                outtextxy(165,123,nomeJogador);
                Sleep(500);
                printf("\n%d - %s\n",jogo[idCor].id,jogo[idCor].nome);
            }



            clearmouseclick(WM_LBUTTONDOWN);

        }

        /*PEGA O CLIQUE NA COR SORTEADA DA FASE 1
        A CADA CLIQUE CERTO O ITEM É REMOVIDO DA FILA (f1) E INSERIDO NA FILA (f2)
        NO FINAL SÃO REMOVIDOS O RESTANTE DOS ITENS DA FILA (f1) E INSERIDO NA FILA (f2)
        TAMBEM SAO COMPUTADOS OS PONTOS DA FASE*/

        if(sequencia==1){
                //VERMELHO
                if(mousex() > 138 && mousex() < 190 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor= 1;
                    if(verificaSequencia(f1,1)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        totalGeral += 1;
                        somaCliques+=1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERMELHO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=5;
                    }
                }
                //CIANO
                if(mousex() > 199 && mousex() < 255 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 6;
                    if(verificaSequencia(f1,6)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        totalGeral += 1;
                        somaCliques+=1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CIANO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=5;
                    }

                }
                //MAGENTA
                if(mousex() > 266 && mousex() < 309 && mousey() > 249 && mousey() < 301 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 7;
                    if(verificaSequencia(f1,7)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        totalGeral += 1;
                        somaCliques+=1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MAGENTA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=5;
                    }

                }
                //VERDE
                if(mousex() > 259 && mousex() < 316 && mousey() > 310 && mousey() < 366 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 8;
                    if(verificaSequencia(f1,8)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        totalGeral += 1;
                        somaCliques+=1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERDE",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=5;
                    }

                }
                //AMARELO
                if(mousex() > 200 && mousex() < 249 && mousey() > 364 && mousey() < 418 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 3;
                    if(verificaSequencia(f1,3)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        totalGeral += 1;
                        somaCliques+=1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AMARELO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=5;
                    }

                }
                //CINZA
                if(mousex() > 134 && mousex() < 191 && mousey() > 358 && mousey() < 420 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 5;
                    if(verificaSequencia(f1,5)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        totalGeral += 1;
                        somaCliques+=1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CINZA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=5;
                    }

                }
                //MARROM
                if(mousex() > 72 && mousex() < 124 && mousey() > 308 && mousey() < 361 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 4;
                    if(verificaSequencia(f1,4)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        totalGeral += 1;
                        somaCliques+=1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MARROM",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=5;
                    }


                }
                //AZUL
                if(mousex() > 81 && mousex() < 129 && mousey() > 236 && mousey() < 302 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 2;
                    if(verificaSequencia(f1,idCor)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        totalGeral += 1;
                        somaCliques+=1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AZUL",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=5;
                    }

                }

                if(somaCliques == 5){
                    sequencia=0;

                    //totalPontosFase[0] = totalGeral*2;
                    totalGeral+= somaCliques*2;
                    somaCliques = 0;

                    //if(totalPontosFase[0]==10){
                    if(totalGeral==15){
                        readimagefile("passou.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        //printf("total geral %d", totalGeral);
                        tela = 12;
                        mapa=0;
                    }else{
                        readimagefile("perdeu.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);

                        tela=6;
                        if(totalGeral==0){
                            settextstyle(DEFAULT_FONT, 0, 7);
                            outtextxy(170,335,pontos);
                        }
                    }

                    for(i=1;i<totalGeral+1;i++){
                        itoa(i,pontos,10);
                        Sleep(5);
                        settextstyle(DEFAULT_FONT, 0, 7);
                        outtextxy(150,325,pontos);
                    }

                    while(!isEmpty(f1))
                    {
                        removerDaFila(&f1,&idCor);
                        //printf("\nremovido: %d\n",idCor);
                        inserirNaFila(&f2,idCor);
                    }
                    //printf("\n\nDADOS NA FILA 1 ABAIXO");
                    //imprimirFila(f1);
                    //printf("\n\nDADOS NA FILA 2 ABAIXO");
                    //imprimirFila(f2);
                }

        }
        //PROGRAMANDO A FASE 2
        if(tela==12 && mousex() > 51 && mousex() < 346 && mousey() > 434 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN)){
            readimagefile("mapa2.jpg", 0, 0, 400, 700);
            mapa=2;
        }
        if(mapa==2 && mousex() > 270 && mousex() < 295 && mousey() > 455 && mousey() < 475 && ismouseclick(WM_LBUTTONDOWN))
        {
            readimagefile("start.jpg", 0, 0, 400, 700);
            tela=5; mapa=0;
            fase=2;
        }
        if(fase==2 && mousex() > 156 && mousex() < 237 && mousey() > 266 && mousey() < 345 && ismouseclick(WM_LBUTTONDOWN))
        {
            fase=0; tela=0; //OPÇÃO DE PARADA DO SORTEIO
            sequencia=2;
            printf("\n\n====Fase 2=====\n");
            for (i = 0;i<6;i++)
            {
                idCor = corSorteada[i]-1;
                readimagefile(jogo[idCor].nome, 0, 0, 400, 700);
                Sleep(1000);
                readimagefile("telajogo.jpg", 0, 0, 400, 700);
                setbkcolor(15);
                setcolor(0);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                outtextxy(110,510,"2");
                outtextxy(250,510,pontos);
                outtextxy(165,123,nomeJogador);
                Sleep(500);
                printf("\n%d - %s\n",jogo[idCor].id,jogo[idCor].nome);
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }

        /*PEGA O CLIQUE NA COR SORTEADA DA FASE 1
        A CADA CLIQUE CERTO O ITEM É REMOVIDO DA FILA (f1) E INSERIDO NA FILA (f2)
        NO FINAL SÃO REMOVIDOS O RESTANTE DOS ITENS DA FILA (f1) E INSERIDO NA FILA (f2)
        TAMBEM SAO COMPUTADOS OS PONTOS DA FASE*/

        if(sequencia==2){
                //VERMELHO
                if(mousex() > 138 && mousex() < 190 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor= 1;
                    if(verificaSequencia(f2,1)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERMELHO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=6;
                    }
                }
                //CIANO
                if(mousex() > 199 && mousex() < 255 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 6;
                    if(verificaSequencia(f2,6)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CIANO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=6;
                    }

                }
                //MAGENTA
                if(mousex() > 266 && mousex() < 309 && mousey() > 249 && mousey() < 301 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 7;
                    if(verificaSequencia(f2,7)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MAGENTA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=6;
                    }

                }
                //VERDE
                if(mousex() > 259 && mousex() < 316 && mousey() > 310 && mousey() < 366 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 8;
                    if(verificaSequencia(f2,8)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERDE",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=6;
                    }

                }
                //AMARELO
                if(mousex() > 200 && mousex() < 249 && mousey() > 364 && mousey() < 418 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 3;
                    if(verificaSequencia(f2,3)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AMARELO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=6;
                    }

                }
                //CINZA
                if(mousex() > 134 && mousex() < 191 && mousey() > 358 && mousey() < 420 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 5;
                    if(verificaSequencia(f2,5)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CINZA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=6;
                    }

                }
                //MARROM
                if(mousex() > 72 && mousex() < 124 && mousey() > 308 && mousey() < 361 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 4;
                    if(verificaSequencia(f2,4)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MARROM",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=6;
                    }


                }
                //AZUL
                if(mousex() > 81 && mousex() < 129 && mousey() > 236 && mousey() < 302 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 2;
                    if(verificaSequencia(f2,idCor)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AZUL",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=6;
                    }

                }

                if(somaCliques == 6){
                    sequencia=0;

                    //totalPontosFase[1] = totalGeral*2;
                    totalGeral+= somaCliques*2;
                    somaCliques = 0;

                    if(totalGeral==33){
                        readimagefile("passou.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        //printf("total geral %d", totalGeral);
                        tela=13;
                        mapa=0;
                    }else{
                        readimagefile("perdeu.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        tela=6;
                    }

                    for(i=1;i<totalGeral+1;i++){
                        itoa(i,pontos,10);
                        Sleep(5);
                        settextstyle(DEFAULT_FONT, 0, 7);
                        outtextxy(140,325,pontos);
                    }

                    while(!isEmpty(f2))
                    {
                        removerDaFila(&f2,&idCor);
                        //printf("\nremovido: %d\n",idCor);
                        inserirNaFila(&f1,idCor);
                    }
                    //printf("\n\nDADOS NA FILA 1 ABAIXO");
                    //imprimirFila(f1);
                    //printf("\n\nDADOS NA FILA 2 ABAIXO");
                    //imprimirFila(f2);
                }

        }

        //PROGRAMANDO A FASE 3
        if(tela==13 && mousex() > 51 && mousex() < 346 && mousey() > 434 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN)){
            readimagefile("mapa3.jpg", 0, 0, 400, 700);
            mapa=3;

        }
        if(mapa==3 && mousex() > 187 && mousex() < 212 && mousey() > 455 && mousey() < 475 && ismouseclick(WM_LBUTTONDOWN))
        {
            readimagefile("start.jpg", 0, 0, 400, 700);
            tela=5; mapa=0;
            fase=3;
        }
        if(fase==3 && mousex() > 156 && mousex() < 237 && mousey() > 266 && mousey() < 345 && ismouseclick(WM_LBUTTONDOWN))
        {
            fase=0; tela=0; //OPÇÃO DE PARADA DO SORTEIO
            sequencia=3;
            printf("\n====Fase 3=====\n");
            for (i = 0;i<7;i++)
            {
                idCor = corSorteada[i]-1;
                readimagefile(jogo[idCor].nome, 0, 0, 400, 700);
                Sleep(1000);
                readimagefile("telajogo.jpg", 0, 0, 400, 700);
                setbkcolor(15);
                setcolor(0);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                outtextxy(110,510,"3");
                outtextxy(250,510,pontos);
                outtextxy(165,123,nomeJogador);
                Sleep(500);
                printf("\n%d - %s\n",jogo[idCor].id,jogo[idCor].nome);
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }

        /*PEGA O CLIQUE NA COR SORTEADA DA FASE 1
        A CADA CLIQUE CERTO O ITEM É REMOVIDO DA FILA (f1) E INSERIDO NA FILA (f2)
        NO FINAL SÃO REMOVIDOS O RESTANTE DOS ITENS DA FILA (f1) E INSERIDO NA FILA (f2)
        TAMBEM SAO COMPUTADOS OS PONTOS DA FASE*/

        if(sequencia==3){
                //VERMELHO
                if(mousex() > 138 && mousex() < 190 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor= 1;
                    if(verificaSequencia(f1,1)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERMELHO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=7;
                    }
                }
                //CIANO
                if(mousex() > 199 && mousex() < 255 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 6;
                    if(verificaSequencia(f1,6)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CIANO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=7;
                    }

                }
                //MAGENTA
                if(mousex() > 266 && mousex() < 309 && mousey() > 249 && mousey() < 301 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 7;
                    if(verificaSequencia(f1,7)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MAGENTA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=7;
                    }

                }
                //VERDE
                if(mousex() > 259 && mousex() < 316 && mousey() > 310 && mousey() < 366 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 8;
                    if(verificaSequencia(f1,8)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERDE",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=7;
                    }

                }
                //AMARELO
                if(mousex() > 200 && mousex() < 249 && mousey() > 364 && mousey() < 418 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 3;
                    if(verificaSequencia(f1,3)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AMARELO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=7;
                    }

                }
                //CINZA
                if(mousex() > 134 && mousex() < 191 && mousey() > 358 && mousey() < 420 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 5;
                    if(verificaSequencia(f1,5)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CINZA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=7;
                    }

                }
                //MARROM
                if(mousex() > 72 && mousex() < 124 && mousey() > 308 && mousey() < 361 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 4;
                    if(verificaSequencia(f1,4)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MARROM",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=7;
                    }


                }
                //AZUL
                if(mousex() > 81 && mousex() < 129 && mousey() > 236 && mousey() < 302 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 2;
                    if(verificaSequencia(f1,idCor)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AZUL",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=7;
                    }

                }

                if(somaCliques == 7){
                    sequencia=0;

                    //totalPontosFase[2] = totalGeral*2;
                    totalGeral+= somaCliques*2;
                    somaCliques = 0;

                    if(totalGeral==54){
                        readimagefile("passou.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        //printf("total geral %d", totalGeral);
                        tela=14;
                        mapa=0;
                    }else{
                        readimagefile("perdeu.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        tela=6;
                    }

                    for(i=1;i<totalGeral+1;i++){
                        itoa(i,pontos,10);
                        Sleep(5);
                        settextstyle(DEFAULT_FONT, 0, 7);
                        outtextxy(140,325,pontos);
                    }

                    while(!isEmpty(f1))
                    {
                        removerDaFila(&f1,&idCor);
                        //printf("\nremovido: %d\n",idCor);
                        inserirNaFila(&f2,idCor);
                    }
                    //printf("\n\nDADOS NA FILA 1 ABAIXO");
                    //imprimirFila(f1);
                    //printf("\n\nDADOS NA FILA 2 ABAIXO");
                    //imprimirFila(f2);
                }

        }

        //PROGRAMANDO A FASE 4
        if(tela==14 && mousex() > 51 && mousex() < 346 && mousey() > 434 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN)){
            readimagefile("mapa4.jpg", 0, 0, 400, 700);
            mapa = 4;

        }
        if(mapa==4 && mousex() > 187 && mousex() < 212 && mousey() > 528 && mousey() < 551 && ismouseclick(WM_LBUTTONDOWN))
        {
            readimagefile("start.jpg", 0, 0, 400, 700);
            tela=5; mapa=0;
            fase=4;
        }
        if(fase==4 && mousex() > 156 && mousex() < 237 && mousey() > 266 && mousey() < 345 && ismouseclick(WM_LBUTTONDOWN))
        {
            fase=0; tela=0; //OPÇÃO DE PARADA DO SORTEIO
            sequencia=4;
            printf("\n====Fase 4=====\n");
            for (i = 0;i<8;i++)
            {
                idCor = corSorteada[i]-1;
                readimagefile(jogo[idCor].nome, 0, 0, 400, 700);
                Sleep(1000);
                readimagefile("telajogo.jpg", 0, 0, 400, 700);
                setbkcolor(15);
                setcolor(0);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                outtextxy(110,510,"4");
                outtextxy(250,510,pontos);
                outtextxy(165,123,nomeJogador);
                Sleep(500);
                printf("\n%d - %s\n",jogo[idCor].id,jogo[idCor].nome);
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }

        /*PEGA O CLIQUE NA COR SORTEADA DA FASE 1
        A CADA CLIQUE CERTO O ITEM É REMOVIDO DA FILA (f1) E INSERIDO NA FILA (f2)
        NO FINAL SÃO REMOVIDOS O RESTANTE DOS ITENS DA FILA (f1) E INSERIDO NA FILA (f2)
        TAMBEM SAO COMPUTADOS OS PONTOS DA FASE*/

        if(sequencia==4){
                //VERMELHO
                if(mousex() > 138 && mousex() < 190 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor= 1;
                    if(verificaSequencia(f2,1)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERMELHO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=8;
                    }
                }
                //CIANO
                if(mousex() > 199 && mousex() < 255 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 6;
                    if(verificaSequencia(f2,6)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CIANO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=8;
                    }

                }
                //MAGENTA
                if(mousex() > 266 && mousex() < 309 && mousey() > 249 && mousey() < 301 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 7;
                    if(verificaSequencia(f2,7)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MAGENTA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=8;
                    }

                }
                //VERDE
                if(mousex() > 259 && mousex() < 316 && mousey() > 310 && mousey() < 366 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 8;
                    if(verificaSequencia(f2,8)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERDE",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=8;
                    }

                }
                //AMARELO
                if(mousex() > 200 && mousex() < 249 && mousey() > 364 && mousey() < 418 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 3;
                    if(verificaSequencia(f2,3)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AMARELO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=8;
                    }

                }
                //CINZA
                if(mousex() > 134 && mousex() < 191 && mousey() > 358 && mousey() < 420 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 5;
                    if(verificaSequencia(f2,5)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CINZA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=8;
                    }

                }
                //MARROM
                if(mousex() > 72 && mousex() < 124 && mousey() > 308 && mousey() < 361 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 4;
                    if(verificaSequencia(f2,4)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MARROM",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=8;
                    }


                }
                //AZUL
                if(mousex() > 81 && mousex() < 129 && mousey() > 236 && mousey() < 302 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 2;
                    if(verificaSequencia(f2,idCor)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AZUL",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=8;
                    }

                }

                if(somaCliques == 8){
                    sequencia=0;

                    //totalPontosFase[3] = totalGeral*2;
                    totalGeral+= somaCliques*2;
                    somaCliques = 0;

                    if(totalGeral==78){
                        readimagefile("passou.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        //printf("total geral %d", totalGeral);
                        tela=15;
                        mapa=0;
                    }else{
                        readimagefile("perdeu.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        tela=6;
                    }

                    for(i=1;i<totalGeral+1;i++){
                        itoa(i,pontos,10);
                        Sleep(5);
                        settextstyle(DEFAULT_FONT, 0, 7);
                        outtextxy(140,325,pontos);
                    }

                    while(!isEmpty(f2))
                    {
                        removerDaFila(&f2,&idCor);
                        //printf("\nremovido: %d\n",idCor);
                        inserirNaFila(&f1,idCor);
                    }
                    //printf("\n\nDADOS NA FILA 1 ABAIXO");
                    //imprimirFila(f1);
                    //printf("\n\nDADOS NA FILA 2 ABAIXO");
                    //imprimirFila(f2);
                }

        }

        //PROGRAMNDO A FASE 5
        if(tela==15 && mousex() > 51 && mousex() < 346 && mousey() > 434 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN)){
            readimagefile("mapa5.jpg", 0, 0, 400, 700);
            mapa = 5;

        }
        if(mapa==5 && mousex() > 20 && mousex() < 45 && mousey() > 455 && mousey() < 475 && ismouseclick(WM_LBUTTONDOWN))
        {
            readimagefile("start.jpg", 0, 0, 400, 700);
            tela=5; mapa=0;
            fase = 5;
        }
        if(fase==5 && mousex() > 156 && mousex() < 237 && mousey() > 266 && mousey() < 345 && ismouseclick(WM_LBUTTONDOWN))
        {
            fase=0; tela=0; //OPÇÃO DE PARADA DO SORTEIO
            sequencia=5;
            printf("\n====Fase 5=====\n");
            for (i = 0;i<9;i++)
            {
                idCor = corSorteada[i]-1;
                readimagefile(jogo[idCor].nome, 0, 0, 400, 700);
                Sleep(1000);
                readimagefile("telajogo.jpg", 0, 0, 400, 700);
                setbkcolor(15);
                setcolor(0);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                outtextxy(110,510,"5");
                outtextxy(250,510,pontos);
                outtextxy(165,123,nomeJogador);
                Sleep(500);
                printf("\n%d - %s\n",jogo[idCor].id,jogo[idCor].nome);
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }

        /*PEGA O CLIQUE NA COR SORTEADA DA FASE 1
        A CADA CLIQUE CERTO O ITEM É REMOVIDO DA FILA (f1) E INSERIDO NA FILA (f2)
        NO FINAL SÃO REMOVIDOS O RESTANTE DOS ITENS DA FILA (f1) E INSERIDO NA FILA (f2)
        TAMBEM SAO COMPUTADOS OS PONTOS DA FASE*/

        if(sequencia==5){
                //VERMELHO
                if(mousex() > 138 && mousex() < 190 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor= 1;
                    if(verificaSequencia(f1,1)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERMELHO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=9;
                    }
                }
                //CIANO
                if(mousex() > 199 && mousex() < 255 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 6;
                    if(verificaSequencia(f1,6)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CIANO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=9;
                    }

                }
                //MAGENTA
                if(mousex() > 266 && mousex() < 309 && mousey() > 249 && mousey() < 301 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 7;
                    if(verificaSequencia(f1,7)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MAGENTA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=9;
                    }

                }
                //VERDE
                if(mousex() > 259 && mousex() < 316 && mousey() > 310 && mousey() < 366 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 8;
                    if(verificaSequencia(f1,8)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERDE",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=9;
                    }

                }
                //AMARELO
                if(mousex() > 200 && mousex() < 249 && mousey() > 364 && mousey() < 418 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 3;
                    if(verificaSequencia(f1,3)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AMARELO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=9;
                    }

                }
                //CINZA
                if(mousex() > 134 && mousex() < 191 && mousey() > 358 && mousey() < 420 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 5;
                    if(verificaSequencia(f1,5)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CINZA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=9;
                    }

                }
                //MARROM
                if(mousex() > 72 && mousex() < 124 && mousey() > 308 && mousey() < 361 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 4;
                    if(verificaSequencia(f1,4)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MARROM",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=9;
                    }


                }
                //AZUL
                if(mousex() > 81 && mousex() < 129 && mousey() > 236 && mousey() < 302 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 2;
                    if(verificaSequencia(f1,idCor)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AZUL",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=9;
                    }

                }

                if(somaCliques == 9){
                    sequencia=0;

                    //totalPontosFase[4] = totalGeral*2;

                    totalGeral+= somaCliques*2;
                    somaCliques = 0;

                    if(totalGeral==105){
                        readimagefile("passou.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        //printf("total geral %d", totalGeral);
                        tela=16;
                        mapa=0;
                    }else{
                        readimagefile("perdeu.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        tela=6;
                    }

                    for(i=1;i<totalGeral+1;i++){
                        itoa(i,pontos,10);
                        Sleep(5);
                        settextstyle(DEFAULT_FONT, 0, 7);
                        outtextxy(110,325,pontos);
                    }

                    while(!isEmpty(f1))
                    {
                        removerDaFila(&f1,&idCor);
                        //printf("\nremovido: %d\n",idCor);
                        inserirNaFila(&f2,idCor);
                    }
                    //printf("\n\nDADOS NA FILA 1 ABAIXO");
                    //imprimirFila(f1);
                    //printf("\n\nDADOS NA FILA 2 ABAIXO");
                    //imprimirFila(f2);
                }

        }

        //PROGRAMNDO A FASE 6
        if(tela==16 && mousex() > 51 && mousex() < 346 && mousey() > 434 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN)){
            readimagefile("mapa6.jpg", 0, 0, 400, 700);
            mapa = 6;

        }
        if(mapa==6 && mousex() > 20 && mousex() < 45 && mousey() > 306 && mousey() < 327 && ismouseclick(WM_LBUTTONDOWN))
        {
            readimagefile("start.jpg", 0, 0, 400, 700);
            tela=5; mapa=0;
            fase=6;
        }
        if(fase==6 && mousex() > 156 && mousex() < 237 && mousey() > 266 && mousey() < 345 && ismouseclick(WM_LBUTTONDOWN))
        {
            fase=0; tela=0; //OPÇÃO DE PARADA DO SORTEIO
            sequencia=6;
            printf("\n====Fase 6=====\n");
            for (i = 0;i<10;i++)
            {
                idCor = corSorteada[i]-1;
                readimagefile(jogo[idCor].nome, 0, 0, 400, 700);
                Sleep(1000);
                readimagefile("telajogo.jpg", 0, 0, 400, 700);
                setbkcolor(15);
                setcolor(0);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                outtextxy(110,510,"6");
                outtextxy(250,510,pontos);
                outtextxy(165,123,nomeJogador);
                Sleep(500);
                printf("\n%d - %s\n",jogo[idCor].id,jogo[idCor].nome);
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }

        /*PEGA O CLIQUE NA COR SORTEADA DA FASE 1
        A CADA CLIQUE CERTO O ITEM É REMOVIDO DA FILA (f1) E INSERIDO NA FILA (f2)
        NO FINAL SÃO REMOVIDOS O RESTANTE DOS ITENS DA FILA (f1) E INSERIDO NA FILA (f2)
        TAMBEM SAO COMPUTADOS OS PONTOS DA FASE*/

        if(sequencia==6){
                //VERMELHO
                if(mousex() > 138 && mousex() < 190 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor= 1;
                    if(verificaSequencia(f2,1)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERMELHO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=10;
                    }
                }
                //CIANO
                if(mousex() > 199 && mousex() < 255 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 6;
                    if(verificaSequencia(f2,6)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CIANO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=10;
                    }

                }
                //MAGENTA
                if(mousex() > 266 && mousex() < 309 && mousey() > 249 && mousey() < 301 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 7;
                    if(verificaSequencia(f2,7)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MAGENTA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=10;
                    }

                }
                //VERDE
                if(mousex() > 259 && mousex() < 316 && mousey() > 310 && mousey() < 366 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 8;
                    if(verificaSequencia(f2,8)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERDE",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=10;
                    }

                }
                //AMARELO
                if(mousex() > 200 && mousex() < 249 && mousey() > 364 && mousey() < 418 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 3;
                    if(verificaSequencia(f2,3)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AMARELO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=10;
                    }

                }
                //CINZA
                if(mousex() > 134 && mousex() < 191 && mousey() > 358 && mousey() < 420 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 5;
                    if(verificaSequencia(f2,5)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CINZA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=10;
                    }

                }
                //MARROM
                if(mousex() > 72 && mousex() < 124 && mousey() > 308 && mousey() < 361 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 4;
                    if(verificaSequencia(f2,4)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MARROM",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=10;
                    }


                }
                //AZUL
                if(mousex() > 81 && mousex() < 129 && mousey() > 236 && mousey() < 302 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 2;
                    if(verificaSequencia(f2,idCor)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AZUL",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=10;
                    }

                }

                if(somaCliques == 10){
                    sequencia=0;

                    //totalPontosFase[5] = totalGeral*2;
                    totalGeral+= somaCliques*2;
                    somaCliques = 0;

                    if(totalGeral==135){
                        readimagefile("passou.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        //printf("total geral %d", totalGeral);
                        tela=17;
                        mapa=0;
                    }else{
                        readimagefile("perdeu.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        tela=6;
                    }

                    for(i=1;i<totalGeral+1;i++){
                        itoa(i,pontos,10);
                        Sleep(5);
                        settextstyle(DEFAULT_FONT, 0, 7);
                        outtextxy(110,325,pontos);
                    }

                    while(!isEmpty(f2))
                    {
                        removerDaFila(&f2,&idCor);
                        //printf("\nremovido: %d\n",idCor);
                        inserirNaFila(&f1,idCor);
                    }
                    //printf("\n\nDADOS NA FILA 1 ABAIXO");
                    //imprimirFila(f1);
                    //printf("\n\nDADOS NA FILA 2 ABAIXO");
                    //imprimirFila(f2);
                }

        }


        //PROGRAMNDO A FASE 7
        if(tela==17 && mousex() > 51 && mousex() < 346 && mousey() > 434 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN)){
            readimagefile("mapa7.jpg", 0, 0, 400, 700);
            mapa = 7;

        }
        if(mapa==7 && mousex() > 20 && mousex() < 45 && mousey() > 234 && mousey() < 253 && ismouseclick(WM_LBUTTONDOWN))
        {
            readimagefile("start.jpg", 0, 0, 400, 700);
            tela=5; mapa=0;
            fase=7;
        }
        if(fase==7 && mousex() > 156 && mousex() < 237 && mousey() > 266 && mousey() < 345 && ismouseclick(WM_LBUTTONDOWN))
        {
            fase=0; tela=0; //OPÇÃO DE PARADA DO SORTEIO
            sequencia=7;
            printf("\n====Fase 7=====\n");
            for (i = 0;i<11;i++)
            {
                idCor = corSorteada[i]-1;
                readimagefile(jogo[idCor].nome, 0, 0, 400, 700);
                Sleep(1000);
                readimagefile("telajogo.jpg", 0, 0, 400, 700);
                setbkcolor(15);
                setcolor(0);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                outtextxy(110,510,"7");
                outtextxy(250,510,pontos);
                outtextxy(165,123,nomeJogador);
                Sleep(500);
                printf("\n%d - %s\n",jogo[idCor].id,jogo[idCor].nome);
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }

        /*PEGA O CLIQUE NA COR SORTEADA DA FASE 7
        A CADA CLIQUE CERTO O ITEM É REMOVIDO DA FILA (f1) E INSERIDO NA FILA (f2)
        NO FINAL SÃO REMOVIDOS O RESTANTE DOS ITENS DA FILA (f1) E INSERIDO NA FILA (f2)
        TAMBEM SAO COMPUTADOS OS PONTOS DA FASE*/

        if(sequencia==7){
                //VERMELHO
                if(mousex() > 138 && mousex() < 190 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor= 1;
                    if(verificaSequencia(f1,1)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERMELHO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=11;
                    }
                }
                //CIANO
                if(mousex() > 199 && mousex() < 255 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 6;
                    if(verificaSequencia(f1,6)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CIANO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=11;
                    }

                }
                //MAGENTA
                if(mousex() > 266 && mousex() < 309 && mousey() > 249 && mousey() < 301 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 7;
                    if(verificaSequencia(f1,7)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MAGENTA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=11;
                    }

                }
                //VERDE
                if(mousex() > 259 && mousex() < 316 && mousey() > 310 && mousey() < 366 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 8;
                    if(verificaSequencia(f1,8)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERDE",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=11;
                    }

                }
                //AMARELO
                if(mousex() > 200 && mousex() < 249 && mousey() > 364 && mousey() < 418 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 3;
                    if(verificaSequencia(f1,3)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AMARELO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=11;
                    }

                }
                //CINZA
                if(mousex() > 134 && mousex() < 191 && mousey() > 358 && mousey() < 420 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 5;
                    if(verificaSequencia(f1,5)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CINZA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=11;
                    }

                }
                //MARROM
                if(mousex() > 72 && mousex() < 124 && mousey() > 308 && mousey() < 361 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 4;
                    if(verificaSequencia(f1,4)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MARROM",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=11;
                    }


                }
                //AZUL
                if(mousex() > 81 && mousex() < 129 && mousey() > 236 && mousey() < 302 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 2;
                    if(verificaSequencia(f1,idCor)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AZUL",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=11;
                    }

                }

                if(somaCliques == 11){
                    sequencia=0;

                    //totalPontosFase[6] = totalGeral*2;
                    totalGeral+= somaCliques*2;
                    somaCliques = 0;

                    if(totalGeral==168){
                        readimagefile("passou.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        //printf("total geral %d", totalGeral);
                        tela=18;
                        mapa=0;
                    }else{
                        readimagefile("perdeu.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        tela=6;
                    }

                    for(i=1;i<totalGeral+1;i++){
                        itoa(i,pontos,10);
                        //printf("\nint: %d -> char: %s\n",i,pontos);
                        Sleep(5);
                        settextstyle(DEFAULT_FONT, 0, 7);
                        outtextxy(110,325,pontos);
                    }

                    while(!isEmpty(f1))
                    {
                        removerDaFila(&f1,&idCor);
                        //printf("\nremovido: %d\n",idCor);
                        inserirNaFila(&f2,idCor);
                    }
                    //printf("\n\nDADOS NA FILA 1 ABAIXO");
                    //imprimirFila(f1);
                    //printf("\n\nDADOS NA FILA 2 ABAIXO");
                    //imprimirFila(f2);
                }

        }

        //PROGRAMNDO A FASE 8
        if(tela==18 && mousex() > 51 && mousex() < 346 && mousey() > 434 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN)){
            readimagefile("mapa8.jpg", 0, 0, 400, 700);
            mapa = 8;

        }
        if(mapa==8 && mousex() > 20 && mousex() < 45 && mousey() > 160 && mousey() < 180 && ismouseclick(WM_LBUTTONDOWN))
        {
            readimagefile("start.jpg", 0, 0, 400, 700);
            tela=5; mapa=0;
            fase=8;
        }
        if(fase==8 && mousex() > 156 && mousex() < 237 && mousey() > 266 && mousey() < 345 && ismouseclick(WM_LBUTTONDOWN))
        {
            fase=0; tela=0; //OPÇÃO DE PARADA DO SORTEIO
            sequencia=8;
            printf("\n====Fase 8=====\n");
            for (i = 0;i<12;i++)
            {
                idCor = corSorteada[i]-1;
                readimagefile(jogo[idCor].nome, 0, 0, 400, 700);
                Sleep(1000);
                readimagefile("telajogo.jpg", 0, 0, 400, 700);
                setbkcolor(15);
                setcolor(0);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                outtextxy(110,510,"8");
                outtextxy(250,510,pontos);
                outtextxy(165,123,nomeJogador);
                Sleep(500);
                printf("\n%d - %s\n",jogo[idCor].id,jogo[idCor].nome);
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }

        /*PEGA O CLIQUE NA COR SORTEADA DA FASE 8
        A CADA CLIQUE CERTO O ITEM É REMOVIDO DA FILA (f2) E INSERIDO NA FILA (f1)
        NO FINAL SÃO REMOVIDOS O RESTANTE DOS ITENS DA FILA (f2) E INSERIDO NA FILA (f1)
        TAMBEM SAO COMPUTADOS OS PONTOS DA FASE*/

        if(sequencia==8){
                //VERMELHO
                if(mousex() > 138 && mousex() < 190 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor= 1;
                    if(verificaSequencia(f2,1)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERMELHO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=12;
                    }
                }
                //CIANO
                if(mousex() > 199 && mousex() < 255 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 6;
                    if(verificaSequencia(f2,6)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CIANO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=12;
                    }

                }
                //MAGENTA
                if(mousex() > 266 && mousex() < 309 && mousey() > 249 && mousey() < 301 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 7;
                    if(verificaSequencia(f2,7)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MAGENTA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=12;
                    }

                }
                //VERDE
                if(mousex() > 259 && mousex() < 316 && mousey() > 310 && mousey() < 366 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 8;
                    if(verificaSequencia(f2,8)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERDE",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=12;
                    }

                }
                //AMARELO
                if(mousex() > 200 && mousex() < 249 && mousey() > 364 && mousey() < 418 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 3;
                    if(verificaSequencia(f2,3)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AMARELO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=12;
                    }

                }
                //CINZA
                if(mousex() > 134 && mousex() < 191 && mousey() > 358 && mousey() < 420 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 5;
                    if(verificaSequencia(f2,5)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CINZA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=12;
                    }

                }
                //MARROM
                if(mousex() > 72 && mousex() < 124 && mousey() > 308 && mousey() < 361 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 4;
                    if(verificaSequencia(f2,4)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MARROM",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=12;
                    }


                }
                //AZUL
                if(mousex() > 81 && mousex() < 129 && mousey() > 236 && mousey() < 302 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 2;
                    if(verificaSequencia(f2,idCor)==1){
                        removerDaFila(&f2,&idCor);
                        inserirNaFila(&f1,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AZUL",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=12;
                    }

                }

                if(somaCliques == 12){
                    sequencia=0;
                    totalGeral+= somaCliques*2;
                    somaCliques = 0;

                    if(totalGeral==204){
                        readimagefile("final.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        //printf("total geral %d", totalGeral);
                        tela=7;//TELA Q MOSTRA QUANDO VENCE O JOGO
                        mapa=0;
                    }else{
                        readimagefile("perdeu.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        tela=6;
                    }

                    for(i=1;i<totalGeral+1;i++){
                        itoa(i,pontos,10);
                        Sleep(5);
                        settextstyle(DEFAULT_FONT, 0, 7);
                        outtextxy(120,340,pontos);
                    }

                    while(!isEmpty(f2))
                    {
                        removerDaFila(&f2,&idCor);
                        //printf("\nremovido: %d\n",idCor);
                        inserirNaFila(&f1,idCor);
                    }

                }

        }
        //SE GANHOU E CLICAR EM CONTINUAR EXECUTA ESSE BOTAO
        if(tela==7 && mousex() > 83 && mousex() < 315 && mousey() > 460 && mousey() < 522 && ismouseclick(WM_LBUTTONDOWN)){
            //AQUI COLOCAR A TELA PRA EXIBIR O RANKING
            strcpy(j.nome,nomeJogador);
            j.record=totalGeral;
            inserirNaLista(&L,j);

            if(isEmpty(f1)){
                while(!isEmpty(f2))
                {
                    removerDaFila(&f2,&idCor);
                }
            }else{
                while(!isEmpty(f1))
                {
                    removerDaFila(&f1,&idCor);
                }
            }

            for (i = 0;i<15;i++)
            {
                x = rand()%8;
                corSorteada[i] = jogo[x].id;
                inserirNaFila(&f1,corSorteada[i]);
                //printf("%d\n",corSorteada[i]);
            }

            tela=8;
            readimagefile("ranking.jpg", 0, 0, 400, 700);
            imprimirLista(L);
            strcpy(nomeJogador,"\0");
            strcpy(pontos,"\0");
            totalGeral=0;

        }
        //PROGRAMANDO A FASE BONUS
        if(tela==7 && mousex() > 110 && mousex() < 290 && mousey() > 530 && mousey() < 580 && ismouseclick(WM_LBUTTONDOWN)){
            readimagefile("mapafinal.jpg", 0, 0, 400, 700);
            mapa = 9;
        }
        if(mapa==9 && mousex() > 95 && mousex() < 130 && mousey() > 158 && mousey() < 181 && ismouseclick(WM_LBUTTONDOWN))
        {
            readimagefile("start.jpg", 0, 0, 400, 700);
            tela=5; mapa=0;
            fase=9;
        }
        if(fase==9 && mousex() > 156 && mousex() < 237 && mousey() > 266 && mousey() < 345 && ismouseclick(WM_LBUTTONDOWN))
        {
            fase=0; tela=0; //OPÇÃO DE PARADA DO SORTEIO
            sequencia=9;
            printf("\n====BONUS=====\n");
            for (i = 0;i<15;i++)
            {
                idCor = corSorteada[i]-1;
                readimagefile(jogo[idCor].nome, 0, 0, 400, 700);
                Sleep(1000);
                readimagefile("telajogo.jpg", 0, 0, 400, 700);
                setbkcolor(15);
                setcolor(0);
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                outtextxy(70,510,"Bônus");
                outtextxy(250,510,pontos);
                outtextxy(165,123,nomeJogador);
                Sleep(500);
                printf("\n%d - %s\n",jogo[idCor].id,jogo[idCor].nome);
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }

        /*PEGA O CLIQUE NA COR SORTEADA DA FASE 8
        A CADA CLIQUE CERTO O ITEM É REMOVIDO DA FILA (f2) E INSERIDO NA FILA (f1)
        NO FINAL SÃO REMOVIDOS O RESTANTE DOS ITENS DA FILA (f2) E INSERIDO NA FILA (f1)
        TAMBEM SAO COMPUTADOS OS PONTOS DA FASE*/

        if(sequencia==9){
                //VERMELHO
                if(mousex() > 138 && mousex() < 190 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor= 1;
                    if(verificaSequencia(f1,1)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERMELHO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=15;
                    }
                }
                //CIANO
                if(mousex() > 199 && mousex() < 255 && mousey() > 195 && mousey() < 250 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 6;
                    if(verificaSequencia(f1,6)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CIANO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=15;
                    }

                }
                //MAGENTA
                if(mousex() > 266 && mousex() < 309 && mousey() > 249 && mousey() < 301 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 7;
                    if(verificaSequencia(f1,7)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MAGENTA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=15;
                    }

                }
                //VERDE
                if(mousex() > 259 && mousex() < 316 && mousey() > 310 && mousey() < 366 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 8;
                    if(verificaSequencia(f1,8)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d VERDE",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=15;
                    }

                }
                //AMARELO
                if(mousex() > 200 && mousex() < 249 && mousey() > 364 && mousey() < 418 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 3;
                    if(verificaSequencia(f1,3)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AMARELO",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=15;
                    }

                }
                //CINZA
                if(mousex() > 134 && mousex() < 191 && mousey() > 358 && mousey() < 420 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 5;
                    if(verificaSequencia(f1,5)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d CINZA",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=15;
                    }

                }
                //MARROM
                if(mousex() > 72 && mousex() < 124 && mousey() > 308 && mousey() < 361 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 4;
                    if(verificaSequencia(f1,4)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d MARROM",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=15;
                    }


                }
                //AZUL
                if(mousex() > 81 && mousex() < 129 && mousey() > 236 && mousey() < 302 && ismouseclick(WM_LBUTTONDOWN)){
                    idCor = 2;
                    if(verificaSequencia(f1,idCor)==1){
                        removerDaFila(&f1,&idCor);
                        inserirNaFila(&f2,idCor);

                        somaCliques+=1;
                        totalGeral += 1;
                        itoa(totalGeral,pontos,10);
                        outtextxy(250,510,pontos);
                        //printf("\n\nPONTOS: %d - CLIQUES: %d - IDCOR: %d AZUL",somaPontosPorFase,somaCliques,corSorteada[i]);
                    }else{
                        somaCliques=15;
                    }

                }

                if(somaCliques == 15){

                    totalGeral+= somaCliques*2;
                    somaCliques = 0;

                    if(totalGeral==249){
                        tela=9;
                        while(sequencia==9){
                            if(mousex() > 88 && mousex() < 331 && mousey() > 487 && mousey() < 553 && ismouseclick(WM_LBUTTONDOWN)){
                                sequencia=0;
                            }
                            readimagefile("winner1.jpg", 0, 0, 400, 700);
                            readimagefile("winner2.jpg", 0, 0, 400, 700);
                            readimagefile("winner3.jpg", 0, 0, 400, 700);

                        }

                    }else{
                        readimagefile("perdeu.jpg", 0, 0, 400, 700);
                        //totalGeral += pontuacao(totalPontosFase);
                        tela=6;//TELA Q MOSTRA QUANDO PERDE O JOGO
                    }

                    if(sequencia==0){
                        strcpy(j.nome,nomeJogador);
                        j.record=totalGeral;
                        inserirNaLista(&L,j);

                        if(isEmpty(f1)){
                            while(!isEmpty(f2))
                            {
                                removerDaFila(&f2,&idCor);
                            }
                        }else{
                            while(!isEmpty(f1))
                            {
                                removerDaFila(&f1,&idCor);
                            }
                        }

                        for (i = 0;i<15;i++)
                        {
                            x = rand()%8;
                            corSorteada[i] = jogo[x].id;
                            inserirNaFila(&f1,corSorteada[i]);
                            //printf("%d\n",corSorteada[i]);
                        }

                        tela=8;
                        readimagefile("ranking.jpg", 0, 0, 400, 700);
                        imprimirLista(L);
                        strcpy(nomeJogador,"\0");
                        strcpy(pontos,"\0");
                        totalGeral=0;
                        somaCliques=0;
                    }


                }

        }

        //FINAL DA FASE BONUS

        //QUANDO PRESSIONADO O BOTÃO VOLTAR DURANTE O JOGO
        if((sequencia==1||sequencia==2||sequencia==3||sequencia==4||sequencia==5||sequencia==6||sequencia==7||sequencia==8||sequencia==9
            ||tela==5||mapa==2||mapa==3||mapa==4||mapa==5||mapa==6||mapa==7||mapa==8||mapa==9)
           && mousex() > 85 && mousex() < 120 && mousey() > 610 && mousey() < 630 && ismouseclick(WM_LBUTTONDOWN))
        {
            //CHAMA A TELA QUE PERGUNTA SE QUER SAIR OU NAO
            readimagefile("telajogosair.jpg", 0, 0, 400, 700);
            aux=tela;
            tela=10;
            //continue;
            while(tela==10){
                Sleep(1000);
                //SE CLICAR EM SIM ELE SAI DO JOGO E VOLTA PARA O MENU INICIAL
                //SE CLICAR EM NAO ELE VOLTA PARA A FASE DO JOGO EM QUE ESTAVA, E CONTINUA A SEQUENCIA DE ONDE PAROU
                if(tela==10 && mousex() > 76 && mousex() < 177 && mousey() > 280 && mousey() < 330 && ismouseclick(WM_LBUTTONDOWN)){
                    printf("\nSAIU DO JOGO");
                    sequencia=0;
                    mapa=0;
                    strcpy(j.nome,nomeJogador);
                    j.record=totalGeral;
                    inserirNaLista(&L,j);

                    if(isEmpty(f1)){
                        while(!isEmpty(f2))
                        {
                            removerDaFila(&f2,&idCor);
                        }
                    }else{
                        while(!isEmpty(f1))
                        {
                            removerDaFila(&f1,&idCor);
                        }
                    }

                    for (i = 0;i<15;i++)
                    {
                        x = rand()%8;
                        corSorteada[i] = jogo[x].id;
                        inserirNaFila(&f1,corSorteada[i]);
                        //printf("%d\n",corSorteada[i]);
                    }

                    tela=8;
                    readimagefile("ranking.jpg", 0, 0, 400, 700);
                    imprimirLista(L);
                    strcpy(nomeJogador,"\0");
                    strcpy(pontos,"\0");
                    totalGeral=0;
                    somaCliques=0;

                    if(isEmpty(f1)){
                            while(!isEmpty(f2))
                            {
                                removerDaFila(&f2,&idCor);
                            }
                        }else{
                            while(!isEmpty(f1))
                            {
                                removerDaFila(&f1,&idCor);
                            }
                        }

                        for (i = 0;i<15;i++)
                        {
                            x = rand()%8;
                            corSorteada[i] = jogo[x].id;
                            inserirNaFila(&f1,corSorteada[i]);
                            //printf("%d\n",corSorteada[i]);
                        }

                }else if(tela==10 && mousex() > 223 && mousex() < 323 && mousey() > 277 && mousey() < 330 && ismouseclick(WM_LBUTTONDOWN)){

                    if(sequencia==1){
                        readimagefile("telajogo.jpg", 0, 0, 400, 700);
                        outtextxy(250,510,pontos);
                        outtextxy(110,510,"1");
                    }else if(sequencia==2){
                        readimagefile("telajogo.jpg", 0, 0, 400, 700);
                        outtextxy(250,510,pontos);
                        outtextxy(110,510,"2");
                    }else if(sequencia==3){
                        readimagefile("telajogo.jpg", 0, 0, 400, 700);
                        outtextxy(250,510,pontos);
                        outtextxy(110,510,"3");
                    }else if(sequencia==4){
                        readimagefile("telajogo.jpg", 0, 0, 400, 700);
                        outtextxy(250,510,pontos);
                        outtextxy(110,510,"4");
                    }else if(sequencia==5){
                        readimagefile("telajogo.jpg", 0, 0, 400, 700);
                        outtextxy(250,510,pontos);
                        outtextxy(110,510,"5");
                    }else if(sequencia==6){
                        readimagefile("telajogo.jpg", 0, 0, 400, 700);
                        outtextxy(250,510,pontos);
                        outtextxy(110,510,"6");
                    }else if(sequencia==7){
                        readimagefile("telajogo.jpg", 0, 0, 400, 700);
                        outtextxy(250,510,pontos);
                        outtextxy(110,510,"7");
                    }else if(sequencia==8){
                        readimagefile("telajogo.jpg", 0, 0, 400, 700);
                        outtextxy(250,510,pontos);
                        outtextxy(110,510,"8");
                    }else if(sequencia==9){
                        readimagefile("telajogo.jpg", 0, 0, 400, 700);
                        outtextxy(250,510,pontos);
                        outtextxy(110,510,"9");
                    }

                    if(mapa==1){
                        readimagefile("mapa1.jpg", 0, 0, 400, 700);
                        mapa=1;
                    }else if(mapa==2){
                        readimagefile("mapa2.jpg", 0, 0, 400, 700);
                        mapa=2;
                    }else if(mapa==3){
                        readimagefile("mapa3.jpg", 0, 0, 400, 700);
                        mapa=3;
                    }else if(mapa==4){
                        readimagefile("mapa4.jpg", 0, 0, 400, 700);
                        mapa=4;
                    }else if(mapa==5){
                        readimagefile("mapa5.jpg", 0, 0, 400, 700);
                        mapa=5;
                    }else if(mapa==6){
                        readimagefile("mapa6.jpg", 0, 0, 400, 700);
                        mapa=6;
                    }else if(mapa==7){
                        readimagefile("mapa7.jpg", 0, 0, 400, 700);
                        mapa=7;
                    }else if(mapa==8){
                        readimagefile("mapa8.jpg", 0, 0, 400, 700);
                        mapa=8;
                    }else if(mapa==9){
                        readimagefile("mapafinal.jpg", 0, 0, 400, 700);
                        mapa=9;
                    }

                    tela=aux;

                    if(tela==5){
                        readimagefile("start.jpg", 0, 0, 400, 700);
                    }
                }
            }
        }

        if(tela==8 && mousex()>97 && mousex()<288 && mousey()>543 && mousey()<587 && ismouseclick(WM_LBUTTONDOWN)){
            readimagefile("inicio.jpg", 0, 0, 400, 700);
            tela=3;
        }


        //QUANDO PRESSIONADO O BOTÃO VOLTAR
        if(mousex() > 85 && mousex() < 120 && mousey() > 610 && mousey() < 630 && ismouseclick(WM_LBUTTONDOWN))
        {
            if(tela==9||tela==8||tela==3){
                readimagefile("menu.jpg", 0, 0, 400, 700);
                tela=2;
            }else if(tela==19||tela==4||mapa==1){
                readimagefile("inicio.jpg", 0, 0, 400, 700);
                tela=3;
            }else if(tela==2){
                readimagefile("principal.jpg", 0, 0, 400, 700);
                tela=1;
            }

        }




           if(tela==4 && mousex() > 35 && mousex() < 62 && mousey() > 425 && mousey() < 458 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"Q");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 69 && mousex() < 96 && mousey() > 425 && mousey() < 458 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"W");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);
            }
            if(tela==4 && mousex() > 102 && mousex() < 129 && mousey() > 425 && mousey() < 458 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"E");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 136 && mousex() < 162 && mousey() > 425 && mousey() < 458 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"R");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 167 && mousex() < 195 && mousey() > 425 && mousey() < 458 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"T");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 202 && mousex() < 229 && mousey() > 425 && mousey() < 458 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"Y");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 236 && mousex() < 262 && mousey() > 425 && mousey() < 458 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"U");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 269 && mousex() < 296 && mousey() > 425 && mousey() < 458 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"I");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 301 && mousex() < 328 && mousey() > 425 && mousey() < 458 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"O");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 336 && mousex() < 362 && mousey() > 425 && mousey() < 458 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"P");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 53 && mousex() < 79 && mousey() > 465 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"A");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 85 && mousex() < 112 && mousey() > 465 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"S");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 118 && mousex() < 147 && mousey() > 465 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"D");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 153 && mousex() < 177 && mousey() > 465 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"F");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 187 && mousex() < 212 && mousey() > 465 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"G");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 219 && mousex() < 245 && mousey() > 465 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"H");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 251 && mousex() < 278 && mousey() > 465 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"J");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 285 && mousex() < 312 && mousey() > 465 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"K");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 319 && mousex() < 345 && mousey() > 465 && mousey() < 496 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"L");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 86 && mousex() < 111 && mousey() > 502 && mousey() < 535 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"Z");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 119 && mousex() < 145 && mousey() > 502 && mousey() < 535 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"X");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 154 && mousex() < 178 && mousey() > 502 && mousey() < 535 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"C");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 186 && mousex() < 212 && mousey() > 502 && mousey() < 535 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"V");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 219 && mousex() < 245 && mousey() > 502 && mousey() < 535 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"B");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 253 && mousex() < 279 && mousey() > 502 && mousey() < 535 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"N");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            if(tela==4 && mousex() > 285 && mousex() < 311 && mousey() > 502 && mousey() < 535 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador,"M");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);

            }
            //ESPAÇO
            if(tela==4 && mousex() > 119 && mousex() < 278 && mousey() > 541 && mousey() < 573 && ismouseclick(WM_LBUTTONDOWN))
            {
                 strcat(nomeJogador," ");
                 setbkcolor(15);
                 setcolor(0);
                 settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
                 tamanhoNome = strlen(nomeJogador);
                 if(tamanhoNome>10){
                     nomeJogador[(strlen(nomeJogador))-1] = 0;
                 }
                 outtextxy(65,375,nomeJogador);
            }
            //ENTER
            if(tela==4 && mousex() > 285 && mousex() < 361 && mousey() > 540 && mousey() < 575 && ismouseclick(WM_LBUTTONDOWN))
            {
                tela=3;
                readimagefile("inicio.jpg", 0, 0, 400, 700);
                outtextxy(65,375,nomeJogador);

            }
            //APAGAR
            if(tela==4 && mousex() > 322 && mousex() < 362 && mousey() > 502 && mousey() < 535 && ismouseclick(WM_LBUTTONDOWN))
            {
                nomeJogador[(strlen(nomeJogador))-1] = 0;
                readimagefile("teclado.jpg", 0, 0, 400, 700);
                outtextxy(65,375,nomeJogador);
                //printf("%s",nomeJogador);
            }

            //SE PERDEU E CLICAR NO SIM
            if(tela==6 && mousex() > 55 && mousex() < 185 && mousey() > 501 && mousey() < 567 && ismouseclick(WM_LBUTTONDOWN)){
                strcpy(j.nome,nomeJogador);
                j.record=totalGeral;
                inserirNaLista(&L,j);

                if(isEmpty(f1)){
                    while(!isEmpty(f2))
                    {
                        removerDaFila(&f2,&idCor);
                    }
                }else{
                    while(!isEmpty(f1))
                    {
                        removerDaFila(&f1,&idCor);
                    }
                }

                for (i = 0;i<15;i++)
                {
                    x = rand()%8;
                    corSorteada[i] = jogo[x].id;
                    inserirNaFila(&f1,corSorteada[i]);
                    //printf("%d\n",corSorteada[i]);
                }
                tela=8;
                readimagefile("ranking.jpg", 0, 0, 400, 700);
                imprimirLista(L);
                strcpy(pontos,"\0");
                totalGeral=0;

            }
            //SE PERDEU E CLICAR NO NÃO
            if(tela==6 && mousex() > 211 && mousex() < 340 && mousey() > 501 && mousey() < 567 && ismouseclick(WM_LBUTTONDOWN)){
                strcpy(j.nome,nomeJogador);
                j.record=totalGeral;
                inserirNaLista(&L,j);

                if(isEmpty(f1)){
                    while(!isEmpty(f2))
                    {
                        removerDaFila(&f2,&idCor);
                    }
                }else{
                    while(!isEmpty(f1))
                    {
                        removerDaFila(&f1,&idCor);
                    }
                }

                for (i = 0;i<15;i++)
                {
                    x = rand()%8;
                    corSorteada[i] = jogo[x].id;
                    inserirNaFila(&f1,corSorteada[i]);
                    //printf("%d\n",corSorteada[i]);
                }

                tela=3;
                readimagefile("ranking.jpg", 0, 0, 400, 700);
                imprimirLista(L);
                strcpy(nomeJogador,"\0");
                strcpy(pontos,"\0");
                totalGeral=0;


            }

        clearmouseclick(WM_LBUTTONDOWN);


    }while(!kbhit());


    getchar();
    closegraph();
}
