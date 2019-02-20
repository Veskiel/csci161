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
  int length ;
  int height;
  int upHeight;
  int upLength;
  int cropHeight =5;
  int cropLength = 4;
  int goodcrop = 3;
  //int badCrop =6;
  int downHeight;
  int downLength;


  const string filename = "./resource/image.txt";
//  const string filename = "./resource/bad.txt";
  int **image = load(filename,length, height);
if(image!=0){
  show(image, length, height);
}
cout<<endl;
//crop(image, length, height, badCrop , badCrop , cropHeight , cropLength);

int **croppedImage = crop(image, length, height, goodcrop , goodcrop , cropHeight , cropLength);
show(croppedImage, cropLength, cropHeight);
save("./resource/cropped.txt", croppedImage, cropLength, cropHeight);
cout<<endl;
int **upImage = upSample(image, length, height, upLength, upHeight);
show(upImage, upLength, upHeight);
save("./resource/upsampled.txt", upImage, upLength, upHeight);
cout<<endl;
//int **downImage =downSample(upImage, length, height, downLength, downHeight);
//show(downImage, downLength, downHeight);
//save("./resource/downsampled.txt",downImage, downLength, downHeight);
invert(image, length , height);
show(image, length, height);
save("./resource/Inverted.txt", image, length, height);
}


int **load(string imageFile, int &length, int &height)
{
  ifstream inputfile(imageFile.c_str());
  if(inputfile.is_open()){

    inputfile >> length; //cin>>length
    inputfile >> height;
    if(length<1||height<1){
      cout<<"invalid size"<<endl;
      return 0;
    }
    int **image = new int*[height];
    for(int row=0; row<height; row++){
      //set the current row of the returning array to a new array for the data in the row
      image[row] = new int[length];
      for(int col=0; col<length; col++){
        inputfile>>image[row][col];
        if(image[row][col] < 0 || image[row][col] > 255)
        {
          cout<<"invalid value in image"<<endl;
          free(image, length, row);
          return 0;
        }
      }
    }
    return image;
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
  ofstream outputfile(imageFile.c_str());
  outputfile<<image<<"\t";
  outputfile.close();
}

/**
* Crops the image from a starting cell with specific length and height.
*/
int **crop(int **image, int length, int height, int cropRowStart, int cropColStart, int cropLength, int cropHeight)
{

//  cout<<"in crop"<<endl;
  int **croppedImage = new int*[cropLength];
  for(int row = 0; row < cropLength; row++){
    croppedImage[row] = new int[cropHeight];
  }


  for(int i = 0; i < cropLength; i++){
      for(int j = 0; j < cropHeight; j++){
        croppedImage[i][j] = image[cropRowStart + i][cropColStart + j];
    }
  }
  return croppedImage;
}

/**
* Up-samples the image by a factor of 2.
*/
int **upSample(int **image, int length, int height, int &upLength, int &upHeight)
{
upLength = 2*length;
upHeight = 2*height;

  int **upImage = new int*[upHeight];
  for(int row=0;row<upHeight; row++)
  {
  upImage[row] = new int[upLength];
  }
    for(int i = 0; i < height; i++){
      for(int j = 0; j <length; j++){
        upImage[2*i][2*j] = image[i][j];
        upImage[2*i][2*j+1] = image[i][j];
        upImage[2*i+1][2*j] = image[i][j];
        upImage[2*i+1][2*j+1] =image[i][j];
      }

    }
  return upImage;
}

/**
* Down-samples the image by a factor of 2. If either of the image resolution is not an
* even number, Down-sample operation is aborted.
*/
int **downSample(int **image, int length, int height, int &downLength, int &downHeight)
{
  downLength = 2/length;
  downHeight = 2/height;

    int **downImage = new int*[downHeight];
    for(int row=0;row<downHeight; row++)
    {
    downImage[row] = new int[downLength];
    }
      for(int i = 0; i < height; i++){
        cout<<"inside first loop"<<endl;
        cout<<"i= " <<i <<endl;
        for(int j = 0; j <length; j++){
          cout<<"inside second loop"<<endl;
          cout<<"j= "<<j<<endl;
          downImage[i][j] = image[i*2][j*2];
        }

      }
    return downImage;
}

/**
* Flips each pixel value into its opposite grayscale intensity value.
*/
void invert(int **image, int length, int height)
{
  for(int i=0; i<height; i++){
    for(int j = 0; j < length; j++){
          image[i][j] = 255-image[i][j];

        }
      }
}
/**
* Shows the image data in separate lines.
*/
void show(int **image, int length, int height)
{
  for(int row=0; row<height; row++){
    for(int col=0; col<length; col++){
        cout<<image[row][col]<<"\t";
      }
  cout<<endl;
  }
}


/**
* Frees the memory pointed by image pointer.
*/
void free(int **image, int &length, int &height)
{
  for(int row=0; row<height; row++){
      delete[] image[row];
      }
  delete[] image;

}
