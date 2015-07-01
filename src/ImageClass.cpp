#include <iterator>
#include <algorithm>

#include "../include/ImageClass.hpp"
#include "../include/Util.hpp"

using std::find;

//Computes the mean activations based on a set of images which belong to the imageClass
//WARNING: Removes any previously stored meanActivations and image names
void ImageClass::computeMeanActivations(vector<pair<string,Image *> > &images, const CNNScheme &scheme){
  meanActivations.clear();
  imageNames.clear();
  float numImages = (float)images.size();
  for(vector<pair<string,Image *> >::iterator it = images.begin(); it!=images.end();it++) imageNames.push_back(it->first);
  //For each layer
  for(int i = 0 ; i < scheme.getNumLayers(); i++){
    int currentSize = scheme.layerSize[i];
    vector<pair<int,float> > currentMeans;
    //For each feature in the layer
    for(int j=0;j<currentSize;j++){
      float totalActivations=0.0;
      //Add the activation from each image
      for(vector<pair<string,Image *> >::iterator it = images.begin(); it!=images.end();it++){
         vector<pair<int,float> > &imageFeaturesForLayer = (it->second)->activations[i];
        for(vector<pair<int,float> >::iterator it2 = imageFeaturesForLayer.begin(); it2!=imageFeaturesForLayer.end(); it2++){
          if(it2->first==j) totalActivations+=it2->second;
          else if(it2->first>j)break;
        }
      }
      currentMeans.push_back(pair<int,float>(j,totalActivations/numImages));
    }
    meanActivations.push_back(currentMeans);
  }
}


//Computes the mean activations based on a set of images which belong to the imageClass
//WARNING: Removes any previously stored meanActivations and image names
void ImageClass::computeMeanActivationsThreshold(vector<pair<string,Image *> > &images, const CNNScheme &scheme, const CNNFeatures &cnn){
  meanActivations.clear();
  imageNames.clear();
  float numImages = (float)images.size();
  for(vector<pair<string,Image *> >::iterator it = images.begin(); it!=images.end();it++) imageNames.push_back(it->first);
  //For each layer
  for(int i = 0 ; i < scheme.getNumLayers(); i++){
    int currentSize = scheme.layerSize[i];
    vector<pair<int,float> > currentMeans;
    //For each feature in the layer
    for(int j=0;j<currentSize;j++){
      float totalActivations=0.0;
      //Add the activation from each image
      for(vector<pair<string,Image *> >::iterator it = images.begin(); it!=images.end();it++){
         vector<pair<int,float> > &imageFeaturesForLayer = (it->second)->activations[i];
        for(vector<pair<int,float> >::iterator it2 = imageFeaturesForLayer.begin(); it2!=imageFeaturesForLayer.end(); it2++){
          if(it2->first==j) totalActivations+=it2->second;
          else if(it2->first>j)break;
        }
      }
      //Add value only if passes the threshold
      const Feature *f = &cnn.features[i][j];
      if(totalActivations/numImages > f->mean+2*f->stdDev){
        currentMeans.push_back(pair<int,float>(j,totalActivations/numImages));
      }
    }
    meanActivations.push_back(currentMeans);
  }
}


////Computes the mean activation from a set of images which are suposed to belong to this imageClass
////WARNING: Removes any previously stored meanActivations and image names
//void ImageClass::computeMeanActivations(const map<string,Image> &images, const map<string,CNNLayer> &CNN){
//  meanActivations.clear();
//  imageNames.clear();
//  int numImages = images.size();
//  for(map<string,Image>::const_iterator it3 = images.begin(); it3!=images.end();it3++) imageNames.push_back(it3->first);
//  //For each layer
//  for(map<string,CNNLayer>::const_iterator it = CNN.begin(); it!=CNN.end(); it++){
//    string currentLayer = it->first;
//    const map<int,CNNFeature> &layerFeats = it->second.getFeaturesConst();
//    //If its the first time we read a layer, add it
//    if(meanActivations.find(currentLayer)==meanActivations.end()){
//      map<int,float> emptyMap;
//      meanActivations.insert(pair<string,map<int,float> >(currentLayer,emptyMap));
//    }
//    //For each feature in the layer
//    for(map<int,CNNFeature>::const_iterator it2=layerFeats.begin(); it2!=layerFeats.end();it2++){
//      int currentFeat = it2->first;
//      float totalActivations=0.0;
//      //Add the activation from each image
//      for(map<string,Image>::const_iterator it3 = images.begin(); it3!=images.end();it3++){
//        int idx = it3->second.getLayersIDX().find(currentLayer)->second;
//        const vector<pair<int,float> > &activ = it3->second.getActivationsConst()[idx];
//        float val = 0.0;
//        for(vector<pair<int,float> >::const_iterator it_f = activ.begin();it_f!=activ.end();it_f++){
//          if(it_f->first<currentFeat)it_f++;
//          else if(it_f->first>currentFeat)break;
//          else val = it_f->second;
//        }
//        totalActivations+=val;
//      }
//      meanActivations[currentLayer][currentFeat] = totalActivations/(float)numImages;
//      //printf("processed feature %u\n",currentFeat);
//    }
//  }
//}
//
//
////Computes the mean activation of some images which belong to this imageClass.
////The list of images which belong are defined in the vector
////WARNING: Removes any previously stored meanActivations and image names
//void ImageClass::computeMeanActivations(vector<string> &imagesByClass, const map<string,Image> &images, const map<string,CNNLayer> &CNN){
//  meanActivations.clear();
//  imageNames.clear();
//  int numImages = imagesByClass.size();
//  //Store the names of the images belonging to the class (i.e., found in the vector)
//  for(map<string,Image>::const_iterator it3 = images.begin(); it3!=images.end();it3++){
//    if(find(imagesByClass.begin(),imagesByClass.end(),it3->first)==imagesByClass.end()) continue;
//    imageNames.push_back(it3->first);
//  }
//  //For each layer
//  for(map<string,CNNLayer>::const_iterator it = CNN.begin(); it!=CNN.end(); it++){
//    string currentLayer = it->first;
//    const map<int,CNNFeature> &layerFeats = it->second.getFeaturesConst();
//    //If its the first time we read a layer, add it
//    if(meanActivations.find(currentLayer)==meanActivations.end()){
//      map<int,float> emptyMap;
//      meanActivations.insert(pair<string,map<int,float> >(currentLayer,emptyMap));
//    }
//    //For each feature in the layer
//    for(map<int,CNNFeature>::const_iterator it2=layerFeats.begin(); it2!=layerFeats.end();it2++){
//      int currentFeat = it2->first;
//      float totalActivations=0.0;
//      //Add the activation from each image
//      for(map<string,Image>::const_iterator it3 = images.begin(); it3!=images.end();it3++){
//        int idx = it3->second.getLayersIDX().find(currentLayer)->second;
//        const vector<pair<int,float> > &activ = it3->second.getActivationsConst()[idx];
//        float val = 0.0;
//        for(vector<pair<int,float> >::const_iterator it_f = activ.begin();it_f!=activ.end();it_f++){
//          if(it_f->first<currentFeat)it_f++;
//          else if(it_f->first>currentFeat)break;
//          else {
//            val = it_f->second;
//            break;
//          }
//        }
//        totalActivations+=val;
//        printf("adding activation of image %s which is %f and totals %f\n",it3->first,val,totalActivations):
//      }
//      if(totalActivations!=0.0) meanActivations[currentLayer][currentFeat] = totalActivations/(float)numImages;
//    }
//  }
//}

pair<ImageClass,float> ImageClass::findClosestClassByEucliDist(const vector<ImageClass> &iClassCandidates, const CNNScheme &scheme){
  const ImageClass &target = *this;
  if(iClassCandidates.size()<1){
    printf("ImageClass::findClosestClassByEucliDist::ERROR empty vector of candidates to compare. Returning self.\n");
    return pair<ImageClass,float>(target,0.0);
  }
  ImageClass closest;
  //Initialize closest distance to distance to first, unless its self, skip
  if(iClassCandidates.front().getName().compare(target.getName())==0){
    if(next(iClassCandidates.begin())==iClassCandidates.end()){
      printf("ImageClass::findClosestClassByEucliDist::ERROR one one class to compare and it is self. Returning self.\n");
      return pair<ImageClass,float>(target,0.0);
    }
    closest = *next(iClassCandidates.begin());
  }
  else closest = iClassCandidates.front();
  float closestDist = Util::euclideanDistanceImageClass(target, closest, scheme);
  //printf("%f %s --- %s\n",closestDist,target.getName().c_str(),closest.getName().c_str());
  for (vector<ImageClass>::const_iterator i = std::next(iClassCandidates.begin()); i != iClassCandidates.end(); i++){
    //Skip self comparation
    if((*i).getName().compare(target.getName())==0) continue;
    float currentDist = Util::euclideanDistanceImageClass(target, *i, scheme);
    if(currentDist<closestDist){
      closestDist=currentDist;
      closest = *i;
    }
    //printf("%f %s --- %s\n",currentDist,target.getName().c_str(),(*i).getName().c_str());
  }
  return pair<ImageClass,float>(closest,closestDist);
}

//pair<ImageClass,float> ImageClass::findClosestClassByEucliDist(const map<string,ImageClass> &iClassCandidates, const map<string,CNNLayer> &layers){
//  const ImageClass &target = *this;
//  if(iClassCandidates.size()<1){
//    printf("ImageClass::findClosestClassByEucliDist::ERROR empty vector of candidates to compare. Returning self.\n");
//    return pair<ImageClass,float>(target,0.0);
//  }
//  ImageClass closest;
//  //If the first is self, skip
//  if(iClassCandidates.begin()->second.getName().compare(target.getName())==0){
//    if(next(iClassCandidates.begin())==iClassCandidates.end()){
//      printf("ImageClass::findClosestClassByEucliDist::ERROR only one class to compare and it is self. Returning self.\n");
//      return pair<ImageClass,float>(target,0.0);
//    }
//    closest = next(iClassCandidates.begin())->second;
//  }
//  else closest = iClassCandidates.begin()->second;
//  float closestDist = Util::euclideanDistanceImageClass(layers, target, closest);
//  for (map<string,ImageClass>::const_iterator i = std::next(iClassCandidates.begin()); i != iClassCandidates.end(); i++){
//    //Skip self comparation
//    if(i->second.getName().compare(target.getName())==0) continue;
//    float currentDist = Util::euclideanDistanceImageClass(layers, target, i->second);
//    if(currentDist<closestDist){
//      printf("new closest for %s is %s at %f\n",target.getName().c_str(),i->first.c_str(),currentDist);
//      closestDist=currentDist;
//      closest = i->second;
//    }
//    printf("closest for %s is still %s with %f. %s was further at %f\n",target.getName().c_str(),closest.getName().c_str(),closestDist,i->first.c_str(),currentDist);
//  }
//  return pair<ImageClass,float>(closest,closestDist);
//}
//
//void ImageClass::printAccumulatedMeanAct(){
//  float total = 0;
//  for(map<string,map<int,float> >::iterator it = meanActivations.begin(); it!=meanActivations.end();it++){
//    map<int,float> &layer = it->second;
//    for(map<int,float>::iterator it2 = layer.begin(); it2!=layer.end(); it2++){
//      total+=it2->second;
//    }
//  }
//  printf("ImageClass::printAccumulatedMeanAct::ImageClass %s has an accumulated %f activations\n",name.c_str(),total);
//}
