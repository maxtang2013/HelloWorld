#include "pngwriter.h"
#include <iostream>

int main(int argc, char**argv)
{
    if (argc != 3)
    {
        std::cout << "Usage:\n"
                  << "  GenAlpha src dst\n";
        return -1;
    }


    pngwriter reader;
    reader.readfromfile(argv[1]);

    int width = reader.getwidth();
    int height = reader.getheight();

#ifdef PRINTSRCINFO	
    std::cout << width <<"," << height << " :" << reader.getbitdepth() << std::endl;
#endif

    pngwriter writer(width, height, 0, argv[2]);

    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            int alpha = reader.read(i+1, j+1, 4);
            writer.plot(i, j, alpha, alpha, alpha);
        }
    }

	writer.write_png();
	writer.close();

	return 0;
}
