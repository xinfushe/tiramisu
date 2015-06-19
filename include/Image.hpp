#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <map>

#include "CNNLayer.hpp"

using std::string;
using std::map;

class Image {
  public:
    string getName() const {return name;}
    string getPath() const {return path;}
    inline map<string,map<int,float> > getActivations() const {return activations;}
    inline map<string,map<int,float> > getRelevantFeatures() const {return relevantFeatures;}
    inline void setName(string n) {name=n;}
    inline void setPath(string p) {path=p;}
    inline void setActivations(const map<string,map<int,float> > &a) {activations=a;}
    void addActivations(const string path, const string layerName);
    void exploreImage() ;
    void computeRelevantFeatures(const map<string,CNNLayer> &CNN);

  protected:
    string name;
    string path;
    map<string,map<int,float> > activations;
    map<string,map<int,float> > relevantFeatures;
}; //  Image

#endif
