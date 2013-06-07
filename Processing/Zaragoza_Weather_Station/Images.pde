/*
  Weather Station
  (c) Arduino Verkstad AB 2013
  Author: Clara Leivas
  
  This program visualizes the data gathered from a weather station. 
  The data is wind speed in RPS (rotations per seconds), temperature 
  in celsius, air humidity in %, sound pollution (this data is not of 
  a particular unit) and pictures taken with a small camera mounted 
  on the weather station.
  
  For more instructions on the weather station please see:
  http://cuartielles.com/verkstad/edu/CoursesSummerCampZGZEs/Ballooning
  
  Use left and right arrow key to scroll through the pictures and data.
*/

/** Image variables **/
PImage fade;
PImage tobbe;

int x, y, imgWidth, imgHeight, space;

/** setup image size and mode **/
void setupSmallImages(){
  imageMode(CENTER);
  rectMode(CENTER);
  
  fade = loadImage("fade.png");
  tobbe = loadImage("tobbe.png");
  
  imgWidth = img[0].width/20;
  imgHeight = img[0].height/20;
  space = 10;
  x = width/2;
  y = height/2+img[0].height/4+imgHeight/2+space;
}

/** draw small images **/
void drawSmallImages(){
  if(chooseImg==nmbOfLines-1){
    leftImgs(2);  
  }
  else if(chooseImg==nmbOfLines-2){
    leftImgs(2); 
    rightImgs(1);
  }
  else if(chooseImg==0){
    rightImgs(2); 
  } 
  else if(chooseImg==1){
    rightImgs(2);
    leftImgs(1);
  }  
  else if(chooseImg<nmbOfLines-1 && chooseImg>1){
     leftImgs(2);
     rightImgs(2);
  }

  image(fade, x,  y, 5*imgWidth+4*space, imgHeight);
  image(img[chooseImg], x, y, imgWidth, imgHeight);  
  
  rectMode(CENTER);
  noFill();
  stroke(80);
  strokeWeight(3);
  rect(x, y, imgWidth, imgHeight, 2);
}

/** images to the right of center **/
void rightImgs(int i){
  if(i==2)image(img[chooseImg+2], x+2*imgWidth+2*space, y, imgWidth, imgHeight);  
  image(img[chooseImg+1], x+imgWidth+space, y, imgWidth, imgHeight);
}

/** images to the lef of center **/
void leftImgs(int i){
    if(i==2)image(img[chooseImg-2], x-2*imgWidth-2*space, y, imgWidth, imgHeight);
    image(img[chooseImg-1],  x-imgWidth-space, y, imgWidth, imgHeight);  
}

/** draw Tobbe, the mascot **/
void drawTobbe(){
  imageMode(CORNER);
  int xt =x+img[0].width/4;
  int yt = height/2+img[0].height/4-3*tobbe.height/4;
  rectMode(CENTER);
  noFill();
  stroke(80);
  strokeWeight(5);
  rect(x+step, height/2, img[0].width/2, img[0].height/2, 4);

  image(tobbe, xt, yt);
  imageMode(CENTER);
}
