#include <iostream>
#include <ctime>

void Amesteca(bool baCartiDate[]);
int UrmatoareaCarte(bool baCartiDate[]);
int PunctajMana(int iaMana[], const int kiContorCarte);
void AfiseazaCarte(int iCarte);
void AfiseazaMana(int iaMana[], const int kiContorCarte);
void AfiseazaPsiM(int iaManaCasa[], const int kiContorCartiC, int iaManaJucator[], const int kiContorCartiJ); //Afiseaza mainile si punctajul

int main() {
	using namespace std;
	//Aceasta secventa de instructiuni este folosita ca functia rand()
	//sa afiseze la fiecare executie carti diferite
	time_t timp;
	time(&timp);
	srand(timp);

	bool baCartiDate[52];
	int iContorCartiC = 0;
	int iaManaCasa[12];
	int iContorCartiJ = 0;
	int iaManaJucator[12];  //Jucatorul poate sa aiba in mana maxim 11 carti (4 de 1, 4 de 2, 3 de 3) (aproape imposibil, stiu:) )
							//La a 12-a carte pierde automat

	//Acest ciclu se executa odata pentru fiecare mana
	while(true) {

		//Amesteca cartile. Vezi functia corespunzatoare
		Amesteca(baCartiDate);
		//Impartirea cartilor. 2 carti pentru casa, 2 pentru jucator.
		iaManaJucator[0]	= UrmatoareaCarte(baCartiDate);
		iaManaCasa[0]		= UrmatoareaCarte(baCartiDate);
		iaManaJucator[1]	= UrmatoareaCarte(baCartiDate);
		iaManaCasa[1]		= UrmatoareaCarte(baCartiDate);
		iContorCartiC		= 2;
		iContorCartiJ		= 2;
		//Afiseaza mesaj pentru inceperea unei maini noi
		cout<<endl<<"================================================================================"<<endl;
		cout<<"+------------------------+"<<endl;
		cout<<"|----------Mana----------|"<<endl;
		cout<<"|----------Noua----------|"<<endl;
		cout<<"+------------------------+"<<endl;

		//In acest joc jucatorul are doua optiuni: Hit sau Stand.
		//Hit -> Mai primeste o carte; Stand -> Nu mai primeste
		char cOptiuneJucator;
		bool bHit	= true;
		int iPunctajJucator	= PunctajMana(iaManaJucator, iContorCartiJ);
		// Daca playerul mai doreste o carte, primeste dupa care se calculeaza scorul si se afiseaza mana.
		do{
			//Afiseaza mainile (se afiseaza doar o carte a casei si 2 ale jucatorului)
			cout << "Mana Casei" << endl;
			cout << "[] ";
			AfiseazaCarte(iaManaCasa[1]);
			cout << endl;
			cout << "Mana Jucatorului: Punctaj = " << PunctajMana(iaManaJucator, iContorCartiJ) << endl;
			AfiseazaMana(iaManaJucator, iContorCartiJ);


			cout << "D daca mai doriti o carte sau N daca va opriti:";
			cin >> cOptiuneJucator;
			if (cOptiuneJucator == 'D' || cOptiuneJucator == 'd') {
				iaManaJucator[iContorCartiJ] = UrmatoareaCarte(baCartiDate);
				++iContorCartiJ;
			} else if (cOptiuneJucator == 'N' || cOptiuneJucator == 'n') {
				bHit = false;
			} else {
				cout << "Eroare: Incearca din nou" << endl;
			}
			cout << endl;

			//Calculeaza Punctaj
			iPunctajJucator	= PunctajMana(iaManaJucator, iContorCartiJ);
		} while (bHit && iPunctajJucator < 22);

		// Daca jcuatorul nu mai doreste carti se verifica cine a castigat
		if (iPunctajJucator > 21) {
			// Casa castiga
			cout << "**** Casa a castigat!!! ****" << endl;
			AfiseazaPsiM(iaManaCasa, iContorCartiC, iaManaJucator, iContorCartiJ);
		} else {
			// Daca jucatorul nu a pierdut si casa este sub 17 pct, casa mai ia carti
			int iPunctajCasa		= PunctajMana(iaManaCasa, iContorCartiC);
			while (iPunctajCasa < 17) {
				iaManaCasa[iContorCartiC] = UrmatoareaCarte(baCartiDate);
				++iContorCartiC;
				iPunctajCasa		= PunctajMana(iaManaCasa, iContorCartiC);
			}
			bool bCasaPierde	= (iPunctajCasa > 21);
			if (bCasaPierde) {
				// Casa pierde, jucatorul castiga
				cout << "**** Jucatorul a castigat!!! ****" << endl;
				AfiseazaPsiM(iaManaCasa, iContorCartiC, iaManaJucator, iContorCartiJ);
			} else {
				// Compara punctajele
				if (iPunctajJucator == iPunctajCasa) {
					//Egalitate
					cout << "**** Egalitate!!! ****" << endl;
					AfiseazaPsiM(iaManaCasa, iContorCartiC, iaManaJucator, iContorCartiJ);
				} else if (iPunctajJucator > iPunctajCasa) {
					// Jucatorul castiga
					cout << "**** Jucatorul a castigat!! ****" << endl;
					AfiseazaPsiM(iaManaCasa, iContorCartiC, iaManaJucator, iContorCartiJ);
				} else {
					// Casa castiga
					cout << "**** Casa a castigat!!! ****" << endl;
					AfiseazaPsiM(iaManaCasa, iContorCartiC, iaManaJucator, iContorCartiJ);
				}
			}
        }
	}
 	return EXIT_SUCCESS;
}


//Aceasta functie seteaza toate cartile din pachet ca fiind neimpartite
void Amesteca(bool baCartiDate[]) {
	for (int iContor=0; iContor<52; ++iContor) {
		baCartiDate[iContor]=false;
	}
}

//Aceasta functie returneaza valoarea unei carti noi si verifica daca a fost sau nu impartita deja
int UrmatoareaCarte(bool baCartiDate[]) {
	bool bCarteData	= true;
	int iCarteNoua	= -1;
	do {
		iCarteNoua = (rand() % 52);
		if (!baCartiDate[iCarteNoua]) {
			bCarteData = false;
		}
	} while (bCarteData);
	return iCarteNoua;
}

int PunctajMana(int iaMana[], const int kiNumarCarte) {
	int iContorAs	= 0;
	int iPunctaj	= 0;
	for (int iContorCarti = 0; iContorCarti < kiNumarCarte; ++iContorCarti) {
		const int kiUrmatoareaCarte = iaMana[iContorCarti];
		const int kiRang = (kiUrmatoareaCarte % 13);
		if (kiRang == 0) {
			++iContorAs;
			++iPunctaj;
		} else if (kiRang < 9) {
			iPunctaj = iPunctaj + (kiRang + 1);
		} else {
			iPunctaj = iPunctaj + 10;
		}
	}
	while (iContorAs > 0 && iPunctaj < 12) {
		--iContorAs;
		iPunctaj = iPunctaj + 10;
	}
	return iPunctaj;
}

void AfiseazaMana(int iaMana[], const int kiNumarCarte) {
	using namespace std;
	for (int iContorCarti = 0; iContorCarti < kiNumarCarte; ++iContorCarti) {
		const int kiUrmatoareaCarte = iaMana[iContorCarti];
		AfiseazaCarte(kiUrmatoareaCarte);
		cout << " ";
	}
	cout << endl;
}

void AfiseazaCarte(int iCarte) {
	using namespace std;
	//Afiseaza Rang
	const int kiRang = (iCarte % 13);
	if (kiRang == 0) {
		cout << 'A';
	} else if (kiRang < 9) {
		cout << (kiRang + 1);
	} else if (kiRang == 9) {
		cout << "10";
	} else if (kiRang == 10) {
		cout << 'J';
	} else if (kiRang == 11) {
		cout << 'Q';
	} else {
		cout << 'K';
	}

}

void AfiseazaPsiM(int iaManaCasa[], const int kiContorCartiC, int iaManaJucator[], const int kiContorCartiJ) {
	using namespace std;
	cout << "Mana Casei: Punctaj = " << PunctajMana(iaManaCasa, kiContorCartiC) << endl;
	AfiseazaMana(iaManaCasa, kiContorCartiC);
	cout << "Mana Jucatorului: Punctaj = " <<PunctajMana(iaManaJucator, kiContorCartiJ) << endl;
	AfiseazaMana(iaManaJucator, kiContorCartiJ);
	cout << endl;
}
