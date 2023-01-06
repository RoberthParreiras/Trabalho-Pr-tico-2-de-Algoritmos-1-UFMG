#include <iostream>
#include <vector>
#include <functional> //std::greater
#include <utility> //std::pair
#include <queue> //std::priority_queue
#include <string>
#include <limits.h> //INT_MAX  


/*A funcao retorna a rota com a maior capacidade entre a cidade origem e a cidade destino*/
int CarregamentoMaximo(std::vector<std::vector<std::pair<int, int>>>& rotas, int origem, int destino)
{
    std::vector<int> capacidades(rotas.size(), -1); //cria e "seta" a capacidade de cada cidade como -1
    capacidades[origem] = INT_MAX;     
    
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>> parPesoCid;    //fila de prioridade para armazenar a capacidade e cidade
    parPesoCid.push(std::make_pair(0, origem)); //"seta" a cidade origem com peso 0
    
    std::pair<int, int> topo; //recebe o topo da fila de prioridade
    int cidadeAtual, peso;

    //insere todos os pesos e cidades das rotas na fila de prioridade
    for(cidadeAtual = 1; cidadeAtual < rotas.size(); ++cidadeAtual) {
        for(std::pair<int, int> par : rotas[cidadeAtual]) {
            parPesoCid.push(std::make_pair(par.first, par.second));
        }
    }

    //checa, enquanto a fila de prioridade nao estiver vazia, qual rotas entre origem e destino tem maior peso
    while(!parPesoCid.empty()) {
        topo = parPesoCid.top();
        cidadeAtual = topo.second;
        parPesoCid.pop();
 
        for(std::pair<int, int> par : rotas[cidadeAtual]) {
            peso = std::max(std::min(capacidades[cidadeAtual], par.first), capacidades[par.second]);  //compara qual a menor capacidade entre cidade atual e cidade vizinha. Apos, compara qual a maior capacidade entre a comparacao anterior com a capacidade armazenada da proxima cidade.

            //se a capacidade for maior que a armazenada, atualiza para a capacidade maior
            if(peso > capacidades[par.second]) {
                capacidades[par.second] = peso;
                parPesoCid.push(std::make_pair(peso, par.second));  
            }
        }
    }

    return capacidades[destino];    //retorna a capacidade do destino
}

int main(int argc, char* argv[]) {
	int cidades, rodovias, consultas, cidade, cidadeVizinha, peso;
    std::string cid, cid2, rod, cons, ps;
    std::cin >> cid >> rod >> cons; //le cada string da primeira linha do arquivo.txt
    
    cidades = std::stoi(cid);       //
    rodovias = std::stoi(rod);      //converte string para inteiro
    consultas = std::stoi(cons);    //

    std::vector<std::vector<std::pair<int, int>>> rotas;            //cria o vetor que armazena todas as cidades
    rotas.assign(cidades + 1, std::vector<std::pair<int, int>>());  //
 
    //armazena o peso e as cidades vizinhas de cada cidade
	for(int i = 1; i <= rodovias; ++i) {
        std::cin >> cid >> cid2 >> ps;
        cidade = std::stoi(cid);            
        cidadeVizinha = std::stoi(cid2);
        peso = std::stoi(ps);

		rotas[cidade].push_back(std::make_pair(peso, cidadeVizinha));
    }

    //imprime o resultado das consultas
    for(int i = 1; i <= consultas; ++i) {
        std::cin >> cidade >> cidadeVizinha;

        if(i != consultas)
            std::cout << CarregamentoMaximo(rotas, cidade, cidadeVizinha) << std::endl;
        else
            std::cout << CarregamentoMaximo(rotas, cidade, cidadeVizinha);   //sendo a ultima consulta, nao tem quebra de linha
    }

    return 0;
}