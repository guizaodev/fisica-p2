#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define E_1G_TNT 4184.0
#define E_C 1673.6
#define R 6
#define MASSA_PEDRA 20.0
#define MASSA_CAPACETE 1.5
#define MASSA_ROUPA 85.0
#define MASSA_INICIAL_NAVE 4200.0
#define MASSA_AGUA 1.0
#define MASSA_TOTAL_OBJ 294
#define V_GAS 900.0
#define TEMPO_SOLTA_GAS 0.010 // g/s
#define V_IDEAL_NAVE 0.1
#define DISTANCIA_ESTACAO 1000.0
#define TEMPO_DE_OXIGENIO 3600.0
float energia_cinetica2g = E_1G_TNT * 2 * 0.2; // 20% da energia de 2 gramas de TNT

int main()
{

    float massa = 0;
    float ec_total = 0;
    float v = 0;
    float momento = 0;
    for (int qtd_tnt = 1; qtd_tnt <= 5; qtd_tnt++)
    {
        for (int qtd_pedra = 0; qtd_pedra <= 6; qtd_pedra++)
        {

            for (int qtd_roupa = 0; qtd_roupa <= 2; qtd_roupa++)
            {
                for (int qtd_capacete = 0; qtd_capacete <= 2; qtd_capacete++)
                {
                    for (int qtd_agua = 1; qtd_agua < 50; qtd_agua++)
                    {
                        massa = (MASSA_PEDRA * qtd_pedra) + (MASSA_CAPACETE * qtd_capacete) + (MASSA_ROUPA * qtd_roupa) + (MASSA_AGUA / qtd_agua);

                        ec_total = energia_cinetica2g * qtd_tnt;
                        v = sqrt((2 * ec_total) / massa); // e=mv^2/2
                        momento = massa * R * v;
                        if (momento > 4995 && momento < 5010 && qtd_tnt < 4)
                        {
                            //verifica volta
                            float v_obj = 0;
                            float v_nave = 0;
                            int qtd_tnt_resta = 5 - qtd_tnt;
                            float ec_volta = 0;
                            float momento_obj = 0;
                            float massa_rest = 0;
                            for (int i = qtd_tnt_resta; i > 0; i--)
                            {
                                ec_volta = energia_cinetica2g * i;
                                massa_rest = MASSA_TOTAL_OBJ - massa;
                                v_obj = sqrt((2 * ec_volta) / massa_rest);
                                momento_obj = v_obj * massa_rest;
                                // v_obj * massa_rest = v_nave * massa_atual_nave
                                v_nave = momento_obj / (MASSA_INICIAL_NAVE - MASSA_TOTAL_OBJ);

                                // VERIFICAÇÃO DO FREIO
                                float massa_gas = 0.0;
                                float massa_atual_nave = MASSA_INICIAL_NAVE - MASSA_TOTAL_OBJ;
                                float tempo_freio = 0, a_freio = 0, dist_freio = 0, tempo_MRU;
                                // Massa_atual_nave * V_IDEAL_NAVE = Massa_atual_nave * v_nave - Massa_gas*v_gas*sen 45;
                                massa_gas = (massa_atual_nave * (V_IDEAL_NAVE - v_nave)) / (V_GAS * (-1) * (sqrt(2) / 2));
                                tempo_freio = massa_gas / TEMPO_SOLTA_GAS;
                                // v = vo - at;
                                a_freio = (V_IDEAL_NAVE - v_nave) / tempo_freio;
                                // v^2 = vo^2 - 2*a*var_x -> var_x = (v^2 - vo^2) / (-2a);
                                dist_freio = (V_IDEAL_NAVE * V_IDEAL_NAVE - v_nave * v_nave) / (2 * a_freio);

                                tempo_MRU = (DISTANCIA_ESTACAO - dist_freio) / v_nave;
                                if (tempo_MRU + tempo_freio < 3600 && massa_gas <= 1.5) // ===================== // ---------- X
                                {
                                    printf("------INICIO------\n");
                                    printf("Momento: %.3f\t\t|\tMassa: %.2f\t\t\t|\tQuantidade de TNT: %.1f\n", momento, massa, ec_total / energia_cinetica2g);
                                    printf("Ec total: %.3f\t\t|\tVelocidade: %.2f  \n", ec_total, v);
                                    printf("Qtd. roupa: %d\t\t\t|\tQtd. pedra: %d\t\t\t|\tQtd. capacete: %d\t|\tQtd. agua: %.2f\n", qtd_roupa, qtd_pedra, qtd_capacete, MASSA_AGUA / qtd_agua);
                                    printf("==============");
                                    printf("\nVelocidade nave: %.4f\t|\tMassa restante: %.2f\t|\tQtd. TNT: %d\n", v_nave, massa_rest, i);
                                    printf("--------------");
                                    printf("\nMassa gas: %.2f\t\t\t|\tTempo_freio: %.2f\t\t|\tDist_freio: %.2f\n", massa_gas, tempo_freio, dist_freio);
                                    printf("Tempo que levou: %.2f\n", tempo_freio + tempo_MRU);
                                    printf("Distancia percorrida em MRU: %.2f\n", DISTANCIA_ESTACAO - dist_freio);
                                    printf("Vocês conseguiram chegar vivos!\n");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
