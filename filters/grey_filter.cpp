// Program: c++filters.cpp
//FCAI_OOP_2023/2024_year two_Assignment1_first submition
// Purpose: to make changes in certain image by using six filters
// Authors , IDs, & Emails:
// Mariam Mahmoud Ibrahim -> 20221207 -> 288mariam@gmail.com
// My team partners
// Malak Ahmed -> 20221157 -> malakeltabakh2020@gmail.com
// Hadeel Khaled -> 20220444 -> hadeelkhaled315@gmail.com
// Date: 5 oct 2023
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char photo[SIZE][SIZE];
unsigned char image[SIZE][SIZE];
unsigned char imageT[SIZE][SIZE];
int arr1[128][128];
int arr2[128][128];
int arr3[128][128];
int arr4[128][128];


void load_Image ();
void save_Image ();
void Black_White();
void merge_image();
void Invert ();
void flip_image();
void rotate90 ();
void rotate180 ();
void rotate270 ();
void LightOrDark();
void crop_image();
void detect_edges();
void enlarge (int k);
void shrink(int e);
void Mirror_Image ();
void shuffle (int k,int b, int a, int s);
void Blur();
void skew_horizontal(double k);
void skew_horizontal45();
void skew_vertical(double k);
void skew_vertical45();
bool menu();

int main() {
    cout<<"welcome to our program\n";
    bool flag=true;
    load_Image();
    while(flag){
        if (!menu())
            break;
    }
    cout<<"Thank you and hope you have enjoyed it\n";
    return 0;
}

//_________________________________________
void load_Image () {
    char imageFileName[100];
    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image (getting time)
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________________________________________
void save_Image () {
    char imageFileName[100];
    // Get gray scale image file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image (saving time)
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________________________________________
void Black_White() {
//to invert the image to black and white only
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

//if the approximate pixel value is near to 255 so make it equal to 255(white)
//if the approximate pixel value is near to 0 so make it equal to 0 (black)
            if (image[i][j] > 111)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}
//__________________________________________
void Invert() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

            //dark tones become light and vice verse
            image[i][j] = 255 - image[i][j];

            // invert colors
        }
    }
}

//_________________________________________
void merge_image() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            // cout<<image[i][j]<<" "<<photo[i][j]<<"\n";
            image[i][j]= (image[i][j]+photo[i][j])/2;


        }
    }
}
//_____________________________________________
void flip_image() {
//to choose a dimension the photo have to be flipped around
    char dim;
    cout<<"Do you want to flip the image vertically (V) or horizontally (H)? ";
    cin>>dim;
    if (dim=='V'|| dim=='v'){
        //if vertical, we will loop until the half of the image (from left to right) and swap each pixel with its corresponding one
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE/2; ++j) {
                swap(image[i][j],image[i][SIZE-j]);
            }
        }
    }
    else if (dim=='H'|| dim =='h'){
        //if vertical, we will loop until the half of the image (from up to down) and swap each pixel at the top with its corresponding one on the other half
        for (int i = 0; i < SIZE/2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                swap(image[i][j],image[SIZE-i][j]);
            }
        }
    }
}
//____________________________________________________

void rotate90() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            // swap(image[i][j],image[j][i]);
            int temp = image[i][j];
            image[i][j]=image[j][i];
            image[j][i]=temp;
            // transpose the matrix
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE/2; j++) {
            // swap(image[i][j],image[j][i]);
            int temp = image[i][j];
            image[i][j]=image[i][SIZE-j-1];
            image[i][SIZE-j-1]=temp;
            // reverse the matrix
        }
    }
}

//_________________________________________
void rotate180(){
    // to rotate 180 it means to rotate 90 two times so call it twice
    rotate90();
    rotate90();
}

//_________________________________________
void rotate270(){
    // to rotate 270 it means that rotate 90 first then rotate 90 again and finally
    // rotate 90 so i will call rotate90 function 3 times
    rotate90();
    rotate90();
    rotate90();
}


//--------------------------------------------
void LightOrDark() {
    char e;
    cout<<"which effect do you want to be applied? to light (l) or to dark (d) ";
    cin>>e;
    if (e=='l'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                if(image[i][j]+ ((255-image[i][j])/2)< 255) {
//increase the value of the pixel by the half of the remaining in order not to have an overflow
                    image[i][j]+= ((255-image[i][j])/2);
                }

            }
        }
    } else if (e=='d'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
//divide the color by 2, so it can be darker since black is equal to 0
                if(image[i][j]- (image[i][j]/2)> 0) {
                    image[i][j] -= (image[i][j] / 2);
                }
            }
        }
    }
}
//--------------------------------------------------------------------
void detect_edges() {
//make a photo with oly the detected edges of the original one

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            //compare each pixel with its neighbour, if the difference id a certain value (depends on if the difference seems a big value )
            //if yes, make this pixel black(an edge). If no, make it white(not considered as an edge)
            if (abs(image[i][j] - image[i][j+1] ) >= 30){
                image[i][j]=0;
            }else
                image[i][j]=255;
        }
    }

}
//---------------------------------------------
void enlarge(int k) {
    // k is variable to determine the quad of image
    if (k == 1) { // first quad
        for (int i = 0, t = 0; i < 127, t < SIZE; ++i, t += 2) {
            for (int j = 0, y = 0; j < 127, y < SIZE; ++j, y += 2) {
                // copy each pixel in original image and write it four times in other image
                int x = image[i][j];
                imageT[t][y] = x;
                imageT[t + 1][y] = x;
                imageT[t][y + 1] = x;
                imageT[t + 1][y + 1] = x;
            }
        }
    } else if (k == 2) { // second quad
        for (int i = 0, t = 0; i < 127, t < SIZE; ++i, t += 2) {
            for (int j = 127, y = 0; j < SIZE, y < SIZE; ++j, y += 2) {
                // copy each pixel in original image and write it four times in other image
                int x = image[i][j];
                imageT[t][y] = x;
                imageT[t + 1][y] = x;
                imageT[t][y + 1] = x;
                imageT[t + 1][y + 1] = x;
            }
        }
    } else if (k == 3) { // third quad
        for (int i = 127, t = 0; i < SIZE, t < SIZE; ++i, t += 2) {
            for (int j = 0, y = 0; j < 127, y < SIZE; ++j, y += 2) {
                // copy each pixel in original image and write it four times in other image
                int x = image[i][j];
                imageT[t][y] = x;
                imageT[t + 1][y] = x;
                imageT[t][y + 1] = x;
                imageT[t + 1][y + 1] = x;
            }
        }
    } else if (k == 4) { // fourth quad
        for (int i = 127, t = 0; i < SIZE, t < SIZE; ++i, t += 2) {
            for (int j = 127, y = 0; j < SIZE, y < SIZE; ++j, y += 2) {
                // copy each pixel in original image and write it four times in other image
                int x = image[i][j];
                imageT[t][y] = x;
                imageT[t + 1][y] = x;
                imageT[t][y + 1] = x;
                imageT[t + 1][y + 1] = x;
            }
        }
    }
    //coping all work done on the new image to the original one
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = imageT[i][j];}
//-------------------------------------------------
void shrink(int e) {
    unsigned char n[SIZE][SIZE];
    int x=0;
    int i,j;
//calculate the sum of surrounding 4 pixels and put them in targeted pixel then move by 2
    for (i = 0; i < SIZE-1; i+=e) {
        int y=0;
        for ( j = 0; j< SIZE-1; j+=e) {
            int sum=0, count=0;
            for(int w=0; w<e ;w++){
                for(int z=0 ; z<e; z++) {
                    sum += image[i+w][j+z];
                    count++;
                    //cout<<count<<" ";
                }
            }
            n[x][y]=sum/count;
            y++;

        }
        x++;

    }
    for ( i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (i < 255/e && j < 255/e) {
                image[i][j] = n[i][j];
            } else
                image[i][j] = 255;
        }
    }}
//-------------------------------------------
void  Mirror_Image () {
//to choose a half and copy it as it is on the other side
    string half;
    cout<<"which half do you want to be mirrored?";
    cin>>half;
    // for left or right, we loop to the half of the picture from left to right the copy each pixel to the other side of the picture but from right to lef
    //(size-j) means that we copy a pixel on the other side according to the opposite position
    if (half=="left"){
        for (int i = 0; i <SIZE; ++i) {
            for (int j = 0; j < SIZE/2; ++j) {
                image[i][SIZE-j]=image[i][j];
            }
        }
    }
    else if (half=="right"){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE/2; ++j) {
                image[i][j]=image[i][SIZE-j];
            }
        }
    }
        // for up or down , we loop to the half of the picture from up to down the copy each pixel to the other side of the picture but from down to up
        //(size-i) means that we copy a pixel on the other side according to the opposite position
    else if (half=="up"){
        for (int i = 0; i < SIZE/2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[SIZE-i][j]=image[i][j];
            }
        }
    }
    else if (half=="down"){
        for (int i = 0; i < SIZE/2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j]=image[SIZE-i][j];
            }
        }
    }
}
//--------------------------------------------------
void shuffle (int k, int b, int a, int s){
    // k b a s is my quarters order
    for (int i = 0 , t=0,y=127,n=127 , B=0; i < 127,t<127,y<SIZE,n<SIZE , B<128; ++i,++t,++y,++n,B++) {
        for (int j = 0 ,d=127,l=0,m=127 ,A=0 ; j < 127,d<SIZE,l<127,m<SIZE , A<128; ++j,++d,++l,++m,++A) {
            // making array of each quad that contain n quad of original image
            arr1[B][A]=image[i][j];
            arr2[B][A]=image[t][d];
            arr3[B][A]=image[y][l];
            arr4[B][A]=image[n][m];
        }
    }
    // k is for first quad in the new image (imageT) while it's value is the number of quad in the
    // original image
    if(k==1){// copy first quad into first place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t ++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y ++) {
                image[i][j]=arr1[t][y];
            }
        }
    }
    else if (k==2) {// copy second quad into first place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y++) {
                image[i][j] = arr2[t][y];
            }
        }
    }
    else if(k==3){// copy third quad into first place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t ++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y ++) {
                image[i][j]=arr3[t][y];
            }
        }
    }
    else if (k==4){// copy fourth quad into first place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t ++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y ++) {
                image[i][j]=arr4[t][y];
            }
        }
    }// b is for second quad in the new image (imageT) while it's value is the number of quad in the
    // original image
    if(b==1){// copy first quad into second place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr1[t][y];
            }
        }
    }
    else if (b==2){// copy second quad into second place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr2[t][y];
            }
        }
    }
    else if (b==3){// copy third quad into second place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr3[t][y];
            }
        }
    }
    else if (b==4){// copy fourth quad into second place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr4[t][y];
            }
        }
    }// a is for third quad in the new image (imageT) while it's value is the number of quad in the
    // original image
    if(a==1){// copy first quad into third place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y ++) {
                image[i][j]=arr1[t][y];
            }
        }
    }
    else if (a==2){// copy second quad into third place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y ++) {
                image[i][j]=arr2[t][y];
            }
        }
    }
    else if (a==3){// copy third quad into third place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y ++) {
                image[i][j]=arr3[t][y];
            }
        }
    }
    else if (a==4){// copy fourth quad into third place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y ++) {
                image[i][j]=arr4[t][y];
            }
        }
    }
    // s is for fourth and last quad in the new image (imageT) while it's value is the number of quad in the
    // original image
    if(s==1){// copy first quad into fourth place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr1[t][y];
            }
        }
    }
    else if (s==2){// copy second quad into fourth place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr2[t][y];
            }
        }
    }
    else if (s==3){// copy third quad into fourth place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr3[t][y];
            }
        }
    }
    else if (s==4){// copy fourth quad into fourth place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr4[t][y];
            }
        }
    }
    /*for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = imageT[i][j];*/
}
//---------------------------------------------------------
void Blur() {
    unsigned char n[SIZE][SIZE];
    int i,j;
    for (i = 0; i < 256; i++) {
        for (j = 0; j < 256; j++) {
            int sum = image[i][j];
            int count = 1;
            int x,y;
            // calculate the average of the surrounding pixels and then divide the sum on the number of them
            for ( x = -2; x <= 2; x++) {
                for ( y = -2;y <= 2; y++) {
                    if (i + x >= 0 && i + x < 256 && j + y >= 0 && j + y < 256) {
                        sum += image[i + x][j + y];
                        count++;
                    }
                }
            }

            n[i][j] = sum / count;
        }
    }


    for ( i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            image[i][j] = n[i][j];

        }
    }
}
//-------------------------------------------------------------
void crop_image() {
//we crop the image starting from an index according to a specific length and width
    int x,y,l,w;
    cout<<"Enter an x, y position and length and width: ";
    cin>>x>>y>>l>>w;
// if a pixel position is less than x or y (outside the chosen index) or it is bigger than (x+l) or (y+w) (outside the specific length and width needed,
//this means that the pixel is outside the boundaries, and we make the pixel white
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (i < x || i > x + l || j < y || j> y + w) {
                image[i][j] = 255;}

        }

    }}
//--------------------------------------------------------------

void skew_horizontal(double k){
    // continue
    double pi=2*acos(0.0);// to get pi accurate value
    k=(pi*k)/180;// to get angle by radian
    double let=tan(k)*256;// get # of pixels will be white (to leave it )
    double n=256.0/(256-let);// get # of pixels will be taken from old image (compressed image)
    double start = let/256/* steps i will move (make it like ladder)*/,used=0,help;
    int moved=0,pixs=0;// pixels avg that i will copy & number olf pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to make all new image white
            imageT[i][j] = 255;
    for (int i = 0; i < SIZE; i++){// move on row and rows will be constants
        help=0;// curent this will define where i should start and where i will end
        for (int j = let-used; j < SIZE-used; j++){// loop for column begin from # of pixels i will leave in new image
            moved=0,pixs=0;
            for( int m =max(0,(int)ceil(help-n))/* to get region and to avoid -ve values*/;m<min(SIZE,(int)ceil(help+n))/* to make sure it will not get out SIZE*/;++m,++pixs){// loop on old image
                // pixels i need to use & increment pixels #
                moved+=image[i][m];
            }// sum of all pixels will be compressed
            moved/=max(1,pixs);// get pixels average (sum of them/there number)
            imageT[i][j]=moved;
            help+=n;// no. of pixels used
        }
        used+=start;
    }
    /*int start=SIZE-1,end=sqrt((255*255)+(rest*rest));
    for (int i = n; i < SIZE; i+=n){
        for (int j = 0; j < SIZE; j++){
            imageT[end][start]=image[i][j];
        }
    }*/
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to copy new image in old one
            image[i][j] = imageT[i][j];
}
void skew_horizontal45(){
    //it will give me straight line in the off diagonal of the matrix
    int f=255;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to make all new image white
            imageT[i][j] = 255;
    for(int i=0; i<SIZE; ++i)
        //make straight line diagonally
        imageT[i][f--]=0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to copy new image in old one
            image[i][j] = imageT[i][j];
}
void skew_vertical(double k){
    // continue
    double pi=2*acos(0.0);// to get pi accurate value
    k=(pi*k)/180;// to get angle by radian
    double let=tan(k)*256;// get # of pixels will be white (to leave it )
    double n=256.0/(256-let);// get # of pixels will be taken from old image (compressed image)
    double start = let/256/* steps i will move (make it like ladder)*/,used=0,help;
    int moved=0,pixs=0;// pixels avg that i will copy & number olf pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to make all new image white
            imageT[i][j] = 255;
    for (int i = 0; i < SIZE; i++){// move on column and columns will be constants
        help=0;// curent this will define where i should start and where i will end
        for (int j = let-used; j < SIZE-used; j++){// loop for row begin from # of pixels i will leave in new image
            moved=0,pixs=0;
            for( int m =max(0,(int)ceil(help-n))/* to get region and to avoid -ve values*/;m<min(SIZE,(int)ceil(help+n))/* to make sure it will not get out SIZE*/;++m,++pixs){// loop on old image
                // pixels i need to use & increment pixels #
                moved+=image[m][i];
            }// sum of all pixels will be compressed
            moved/=max(1,pixs);// get pixels average (sum of them/there number)
            imageT[j][i]=moved;//row become column and vice versa
            help+=n;// no. of pixels used
        }
        used+=start;
    }
    /*int start=SIZE-1,end=sqrt((255*255)+(rest*rest));
    for (int i = n; i < SIZE; i+=n){
        for (int j = 0; j < SIZE; j++){
            imageT[end][start]=image[i][j];
        }
    }*/
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to copy new image in old one
            image[i][j] = imageT[i][j];
}
void skew_vertical45(){
    //it will give me straight line in the principal diagonal of the matrix
    int f=255;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to make all new image white
            imageT[i][j] = 255;
    for(int i=0; i<SIZE; ++i)
        //make straight line diagonally
        imageT[f--][i]=0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to copy new image in old one
            image[i][j] = imageT[i][j];
}
bool menu(){
    // function to resending menu till user type 0
    char n,s,m;
    int a,b,c,d;
    double q;
    string t;
    char mergeFileName[100];
    cout<<"please choose filter from 0 to 9 or from a to s:\n";
    cout<<"1-Black and White Filter\n"<<"2-Invert Filter\n"<<"3-Merge Filter\n"<<"4-Flip Filter\n"<<"5-Rotating Filter\n"<<"6-Darken and Lighten Filter\n"<<"7-Detect Image Edges\n"<<"8-Enlarge Image\n"<<"9-Shrink Image\n"<<"a-Mirror Image\n"<<"b-Shuffle Image\n"<<"c-Blur Image\n"<<"d-Crop Image\n"<<"e-Skew Horizontally\n"<<"f-skew vertically\n"<<"s-Save image to file\n"<<"0-Exit\n";
    cin>>m;
    switch(m){
        case '1':
            Black_White();
            return true;
            break;
        case '2':
            Invert();
            return true;
            break;
        case '3':
            cout<<"Please enter name of image file to merge with:";
            cin >> mergeFileName;
            strcat (mergeFileName, ".bmp");
            readGSBMP(mergeFileName,photo);
            merge_image();
            return true;
            break;
        case '4':
            flip_image();
            return true;
            break;
        case '5':
            cout<<"choose one of directions\n 1-90\n 2-180\n 3-270\n";
            cin>>n;
            if(n=='1') {
                rotate90();
            }
            else if (n=='2'){
                rotate180();
            }
            else if (n=='3'){
                rotate270();
            }
            return true;
            break;
        case '6':
            LightOrDark();
            return true;
            break;
        case '7':
            detect_edges();
            return true;
            break;
        case '8':
            cout<<"please enter which quad do you want\n 1-first\n 2-second\n 3-third\n 4-fourth\n";
            cin>>a;
            enlarge(a);
            return true;
            break;
        case '9':
            cout<<"enter ratio you want to shrink with\n 1-(1/2)\n 2-(1/3)\n 3-(1/4)\n";
            cin>>t;
            if(t=="1/2")
                shrink(2);
            if(t=="1/3")
                shrink(3);
            if(t=="1/4")
                shrink(4);
            return true;
            break;
        case 'a':
            Mirror_Image();
            return true;
            break;
        case 'b':
            cout<<"please enter the order you want to shuffle the image\n";
            cin>>a>>b>>c>>d;
            shuffle(a,b,c,d);
            return true;
            break;
        case 'c':
            Blur();
            return true;
            break;
        case 'd':
            crop_image();
            return true;
            break;
        case 'e':
            cout<<"please enter an angle to skew horizontally image according to it\n";
            cin>>q;
            if(q!=45)
                skew_horizontal(q);
            else
                skew_horizontal45();
            return true;
            break;
        case 'f':
            cout<<"please enter an angle to skew vertically image according to it\n";
            cin>>q;
            if(q!=45)
                skew_vertical(q);
            else
                skew_vertical45();
            return true;
            break;
        case 's':
            save_Image();
            cout<<"Choose :\n n-New Image and More filters\n e-Exit\n";
            cin>>s;
            if (s =='n'){
                load_Image();
                return true;
            }
            else{return false;}

        case '0':
            return false;
    }
}
