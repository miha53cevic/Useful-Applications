#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

int main()
{
	//User Interface
	std::string format;

	std::cout << "PNG\nJPG\nChoose : ";
	std::cin >> format;
	std::cout << "Place image into the folder with the .exe and rename it to 'pic'";

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
	else std::cout << "ERROR";




	// Getting color of pixel in grayshade and then converting to ascii \\

	/*
					 * The greyscale value is calculated according to
					 * the following formula
					 * GREY = 0.299 * RED + 0.587 * GREEN + 0.114 * BLUE
					 * For more information see http://en.wikipedia.org/wiki/Grayscale
	*/
	double redPart = 0.299;
	double greenPart = 0.587;
	double bluePart = 0.114;

	for (int i = 0; i < (int)image.getSize().y; i++)
	{
		for (int j = 0; j < (int)image.getSize().x; j++)
		{
			sf::Color pixelColor = image.getPixel(i, j);

			double greyShade = redPart * (double)pixelColor.r + greenPart * (double)pixelColor.g + bluePart * (double)pixelColor.b;
			
			image.setPixel(i, j, sf::Color::Color(greyShade, greyShade, greyShade));
		}
	}

	//Save grayscale version
	image.saveToFile("grayscale.jpg");

	std::cout << "\n";
	system("pause");
	return 0;
}