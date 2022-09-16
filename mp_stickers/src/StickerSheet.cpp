#include "StickerSheet.h"
#include "Image.h"
using namespace std;


StickerSheet::StickerSheet(const Image & picture, unsigned max) {
  max_ = max;
  basePic_= picture;
  x_array = new unsigned[max];
  y_array = new unsigned[max];
  stickers_= new sticker[max_];
  for (unsigned i = 0; i < max_; i++){
    stickers_[i].im = NULL;
  }
  count_=0;
}

StickerSheet::~StickerSheet(){
  _delete();
}

void StickerSheet::_delete(){
  if(stickers_!=NULL){
    delete[] stickers_;
    stickers_ = NULL;
  }
  delete[] x_array;
  delete[] y_array;
}


StickerSheet::StickerSheet(const StickerSheet &other){
  _copy(other);
}

void StickerSheet::_copy(const StickerSheet& other){
  basePic_ = other.basePic_;
  max_ = other.max_;
  count_ = other.count_;
  stickers_ = new sticker[max_];
  for (unsigned i=0;i<max_;i++){
    stickers_[i].im=NULL;
  }
  for (unsigned i=0;i<count_;i++){
    stickers_[i].im= new Image(*(other.stickers_[i].im));
    stickers_[i].x=other.stickers_[i].x;
    stickers_[i].y=other.stickers_[i].y;
  }
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
  _delete();
  _copy(other);
  return *this;
}
void StickerSheet::changeMaxStickers(unsigned max){
  sticker* oldcopy=stickers_;
  stickers_ = new sticker[max];
  unsigned new_max_num = (max<count_ ? max:count_);
  for (unsigned i=0; i < new_max_num; i++){
    stickers_[i] = oldcopy[i];
    stickers_[i].im =new Image(*(oldcopy[i].im));
    delete oldcopy[i].im;
  }

  if (max<count_){
    for (unsigned i=max_;i<count_;i++){
      delete oldcopy[i].im;
    };
    count_=max;
  }
  delete [] oldcopy;
  max_=max;
}


int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
  if (count_==max_) return -1;
  stickers_[count_].im= new Image(sticker);

  stickers_[count_].x=x;
  stickers_[count_].y=y;

  return count_++;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (index > max_) {
    return false;
  }
  if (stickers_[index].im == NULL) {
    return false;
  }
  stickers_[index].x=x;
  stickers_[index].y=y;
  return true;
}


void StickerSheet::removeSticker(unsigned index){
  if (index<max_ && stickers_[index].im!=NULL){

    delete stickers_[index].im;
    for (unsigned i=index+1;i<count_;i++){
      stickers_[i-1]=stickers_[i];
    }
    stickers_[count_-1].im=NULL; 
    count_--;
  }
}

Image * StickerSheet::getSticker(unsigned index) {
  if (index < max_ && stickers_[index].im != NULL) {
    return  stickers_[index].im;
  }
  return NULL;
}

Image StickerSheet::render() const{

  unsigned maxw=basePic_.width(),maxh=basePic_.height();
  for (unsigned i=0;i<count_;i++){
    unsigned pwidth=stickers_[i].im->width()+stickers_[i].x;
    maxw=(pwidth>maxw ? pwidth:maxw);
    unsigned pheight=stickers_[i].im->height()+stickers_[i].y;
    maxh=(pheight>maxh ? pheight:maxh);
  }

  Image sheet;
  sheet.resize(maxw,maxh);

  for (unsigned x=0;x<basePic_.width();x++){
    for(unsigned y=0;y<basePic_.height();y++){
      HSLAPixel & pix = sheet.getPixel(x,y);
      pix=basePic_.getPixel(x,y);
    }
  }


  for (unsigned i=0;i<count_;i++){
    for (unsigned x=0;x<stickers_[i].im->width();x++){
      for (unsigned y=0;y<stickers_[i].im->height();y++){
        HSLAPixel & pix = sheet.getPixel(x+stickers_[i].x,y+stickers_[i].y);
        HSLAPixel & copypix=stickers_[i].im->getPixel(x,y);
        if (copypix.a!=0){
          pix=copypix;
        }
      }
    }
  }

  return sheet;
}