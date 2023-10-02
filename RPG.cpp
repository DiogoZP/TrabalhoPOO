/* Crie um jogo de RPG em C++ de acordo com as seguintes instruções:
O RPG simulará um combate em uma arena entre personagens. Terá (no mínimo) as classes JogoRPG,
Personagem, e mais 6 classes distintas representando diferentes arquétipos. Por exemplo, Guerreiro(a),
Bruxo(a), Ladrão, Arqueiro(a), etc.
A classe Personagem deve ter no mínimo os seguintes atributos:
Nome do personagem.
Pontos de vida (VID).
Pontos de ataque (ATQ).
Pontos de defesa (DEF).
Lista de personagens derrotados.
Cada classe que identifica um arquétipo será derivada da classe Personagem.
Cada arquétipo terá um ataque especial, exclusivo de sua classe. Este ataque poderá ocorrer,
aleatoriamente, durante um round de combate. Ou seja, em vez do ataque normal, ocorrerá o ataque
especial. Este ataque terá um nome específico e causará mais dano do que um ataque normal.
O ataque especial também poderá causar sangramento, onde o outro personagem sangrará por um número
de rounds calculado aleatoriamente (mínimo de 2 rounds, máximo de 6 rounds). O sangramento causará
uma perda (baixa) de vida a cada round, independente do dano atual recebido no round.
O sangramento deve ser calculado no início de cada round, portanto, um personagem pode ser derrotado
sem receber dano de ataque no round.
Caso ambos os personagens fiquem sem vida devido a sangrarem no início do round, um dos dois
personagens será sorteado para avançar e o outro será considerado derrotado.
Implemente construtores para inicializar o nome, VID, ATQ e DEF do personagem. Implemente um
método para exibir as estatísticas do personagem.
Cada personagem irá armazenar a lista de personagens que derrotou. Use alguma estrutura de dados para
armazenar cada personagem que foi derrotado.
Cada combate poderá durar no máximo 10 rounds. Se nenhum dos dois personagens forem derrotados ao
fim de 10 rounds, o personagem que causou mais dano será considerado o vencedor.
Ao fim de cada combate seu jogo deve exibir uma tabela com as estatísticas do combate, considerando
dano efetuado por cada personagem, vida restante de cada personagem, número de rounds ocorridos, e
quantos ataques especiais ocorreram. */

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

class Personagem {
    protected: 
        string _nome;
        int _hp;
        int _hpAtual;
        int _atk;
        int _atkAtual;
        int _def;
        int _defAtual;
        int _danoCausado;
        int _numAtaquesEspeciais;
        int _sangramento;
        vector<Personagem*> _derrotados;

    public:
        Personagem(string nome, int hp, int atk, int def) : _nome(nome), _hp(hp), _hpAtual(hp), _atk(atk), _atkAtual(atk), _def(def), _defAtual(def),    _danoCausado(0), _numAtaquesEspeciais(0), _sangramento(0){}
        void exibir() {
            cout << "Nome: " << _nome << endl;
            cout << "HP: " << _hp << endl;
            cout << "ATK: " << _atk << endl;
            cout << "DEF: " << _def << endl;
            int num = _derrotados.size();
            for(int i = 0; i < num; i++) {
                cout << _derrotados[i]->_nome << endl;
            }
            system("pause");
        }
        void exibirAtual()
        {
            cout << "Nome: " << _nome << endl;
            cout << "HP: " << _hpAtual << endl;
            cout << "ATK: " << _atkAtual << endl;
            cout << "DEF: " << _defAtual << endl;
            cout << "Derrotados: " << endl;
            int num = _derrotados.size();
            for(int i = 0; i < num; i++) {
                cout << _derrotados[i]->_nome << endl;
            }
            system("pause");
        }
        void setHpAtual(int hp) {
            _hpAtual = hp;
        }
        void resetar() {
            _hpAtual = _hp;
            _atkAtual = _atk;
            _defAtual = _def;
            _danoCausado = 0;
            _numAtaquesEspeciais = 0;
            _sangramento = 0;
        }
        int getDanoCausado() {
            return _danoCausado;
        }
        string getNome() {
            return _nome;
        }
        int getSangramento() {
            return _sangramento;
        }
        int getHp() {
            return _hp;
        }
        int getHpAtual() {
            return _hpAtual;
        }
        void atacar(Personagem *p) {
            srand(rand() % 100 + 1);
            if((rand() % 20 + 1) > 10){
                _numAtaquesEspeciais++;
                AtaqueEspecial(p);
            }
            else {
            int dano = p->receberDano(_atkAtual);
            _danoCausado += dano;
            cout << _nome << " golpeou causando " << dano << " de dano." << endl;
            }
        }
        int receberDano(int dano) {
            _hpAtual -= dano - _def;
            return dano - _def;
        }
        void receberSangramento()
        {
            srand(rand() % 100 + 1);
            _sangramento = rand() % 6 + 2;
        }
        void sangrar() {
            receberDano(_sangramento);
            _sangramento--;
        }
        void reduzirDefesa(int valor) {
            _defAtual -= valor;
        }
        void resetarDefesa() {
            _defAtual = _def;
        }
        void reduzirAtaque(int valor) {
            _atkAtual -= valor;
        }
        void resetarAtaque() {
            _atkAtual = _atk;
        }
        void virtual AtaqueEspecial(Personagem *p) {
            _danoCausado += p->receberDano(_atkAtual);
        }
        void derrotar(Personagem *p) {
            _derrotados.push_back(p);
        }
        bool estaVivo() {
            return _hpAtual > 0;
        }
};

class Guerreiro : public Personagem {
    public:
        Guerreiro(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}
        void exibir() {
            Personagem::exibir();
            cout << "Ataque especial: Furia" << endl;
        }

        void AtaqueEspecial(Personagem *p) override {
            srand(rand() % 100 + 1);
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
            }
            _atkAtual += 5;
            int dano = p->receberDano(_atkAtual);
            _danoCausado += dano;
            cout << _nome << " usou Furia e causou " << dano << " de dano." << endl;
        }
};

class Ladino : public Personagem {
    public:
        Ladino(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}
        void exibir() {
            Personagem::exibir();
            cout << "Ataque especial: Golpe Critico" << endl;
        }

        void AtaqueEspecial(Personagem *p) override {
            p->receberSangramento();
            int dano = p->receberDano(_atkAtual);
            _danoCausado += dano;
            cout << _nome << " usou Golpe Critico e causou sangramento e " << dano << " de dano." << endl;
        }
};

class Clerigo : public Personagem {
    public:
        Clerigo(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}
        void exibir() {
            Personagem::exibir();
            cout << "Ataque especial: Cura" << endl;
        }

        void AtaqueEspecial(Personagem *p) override {
            _hpAtual += _atkAtual;
            cout << _nome << " usou Cura e recuperou " << _atkAtual << " de vida." << endl;
        }
};

class Bruxo : public Personagem {
    public:
        Bruxo(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}
        void exibir() {
            Personagem::exibir();
            cout << "Ataque especial: Escudo Magico" << endl;
        }

        void AtaqueEspecial(Personagem *p) override {
            srand(rand() % 100 + 1);
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
            }
            _defAtual += 5;
            int dano = p->receberDano(_atkAtual);
            _danoCausado += dano;
            cout << _nome << " usou Escudo Magico recebendo 5 de defesa e causou " << dano << " de dano." << endl;
        }
};

class Bardo : public Personagem {
    public:
        Bardo(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}
        void exibir() {
            Personagem::exibir();
            cout << "Ataque especial: Encantar" << endl;
        }

        void AtaqueEspecial(Personagem *p) override {
            srand(rand() % 100 + 1);
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
            }
            p->reduzirAtaque(5);
            int dano = p->receberDano(_atkAtual);
            _danoCausado += dano;
            cout << _nome << " usou Encantar reduzindo o ataque do inimigo em 5 e causou " << dano << " de dano." << endl;
        }
};

class Arqueiro : public Personagem {
    public:
        Arqueiro(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}
        void exibir() {
            Personagem::exibir();
            cout << "Ataque especial: Flecha Perfurante" << endl;
        }

        void AtaqueEspecial(Personagem *p) override {
            srand(rand() % 100 + 1);
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
            }
            p->reduzirDefesa(5);
            int dano = p->receberDano(_atkAtual);
            _danoCausado += dano;
            cout << _nome << " usou Flecha Perfurante reduzindo a defesa do inimigo em 5 e causou " << dano << " de dano." << endl;
        }
};

class JogoRPG {
    private:
    int _numParticipantes;
    vector<Personagem*> _participantes;
    public:
    void iniciarTorneio()
    {
        cout << "Digite o numero de participantes: " << endl;
        cin >> _numParticipantes;
        for(int i = 0; i < _numParticipantes; i++) {
            cout << "Digite o nome do personagem: " << endl;
            string nome;
            cin >> nome;
            cout << "Digite o tipo do personagem: " << endl;
            cout << "1 - Guerreiro" << endl;
            cout << "2 - Ladino" << endl;
            cout << "3 - Clerigo" << endl;
            cout << "4 - Bruxo" << endl;
            cout << "5 - Bardo" << endl;
            cout << "6 - Arqueiro" << endl;
            int tipo;
            cin >> tipo;
            switch(tipo) {
                case 1:
                    _participantes.push_back(new Guerreiro(nome, 100, 10, 5));
                    break;
                case 2:
                    _participantes.push_back(new Ladino(nome, 100, 10, 5));
                    break;
                case 3:
                    _participantes.push_back(new Clerigo(nome, 100, 10, 5));
                    break;
                case 4:
                    _participantes.push_back(new Bruxo(nome, 100, 10, 5));
                    break;
                case 5:
                    _participantes.push_back(new Bardo(nome, 100, 10, 5));
                    break;
                case 6:
                    _participantes.push_back(new Arqueiro(nome, 100, 10, 5));
                    break;
            }
        }
    }

    void iniciarCombate()
    {
        int numParticipantes = _participantes.size();
        for(int i = 0; i < numParticipantes; i++) {
            for(int j = i + 1; j < numParticipantes; j++) {
                if(_participantes[i]->getNome() != _participantes[j]->getNome() && _participantes[i]->estaVivo() && _participantes[j]->estaVivo()) {
                    combate(_participantes[i], _participantes[j]);
                }
            }
        }
    }

    void exibirRodadas(Personagem *p1, Personagem *p2, int numRounds)
    {
        system("cls");
        cout << p1->getNome() << " vs " << p2->getNome() << " - Rodada " << numRounds << endl;
        cout << p1->getNome() << " - HP: " << p1->getHpAtual() << "/" << p1->getHp() << endl;
        cout << p2->getNome() << " - HP: " << p2->getHpAtual() << "/" << p2->getHp() << endl;
    }

    void combate(Personagem *p1, Personagem *p2)
    {
        int numRounds = 0;
        srand(rand() % 100 + 1);
        int iniciativa = rand() % 2;
        while(p1->estaVivo() && p2->estaVivo() && numRounds < 10) {
            if(iniciativa == 0) {
                exibirRodadas(p1, p2, numRounds+1);
                p1->atacar(p2);
                p2->atacar(p1);
                system("pause");
            }
            else {
                exibirRodadas(p1, p2, numRounds+1);
                p2->atacar(p1);
                p1->atacar(p2);
                system("pause");
            }
            if(p1->getSangramento() > 0) {
                p1->sangrar();
            }
            if(p2->getSangramento() > 0) {
                p2->sangrar();
            }
            numRounds++;
        }
        if(p1->estaVivo() && p2->estaVivo() && p1->getDanoCausado() != p2->getDanoCausado()) {
            if(p1->getDanoCausado() > p2->getDanoCausado()) {
                p2->setHpAtual(0);
                p1->derrotar(p2);
                cout << p1->getNome() << " venceu!" << endl;
                p1->exibirAtual();
                p1->resetar();
            }
            else {
                p1->setHpAtual(0);
                p2->derrotar(p1);
                cout << p2->getNome() << " venceu!" << endl;
                p2->exibirAtual();
                p2->resetar();
            }
        }
        else if(p1->estaVivo() && !p2->estaVivo()) {
            p1->derrotar(p2);
            cout << p1->getNome() << " venceu!" << endl;
            p1->exibirAtual();
            p1->resetar();
        }
        else if(!p1->estaVivo() && p2->estaVivo()) {
            p2->derrotar(p1);
            cout << p2->getNome() << " venceu!" << endl;
            p2->exibirAtual();
            p2->resetar();
        }
        else {
            if(rand() % 2 == 0) {
                p2->setHpAtual(0);
                p1->derrotar(p2);
                cout << p1->getNome() << " venceu!" << endl;
                p1->exibirAtual();
                p1->resetar();
            }
            else {
                p1->setHpAtual(0);
                p2->derrotar(p1);
                cout << p2->getNome() << " venceu!" << endl;
                p2->exibirAtual();
                p2->resetar();
            }
        }
    }
};

int main(){
    srand(time(NULL));
    JogoRPG jogo;
    jogo.iniciarTorneio();
    jogo.iniciarCombate();
    return 0;
}
