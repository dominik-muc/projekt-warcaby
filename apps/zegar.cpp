#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <thread>
#include <Warcaby/zegar.h>


void wypisz_czasy(std::string typ,int bialy,int czarny)
{
    std::cout << "\e[0;10H";
    if(typ=="pvp")
    {
        int bialymilisek=bialy%10,bialysek=(bialy/10)%60,bialymin=bialy/600;
        printf("BIALY: ");
        if(bialymin<10)
            printf("0");
        printf("%d:",bialymin);
        if(bialysek<10)
            printf("0");
        printf("%d.%d       ",bialysek,bialymilisek);
        int czarnymilisek=czarny%10,czarnysek=(czarny/10)%60,czarnymin=czarny/600;
        printf("CZARNY: ");
        if(czarnymin<10)
            printf("0");
        printf("%d:",czarnymin);
        if(czarnysek<10)
            printf("0");
        printf("%d.",czarnysek);
        printf("%d\n",czarnymilisek);
    }
    if(typ=="pve")
    {
        int bialymilisek=bialy%10,bialysek=(bialy/10)%60,bialymin=bialy/600;
        printf("BIALY: ");
        if(bialymin<10)
            printf("0");
        printf("%d:",bialymin);
        if(bialysek<10)
            printf("0");
        printf("%d.%d\n",bialysek,bialymilisek);
    }
}




int main()
{
    std::ifstream plik("danezegar.txt");
    std::string type,wywolanie;
    int time=180, start=0;
    if (!plik.is_open())
        std::cerr << "Nie można otworzyc pliku." << std::endl;

    while(start==0)
    {
        if(plik >> wywolanie)
        {
            if(wywolanie=="time")
                plik >> time;
            else if(wywolanie=="type")
                plik >> type;
            else if(wywolanie=="start")
                start=1;
        }
        else
        {
            plik.clear();
            plik.seekg(0, std::ios::end);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }
    std::cout << "\e[2J\e[H";
    int bialy=time*10,czarny=0;
    if(type=="pvp")
        czarny=time*10;

    int ktory=0,wczyt,x=0,linia=0;

    while((type=="pvp" && bialy>0 && czarny>0) || (type=="pve" && bialy>0))
    {
        wypisz_czasy(type,bialy,czarny);
        if(linia==0)
        {
            if(ktory==0)
                std::cout << "         -----\n";
            if(ktory==1)
                std::cout << "                              ------\n";
        }
	else
                std::cout << "                                       \n";
	
        linia^=1;
        if(plik >> wczyt)
        {
            if(x==1 && !ktory)
                bialy+=20;
            else if(x==1)
                czarny+=20;
            ktory^=1;
            x=1;
        }
        else
        {
            plik.clear();
            plik.seekg(0, std::ios::end);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if(!ktory)
            bialy--;
        else
            czarny--;
    }
    if(bialy==0)
        //tutaj przegrywa bialy
    else if(czarny==0 && type!="pvp")
        //tutaj przegrywa czarny 
    plik.close();
    //wyczyszczenie pliku danezegar
    std::ofstream plik1("danezegar.txt", std::ios::trunc);
    plik1.close();

    return 0;
}
