#pragma once
#include "Dino.h"
#include "DinoType.h"
#include "Utils.h"

class Player 
{

public:
    int balance = 500; 
    std::vector<Dino*> dinos;
    std::vector<Dino*> selectedDinos;

    void addDino(Dino* dino) 
    {
        dinos.push_back(dino);
    }

    void deleteDino(Dino* dino) 
    {
        dinos.erase(std::remove(dinos.begin(), dinos.end(), dino), dinos.end());
    }

    void randomDinoPull()
    {
        for (int i = 0; i < 3; i++)
        {
            DinoPerkType type = static_cast<DinoPerkType>(rand() % 3);
            DinoType dinoType = static_cast<DinoType>(rand() % 3);
            switch (dinoType) {
            case STAT_STR:
                selectedDinos.push_back(new DinoStr(dinoType));
                break;
            case STAT_DEX:
                selectedDinos.push_back(new DinoDex(dinoType));
                break;
            case STAT_INT:
                selectedDinos.push_back(new DinoInt(dinoType));
                break;
            default:
                break;
            }
        }
    }

    void attackEnemy(Player& enemy, std::vector<Dino*>& dinosToAttack, Terrain terrain)
    {
        if (dinosToAttack.empty() || selectedDinos.empty()) {
            return;
        }

        Dino* enemyDino = dinosToAttack.back();

        Dino* myDino = selectedDinos.back();
        myDino->triggerAttack();

        int damage = myDino->damage(terrain);

        if (enemyDino->ProcessDamage(damage)) {
            enemyDino->isDead = true;  // Отмечаем динозавра как мертвого
        }
    }



    void saveDinosToFile(const std::string& filename) {
        std::ofstream file(filename, std::ios::trunc);
        if (file.is_open()) {
            file << balance << "\n";

            for (const Dino* dino : dinos) {
                file << dino->type << " " << dino->HP << " " << dino->cost << "\n";
            }
            file.close();
        }
        
    }



    void loadDinosFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            dinos.clear();
            std::string balanceLine;
            if (std::getline(file, balanceLine)) {
                balance = std::stoi(balanceLine);
            }
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                int type, hp, cost;
                if (iss >> type >> hp >> cost) {
                    DinoType dinoType = static_cast<DinoType>(type);
                    Dino* dino = nullptr;
                    switch (dinoType) {
                    case Tyrannosaur:
                        dino = new DinoStr(dinoType);
                        break;
                    case Brachiosaurus:
                        dino = new DinoDex(dinoType);
                        break;
                    case Triceratops:
                        dino = new DinoInt(dinoType);
                        break;
                    }
                    if (dino) {
                        dino->HP = hp;
                        dino->cost = cost;
                        dinos.push_back(dino);
                    }
                }
            }
            file.close();
        }
    }



};