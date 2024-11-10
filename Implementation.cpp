//#include "Headers.h"
//
//using namespace std;
//
//LabelGenerator::LabelGenerator() {
//    label = "";
//    counter = 0;
//}
//
//LabelGenerator::LabelGenerator(const string &text, int c) {
//    label = text;
//    counter = c;
//}
//
//string LabelGenerator::nextLabel() {
//    return label + to_string(counter++);
//}
//
////FileLabelGenerator::FileLabelGenerator(string text, int c, string fileName) {
////    label = text;
////    counter = c;
////    file.open(fileName);
////}
////
////string FileLabelGenerator::nextLabel() {
////    string sentence;
////    while (getline(file, sentence, '\n'));
////    return label + to_string(counter++) + sentence;
////}
