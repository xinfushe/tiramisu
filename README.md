# Tiramisu

"Representation learning is a set of methods that allows a machine to be fed with raw data and to automatically discover the representations needed for detection or classification. Deep-learning methods are representation-learning methods..."
[Yann LeCun, Yoshua Bengio & Geoffrey Hinton, "Deep Learning", Nature, 521, p.436–444, 28 May 2015]

The goal of this project is to build an inference system based on deep learning learnt representations. Representations are extracted from CNN (see the fork of caffe project in https://github.com/dariogarcia/caffe). These representation are then loaded by tiramisu, which will explore its structural properties, and exploit them for inference through graph mining methods. 

# Scripts and Code structure

Tiramisu includes a set of scripts for extracting data from caffe. These scripts call the feature extraction code of caffe, and store the output files. Currently there are two scripts for two different network architectures, as the layers being extracted are hardcoded.

The main code of Tiramisu, found in src/, works on the processing of caffe output files, and therefore typically requires a previous call to the scripts.
