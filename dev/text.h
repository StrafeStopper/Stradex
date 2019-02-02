#ifndef TEXT_H
#define TEXT_H


extern cTexture streamedText[6];
extern void textStream(std::string tts);
extern void renderTextStream(SDL_Rect camera);
extern void renderBuildNumber(int b);
extern cTexture buildText;
extern SDL_Rect tsClip[1];
#endif //TEXT_H
