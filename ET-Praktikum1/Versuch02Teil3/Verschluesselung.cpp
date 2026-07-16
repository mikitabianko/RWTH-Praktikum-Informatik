#include <iostream>
#include <string>

using namespace std;

string verschluesseln(char schluessel[2][26], string wort)
{
	for (unsigned int i = 0; i < wort.length(); i++)
	{
		int position = wort[i] - 'A';

		if (position >= 0 && position < 26)
		{
			wort[i] = schluessel[1][position];
		}
	}
	return wort;
}

string entschluesseln(char schluessel[2][26], string wort)
{
	for (unsigned int i = 0; i < wort.length(); i++)
	{
		int position = wort[i] - 'A';

		if (position >= 0 && position < 26)
		{
			wort[i] = schluessel[1][position];
		}
	}
	return wort;
}

int main()
{
	char verschluesselungsTabelle[2][26];
	char entschluesselungsTabelle[2][26];
	string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string geheimAlphabet = "QWERTZUIOPASDFGHJKLYXCVBNM";
	string wort;

	for (unsigned int i = 0; i < alphabet.length(); i++)
	{
		verschluesselungsTabelle[0][i] = alphabet[i];
		verschluesselungsTabelle[1][i] = geheimAlphabet[i];

		entschluesselungsTabelle[0][i] = alphabet[i];
	}

	for (unsigned int i = 0; i < geheimAlphabet.length(); i++)
	{
		int position = geheimAlphabet[i] - 'A';
		entschluesselungsTabelle[1][position] = alphabet[i];
	}

	cout << "Bitte geben Sie ein Wort in Grossbuchstaben ein: ";
	cin >> wort;

	string verschluesseltesWort = verschluesseln(verschluesselungsTabelle, wort);
	string entschluesseltesWort = entschluesseln(entschluesselungsTabelle, verschluesseltesWort);

	cout << "Klartext: " << wort << endl;
	cout << "Verschluesselt: " << verschluesseltesWort << endl;
	cout << "Entschluesselt: " << entschluesseltesWort << endl;

	return 0;
}
