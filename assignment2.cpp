#include <iostream>
#include <fstream>
#include <string>
//#include "image.h"

using namespace std;

/**
* Loads the image data from a file. Stops loading if the image file is corrupted.
*/
int **load(string imageFile, int &length, int &height);

/**
* Saves the image data from the memory into a file.
*/
void save(string imageFile, int **image, int length, int height);

/**
* Crops the image from a starting cell with specific length and height.
*/
int **crop(int **image, int length, int height, int cropRowStart, int cropColStart, int cropLength, int cropHeight);

/**
* Up-samples the image by a factor of 2.
*/
int **upSample(int **image, int length, int height, int &upLength, int &upHeight);

/**
* Down-samples the image by a factor of 2. If either of the image resolution is not an
* even number, Down-sample operation is aborted.
*/
int **downSample(int **image, int length, int height, int &downLength, int &downHeight);

/**
* Flips each pixel value into its opposite grayscale intensity value.
*/
void invert(int **image, int length, int height);

/**
* Shows the image data in separate lines.
*/
void show(int **image, int length, int height);

/**
* Frees the memory pointed by image pointer.
*/
void free(int **image, int &length, int &height);

int main()
{
  int length;
  int height;
  load("./resource/image.txt",length, height);
  cout<<length<<":";
  cout<<height<<":";
  cout<<endl;
}

int **load(string imageFile, int &length, int &height)
{

  ifstream inputfile(imageFile.c_str());
  if(inputfile.is_open()){
    inputfile >> length; //cin>>length
    inputfile >> height;
    int **ret = new int*[height];
      for(int row=0; row<height; row++){
        //set the current row of the returning array to a new array for the data in the row
        ret[row] = new int[length];
        for(int col=0; col<length; col++){
            inputfile>>ret[row][col];
            cout<<ret[row][col]<<" ";

      }
cout<<endl;
    }
  return ret;
}else{
  cout<<"bad user"<<endl;
  return 0;
}
}

/**
* Saves the image data from the memory into a file.
*/
void save(string imageFile, int **image, int length, int height)
{
  //ofstream myfile.open;
}

/**
* Crops the image from a starting cell with specific length and height.
*/
int **crop(int **image, int length, int height, int cropRowStart, int cropColStart, int cropLength, int cropHeight)
{
  return 0;
}

/**
* Up-samples the image by a factor of 2.
*/
int **upSample(int **image, int length, int height, int &upLength, int &upHeight)
{
  return 0;
}

/**
* Down-samples the image by a factor of 2. If either of the image resolution is not an
* even number, Down-sample operation is aborted.
*/
int **downSample(int **image, int length, int height, int &downLength, int &downHeight)
{
  return 0;
}

/**
* Flips each pixel value into its opposite grayscale intensity value.
*/
void invert(int **image, int length, int height)
{

}

/**
* Shows the image data in separate lines.
*/
void show(int **image, int length, int height)
{
}

/**
* Frees the memory pointed by image pointer.
*/
void free(int **image, int &length, int &height)
{
}
