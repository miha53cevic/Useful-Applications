#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

std::string getSymbol(double l_greyShade)
{
	if (l_greyShade >= 230)
		return " ";
	else if (l_greyShade >= 205)
		return ".";
	else if (l_greyShade >= 190)
		return "-";
	else if (l_greyShade >= 165)
		return ":";
	else if (l_greyShade >= 140)
		return "=";
	else if (l_greyShade >= 115)
		return "+";
	else if (l_greyShade >= 90)
		return "x";
	else if (l_greyShade >= 65)
		return "#";
	else if (l_greyShade >= 40)
		return "%";
	else if (l_greyShade >= 0)
		return "@";
}

int main()
{
	//User Interface
	std::string format;

	std::cout << "Stavi sliku u mjesto gdje se nalazi .exe i nazovi ju: 'pic'\n\n";
	std::cout << "PNG\nJPG\n\nIzaberi Format Slike iz ponudenih: ";
	std::cin >> format;

	//Change choice to all caps
	for (auto &i : format)
	{
		i = toupper(i);
	}

	sf::Image image;

	//Loading Image
	if (format == "JPG")
	{
		image.loadFromFile("pic.jpg");
	}
	else if (format == "PNG")
	{
		image.loadFromFile("pic.png");
	}
	else exit(0);

	//Koliko zelis da se piksela gleda kao jedan ASCII Charachter
	int Width = 0;

	std::cout << "Unesi velicinu koliko zelis da se piksela gleda kao jedan ASCII Charachter ( 1 - 10 ovisno o velicini slike ) : ";
	std::cin >> Width;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Getting color of pixel in grayshade and then converting to ascii
	std::ofstream writer("asciiPicture.txt");

	double redPart = 0.299;
	double greenPart = 0.587;
	double bluePart = 0.114;

	/*
		* The greyscale value is calculated according to
		* the following formula
		* GREY = 0.299 * RED + 0.587 * GREEN + 0.114 * BLUE
		* For more information see http://en.wikipedia.org/wiki/Grayscale
	*/

	//Verzija za 1:1 skliranje znaci 1 piksel 1 charachter
	if (Width == 0)
	{
		for (int i = 0; i < (int)image.getSize().y; i++)
		{
			for (int j = 0; j < (int)image.getSize().x; j++)
			{
				sf::Color pixelColor = image.getPixel(j, i);	//Prima [x][y]

				double greyShade = redPart * (double)pixelColor.r + greenPart * (double)pixelColor.g + bluePart * (double)pixelColor.b;

				/*		
						* Ispis i naði ascii simbol za tu vrijednost boje od 0 - 255
						* Gdje je 0 crna boja a 255 bijela boja
				*/

				writer << getSymbol(greyShade);
			}
			writer << "\n";
		}
	}



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Ovo Radi sa 1 Width, a to je zapravo 0 pa ovaj kod kod gore nije potreban, ali je ostavljen jer je brzi u kompilaciji
	else if (Width > 0)
	{
		std::vector<double> ValueHolder;

		for (int i = 0; i < (int)image.getSize().y / Width; i++)
		{
			for (int j = 0; j < (int)image.getSize().x / Width; j++)
			{
				sf::Color pixelColor;
				double greyShade;

				for (int k = 0; k < Width; k++)
				{
					for (int l = 0; l < Width; l++)
					{
						//Gleda sve piksele desno i ispod toga piksela koji je pocetni
						pixelColor = image.getPixel(j * Width + k, i * Width + l);

						greyShade = redPart * (double)pixelColor.r + greenPart * (double)pixelColor.g + bluePart * (double)pixelColor.b;

						ValueHolder.push_back(greyShade);
					}
				}

				double sum = 0;

				for (auto &i : ValueHolder)
				{
					sum += i;
				}

				greyShade = sum / ValueHolder.size();

				writer << getSymbol(greyShade);

				ValueHolder.clear();
			}
			writer << "\n";
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Close .txt document
	writer.close();

	//Signal Finish
	std::cout << "\n\nGotova pretvora - provjeri mjesto gdje se nalazi .exe za .txt";

	std::cout << "\n";
	system("pause");
	return 0;
}