#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include	"memory.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include    "malloc.h"
#include	 "fila-1.h"


int			testa_rotina(char* servico);


//
// opcao: rodar com 'fila rotina'
// por exemplo 'fila NNNNPPPPLA'
// sao NPLA para
// N - entra cliente normal
// P - entra cliente com prioridade de atendimento
// L - lista a situacao
// A - tenta atender alguem
//
// cada letra indica uma acao para nao ter que ficar usando o menu
// e o menu pode apontar para as acoes para nao ter que programar mais nada
//
int			main(int argc, char** argv)
{
	if (argc > 1)	// veio algo na linha de comando
	{
		inicia_trabalhos();
		testa_rotina(argv[1]);
		return 0;
	}	// end if

	inicia_trabalhos();
	char* rotina = "LNNNNPPPPLAAL";
	testa_rotina(rotina);
	return 0;
}	// end main()


int	testa_rotina(char* servico)
{
	printf("\n***** Rotina=[%s] Capacidade %d *****\n", servico, CAPACIDADE);
	int n = strlen(servico);
	printf("\nTotal de acoes: %d\n\n", n);
	for (int i = 0; i < n; i++)
	{
		ciclo(servico[i]);
	};	// end for
	return n;
}	// end testa_rotina()

