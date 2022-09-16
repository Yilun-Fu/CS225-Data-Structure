#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //


  Image photo;
  photo.readFromFile("../alma.png");

  Image I1;
  I1.readFromFile("../i.png");
  Image I2;
  I2.readFromFile("../i.png");
  Image I3;
  I3.readFromFile("../i.png");
  Image I4;
  I4.readFromFile("../i.png");

  StickerSheet testSheet(photo,3);

testSheet.addSticker(I2, 40, 45);
testSheet.addSticker(I3, 25, 75);
testSheet.addSticker(I4, 10, 100);

Image final = testSheet.render();

final.writeToFile("../myImage.png");
  return 0;
}
