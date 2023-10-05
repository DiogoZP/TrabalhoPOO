#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

class Personagem {
    protected: 
        string _nome;
        int _hp, _hpAtual, _atk, _atkAtual, _def, _defAtual, _danoCausado, _danoRecebido, _danoCausadoTotal, _danoRecebidoTotal, _numAtaquesEspeciais, _numAtaquesEspeciaisTotal, _sangramento;
        vector<Personagem*> _derrotados;

    public:
        Personagem(string nome, int hp, int atk, int def) : _nome(nome), _hp(hp), _hpAtual(hp), _atk(atk), _atkAtual(atk), _def(def), _defAtual(def), _danoCausado(0), _numAtaquesEspeciais(0), _sangramento(0), _danoCausadoTotal(0), _danoRecebido(0), _danoRecebidoTotal(0), _numAtaquesEspeciaisTotal(0){}
        void exibirTotal()
        {
            cout << "Nome: " << _nome << endl;
            cout << "HP: " << _hp << endl;
            cout << "ATK: " << _atk << endl;
            cout << "DEF: " << _def << endl;
            cout << "Dano causado: " << _danoCausadoTotal << endl;
            cout << "Dano recebido: " << _danoRecebidoTotal << endl;
            cout << "Numero de ataques especiais: " << _numAtaquesEspeciaisTotal << endl;
            cout << "Derrotados: " << endl;
            int num = _derrotados.size();
            for(int i = 0; i < num; i++) {
                cout << _derrotados[i]->_nome << endl;
            }
        }
        void exibirAtual()
        {
            cout << "Nome: " << _nome << endl;
            cout << "HP: " << _hpAtual << endl;
            cout << "ATK: " << _atkAtual << endl;
            cout << "DEF: " << _defAtual << endl;
            cout << "Dano causado: " << _danoCausado << endl;
            cout << "Dano recebido: " << _danoRecebido << endl;
            cout << "Numero de ataques especiais: " << _numAtaquesEspeciais << endl;
            cout << "Derrotados: " << endl;
            int num = _derrotados.size();
            for(int i = 0; i < num; i++) {
                cout << _derrotados[i]->_nome << endl;
            }
        }
        void setHpAtual(int hp) {
            _hpAtual = hp;
        }
        void resetar() {
            _hpAtual = _hp;
            _atkAtual = _atk;
            _defAtual = _def;
            _sangramento = 0;
            _danoCausadoTotal += _danoCausado;
            _danoCausado = 0;
            _danoRecebidoTotal += _danoRecebido;
            _danoRecebido = 0;
            _numAtaquesEspeciaisTotal += _numAtaquesEspeciais;
            _numAtaquesEspeciais = 0;
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
        int receberDano(int atk) {
            srand(rand() % 100 + 1);
            int d = atk - _def + (rand() % 6);
            if (d < 0) d = 0;
            _hpAtual -= d;
            _danoRecebido += d;
            return d;
        }
        void receberSangramento()
        {
            srand(rand() % 100 + 1);
            _sangramento = rand() % 6 + 2;
        }
        void sangrar() {
            _hpAtual -= _sangramento;
            cout << _nome << " sangrou perdendo " << _sangramento << " de vida." << endl;
            _sangramento--;
        }
        void reduzirDefesa(int valor) {
            _defAtual -= valor;
        }
        void reduzirAtaque(int valor) {
            _atkAtual -= valor;
        }
        void virtual AtaqueEspecial(){}
        void virtual AtaqueEspecial(Personagem *p) {}
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

        void AtaqueEspecial(Personagem *p) override {
            srand(rand() % 100 + 1);
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
                cout << _nome << " causou sangramento no inimigo." << endl;
            }
            _atkAtual += 3;
            int dano = p->receberDano(_atkAtual);
            _danoCausado += dano;
            cout << _nome << " usou Furia recebendo 3 de ataque e causou " << dano << " de dano." << endl;
        }
};

class Ladino : public Personagem {
    public:
        Ladino(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}

        void AtaqueEspecial(Personagem *p) override {
            p->receberSangramento();
            int dano = p->receberDano(_atkAtual);
            _danoCausado += dano;
            cout << _nome << " usou Golpe Critico causando sangramento e " << dano << " de dano." << endl;
        }
};

class Clerigo : public Personagem {
    public:
        Clerigo(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}

        void AtaqueEspecial(Personagem *p) override {
            _hpAtual += _atkAtual;
            cout << _nome << " usou Cura e recuperou " << _atkAtual << " de vida." << endl;
        }
};

class Bruxo : public Personagem {
    public:
        Bruxo(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}

        void AtaqueEspecial(Personagem *p) override {
            srand(rand() % 100 + 1);
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
                cout << _nome << " causou sangramento no inimigo." << endl;
            }
            _defAtual += 3;
            int dano = p->receberDano(_atkAtual);
            _danoCausado += dano;
            cout << _nome << " usou Escudo Magico recebendo 3 de defesa e causou " << dano << " de dano." << endl;
        }
};

class Bardo : public Personagem {
    public:
        Bardo(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}

        void AtaqueEspecial(Personagem *p) override {
            srand(rand() % 100 + 1);
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
                cout << _nome << " causou sangramento no inimigo." << endl;
            }
            p->reduzirAtaque(3);
            int dano = p->receberDano(_atkAtual);
            _danoCausado += dano;
            cout << _nome << " usou Encantar reduzindo o ataque do inimigo em 3 e causou " << dano << " de dano." << endl;
        }
};

class Arqueiro : public Personagem {
    public:
        Arqueiro(string nome, int hp, int atk, int def) : Personagem(nome, hp, atk, def){}

        void AtaqueEspecial(Personagem *p) override {
            srand(rand() % 100 + 1);
            if((rand() % 20 + 1) == 20){
                p->receberSangramento();
                cout << _nome << " causou sangramento no inimigo." << endl;
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
                    _participantes.push_back(new Guerreiro(nome, 100, 15, 5));
                    break;
                case 2:
                    _participantes.push_back(new Ladino(nome, 100, 15, 5));
                    break;
                case 3:
                    _participantes.push_back(new Clerigo(nome, 100, 15, 5));
                    break;
                case 4:
                    _participantes.push_back(new Bruxo(nome, 100, 15, 5));
                    break;
                case 5:
                    _participantes.push_back(new Bardo(nome, 100, 15, 5));
                    break;
                case 6:
                    _participantes.push_back(new Arqueiro(nome, 100, 15, 5));
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
        exibirVencedor();
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
        int numRounds = 1;
        srand(rand() % 100 + 1);
        int iniciativa = rand() % 2;
        while(p1->estaVivo() && p2->estaVivo() && numRounds < 10) {
            if(iniciativa == 0) {
                exibirRodadas(p1, p2, numRounds);
                p1->atacar(p2);
                p2->atacar(p1);
                if(p1->getSangramento() > 0) {
                p1->sangrar();
                }
                if(p2->getSangramento() > 0) {
                p2->sangrar();
                }
                system("pause");
            }
            else {
                exibirRodadas(p1, p2, numRounds);
                p2->atacar(p1);
                p1->atacar(p2);
                if(p1->getSangramento() > 0) {
                p1->sangrar();
                }
                if(p2->getSangramento() > 0) {
                p2->sangrar();
                }
                system("pause");
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

    void exibirVencedor()
    {
        int numParticipantes = _participantes.size();
        for(int i = 0; i < numParticipantes; i++) {
            if(_participantes[i]->estaVivo()) {
                system("cls");
                cout << "         " << _participantes[i]->getNome() << " venceu o torneio!" << endl;
                // printar troféu em ascii
                cout << "             ___________" << endl;
                cout << "            '._==_==_=_.'" << endl;
                cout << "            .-\\:      /-." << endl;
                cout << "           | (|:.     |) |" << endl;
                cout << "            '-|:.     |-'" << endl;
                cout << "              \\::.    /" << endl;
                cout << "               '::. .'" << endl;
                cout << "                 ) (" << endl;
                cout << "               _.' '._" << endl;
                _participantes[i]->exibirTotal();
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
