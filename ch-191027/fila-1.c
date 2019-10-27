#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include	"memory.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include    "malloc.h"

#include	 "fila-1.h"


int		atendimento()
{
	int			a_atender;
	static int	sequencia = 0;
	// o inicio da fila pode apontar para um cliente
	// prioritario que ja foi antendido na sequencia
	if (q_fila <= 0)
	{
		printf("    ATENDIMENTO: Fila Vazia\n");
		return 0;
	}	// end if

	a_atender = SEM_CLIENTE;
	if (sequencia % 3 == 0)
	{
		// vai procurar proximo cliente com prioridade
		for (int i = 1, pos = i; i <= q_fila;)
		{
			//printf("pos, fila[pos] fila[%d] = %c\n", pos, fila[pos]);
			if (fila[pos] == PRIORIDADE)
			{
				a_atender = pos;		// marca pra chamar esse
				break;	// sai do loop: achou
			}
			else
			{
				if (fila[pos] == LIVRE) continue;	// nao tem cliente
				i = i + 1;				// tem cliente aqui	
			}	// end if
			pos = pos + 1;
		}	// end for
	}	// end if

	// se a_atender == SEM_CLIENTE entao podemos atender o
	// proximo cliente, de qualquer fila
	if (a_atender == SEM_CLIENTE)
	{
		a_atender = 1;
		while (fila[a_atender] == LIVRE) a_atender += 1;	// sabe-se que tem alguem na fila
	}	// end if

	sequencia += 1;				// marca atendimento afinal

	// atendimento aqui
	if (fila[a_atender] == PRIORIDADE)
	{
		printf("    ATENDENDO [%s] senha %03d [PRIORIDADE]\n",
			cad[a_atender].nome, cad[a_atender].senha);
		q_fila_prioridade -= 1;
	}
	else
	{
		printf("    ATENDENDO [%s] senha %03d [NORMAL]\n",
			cad[a_atender].nome, cad[a_atender].senha);
		q_fila_normal -= 1;
	}	// end if
	marca_senha_painel(cad[a_atender].senha);
	fila[a_atender] = LIVRE;	// sabe-se que tem alguem na fila
	move_a_fila(a_atender);
	q_fila -= 1;
	ja_atendidos = ja_atendidos + 1;
	return 1;
}	// end atendimento()


int		ciclo(char servico)
{
	switch (servico)
	{

	case ATENDE:
		atendimento();
		break;

	case NORMAL:
		if (q_fila == CAPACIDADE)
		{
			printf("    SEM mais senhas. Por favor AGUARDE\n");
			return -1;
		}	// end if
		q_fila += 1;
		fila[q_fila] = NORMAL;				// entra no fim da fila
		pega_senha(q_fila);
		printf(
			"    CADASTRADO '%s' com senha %03d na fila [Normal] pos=%d\n",
			cad[q_fila].nome,
			cad[q_fila].senha,
			cad[q_fila].posicao_na_fila
		);
		q_fila_normal += 1;
		break;

	case PRIORIDADE:
		if (q_fila == CAPACIDADE)
		{
			printf("    SEM mais senhas. Por favor AGUARDE\n");
			return -1;
		}	// end if
		q_fila += 1;
		fila[q_fila] = PRIORIDADE;			// entra no fim da fila
		pega_senha(q_fila);
		printf(
			"    CADASTRADO '%s' com senha %03d na fila [Prioridade] pos=%d\n",
			cad[q_fila].nome,
			cad[q_fila].senha,
			cad[q_fila].posicao_na_fila
		);
		q_fila_prioridade += 1;
		break;

	case LISTA:
		lista();
		break;

	case LIVRE:
	default:
		printf("Sem atividade\n");
		break;
	}	// end switch
	return 0;
}	// end ciclo()


int		inicia_trabalhos()
{
	printf("***** iniciando expediente CAPACIDADE=%d CLIENTES *****\n\n", CAPACIDADE);

	for (int i = 0; i < CAPACIDADE; i += 1)
		cad[i].nome[0] = 0;

	for (int i = 0; i < CAPACIDADE; i += 1)
		fila[i] = LIVRE;

	ja_atendidos = 0;


	fila[0] = 'X';				// so para separar no debugger
	q_fila_normal = 0;
	q_fila_prioridade = 0;
	q_fila = 0;

	for (int i = 0; i < 5; i += 1)
		ultimas_senhas[i] = SEM_CLIENTE;

	return 0;
}	// end inicia_trabalhos()


int		lista()
{
	printf("\n---------- ---------- ---------- ----------\n");
	printf("\nPainel\n");

	if (q_fila <= 0)
	{
		printf("Fila Vazia\n");
	}
	else
	{
		printf("Tamanho da fila:...... %3d\n\
Normal:............... %3d\n\
Prioritario: ......... %3d\n",
q_fila, q_fila_normal, q_fila_prioridade);
	}	// end if

	if (q_fila > 0)
	{
		// sao 'q_fila' clientes a partir do inicio da fila
		printf("\nFila (%d clientes):\n\n", q_fila);
		for (int i = 1, pos = i; i <= q_fila;)
		{
			if (fila[pos] != LIVRE)
			{
				printf("#%3d: [%s], Senha %d [%c]\n",
					i, cad[pos].nome, cad[pos].senha, fila[pos]);
				i = i + 1;		//conta esse
			}	// end if
			pos = pos + 1;
		};	// end for
	};	// end if

	if (ja_atendidos > 0)
	{
		printf("\nJa atendidos: %d. Ultimas 5 senhas chamadas: ", ja_atendidos);
		for (int i = 0; i < 5; i++)
		{
			if (ultimas_senhas[i] == SEM_CLIENTE)
				printf("     ");
			else
				printf("%3d  ", ultimas_senhas[i]);
		};	// end for
		printf("\n");

		if (ultimas_senhas[0] > 0)
			printf("\nUltima: %d\n", ultimas_senhas[0]);

	}	// end if
	printf("\n---------- ---------- ---------- ----------\n");
	return 0;
};	// end lista()


int		marca_senha_painel(int senha)
{
	for (int i = 4; i > 0; i--)
		ultimas_senhas[i] = ultimas_senhas[i - 1];
	ultimas_senhas[0] = senha;
	return 0;
}	// end marca_painel()


int		move_a_fila(int posicao)
{
	for (int j = posicao + 1; j <= q_fila; j++, posicao++)
	{
		if (fila[j] == LIVRE) return 0;			// so apaga um por vez
		fila[posicao] = fila[j];				// encolhe a fila
		strcpy(cad[posicao].nome, cad[j].nome);	// copia nome
		cad[posicao].senha = cad[j].senha;		// senha
		cad[posicao].posicao_na_fila = posicao;				// apenas pra ajudar num dump
	};	// end for

	return 0;
};	// end if


int pega_senha(int posicao)
{
	static int senha = 500;
	senha = senha + 1;
	sprintf(cad[posicao].nome, "Jose dos Santos de 2%03d Jr.", senha);
	cad[posicao].senha = senha;					// salva so pra conferir
	cad[posicao].posicao_na_fila = posicao;		// se der algo errado depois
	return senha;
}	// end pega_senha();

// end fila-1.c